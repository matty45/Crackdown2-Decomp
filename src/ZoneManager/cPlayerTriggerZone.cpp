// ZoneManager::cPlayerTriggerZone: RuffKing's same-named source object owns
// the box-containment wrapper. CD2 primary slot 12 targets 0x8280E1D8.
#include "ZoneManager/cPlayerTriggerZone.h"
#include "cd2/memory.h"
#include "Vehicle/cVehicle.h"

namespace ZoneManager
{
    bool cPlayerTriggerBase::IsVehicleWithin(const Vehicle::cVehicle *vehicle) const
    {
        return IsWithin(vehicle->RetPosition());
    }

    bool cPlayerTriggerBase::IsInTriggerZone(const CHARACTER::cCharacter *character) const
    {
        typedef Fun_Runtime::cVector<Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> > PlayerVector;
        for (PlayerVector::const_iterator it = m_vContainedPlayers.begin(); it != m_vContainedPlayers.end(); ++it)
        {
            const CHARACTER::cCharacter *contained = *it;
            if (contained && contained == character)
                return true;
        }
        return false;
    }

    cPlayerTriggerBase::~cPlayerTriggerBase()
    {
    }

    bool cPlayerTriggerBase::DoCollision(CHARACTER::cCharacter *character)
    {
        bool collided = false;
        if (m_bDoCollision && character)
        {
            if (IsWithin(character))
            {
                if (!IsInTriggerZone(character))
                    AddPlayer(character);
                collided = true;
            }
            else
                RemovePlayer(character, true);
        }
        return collided;
    }

    void cPlayerTriggerZone::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cPlayerTriggerBase::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, RWS::CSystemCommands::pCSystemCommandsClassID);
             !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case RWS::CSystemCommands::CMD_LoadMatrix:
                m_OBBox.m_mtxTrans = m_Transform;
                m_OBBox.m_vecScale = m_vScale;
                break;
            }
        }
    }

    bool cPlayerTriggerZone::IsWithin(const Fun_Runtime::Vec3 &point) const
    {
        return m_OBBox.IsPenetratingPoint(point);
    }
}
