#ifndef unknown_cVehicleTagGameModePrototype_H
#define unknown_cVehicleTagGameModePrototype_H

#include "rws/attributes.h"
#include "GameManagement/cPvPGameModePrototype.h"

namespace unknown
{
    // STAND-IN: factory 0x8286D898 calls cPvPGameModePrototype's
    // constructor (0x8283E2F8); allocation and registrar give size 0x238.
    class cVehicleTagGameModePrototype : public GameManagement::cPvPGameModePrototype
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual int RetStringID() const;
        // CD2 table 0x8215ED88: new slots 43..45. Destruct shares
        // 0x8273FBA8 with other prototypes; getter names are ours.
        virtual void Destruct();
        virtual bool RetFlag22C() const;
        virtual float RetFloat230() const;
    private:
        unsigned char m_unmodelled148[0x22C - 0x148];
        bool m_bParameter22C;
        unsigned char m_unmodelled22D[0x230 - 0x22D];
        float m_fParameter230;
        unsigned char m_unmodelled234[4];
        CD2_LAYOUT_CHECKS(cVehicleTagGameModePrototype,
            CD2_SIZE(cVehicleTagGameModePrototype, 0x238)
            CD2_OFFSET(cVehicleTagGameModePrototype, m_bParameter22C, 0x22C)
            CD2_OFFSET(cVehicleTagGameModePrototype, m_fParameter230, 0x230))
    };
}

#endif
