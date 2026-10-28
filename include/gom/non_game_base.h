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
    unsigned char m_pad48[0x64 - 0x48];
protected:
    int m_nUniqueID;                        // 0x64
private:
    unsigned char m_pad68[0x7C - 0x68];

public:
    cNonGameBase();
    virtual ~cNonGameBase();
    virtual const Fun_Runtime::cClass &RetClass() const;
    virtual bool IsA(const Fun_Runtime::cClass &) const;
    virtual void HandleAttributes(const RWS::CAttributePacket &);
    virtual Fun_Runtime::RetVal Term();
    virtual int RetUniqueID();
    virtual void HandleEvents(RWS::CMsg &);
    virtual void Slot1();
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
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void UpdateRenderMatrix();      // slot 26: a body copies its matrix into the render matrix (Prop/cProp.h)
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual bool EnterRenderableState();
    virtual void LeaveRenderableState();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual void Slot37();
    virtual void Slot38();
    virtual void Slot39();
    virtual void Slot40();
    virtual void Slot41();
    virtual void Slot42();
    virtual void Slot43();
    virtual void Slot44();
    virtual void Slot45();
    virtual void Slot46();
    virtual void Slot47();
    virtual void Slot48();
    virtual void Slot49();
    virtual void Slot50();
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

    CD2_LAYOUT_CHECKS(cNonGameBase,
        CD2_SIZE(cNonGameBase, 0x7C)
        CD2_OFFSET(cNonGameBase, m_pPrototype, 0x44)
        CD2_OFFSET(cNonGameBase, m_nUniqueID, 0x64))
};

#endif // GOM_NON_GAME_BASE_H
