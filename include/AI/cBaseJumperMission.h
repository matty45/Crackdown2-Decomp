#ifndef AI_CBASEJUMPERMISSION_H
#define AI_CBASEJUMPERMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    class cBaseJumperMission : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8DDC0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cBaseJumperMissionClass = new Fun_Runtime::cClass(0xB4D9, "cBaseJumperMission", 0x400);
            return *cBaseJumperMissionClass;
        }
        static const Fun_Runtime::cClass *ms_pcBaseJumperMissionClass;

        cBaseJumperMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cBaseJumperMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82580578
        virtual void PropagateAttributes(); // 2: 0x82489260
        virtual CAttributeTableEntry * GetAttributeTable(char const *,unsigned int &,void * &,bool); // 3: 0x8245AB70
        virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x82580578
        virtual Fun_Runtime::RetVal Term(); // 6: 0x82580578
        virtual bool EnterPhysicalState(); // 7: 0x82580578
        virtual bool EnterRenderableState(); // 8: 0x82580578
        virtual bool HandleDataInNewDesignBuild(); // 9: 0x82580578
        virtual bool AllocatedFromFixedPool(); // 10: 0x82459EB8
        virtual void Slot12(); // 12: 0x8247F038
        virtual void Slot13(); // 13: 0x824596A0
        virtual void Slot14(); // 14: 0x824569C0
        virtual void Slot15(); // 15: 0x824569D8
        virtual void Slot16(); // 16: 0x82580578
        virtual void Slot17(); // 17: 0x8288FB78
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x827E56A8
        virtual void Slot19(); // 19: 0x82580578
        virtual void Slot20(); // 20: 0x82580578
        virtual void Slot21(); // 21: 0x82580578
        virtual void Slot24(); // 24: 0x824569F0
        virtual void Slot27(); // 27: 0x82580578
        virtual void Slot28(); // 28: 0x82459A38
        virtual void Slot29(); // 29: 0x82580578
        virtual void Slot30(); // 30: 0x824569F8
        virtual bool EnterRenderableState(eResourcesType); // 31: 0x82326A78
        virtual void LeaveRenderableState(); // 32: 0x823BA938
        virtual void Slot33(); // 33: 0x00000000
        virtual void Slot34(); // 34: 0x82489578
        virtual void Slot35(); // 35: 0x82489588
        virtual void Slot36(); // 36: 0x825DEEE0
        virtual void Slot37(); // 37: 0x82709328
        virtual Fun_Runtime::RetVal Reinitialise(GOM::cSpawner const *); // 38: 0x827E56A8
        virtual Fun_Runtime::RetVal TermForReuse(); // 39: 0x82456978
        virtual void Slot40(); // 40: 0x8288FB78
        virtual void Slot41(); // 41: 0x82489580
        virtual void Slot42(); // 42: 0x8245A230
        virtual void Slot43(); // 43: 0x8230E318
        virtual void Slot44(); // 44: 0x82580578
        virtual void Slot45(); // 45: 0x82580578
        virtual void Slot46(); // 46: 0x82580578
        virtual void Slot47(); // 47: 0x82580578
        virtual void Slot48(); // 48: 0x8283D658
        virtual bool IsAlive() const; // 49: 0x82580578
        virtual void Slot51(); // 50: 0x8288AD98
        virtual void Slot52(); // 51: 0x826712A8
        virtual void Slot53(); // 52: 0x8288B248
        virtual void Slot54(); // 53: 0x82C2BEA0
        virtual void Slot55(); // 54: 0x82580578
        virtual void Slot56(); // 55: 0x829851F8
        virtual void Slot57(); // 56: 0x8288BDB0
        virtual void Slot58(); // 57: 0x82889A60
        virtual void Slot59(); // 58: 0x82489590
        virtual void Slot60(); // 59: 0x8280FCC0
        virtual void Slot61(); // 60: 0x82580578
        virtual void Slot62(); // 61: 0x82580578
        virtual void Slot63(); // 62: 0x82580578
        virtual void Slot65(); // 64: 0x82489598
        virtual void Slot66(); // 65: 0x82489150
        virtual void Slot67(); // 66: 0x82580578
        virtual void Slot68(); // 67: 0x823CDC00
    };
}

#endif

