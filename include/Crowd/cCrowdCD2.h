// cCrowdCD2 (Crackdown 2): STAND-IN for the crowd system's global instance pointer only. RuffKing's
// Crowd/Crowd/crowdpathcache.cpp defines `cCrowdCD2 *gpCCD2`; CD2's cBeaconMission::Load (0x82464FB0) tests it at
// 0x83800BC8. The class itself is not modelled.
#ifndef CROWD_CCROWDCD2_H
#define CROWD_CCROWDCD2_H

class cCrowdCD2;
extern cCrowdCD2 *gpCCD2;

#endif // CROWD_CCROWDCD2_H
