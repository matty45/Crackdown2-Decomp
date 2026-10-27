// RenderWare Studio attribute framework (RWS::CAttributeHandler and friends).
//
// Reconstructed from the RuffKing (Ryse prototype, 2010-11-11) PDB via resym. Same codebase as Crackdown 2, built
// later. Layouts are checked at compile time (include/cd2/layout.h) against the reference PDB, and the offsets used by
// CD2 code seen so far agree (CAttributeCommand data at +8; cNPCTintProfile fields at 0x2C/0x4C).
// Member order, access and virtual order follow the PDB: access affects mangled names, and virtual order is the vtable.
// Compiler-generated members (__vecDelDtor, __local_vftable_ctor_closure) are omitted.
// CAttributeHandler's 11 virtuals match CD2's vtable for CHARACTER::cNPCTintProfile (slots 0-10).
// Accessors marked "inline in CD2" were confirmed by byte-exact matches in CHARACTER/cNPCTintProfile.cpp: CD2 inlines
// them, so declaring them out of line produces calls where CD2 has loads.
#ifndef RWS_ATTRIBUTES_H
#define RWS_ATTRIBUTES_H

#include "cd2/layout.h"

class CAttributeTableEntry;
enum eMemType { };

namespace Fun_Runtime
{
    class RetVal;
    class Vec3;
    class Mtx;
    struct RGBA;
}

namespace RWS
{
    class RWSGUIDList;
    class CAttributeHandler;
    class CAttributePacket;

    class RWSGUID
    {
    public:
        unsigned int m_Data[4];

        void Clear() { m_Data[0] = 0; m_Data[1] = 0; m_Data[2] = 0; m_Data[3] = 0; } // inline in CD2
        bool operator==(const RWSGUID &) const;
        RWSGUID &operator=(const RWSGUID &);
        bool operator!=(const RWSGUID &) const;
        bool operator<(const RWSGUID &) const;

        CD2_LAYOUT_CHECKS(RWSGUID,
            CD2_SIZE(RWSGUID, 0x10))
    };

    // Inlined by cAmbientVFXSpawner::HandleAttributes (0x827F9370). Keep the four assignments explicit:
    // a loop changes the compiler's copy sequence and the caller's stack temporaries.
    inline RWSGUID &RWSGUID::operator=(const RWSGUID &src)
    {
        m_Data[0] = src.m_Data[0];
        m_Data[1] = src.m_Data[1];
        m_Data[2] = src.m_Data[2];
        m_Data[3] = src.m_Data[3];
        return *this;
    }

    class CAttributeDataChunk
    {
    public:
        const unsigned int size_;
        const unsigned int type_;
        const unsigned int data_;

    private:
        bool IsEndChunk() const;
        const CAttributeDataChunk *pNextChunk() const;
        CAttributeDataChunk(const CAttributeDataChunk &);
        CAttributeDataChunk();
        CAttributeDataChunk &operator=(const CAttributeDataChunk &);

        CD2_LAYOUT_CHECKS(CAttributeDataChunk,
            CD2_SIZE(CAttributeDataChunk, 0xC)
            CD2_OFFSET(CAttributeDataChunk, type_, 0x4)
            CD2_OFFSET(CAttributeDataChunk, data_, 0x8))
    };

    class CAttributeDataChunkIterator
    {
    private:
        const CAttributeDataChunk *pCurrChunk_;

    public:
        CAttributeDataChunkIterator(const CAttributeDataChunk &);
        bool IsFinished() const { return pCurrChunk_->size_ == 0; } // inline in CD2
        CAttributeDataChunkIterator &operator++();
        const CAttributeDataChunk &operator*() const;
        const CAttributeDataChunk *operator->() const;
        const CAttributeDataChunk *GetDataChunk();

        CD2_LAYOUT_CHECKS(CAttributeDataChunkIterator,
            CD2_SIZE(CAttributeDataChunkIterator, 0x4))
    };

    class CAttributeCommand
    {
    private:
        const CAttributeDataChunk chunk_;

    public:
        unsigned int GetCommandId() const;
        const char *GetAs_char_ptr() const;
        const char GetAs_char() const;
        const unsigned short GetAs_unsigned_short() const;
        const short GetAs_short() const;
        const unsigned int GetAs_unsigned_int() const;
        const int GetAs_int() const;
        const unsigned long GetAs_unsigned_long() const;
        const long GetAs_long() const;
        const float GetAs_float() const { return *(const float *)&chunk_.data_; } // inline in CD2
        const double GetAs_double() const;
        const float GetAs_Real() const;
        const unsigned char GetAs_UInt8() const;
        const unsigned short GetAs_UInt16() const;
        const unsigned int GetAs_UInt32() const { return chunk_.data_; } // inline in CD2
        const unsigned long long GetAs_UInt64() const;
        const char GetAs_Int8() const;
        const short GetAs_Int16() const;
        const int GetAs_Int32() const;
        const Fun_Runtime::RGBA GetAs_RGBA() const;
        const Fun_Runtime::Mtx GetAs_Mtx() const;
        const Fun_Runtime::Vec3 GetAs_Vec3() const;
        const bool GetAs_bool() const;
        const RWSGUID GetAs_RWSGUID() const;
        const RWSGUIDList *GetAs_RWSGUIDList() const;

    protected:
        CAttributeCommand(const CAttributeCommand &);
        CAttributeCommand();
        CAttributeCommand &operator=(const CAttributeCommand &);

        CD2_LAYOUT_CHECKS(CAttributeCommand,
            CD2_SIZE(CAttributeCommand, 0xC))
    };

    class CAttributeCommandIterator
    {
    private:
        CAttributeDataChunkIterator chunkIt_;
        const char *pTargetClass_;

    public:
        CAttributeCommandIterator(const CAttributePacket &, const char *);
        bool IsFinished() const { return chunkIt_.IsFinished(); } // inline in CD2
        CAttributeCommandIterator &operator++();
        const CAttributeCommand &operator*() const;
        const CAttributeCommand *operator->() const;
        const CAttributeDataChunk *GetDataChunk();

    private:
        void SkipToNextAttributeCommand(bool);

        CD2_LAYOUT_CHECKS(CAttributeCommandIterator,
            CD2_SIZE(CAttributeCommandIterator, 0x8)
            CD2_OFFSET(CAttributeCommandIterator, pTargetClass_, 0x4))
    };

    class CAttributePacket
    {
    private:
        const CAttributeDataChunk firstChunk_;

    public:
        bool IsInstanceCreationPacket() const;
        const char *GetNameOfClassToCreate() const;
        RWSGUID GetInstanceId() const;
        CAttributePacket *Clone(eMemType) const;
        CAttributePacket *Update(const CAttributePacket &);
        CAttributeHandler *CreateEntity(bool) const;

    private:
        CAttributePacket(const CAttributePacket &);
        CAttributePacket();
        CAttributePacket &operator=(const CAttributePacket &);

    public:
        static unsigned int BuildInstanceIdChunk(const RWSGUID &, void *);
        static unsigned int BuildClassIdChunk(const char *, void *);
        static unsigned int BuildCreateClassIdChunk(const char *, void *);
        static unsigned int BuildCommandDataChunk(unsigned int, const void *, unsigned int, void *, unsigned int *);
        static unsigned int BuildTerminatorChunk(void *);
        static CAttributePacket *MakePacketFromBuffer(char *);

        CD2_LAYOUT_CHECKS(CAttributePacket,
            CD2_SIZE(CAttributePacket, 0xC))
    };

    class CAttributeHandler
    {
    protected:
        unsigned int m_Flags;
        RWSGUID m_InstanceId;

    private:
        static void (*sm_pNewAttributeHandlerCallBack)();

    public:
        virtual ~CAttributeHandler();
        virtual void HandleAttributes(const CAttributePacket &);
        virtual void PropagateAttributes();
        virtual CAttributeTableEntry *GetAttributeTable(const char *, unsigned int &, void *&, bool);
        virtual void (*GetAttrPostUpdateFunc(void *&))(void *);
        void Add(const RWSGUID &);
        void AddToListOnly();
        void Lock();
        void UnLock();
        bool IsLocked();
        virtual Fun_Runtime::RetVal Init(const CAttributePacket &);
        virtual Fun_Runtime::RetVal Term();
        virtual bool EnterPhysicalState();
        virtual bool EnterRenderableState();
        const RWSGUID *InqInstanceId();
        virtual bool HandleDataInNewDesignBuild();
        virtual bool AllocatedFromFixedPool();

    protected:
        void RemoveMultipleInstances();

    private:
        CAttributeHandler(const CAttributeHandler &);

    protected:
        CAttributeHandler() : m_Flags(0) { m_InstanceId.Clear(); } // inline in CD2

    private:
        CAttributeHandler &operator=(const CAttributeHandler &);

    public:
        static void Remove(const RWSGUID &);
        static CAttributeHandler *Find(const RWSGUID &);
        static void Purge();
        static void PurgeAll();
        static void Open(void (*)());
        static void Close();
        static void RegisterStreamChunkHandlers();
        static void UnRegisterStreamChunkHandlers();
        static void NewAttributeHandlerCreated();

    protected:
        static bool IsAPrototype(const CAttributePacket &);
        static CAttributeHandler *CreatePrototype(const CAttributePacket &);

        CD2_LAYOUT_CHECKS(CAttributeHandler,
            CD2_SIZE(CAttributeHandler, 0x18)
            CD2_OFFSET(CAttributeHandler, m_Flags, 0x4)
            CD2_OFFSET(CAttributeHandler, m_InstanceId, 0x8))
    };
}

#endif // RWS_ATTRIBUTES_H
