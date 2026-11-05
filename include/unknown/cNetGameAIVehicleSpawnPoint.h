#include "rws/attributes.h"
// unknown::cNetGameAIVehicleSpawnPoint: CD2 stand-in. Its inheritance registrar
// names cNetGameAISpawnPoint; MakeNew calls that base constructor and initializes
// the three words at +0xA0..+0xA8. Their descriptive names remain placeholders.
// StaticCreateClass (0x8284D490) builds cClass(0x489D, "cNetGameAIVehicleSpawnPoint", 0xB0); 0xB0 is the size its registrar gives.
#ifndef UNKNOWN_CNETGAMEAIVEHICLESPAWNPOINT_H
#define UNKNOWN_CNETGAMEAIVEHICLESPAWNPOINT_H

#include "fun_runtime/class.h"
#include "unknown/cNetGameAISpawnPoint.h"

namespace unknown
{
    class cNetGameAIVehicleSpawnPoint : public cNetGameAISpawnPoint
    {
    public:
        // CD2 0x8284D420 inlines the derived constructor into the factory.
        cNetGameAIVehicleSpawnPoint() : m_wordA0(0), m_wordA4(0), m_wordA8(0) {}
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2 0x8284D480: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcNetGameAIVehicleSpawnPointClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        unsigned int m_wordA0;
        unsigned int m_wordA4;
        unsigned int m_wordA8;
        CD2_LAYOUT_CHECKS(cNetGameAIVehicleSpawnPoint,
            CD2_SIZE(cNetGameAIVehicleSpawnPoint, 0xB0)
            CD2_OFFSET(cNetGameAIVehicleSpawnPoint, m_wordA0, 0xA0)
            CD2_OFFSET(cNetGameAIVehicleSpawnPoint, m_wordA4, 0xA4)
            CD2_OFFSET(cNetGameAIVehicleSpawnPoint, m_wordA8, 0xA8))
    };
}

#endif // UNKNOWN_CNETGAMEAIVEHICLESPAWNPOINT_H
