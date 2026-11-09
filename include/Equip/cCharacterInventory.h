// STAND-IN: RuffKing cCharacterInventory has no bases, a virtual destructor and a 0x390-byte layout.
// CD2 cCharacterInterface::RetRealCurrentPrimaryEquipment (0x8254E9A0) confirms primary safe pointer +0x350
// in the inventory at character +0x1770. The list/pool storage remains opaque; those containers require 16-byte alignment.
#ifndef EQUIP_CCHARACTERINVENTORY_H
#define EQUIP_CCHARACTERINVENTORY_H

#include "Equip/cEquipment.h"
#include "fun_runtime/safedeletablepointer.h"
#include "cd2/layout.h"

namespace Equip
{
    __declspec(align(16)) class cCharacterInventory
    {
    public:
        cCharacterInventory();
        virtual ~cCharacterInventory();
        cEquipment *RetItemWithEquipmentID(unsigned int); // CD2 0x82614A58
        cEquipment *RetPrimary() { return m_pPrimary; }
    private:
        unsigned char m_unmodelled4[0x350 - 4];
        Fun_Runtime::cSafeDeletablePointer<cEquipment> m_pPrimary;
        unsigned char m_unmodelled360[0x390 - 0x360];
        CD2_LAYOUT_CHECKS(cCharacterInventory,
            CD2_SIZE(cCharacterInventory, 0x390)
            CD2_OFFSET(cCharacterInventory, m_pPrimary, 0x350))
    };
}

#endif
