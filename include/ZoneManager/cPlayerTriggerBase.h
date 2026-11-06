// ZoneManager::cPlayerTriggerBase (Crackdown 2): STAND-IN. Bases and leading fields from RuffKing's cPlayerTriggerZone.h.
// CD2's destructor (0x8280DCC0) restores the vptrs at 0 and 0x18 (the cLoadSaveObject interface), destroys the
// contained-players vector at 0x20 (after the two empty bases, which this compiler places at 0x1C) and calls
// ~CAttributeHandler. The 16-byte members make the class 16-byte aligned,
// as the derived sizes (0x100, 0x110) require. cPlayerTriggerZone's size, 0xE0, is this class's: it adds no fields.
#ifndef ZONEMANAGER_CPLAYERTRIGGERBASE_H
#define ZONEMANAGER_CPLAYERTRIGGERBASE_H

#include "rws/attributes.h"
#include "rws/systemcommands.h"
#include "rws/dynamicallocationpolicy.h"
#include "SaveGame/cLoadSaveObject.h"
#include "fun_runtime/vector.h"
#include "fun_runtime/safedeletablepointer.h"
#include "fun_runtime/mtx.h"
#include "fun_runtime/vec3.h"
#include "CHARACTER/cCharacter.h"
#include "cd2/layout.h"

namespace Vehicle { class cVehicle; }

namespace ZoneManager
{
    class cPlayerTriggerBase : public RWS::CSystemCommands, public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy,
                               public SaveGame::cLoadSaveObject
    {
    public:
        // CD2 0x8280DB80 (RuffKing's signature; the zones' MakeNew functions call it with false or true).
        cPlayerTriggerBase(bool bAllowDeadCharacters);
        // CD2 0x8280DCC0 (out of line: the derived destructors call it).
        virtual ~cPlayerTriggerBase();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2 cPlayerTriggerZone table 0x82155B98 has 18 entries: these are slots 11..17.
        virtual bool DoCollision(CHARACTER::cCharacter *);
        virtual bool IsWithin(const Fun_Runtime::Vec3 &) const = 0;
        virtual bool IsVehicleWithin(const Vehicle::cVehicle *) const;
        virtual void InitTriggerZone();
        virtual void TermTriggerZone();
        virtual void OnPlayerEnter(CHARACTER::cCharacter *) = 0;
        virtual void OnPlayerLeave(CHARACTER::cCharacter *) = 0;

    protected:
        Fun_Runtime::cVector<Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> > m_vContainedPlayers;

    private:
        // RuffKing: PHYSICS::cOBBox m_OBBox, not modelled yet.
        unsigned char m_unmodelled30[0x80 - 0x30];

    protected:
        Fun_Runtime::Mtx m_Transform;
        Fun_Runtime::Vec3 m_vScale;

    private:
        unsigned char m_unmodelledD0[0xE0 - 0xD0];

        CD2_LAYOUT_CHECKS(cPlayerTriggerBase,
            CD2_SIZE(cPlayerTriggerBase, 0xE0)
            CD2_OFFSET(cPlayerTriggerBase, m_vContainedPlayers, 0x20)
            CD2_OFFSET(cPlayerTriggerBase, m_Transform, 0x80)
            CD2_OFFSET(cPlayerTriggerBase, m_vScale, 0xC0))
    };
}

#endif // ZONEMANAGER_CPLAYERTRIGGERBASE_H
