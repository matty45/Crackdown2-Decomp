#ifndef AI_CTRAININGMISSION_H
#define AI_CTRAININGMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    class cTrainingMission : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8BBD0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cTrainingMissionClass = new Fun_Runtime::cClass(0xB4D6, "cTrainingMission", 0x9D0);
            return *cTrainingMissionClass;
        }
        static const Fun_Runtime::cClass *ms_pcTrainingMissionClass;

        cTrainingMission();
        // The body (0x82206500) lies in the order-list region; its deleting wrapper (0x8247F3F8) calls it.
        virtual ~cTrainingMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cTrainingMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82580578
        virtual void PropagateAttributes(); // 2: 0x82482E88
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
        virtual void Slot23(); // 23: 0x82482A30
        virtual void Slot24(); // 24: 0x824569F0
        virtual void Slot25(); // 25: 0x82480E08
        virtual void UpdateRenderMatrix(); // 26: 0x82480DF8
        virtual void Slot27(); // 27: 0x82580578
        virtual void Slot28(); // 28: 0x82459A38
        virtual void Slot29(); // 29: 0x82480DA0
        virtual void Slot30(); // 30: 0x82484C20
        virtual bool EnterRenderableState(eResourcesType); // 31: 0x82326A78
        virtual void LeaveRenderableState(); // 32: 0x823BA938
        virtual void Slot33(); // 33: 0x00000000
        virtual void Slot34(); // 34: 0x8245C6D8
        virtual void Slot35(); // 35: 0x8245C6E8
        virtual void Slot36(); // 36: 0x8245CD58
        virtual void Slot37(); // 37: 0x8245E238
        virtual Fun_Runtime::RetVal Reinitialise(GOM::cSpawner const *); // 38: 0x8245C798
        virtual Fun_Runtime::RetVal TermForReuse(); // 39: 0x82580578
        virtual void Slot40(); // 40: 0x82580578
        virtual void Slot42(); // 42: 0x8245D058
        virtual void Slot43(); // 43: 0x8245AB70
        virtual void Slot44(); // 44: 0x82580578
        virtual void Slot45(); // 45: 0x82580578
        virtual void Slot46(); // 46: 0x82580578
        virtual void Slot47(); // 47: 0x82580578
        virtual void Slot48(); // 48: 0x82580578
        virtual bool IsAlive() const; // 49: 0x82580578
        virtual void Slot51(); // 50: 0x82459EB8
        virtual void Slot52(); // 51: 0x8245C788
        virtual void Slot53(); // 52: 0x8247F038
        virtual void Slot54(); // 53: 0x824596A0
        virtual void Slot55(); // 54: 0x824569C0
        virtual void Slot56(); // 55: 0x824569D8
        virtual void Slot57(); // 56: 0x82580578
        virtual void Slot58(); // 57: 0x8288FB78
        virtual void Slot59(); // 58: 0x827E56A8
        virtual void Slot60(); // 59: 0x82580578
        virtual void Slot61(); // 60: 0x82580578
        virtual void Slot62(); // 61: 0x82580578
        virtual void Slot63(); // 62: 0x82580578
        virtual void Slot65(); // 64: 0x824569F0
        virtual void Slot66(); // 65: 0x8245CE08
        virtual void Slot67(); // 66: 0x82580578
        virtual void Slot68(); // 67: 0x82580578
    };
}

#endif

