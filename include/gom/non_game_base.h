// Hierarchy correction (2026-10-28): cScriptHost groups cSafeDeletable (+0)
// and cRegisteredClass (+0x14), with its own flag at +0x18. In cNonGameBase this
// complete base starts at +0x1C; its interfaces retain offsets +0x1C and +0x30.
// The independent-base interpretation in the historical notes below is superseded.
// cNonGameBase: base of every game object in Crackdown 2 (directly: VFX::cRopes, VEHICLE_CONTROL::cVehicleController,
// the AI behaviours; through cGameBase: the equipment and projectile classes). Its constructor (0x82653588) has 48
// callers in CD2.
// Bases and their order from the Burn PDB, whose offsets are closest to CD2's (RuffKing puts an ActionIO interface
// first). CD2's constructor stores the vptrs at 0, 0x18, 0x1C, 0x30 and 0x38, and each secondary vtable has its base's
// slot count:
//   0x00 RWS::CAttributeHandler        primary; 68 slots for cNonGameBase (11 CAttributeHandler, then 57 own)
//   0x18 RWS::CEventHandler            6 slots; overrides RetUniqueID (returns m_nUniqueID) and HandleEvents (empty)
//   0x1C Fun_Runtime::cSafeDeletable   6 slots; overrides slots 1 and 4 (RetName: "Unnamed Non-Game Object")
//   0x30 Fun_Runtime::cRegisteredClass RetClass, IsA
//   0x38 Network::cNetRoleObject       6 slots; overrides only the destructor
// Size 0x7C (VFX::cRopes' next base and cVehicleController's first field are at 0x7C).
// Own virtuals: slot 11 is RetClassName in every class seen; slot 18 is Init(const GOM::cSpawner *), which returns a
// RetVal (the helicopter controller's override, matching RuffKing's cHelicopterController::Init). The rest are unnamed.
// Fields: m_pPrototype at 0x44 (AI behaviours read it) and m_nUniqueID at 0x64 (RetUniqueID returns it).
#ifndef GOM_NON_GAME_BASE_H
#define GOM_NON_GAME_BASE_H

#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "fun_runtime/class.h"
#include "fun_runtime/retval.h"
#include "fun_runtime/safedeletable.h"
#include "fun_runtime/scripthost.h"
#include "network/netrole.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"

namespace GOM { class cSpawner; }

class cNonGameBase : public RWS::CAttributeHandler, public RWS::CEventHandler, public Fun_Runtime::cScriptHost,
    public Network::cNetRoleObject
{
private:
    unsigned int m_unk40;
protected:
    GOM::cObjectPrototype *m_pPrototype;    // 0x44
private:
    unsigned char m_pad48[0x4C - 0x48];
    // RuffKing m_pOwner. CD2's constructor 0x82653588 clears +0x4C;
    // cGameBase::RetOwnerGameObject (0x82651AB8) reads it and tests its runtime class.
    cNonGameBase *m_pOwner;
protected:
    char *m_p50;
private:
    unsigned char m_pad54[0x64 - 0x54];
protected:
    int m_nUniqueID;                        // 0x64
private:
    unsigned char m_pad68[0x79 - 0x68];
protected:
    // RuffKing's name (its last byte, 0xAA there); cLandVehicle's CanTurnOnPoliceLights (0x826C2B30) and
    // CanTurnOnExhaustFumes (0x826C2BB0) test bit 1 of the byte at 0x79 where RuffKing's test m_nNGBFlags & 2.
    unsigned char m_nNGBFlags;              // 0x79
private:
    unsigned char m_pad7A[0x7C - 0x7A];

public:
        cNonGameBase *RetOwner() const { return m_pOwner; }
        // CD2 0x82652EA0, registered as the script method "RetProtoTypeName"; RuffKing's body.
        const char *RetProtoTypeName() const;
        // CD2 0x82652EC8, registered as the script method "RetCentre" (the linker folded the characters' identical
        // slot-389 override into it).
        Fun_Runtime::Vec3 RetCentre() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // Name and base from RuffKing (112 bytes there: no fields of its own). Squad::MakeNew (0x824D81A0) inlines the
        // constructor of a prototype derived from it straight over GOM::cObjectPrototype's, so this one is inline too.
        class cNonGameBasePrototype : public GOM::cObjectPrototype
        {
        public:
            __forceinline cNonGameBasePrototype(const RWS::CAttributePacket &packet) : GOM::cObjectPrototype(packet) {}
            // RuffKing declares this destructor; Burn inlines it. CD2 0x82684630
            // restores this prototype's tables before the shared resource cleanup.
            virtual ~cNonGameBasePrototype() {}
        };

    static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcNonGameBaseClass; // CD2 0x82652FE0
    cNonGameBase();
    virtual ~cNonGameBase();
    virtual const Fun_Runtime::cClass &RetClass() const;
    virtual bool IsA(const Fun_Runtime::cClass &) const;
    virtual void HandleAttributes(const RWS::CAttributePacket &);
    virtual Fun_Runtime::RetVal Term();
    virtual int RetUniqueID();
    virtual void HandleEvents(RWS::CMsg &);
    virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
    virtual const char *RetName() const;

    // primary slots 11..67
    virtual const char *RetClassName() const;
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);
    // Keep this inherited overload beside Init(cSpawner*): declaring it before
    // RetClassName moves the compiler's new Init slot ahead of slot 11.
    // CD2's non-game table holds 0x82653860, rather than CAttributeHandler's
    // 0x823D9718.
    virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void UpdateRenderMatrix();      // slot 26: a body copies its matrix into the render matrix (Prop/cProp.h)
    virtual void LeavePhysicalState();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    // Slot 31: RuffKing's EnterRenderableState(eResourcesType), a virtual of its own beside CAttributeHandler's
    // EnterRenderableState() (slot 8). CD2: cTrafficLight's override (0x82747898) is in slot 31 of its table, where
    // cTransVehicleDamageProp's holds the function that override tail-calls (0x822DC0B0).
    virtual bool EnterRenderableState(eResourcesType eResources);
    virtual void LeaveRenderableState();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    // Slot 37 returns a result code: cNonGameBase's body (0x82653B00) returns Ret_OK, and cWeaponisedHelicopter's
    // (0x826E1D80) returns cHelicopter's. Name not recovered.
    virtual Fun_Runtime::RetVal Slot37();
    // Slot 38: RuffKing's cBody::Reinitialise has the body of CD2's cBody slot 38 (0x82683780).
    virtual Fun_Runtime::RetVal Reinitialise(const GOM::cSpawner *);
    // Slot 39: RuffKing's cBody::TermForReuse has the body of CD2's cBody slot 39 (0x82683738).
    virtual Fun_Runtime::RetVal TermForReuse();
    virtual void Slot40();
    virtual void Slot41();
    virtual void Slot42();
    virtual void Slot43();
    virtual void Slot44();
    virtual void Slot45();
    // Reference name/signature; CD2 primary slot 46 returns a position value.
    // Its default body (0x823CBEA8) forwards to cScriptHost's separate slot 3.
    virtual Fun_Runtime::Vec3 RetPosition() const;
    virtual void Slot47();
    virtual void Slot48();
    // Slot 49 (the SlotN labels from 33 to 48 are the CD2 slot numbers).
    // The character-interface override at 0x823E7778 reads its reference-named alive flag.
    virtual bool IsAlive() const;
    virtual void Slot51();
    virtual void Slot52();
    virtual void Slot53();
    virtual void Slot54();
    virtual void Slot55();
    virtual void Slot56();
    virtual void Slot57();
    virtual void Slot58();
    virtual void Slot59();
    virtual void Slot60();
    virtual void Slot61();
    virtual void Slot62();
    virtual void Slot63();
    virtual void Slot64();
    virtual void Slot65();
    virtual void Slot66();
    virtual void Slot67();
    virtual void Slot68();

    // CD2: cNonGameBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
    // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
public:
    virtual bool EnterPhysicalState(); // 7: 0x82653B30
public:
    CD2_LAYOUT_CHECKS(cNonGameBase,
        CD2_SIZE(cNonGameBase, 0x7C)
        CD2_OFFSET(cNonGameBase, m_pPrototype, 0x44)
        CD2_OFFSET(cNonGameBase, m_pOwner, 0x4C)
        CD2_OFFSET(cNonGameBase, m_p50, 0x50)
        CD2_OFFSET(cNonGameBase, m_nUniqueID, 0x64)
        CD2_OFFSET(cNonGameBase, m_nNGBFlags, 0x79))
};

#endif // GOM_NON_GAME_BASE_H
