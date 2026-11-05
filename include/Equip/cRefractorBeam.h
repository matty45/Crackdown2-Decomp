// Equip::cRefractorBeam (Crackdown 2): STAND-IN from RuffKing's cRefractorBeam.h (0x50 bytes, the same size as CD2's
// cRefractor member at +0xA10). CD2's cRefractor constructor (0x826107F8) and deleting destructor (0x826108D8) inline
// this class's constructor and destructor: vptr at 0, null profile at 0x10 (the vfptr slot takes the class's 16-byte
// alignment), two zeroed Vec3s at 0x20 and 0x30, and a null safe pointer at 0x40 whose payload is stored before its
// vptr (the converting constructor).
#ifndef EQUIP_CREFRACTORBEAM_H
#define EQUIP_CREFRACTORBEAM_H

#include "cd2/layout.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/safedeletablepointer.h"
#include "CHARACTER/cCharacter.h"

namespace Equip
{
    struct tRefractorBeamProfile;

    class cRefractorBeam
    {
    public:
        cRefractorBeam() : m_pProfile(0), m_pInstigator(0) {}
        virtual ~cRefractorBeam() {}

    private:
        tRefractorBeamProfile *m_pProfile;
        Fun_Runtime::Vec3 m_vPosition;
        Fun_Runtime::Vec3 m_vDirection;
        Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> m_pInstigator;

        CD2_LAYOUT_CHECKS(cRefractorBeam,
            CD2_SIZE(cRefractorBeam, 0x50)
            CD2_OFFSET(cRefractorBeam, m_pProfile, 0x10)
            CD2_OFFSET(cRefractorBeam, m_vPosition, 0x20)
            CD2_OFFSET(cRefractorBeam, m_vDirection, 0x30)
            CD2_OFFSET(cRefractorBeam, m_pInstigator, 0x40))
    };
}

#endif // EQUIP_CREFRACTORBEAM_H
