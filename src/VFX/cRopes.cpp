// Matching update (2026-10-28): ShowRopeSegments remains WIP, 29/34 words with
// the standard verifier. The experimental callee-model extension was discarded.
// Matching update (2026-10-28): the constructor is strict EXACT in plain and
// LTCG builds after correcting the debug-handler and script-host inheritance.
// The historical constructor and RetClass/IsA thunk limitations below are superseded.
// VFX/cRopes.cpp: rope renderer of Crackdown 2.
// Measurement batch 1 (2026-10-23, Sonnet 5.5): 20 of the file's 25 functions byte-exact (see config/matched_functions.json).
// Not done: Render (443 instructions, D3D/VMX128 internals), the constructor (CD2 has one extra dead addi),
// ShowRopeSegments (stack frame 0x70 versus our 0x60) and the RetClass/IsA thunks at -0x4C.
// ForceRangeInsert and ReloadShader are stand-ins that only reproduce code CD2 emits in this file.
#include "VFX/cRopes.h"
#include "rw/rwmem.h"

// The reserve instantiation belongs to another translation unit (CD2 0x826104B8).
// Keep its external definition, including its size argument, visible to LTCG.
extern template void std::vector<VFX::RopeSegmentData *,
    Fun_Runtime::cAllocator<VFX::RopeSegmentData *> >::reserve(size_t);

namespace Fun_Runtime
{
    template <class T> cPoolBase<T>::~cPoolBase() {}
}

D3DVertexDeclaration *CreateRopeVertexDecl(const D3DVERTEXELEMENT9 *);
#include <stdio.h>
#include "GDb/console.h"

namespace VFX
{
    cRopes *g_pRopes;
    bool cRopes::m_bRenderRopes;
    Fun_Runtime::cPool<RopeSegmentData, 600> cRopes::m_SegmentPool;

    const char *const cRopes::pcRopesClassID = "cRopes";

    Fun_Runtime::cClass &cRopes::StaticCreateClass()
    {
        static Fun_Runtime::cClass *pClass = new Fun_Runtime::cClass(0xA2C2A, "cRopes", 0xCC);
        return *pClass;
    }

    const Fun_Runtime::cClass &cRopes::RetClass() const
    {
        return *ms_pcRopesClass;
    }

    bool cRopes::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcRopesClass->IsA(c);
    }

    const char *cRopes::RetClassName() const
    {
        return "cRopes";
    }

    RWS::CAttributeHandler *cRopes::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cRopes;
    }

    cRopes::cRopes()
    {
        m_pSegmentShader = new cDefinedRopeShader;
        D3DVERTEXELEMENT9 elements[3] =
        {
            { 0, 0, 0x2A23B9, 0, 0, 0 },
            { 0, 12, 0x182886, 0, 10, 0 },
            { 0xFF, 0, 0xFFFFFFFF, 0, 0, 0 }
        };
        m_pVertexDecl = CreateRopeVertexDecl(elements);
        g_pRopes = this;
        m_bRenderRopes = true;
        m_lSegments.reserve(600);
        m_lActiveSegments.reserve(600);
        m_ShowRopeSegments.Add(L"ShowRopeSegments", ShowRopeSegments, this, L"", L"vfx", false, 0);
    }

    cRopes::~cRopes()
    {
        delete m_pSegmentShader;
        m_pVertexDecl->Release();
        g_pRopes = 0;
        m_lSegments.clear();
        m_lActiveSegments.clear();
    }

    void cRopes::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cNonGameBase::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, pcRopesClassID); !it.IsFinished(); ++it)
        {
            if (it->GetCommandId() == 0)
            {
                float mem = it->GetAs_float();
                RwMemNative32(&mem, 4);
                m_fSegmentWidth = mem;
            }
        }
    }

    void cRopes::GetRopeSegment(RopeSegmentData **pRopeSegment)
    {
        cRopes *self = g_pRopes;
        *pRopeSegment = m_SegmentPool.GetOne();
        if (*pRopeSegment)
            self->m_lSegments.push_back(*pRopeSegment);
    }

    void cRopes::ReturnRopeSegment(RopeSegmentData **pRopeSegment)
    {
        cRopes *self = g_pRopes;
        Fun_Runtime::cVector<RopeSegmentData *>::iterator it =
            std::find(self->m_lSegments.begin(), self->m_lSegments.end(), *pRopeSegment);
        self->m_lSegments.erase(it);
        m_SegmentPool.ReturnOne(*pRopeSegment);
        *pRopeSegment = 0;
    }

    void cRopes::ShowRopeSegments(void *, wchar_t *cmdLine)
    {
        int value = 0;
        if (swscanf(cmdLine, L"%d", &value) > 0)
            m_bRenderRopes = value != 0;
        GDb::ConsoleOutput(L"Ropes now: %s", m_bRenderRopes ? L"on" : L"off");
    }

    static RWS::CClassFactory::CRegistrar cRopesRegistrar("cRopes", cRopes::MakeNew, 0xCC, false);
}

// Forces the std::vector range-insert instantiation that CD2 emits in this file (used by cVector copies in CD2).
namespace VFX
{
    void ForceRangeInsert(Fun_Runtime::cVector<RopeSegmentData *> &a, Fun_Runtime::cVector<RopeSegmentData *> &b)
    {
        a.insert(a.begin(), b.begin(), b.end());
    }
}

// F31 guess: shader-reload style helper on a global shader object (unknown class; stand-in).
namespace VFX
{
    class cReloadable
    {
    public:
        virtual void Vf0();
        virtual void Vf1();
        virtual void Reload(bool revert);
        unsigned char pad[0x3C - 4];
        void *m_pVS;
        void *m_pPS;
    };
    cReloadable *g_pReloadable;
    void ReleaseVS(void *);
    void ReleasePS(void *);

    bool ReloadShader(bool revert)
    {
        if (g_pReloadable)
        {
            g_pReloadable->Reload(revert);
            cReloadable *p = g_pReloadable;
            ReleaseVS(p->m_pVS);
            ReleasePS(p->m_pPS);
        }
        return true;
    }
}
