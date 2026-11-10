#ifndef AI_CBREACHHOLE_H
#define AI_CBREACHHOLE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cBreachHole : public cNonGameBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcBreachHoleClass;

        cBreachHole();
        // Out of line (CD2 0x8246EB40): the deleting wrapper calls it.
        virtual ~cBreachHole();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cBreachHole's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x823CDC00
        virtual void PropagateAttributes(); // 2: 0x823CDC18
        virtual CAttributeTableEntry * GetAttributeTable(char const *,unsigned int &,void * &,bool); // 3: 0x823D9718
        virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x8288FB78
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8288FB78
        virtual bool EnterPhysicalState(); // 7: 0x827E56A8
        virtual bool EnterRenderableState(); // 8: 0x827E56A8
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x82473D58
        virtual bool AllocatedFromFixedPool(); // 10: 0x82473D68
        virtual void Slot13(); // 13: 0x8246F4D0
        virtual void Slot14(); // 14: 0x824740A8
        virtual void Slot15(); // 15: 0x82474190
        virtual void Slot16(); // 16: 0x82474288
        virtual void Slot17(); // 17: 0x824742D8
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x003C0066
        virtual void Slot19(); // 19: 0x006F006E
        virtual void Slot20(); // 20: 0x00740020
        virtual void Slot21(); // 21: 0x0063006F
        virtual void Slot22(); // 22: 0x006C006F
        virtual void Slot23(); // 23: 0x0072003D
        virtual void Slot24(); // 24: 0x00270023
        virtual void Slot25(); // 25: 0x00430041
        virtual void UpdateRenderMatrix(); // 26: 0x00370046
        virtual void Slot27(); // 27: 0x00340044
        virtual void Slot28(); // 28: 0x0027003E
        virtual void Slot29(); // 29: 0x00250073
        virtual void Slot30(); // 30: 0x003C002F
        virtual bool EnterRenderableState(eResourcesType); // 31: 0x0066006F
        virtual void LeaveRenderableState(); // 32: 0x006E0074
        virtual void Slot33(); // 33: 0x003E003C
        virtual void Slot34(); // 34: 0x00620072
        virtual void Slot35(); // 35: 0x002F003E
        virtual void Slot36(); // 36: 0x00000000
        virtual void Slot37(); // 37: 0x00000000
        virtual Fun_Runtime::RetVal Reinitialise(GOM::cSpawner const *); // 38: 0x8248B4C0
        virtual Fun_Runtime::RetVal TermForReuse(); // 39: 0x8248B578
        virtual void Slot40(); // 40: 0x82580578
        virtual void Slot41(); // 41: 0x823CDC00
        virtual void Slot42(); // 42: 0x823CDC18
        virtual void Slot43(); // 43: 0x823D9718
        virtual void Slot44(); // 44: 0x823D9718
        virtual void Slot45(); // 45: 0x8288FB78
        virtual void Slot46(); // 46: 0x8288FB78
        virtual void Slot47(); // 47: 0x827E56A8
        virtual void Slot48(); // 48: 0x827E56A8
        virtual bool IsAlive() const; // 49: 0x8280DE40
        virtual void Slot51(); // 50: 0x8280E1D8
        virtual void Slot52(); // 51: 0x8220B7E8
        virtual void Slot53(); // 52: 0x8280FB68
        virtual void Slot54(); // 53: 0x8280DFF0
        virtual void Slot55(); // 54: 0x82580578
        virtual void Slot56(); // 55: 0x82580578
        virtual void Slot57(); // 56: 0x8248B4B0
        virtual void Slot58(); // 57: 0x8273FBA8
        virtual void Slot59(); // 58: 0x8246EAF0
        virtual void Slot60(); // 59: 0x8246EC00
        virtual void Slot61(); // 60: 0x82580578
        virtual void Slot62(); // 61: 0x823CDC00
        virtual void Slot63(); // 62: 0x823CDC18
        virtual void Slot64(); // 63: 0x823D9718
        virtual void Slot65(); // 64: 0x823D9718
        virtual void Slot66(); // 65: 0x8288FB78
        virtual void Slot67(); // 66: 0x8288FB78
        virtual void Slot68(); // 67: 0x827E56A8
    };
}

#endif

