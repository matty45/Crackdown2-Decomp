// Damage enum names/values from the reference builds.
#ifndef DAMAGE_DAMAGE_TYPES_H
#define DAMAGE_DAMAGE_TYPES_H
namespace Damage
{
    enum eDamageType
    {
        eDamageType_Default = 0, eDamageType_Water, eDamageType_Fall,
        eDamageType_Collision, eDamageType_AgencyVehicleCollision,
        eDamageType_TransformationBlast, eDamageType_Fire, eDamageType_Explosion,
        eDamageType_Fighting, eDamageType_Firearms, eDamageType_UVLight,
        eDamageType_Acid, eMaxDamageTypes
    };
    enum eDamageActivator
    {
        eDamageActivator_None = 0, eDamageActivator_Firearms,
        eDamageActivator_Strength, eDamageActivator_Driving,
        eDamageActivator_Explosives, eMaxDamageActivators
    };
}
#endif
