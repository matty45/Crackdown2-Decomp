// STAND-IN: RuffKing 24-slot order/size; CD2 table 0x8213FDF0, destructor slot 7.
#ifndef CD2_NETWORK_CREPLICATEDCLASS_H
#define CD2_NETWORK_CREPLICATEDCLASS_H
#include "fun_runtime/class.h"
#include "Network/SNetworkHeader.h"
namespace Fun_Runtime { class Vec3; }
enum etGameMessageType { };
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
    unsigned char m_unknown4[0x38 - 4];
public:
    // RuffKing NetReplicationCD2.h names the object ID; CD2 SetReplicatedObjectID at 0x82C2BEA0 stores +0x38.
    unsigned int m_nObjectID;
    // CD2 0x8282C160 and 0x8282C0D0 read one replicated field by ID (names ours); cFlocket::ReplicateFields calls
    // them and compares the byte at 0x88 with 199.
    void ReadVec3(Fun_Runtime::Vec3 *out, int id);
    void ReadFloat(float *out, int id);
private:
    unsigned char m_unknown3C[0x88 - 0x3C];
public:
    unsigned char m_nUnk88;
private:
    unsigned char m_unknown89[0x230 - 0x89];
    CD2_LAYOUT_CHECKS(cReplicatedClass, CD2_SIZE(cReplicatedClass, 0x230)
        CD2_OFFSET(cReplicatedClass, m_nObjectID, 0x38))
};
#endif
