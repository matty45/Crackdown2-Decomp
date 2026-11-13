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
#include "PHYSICS/cOBBox.h"

namespace Vehicle { class cVehicle; }

namespace ZoneManager
{
    // RuffKing's enum; CD2 stores the trigger-zone type at +0xD0.
    enum eTriggerZoneType
    {
        eTZT_DetectLocalPlayerOnly = 0,
        eTZT_DetectAllPlayers
    };

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
        bool IsWithin(CHARACTER::cCharacter *) const;
        virtual bool IsWithin(const Fun_Runtime::Vec3 &) const = 0;
        bool IsInTriggerZone(const CHARACTER::cCharacter *) const;
        virtual bool IsVehicleWithin(const Vehicle::cVehicle *) const;
        // CD2 0x8280FB68, primary slot 14; inlined at the end of local-trigger construction.
        virtual void InitTriggerZone() { m_bDoCollision = true; }
        virtual void TermTriggerZone();
        // Reference name; CD2 zone Load callbacks test the collision flag at +0xD5.
        bool IsInitialised() const { return m_bDoCollision; }
        virtual void OnPlayerEnter(CHARACTER::cCharacter *) = 0;
        virtual void OnPlayerLeave(CHARACTER::cCharacter *) = 0;

    protected:
        void AddPlayer(CHARACTER::cCharacter *);
        void RemovePlayer(CHARACTER::cCharacter *, bool removeFromContainer);
        Fun_Runtime::cVector<Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> > m_vContainedPlayers;

    protected:
        // RuffKing: PHYSICS::cOBBox m_OBBox, not modelled yet.
        // Now modelled using the reference's complete box layout; CD2's
        // point-containment wrapper confirms this member's +0x30 position.
        PHYSICS::cOBBox m_OBBox;

    protected:
        Fun_Runtime::Mtx m_Transform;
        Fun_Runtime::Vec3 m_vScale;

    private:
        // Reference member names and offsets; CD2's base constructor initializes
        // these, and InitTriggerZone writes the collision flag at +0xD5.
        eTriggerZoneType m_eType;
        bool m_bAllowDeadCharacters;
        bool m_bDoCollision;

        CD2_LAYOUT_CHECKS(cPlayerTriggerBase,
            CD2_SIZE(cPlayerTriggerBase, 0xE0)
            CD2_OFFSET(cPlayerTriggerBase, m_vContainedPlayers, 0x20)
            CD2_OFFSET(cPlayerTriggerBase, m_OBBox, 0x30)
            CD2_OFFSET(cPlayerTriggerBase, m_Transform, 0x80)
            CD2_OFFSET(cPlayerTriggerBase, m_vScale, 0xC0)
            CD2_OFFSET(cPlayerTriggerBase, m_eType, 0xD0)
            CD2_OFFSET(cPlayerTriggerBase, m_bAllowDeadCharacters, 0xD4)
            CD2_OFFSET(cPlayerTriggerBase, m_bDoCollision, 0xD5))
    };
}

#endif // ZONEMANAGER_CPLAYERTRIGGERBASE_H
