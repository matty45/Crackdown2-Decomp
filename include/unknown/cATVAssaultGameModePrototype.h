// STAND-IN: CD2 constructor 0x8287B358 calls cPvPGameModePrototype at 0x8283E2F8.
#ifndef unknown_cATVAssaultGameModePrototype_H
#define unknown_cATVAssaultGameModePrototype_H

#include "cd2/layout.h"
#include "GameManagement/cPvPGameModePrototype.h"

namespace unknown
{
    class cATVAssaultGameModePrototype : public GameManagement::cPvPGameModePrototype
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual int RetStringID() const;
    public:
        // Out of line: CD2 0x8287B358 (MakeNew calls it).
        cATVAssaultGameModePrototype();
        // CD2 0x8287B4C0 destroys the narrow-string member at +0x22C, then
        // calls cGameModePrototype's destructor. Team variants call it out of line.
        virtual ~cATVAssaultGameModePrototype();

    private:
        unsigned char m_unmodelled148[0x260 - 0x148];

        // CD2: cATVAssaultGameModePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8287B538
        virtual GameManagement::etGameModeType RetType() const; // 14: 0x8288C218
        virtual void vf15(); // 15: 0x8288FB78
        virtual void vf16(); // 16: 0x8288FB78
        virtual void vf17(); // 17: 0x8288FB78
        virtual void vf18(); // 18: 0x8288FB78
        virtual void vf19(); // 19: 0x827E56A8
        virtual void vf23(); // 23: 0x8288FB78
        virtual void vf24(); // 24: 0x8288FB78
        virtual void vf25(); // 25: 0x8288AD98
        virtual void vf26(); // 26: 0x8288D5C0
        virtual void vf40(); // 40: 0x8287E160
    private:
        CD2_LAYOUT_CHECKS(cATVAssaultGameModePrototype, CD2_SIZE(cATVAssaultGameModePrototype, 0x260))

    };
}

#endif
