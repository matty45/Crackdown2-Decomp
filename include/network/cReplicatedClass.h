// STAND-IN: RuffKing 24-slot order/size; CD2 table 0x8213FDF0, destructor slot 7.
#ifndef CD2_NETWORK_CREPLICATEDCLASS_H
#define CD2_NETWORK_CREPLICATEDCLASS_H
#include "fun_runtime/class.h"
#include "Network/SNetworkHeader.h"
namespace Fun_Runtime { class Vec3; }
enum etGameMessageType { };
// RuffKing's per-field replication state (NetReplicationCD2.h, 0x14 bytes, as CD2's: cProp::SetPingedFieldStatesForNode
// (0x827303C0) reaches RuffKing's field 3 at +0x3C, and cVehicle's (0x826CE5A0) field 12 at +0xF0).
struct sReplicatedField
{
    enum etReplicatedFieldState
    {
        Normal = (1 << 0),
        WriteAlwaysOnce = (1 << 1),
        WriteAlways = (1 << 2),
        WriteSkipOnce = (1 << 3),
        WriteSkip = (1 << 4),
        WriteReliable = (1 << 5),
        WriteFastOnChange = (1 << 6),
    };
    unsigned char m_iFieldState[16];                    // 0x0
    unsigned short m_iRecentOffset;                     // 0x10
    unsigned char m_iInitialFieldState;                 // 0x12
    // RuffKing's inline (its out-of-line copy 0x829D1210); CD2 inlines it as one byte store.
    void SetState(etReplicatedFieldState state, unsigned char nNodeID) { m_iFieldState[nNodeID] = (unsigned char)state; }
    CD2_LAYOUT_CHECKS(sReplicatedField, CD2_SIZE(sReplicatedField, 0x14))
};
// CD2 cMissionBase places this base at +0x10 after a four-byte registered-class base.
// The reference starts its first field at +0x10 and its bit stream at +0x20.
__declspec(align(16)) class cReplicatedClass
{
public:
    virtual const Fun_Runtime::cClass &RetClass() const;
    virtual bool IsA(const Fun_Runtime::cClass &) const;
    virtual void CalculateRelevancy(int);
    virtual void CalculateLOD(int);
    virtual bool CanSendTermPacketOnNotRelevant() const;
    virtual bool IsInLODRange(unsigned char);
    virtual bool IsSequential() const = 0;
    virtual ~cReplicatedClass();
    virtual void ReplicateInitialFields();
    virtual void ReplicateFields();
    virtual void ReplicateHeaderData();
    virtual void SkipDefaultReplicatedFields();
    virtual void ReplicateFieldsRead();
    virtual void ReplicateFieldsWrite();
    virtual bool IsOwnedLocally() = 0;
    virtual void SendNetInitRequestMsg();
    virtual unsigned int GetNumObjectIDBits() const;
    virtual unsigned int GetOwnerShipTimeStamp();
    virtual etGameMessageType GetTermMessageType() const;
    virtual void SetReplicatedObjectID(unsigned int);
    virtual void SetPingedFieldStatesForNode(unsigned char) = 0;
    virtual void SetOwnerShipTimeStamp(unsigned int);
    virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const = 0;
    virtual unsigned int GetMaxReplicatedFields() const = 0;
private:
    unsigned char m_unknown4[0x30 - 4];
protected:
    // RuffKing's names and offsets; SetFieldStateForNode reads both.
    sReplicatedField *m_pReplicatedFields;              // 0x30
private:
    unsigned char m_unknown34[0x38 - 0x34];
public:
    // RuffKing NetReplicationCD2.h names the object ID; CD2 SetReplicatedObjectID at 0x82C2BEA0 stores +0x38.
    unsigned int m_nObjectID;
    // RuffKing's name and offset; cTacticalObjective::TermReplication (0x82475E50) stores 0xFF here.
    unsigned int m_nNodeID;                             // 0x3C
    // CD2 0x8282C160 and 0x8282C0D0 read one replicated field by ID (names ours); cFlocket::ReplicateFields calls
    // them and compares the byte at 0x88 with 199.
    void ReadVec3(Fun_Runtime::Vec3 *out, int id);
    void ReadFloat(float *out, int id);
    // RuffKing's names; CD2 0x82829E20 and 0x82814AB0, called by cTacticalObjective's Init/TermReplication.
    void InitReplicatedClass(void *pData, bool bAddToHash);
    void TermReplicatedClass();
private:
    unsigned char m_unknown40[0x87 - 0x40];
protected:
    unsigned char m_iHasBeenReplicated;                 // 0x87
    // RuffKing's (out of line there, 0x829D22E8, where the else branch only asserts); CD2 inlines it into cVehicle's
    // SetPingedFieldStatesForNode.
    void SetFieldStateForNode(unsigned char nNodeID, sReplicatedField::etReplicatedFieldState state, int field)
    {
        if (m_iHasBeenReplicated & 6)
            m_pReplicatedFields[field].SetState(state, nNodeID);
    }
public:
    unsigned char m_nUnk88;
private:
    unsigned char m_unknown89[0x224 - 0x89];
public:
    // RuffKing's name and offset; cTacticalObjective::TermReplication tests it before TermReplicatedClass.
    bool m_bRegisteredWithReplicationManager;           // 0x224
private:
    unsigned char m_unknown225[0x230 - 0x225];
    CD2_LAYOUT_CHECKS(cReplicatedClass, CD2_SIZE(cReplicatedClass, 0x230)
        CD2_OFFSET(cReplicatedClass, m_pReplicatedFields, 0x30)
        CD2_OFFSET(cReplicatedClass, m_iHasBeenReplicated, 0x87)
        CD2_OFFSET(cReplicatedClass, m_nObjectID, 0x38)
        CD2_OFFSET(cReplicatedClass, m_nNodeID, 0x3C)
        CD2_OFFSET(cReplicatedClass, m_bRegisteredWithReplicationManager, 0x224))
};
#endif
