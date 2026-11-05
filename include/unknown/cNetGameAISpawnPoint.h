#include "rws/attributes.h"
// unknown::cNetGameAISpawnPoint: CD2 stand-in. Constructor 0x8284D100 calls
// cNetGameSpawnPoint (0x8284D908); the factory allocates 0xA0 bytes.
// StaticCreateClass (0x8284D068) builds cClass(0x4884, "cNetGameAISpawnPoint", 0xA0); 0xA0 is the size its registrar gives.
#ifndef UNKNOWN_CNETGAMEAISPAWNPOINT_H
#define UNKNOWN_CNETGAMEAISPAWNPOINT_H

#include "fun_runtime/class.h"
#include "GameManagement/cNetGameSpawnPoint.h"
#include "editor/guid_event_handler.h"

namespace unknown
{
    class cNetGameAISpawnPoint : public GameManagement::cNetGameSpawnPoint
    {
    public:
        cNetGameAISpawnPoint(); // CD2 0x8284D100, out of line
        // Unlike the implicit-destructor GUID-handler family, CD2 0x8284D180
        // explicitly restores this class's primary vptr before member cleanup.
        virtual ~cNetGameAISpawnPoint() {}
        // CD2 primary slots 15/16 extend the shared spawn-point interface.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual bool IsActive() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2 0x8284D058: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcNetGameAISpawnPointClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // CD2 constructor stores at +0x80/+0x88; meanings remain unrecovered.
        unsigned int m_word80;
        unsigned int m_word84;
        unsigned int m_word88;
        Editor::cGUIDEventHandler<cNetGameAISpawnPoint> m_GUIDEventHandler;
        CD2_LAYOUT_CHECKS(cNetGameAISpawnPoint,
            CD2_SIZE(cNetGameAISpawnPoint, 0xA0)
            CD2_OFFSET(cNetGameAISpawnPoint, m_word80, 0x80)
            CD2_OFFSET(cNetGameAISpawnPoint, m_word88, 0x88)
            CD2_OFFSET(cNetGameAISpawnPoint, m_GUIDEventHandler, 0x8C))
    };
}

#endif // UNKNOWN_CNETGAMEAISPAWNPOINT_H
