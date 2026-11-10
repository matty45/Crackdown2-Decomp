// STAND-IN: Burn/RuffKing name this enum in IsPowerUpActive. CD2 uses the value as a bit index;
// its enumerator names/values have not been recovered, except as noted.
#ifndef CHARACTER_EPOWERUP_H
#define CHARACTER_EPOWERUP_H
namespace CHARACTER
{
    enum ePowerUp
    {
        // Name ours: cCharacter::IsUsingInfiniteAmmo (0x82543058) tests the infinite-ammo flag or this power-up.
        ePowerUp_InfiniteAmmo = 10
    };
}
#endif
