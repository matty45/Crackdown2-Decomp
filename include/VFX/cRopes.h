// VFX::cRopes: rope renderer (CD2 object size 0xCC). Layout from CD2's code; RuffKing's class is 0x118 with different
// bases. Bases: cNonGameBase (gom/non_game_base.h) and the debug-page handler at 0x7C (a stand-in for
// GDb::cDebugPageHandler: only the slots cRopes needs).
#ifndef VFX_CROPES_H
#define VFX_CROPES_H

#define _SECURE_SCL 0
#include <xtl.h>
#include <new>
#include <vector>
#include <algorithm>
#include "rws/attributes.h"
#include "rws/classfactory.h"
#include "cd2/layout.h"
#include "cd2/memory.h"
#include "fun_runtime/class.h"
#include "gom/non_game_base.h"

namespace Fun_Runtime
{
    // Allocator for the std::vectors: allocate() is out of line in CD2, deallocate() is XDestroyHeapBlock.
    template <class T>
    class cAllocator
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        template <class U> struct rebind { typedef cAllocator<U> other; };
        cAllocator() {}
        cAllocator(const cAllocator &) {}
        template <class U> cAllocator(const cAllocator<U> &) {}
        static pointer allocate(size_type n);
        void deallocate(pointer p, size_type) { XDestroyHeapBlock(p); }
        void construct(pointer p, const T &v) { new ((void *)p) T(v); }
        void destroy(pointer) {}
        pointer address(reference r) const { return &r; }
        const_pointer address(const_reference r) const { return &r; }
        size_type max_size() const { return 0x3FFFFFFF; }
    };

    // std::vector wrapper whose push_back is out of line (CD2 calls it rather than inlining std::vector's).
    template <class T>
    class cVector : public std::vector<T, cAllocator<T> >
    {
    public:
        void push_back(const T &v);
        void clear();
    };
    template <class T>
    void cVector<T>::clear()
    {
        std::vector<T, cAllocator<T> >::clear();
    }
    template <class T>
    void cVector<T>::push_back(const T &v)
    {
        std::vector<T, cAllocator<T> >::push_back(v);
    }

    // Pool with a ring buffer of free slots (vptr, capacity, used, get index, put index, avail array, objects, owner).
    template <class T>
    class cPoolBase
    {
    public:
        virtual ~cPoolBase();
        __forceinline T *GetOne()
        {
            T *result;
            if (m_nUsedCount < m_nCapacity)
            {
                T *p = (T *)m_pAvailable[m_nGetI];
                T *pRet;
                if (p)
                    pRet = new ((void *)p) T;
                else
                    pRet = 0;
                m_pAvailable[m_nGetI] = 0;
                if (++m_nGetI >= m_nCapacity)
                    m_nGetI = 0;
                ++m_nUsedCount;
                result = pRet;
            }
            else
            {
                result = 0;
            }
            return result;
        }
        void ReturnOne(T *p)
        {
            m_pAvailable[m_nPutI] = p;
            ++m_nPutI;
            --m_nUsedCount;
            if (m_nPutI >= m_nCapacity)
                m_nPutI = 0;
        }
    protected:
        unsigned int m_nCapacity;
        unsigned int m_nUsedCount;
        unsigned int m_nGetI;
        unsigned int m_nPutI;
        void **m_pAvailable;
        unsigned char *m_pObjects;
        void *m_pOwner;
    };

    template <class T, unsigned int N>
    class cPool : public cPoolBase<T>
    {
    public:
        cPool()
        {
            m_nCapacity = N;
            m_pAvailable = m_dAvailable;
            m_nUsedCount = 0;
            m_pObjects = m_dObjects;
            m_nGetI = 0;
            m_nPutI = 0;
            m_pOwner = 0;
            for (unsigned int i = 0; i < N; ++i)
                m_dAvailable[i] = m_dObjects + i * sizeof(T);
        }
        virtual ~cPool() { Reset(); }
        void Reset();
    private:
        void *m_dAvailable[N];
        unsigned char m_dObjects[N * sizeof(T)];
    };

    template <class T, unsigned int N>
    void cPool<T, N>::Reset()
    {
        if (m_nUsedCount > 0)
        {
            bool bFree[N];
            memset(bFree, 1, N);
            for (unsigned int i = 0; i < N; ++i)
            {
                if (m_dAvailable[i] != 0)
                {
                    int nIndex = (int)((unsigned char *)m_dAvailable[i] - m_pObjects) / (int)sizeof(T);
                    bFree[nIndex] = false;
                }
            }
            for (unsigned int i = 0; i < N; ++i)
            {
                if (bFree[i])
                    ReturnOne((T *)(m_dObjects + i * sizeof(T)));
            }
        }
    }
}

namespace Cmd
{
    class cConsoleCommand
    {
    public:
        cConsoleCommand()
        {
            m_a = 0; m_d = 0; m_e = 0; m_b = 0; m_c = 0; m_f = 0; m_i = false; m_g = 0;
        }
        ~cConsoleCommand();
        void Add(const wchar_t *name, void (*fn)(void *, wchar_t *), void *obj, const wchar_t *blank,
                 const wchar_t *category, bool b, void *extra);
    private:
        unsigned int m_a, m_b, m_c, m_d, m_e, m_f, m_g;
        bool m_h;
        bool m_i;
        char m_pad[2];
    };
}

namespace VFX
{
    class cShader
    {
    public:
        virtual ~cShader();
    private:
        unsigned char m_data[0x60];
    };

    // cDefinedShader<cShader_Rope_Traits>: only the out-of-line constructor matters here.
    class cDefinedRopeShader : public cShader
    {
    public:
        cDefinedRopeShader();
    };

    struct RopeSegmentData
    {
        float x0, y0, z0, w0;
        float x1, y1, z1, w1;
        float rest[4];
        RopeSegmentData() : x0(0.0f), y0(0.0f), z0(0.0f), x1(0.0f), y1(0.0f), z1(0.0f) {}
    };

    class cDebugPageHandler
    {
    public:
        cDebugPageHandler() {}
        virtual ~cDebugPageHandler() {}
        virtual void RenderDebugPage(int, int) {}
    };

    class cRopes : public cNonGameBase, public cDebugPageHandler
    {
    private:
        Fun_Runtime::cVector<RopeSegmentData *> m_lSegments;
        Fun_Runtime::cVector<RopeSegmentData *> m_lActiveSegments;
        cShader *m_pSegmentShader;
        D3DVertexDeclaration *m_pVertexDecl;
        float m_fSegmentWidth;
        Cmd::cConsoleCommand m_ShowRopeSegments;

    public:
        static const Fun_Runtime::cClass *const ms_pcRopesClass;
        static const char *const pcRopesClassID;
        static Fun_Runtime::cPool<RopeSegmentData, 600> m_SegmentPool;
        static bool m_bRenderRopes;

        cRopes();
        virtual ~cRopes();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        void Render();
        static void GetRopeSegment(RopeSegmentData **);
        static void ReturnRopeSegment(RopeSegmentData **);
        virtual void RenderDebugPage(int, int);

        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

    private:
        static void ShowRopeSegments(void *, wchar_t *);

    public:
        CD2_LAYOUT_CHECKS(cRopes,
            CD2_SIZE(cRopes, 0xCC)
            CD2_OFFSET(cRopes, m_lSegments, 0x80)
            CD2_OFFSET(cRopes, m_lActiveSegments, 0x90)
            CD2_OFFSET(cRopes, m_pSegmentShader, 0xA0)
            CD2_OFFSET(cRopes, m_fSegmentWidth, 0xA8)
            CD2_OFFSET(cRopes, m_ShowRopeSegments, 0xAC))
    };

    extern cRopes *g_pRopes;
}

#endif // VFX_CROPES_H
