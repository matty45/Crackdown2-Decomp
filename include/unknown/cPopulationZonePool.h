// Interface-only stand-in; descriptive name is ours. cZoneManager's constructor
// allocates this 0x36A0-byte object, which contains 32 cPopulationZone instances.
// Its table at 0x82155B1C begins with cDebugPageHandler's RetClass/IsA entries,
// followed by the deleting destructor at 0x8280CE08. Storage is not recovered;
// this interface must not be used as an allocation layout.
#ifndef UNKNOWN_CPOPULATIONZONEPOOL_H
#define UNKNOWN_CPOPULATIONZONEPOOL_H
#include "GDb/cDebugPageHandler.h"
namespace unknown
{
    class cPopulationZonePool : public GDb::cDebugPageHandler
    {
    public:
        virtual ~cPopulationZonePool();
    };
}
#endif
