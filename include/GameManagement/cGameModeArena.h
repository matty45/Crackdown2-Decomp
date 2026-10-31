// GameManagement::cGameModeArena: arena definition for game modes (spawn points, launch pads, ToD/weather settings).
// CD2 layout (0x10C bytes), worked out from the ctor (0x8284E4C0), dtor (0x8284E5C0), HandleAttributes (0x8284E6D8) and
// OnShutDownLevel (0x8284EB38). RuffKing's class is 0xF8 with a different base (cGMMResource, 0x5C bytes). CD2's base is
// 0x60 bytes: CAttributeHandler (0x18) plus a polymorphic second base at 0x18 (0x48 bytes, 14 virtuals, virtual dtor first,
// a short handle at 0x1C). RuffKing says that second base is RWS::CEventHandler.
//   0x60 list head+size  0x6C solo vec  0x7C team vec[2]  0x9C pickup vec[2]  0xBC weapon vec  0xCC launch pad vec
//   0xDC barrier  0xE0 ?  0xE4 camera container  0xE8 string id  0xEC/0xF0 ToD phase/period  0xF4/F5 ToD bools
//   0xF8 weather mode  0xFC force weather  0x100/104/108 (unknown, extra versus RuffKing)
// Stand-ins (names ours): cGMMEventBase (second base), cGMMResource (out-of-line ctor/dtor/HandleAttributes), cList, cVec,
// cLocStringManager chain.
#ifndef GAMEMANAGEMENT_CGAMEMODEARENA_H
#define GAMEMANAGEMENT_CGAMEMODEARENA_H

#include <string.h>
#include "rws/attributes.h"
#include "cd2/layout.h"
#include "cd2/memory.h"
#include "fun_runtime/randgen.h"

namespace GameManagement
{
    class cArenaBarrier;
    class cArenaCameraContainer;
    class cGameModeSpawnPoint;
    class cGameModePrototype;
    class cGameModeStartZone;
    class cGameModeCheckpoint;
    class cNetGamePlayerSpawnPoint;
    class cNetGamePickupSpawnPoint;

    // Second base of every GMM resource (vptr at 0x18, 14 virtuals, virtual destructor first).
    class cGMMEventBase
    {
    public:
        virtual ~cGMMEventBase();
        virtual void Ev1();
        virtual void Ev2();
        virtual void Ev3();
        virtual void Ev4();
        virtual void Ev5();
        virtual void Ev6();
        virtual void Ev7();
        virtual void Ev8();
        virtual void Ev9();
        virtual void Ev10();
        virtual void Ev11();
        virtual void Ev12();
        virtual void Ev13();
    protected:
        short m_nHandle;
        short m_nPad;
        unsigned char m_abData[0x40];
    };

    class cGMMResource : public RWS::CAttributeHandler, public cGMMEventBase
    {
    public:
        cGMMResource();
        virtual ~cGMMResource();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    };

    // std::list<T*> with out-of-line push_back and destructor (CD2 0x827FAF00 / 0x82470DA8); constructor inline.
    struct cListNode
    {
        cListNode *m_pNext;
        cListNode *m_pPrev;
        void *m_pValue;
    };
    cListNode *AllocListNode();
    inline cListNode **NextPtr(cListNode *p) { return &p->m_pNext; }
    inline cListNode **PrevPtr(cListNode *p) { return &p->m_pPrev; }

    class cList
    {
    public:
        cList() { cListNode *n = AllocListNode(); if (n) n->m_pNext = n; cListNode **pp = PrevPtr(n); if (pp) *pp = n; m_pHead = n; m_nSize = 0; }
        ~cList();
        void push_back(void *const &);
    private:
        int m_nAlloc;
        cListNode *m_pHead;
        int m_nSize;
    };

    // std::vector<T*> with a leading empty-allocator slot (0x10 bytes). Destructor and erase are inline in CD2.
    template <class T>
    class cVec
    {
    public:
        cVec() : m_pFirst(0), m_pLast(0), m_pEnd(0) {}
        ~cVec() { if (m_pFirst) operator delete(m_pFirst); m_pFirst = 0; m_pLast = 0; m_pEnd = 0; }
        void clear() { erase(m_pFirst, m_pLast); }
        void erase(T *first, T *last)
        {
            if (first != last)
            {
                T *newLast = first + (m_pLast - last);
                if (m_pLast - last > 0)
                    memmove_s(first, (m_pLast - last) * sizeof(T), last, (m_pLast - last) * sizeof(T));
                m_pLast = newLast;
            }
        }
        unsigned int size() const { return (unsigned int)(m_pLast - m_pFirst); }
        const T &operator[](unsigned int i) const { return m_pFirst[i]; }
    private:
        int m_nAlloc;
        T *m_pFirst;
        T *m_pLast;
        T *m_pEnd;
    };

    unsigned int GetTime_msec();

    // String id hashing: h = h * mult + c; the multiplier sits behind a chain of three pointers in the manager.
    struct cLocHashL3 { unsigned char pad[0x10]; int m_nMultiplier; };
    struct cLocHashL2 { cLocHashL3 *m_p; };
    struct cLocHashL1 { cLocHashL2 *m_p; };
    struct cLocStringManager
    {
        unsigned char pad[0x10];
        cLocHashL1 *m_p;
        unsigned int GetStringID(const char *s)
        {
            int mult = m_p->m_p->m_p->m_nMultiplier;
            int id = 0;
            for (char c = *s; c != 0; c = *++s)
                id = id * mult + c;
            return id;
        }
    };
    cLocStringManager *RetLocStringManager();

    // Anything findable by GUID that can be listed in an arena (virtual slot 14 returns the type).
    class cArenaEntity
    {
    public:
        virtual void V0(); virtual void V1(); virtual void V2(); virtual void V3(); virtual void V4();
        virtual void V5(); virtual void V6(); virtual void V7(); virtual void V8(); virtual void V9();
        virtual void V10(); virtual void V11(); virtual void V12(); virtual void V13();
        virtual int RetType();
    };
    struct cEntityManager { unsigned char pad[0xE34]; int m_nCount; };
    cEntityManager *RetEntityManager(int);


    // Message system stand-ins (names ours; real ones are RWS::CEventId / CMsg / CEventHandler).
    struct cEventId { unsigned char m_abData[16]; cEventId(); ~cEventId(); };
    struct cMsg { void **m_ppTarget; void *m_pData; unsigned char m_abPad[0x10]; cMsg(const cEventId &, int); };
    extern void **g_ppMsgNull;
    void RegisterMsg(cEventId &, const char *, const char *);
    void UnRegisterMsg(cEventId &);
    void DispatchMsg(cMsg &);
    inline void SendMsg(cMsg &m) { if (m.m_ppTarget != g_ppMsgNull && *m.m_ppTarget != 0) DispatchMsg(m); }

    // MSVC 2008 std::string layout: allocator slot, 16 byte buffer or heap pointer, size, reserve. Destructor inline.
    class cString
    {
    public:
        ~cString()
        {
            if (m_nRes >= 16)
                operator delete(m_u.m_pPtr);
            m_nSize = 0;
            m_nRes = 15;
            m_u.m_acBuf[0] = 0;
        }
        const char *c_str() const { return m_nRes >= 16 ? m_u.m_pPtr : m_u.m_acBuf; }
    private:
        int m_nAlloc;
        union { char m_acBuf[16]; char *m_pPtr; } m_u;
        unsigned int m_nSize;
        unsigned int m_nRes;
    };
    cString c_strc(const cString &);

    class cGameModeArena;
    class cArenaLinker
    {
    public:
        static cGameModeArena *GetArena(const cString &);
    };
    short RegisterGMM(cGMMResource *);
    void UnregisterGMM(int);

    class cGameModeArena : public cGMMResource
    {
    protected:
        cList m_lCompatibleGameModes;
        cVec<cGameModeSpawnPoint *> m_vPlayerSoloSpawnPoints;
        cVec<cGameModeSpawnPoint *> m_vPlayerTeamSpawnPoints[2];
        cVec<cGameModeSpawnPoint *> m_vPickupSpawnPoints[2];
        cVec<cGameModeSpawnPoint *> m_vWeaponSpawnPoints;
        cVec<cGameModeSpawnPoint *> m_vLaunchPads;
        cArenaBarrier *m_pBarrier;
        void *m_pUnknownE0;
        cArenaCameraContainer *m_pCameraContainer;
        unsigned int m_nStringID;
        float m_fToDPhase;
        float m_fToDPeriod;
        bool m_bForceToD;
        bool m_bToDActive;
        unsigned int m_nWeatherMode;
        bool m_bForceWeather;
        unsigned int m_nUnknown100;
        int m_nUnknown104;
        int m_nUnknown108;

    public:
        static const char *const pcGameModeArenaClassID;

        virtual const char *RetClassName() const;
        virtual void Destruct();
        cGameModeArena();
        virtual void OnShutDownLevel();
        virtual unsigned long RetStringID();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool IsCheckpointArena() const;
        virtual bool IsCHordeArena() const;
        virtual cGameModeStartZone *RetStartZone() const;
        virtual unsigned int RetNumCheckpoints() const;
        virtual cGameModeCheckpoint *RetCheckpoint(unsigned int) const;
        virtual void AddStartZone(cGameModeStartZone *);
        virtual void AddCheckpoint(cGameModeCheckpoint *);
        virtual ~cGameModeArena();

        template <class T>
        static T *GetRandSpawnPointInList(const cVec<cGameModeSpawnPoint *> &);

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const char *RetRWSClassName();

        CD2_LAYOUT_CHECKS(cGameModeArena,
            CD2_SIZE(cGameModeArena, 0x10C)
            CD2_OFFSET(cGameModeArena, m_lCompatibleGameModes, 0x60)
            CD2_OFFSET(cGameModeArena, m_vPlayerSoloSpawnPoints, 0x6C)
            CD2_OFFSET(cGameModeArena, m_vPlayerTeamSpawnPoints, 0x7C)
            CD2_OFFSET(cGameModeArena, m_vPickupSpawnPoints, 0x9C)
            CD2_OFFSET(cGameModeArena, m_vWeaponSpawnPoints, 0xBC)
            CD2_OFFSET(cGameModeArena, m_vLaunchPads, 0xCC)
            CD2_OFFSET(cGameModeArena, m_pBarrier, 0xDC)
            CD2_OFFSET(cGameModeArena, m_nStringID, 0xE8)
            CD2_OFFSET(cGameModeArena, m_fToDPhase, 0xEC)
            CD2_OFFSET(cGameModeArena, m_bForceToD, 0xF4)
            CD2_OFFSET(cGameModeArena, m_nWeatherMode, 0xF8)
            CD2_OFFSET(cGameModeArena, m_nUnknown108, 0x108))
    };
}

#endif // GAMEMANAGEMENT_CGAMEMODEARENA_H
