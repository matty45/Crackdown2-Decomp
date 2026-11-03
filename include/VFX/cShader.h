// VFX::cShader: STAND-IN, 0x64 bytes in CD2 (the shared shader constructors
// link the object through its final word at 0x60). The reference cShader names
// the vertex/pixel shader pointers; CD2's binding callback reads them at 0x3C/0x40.
// CD2's three vtable slots are destructor, callback getter and Reload (the
// reference name, also used by the recovered rope shader callback).
// The callback getter's name is ours: CD2's slot 1 returns
// a function pointer, unlike the later reference build's GetName interface.
#ifndef VFX_CSHADER_H
#define VFX_CSHADER_H
#include <xtl.h>
#include "cd2/layout.h"
namespace VFX
{
    class cShader
    {
    public:
        typedef bool (*ReloadCallback)(bool revert);
        virtual ~cShader();
        virtual ReloadCallback GetReloadCallback() const;
        virtual void Reload(bool revert);
        D3DVertexShader *GetVertexShader() const { return m_pVertexShader; }
        D3DPixelShader *GetPixelShader() const { return m_pPixelShader; }
    private:
        unsigned char m_unmodelled04[0x3C - 4];
    protected:
        D3DVertexShader *m_pVertexShader;
        D3DPixelShader *m_pPixelShader;
    private:
        unsigned char m_unmodelled44[0x64 - 0x44];
        CD2_LAYOUT_CHECKS(cShader,
            CD2_SIZE(cShader, 0x64)
            CD2_OFFSET(cShader, m_pVertexShader, 0x3C)
            CD2_OFFSET(cShader, m_pPixelShader, 0x40))
    };

    // CD2's cached vertex/pixel shader setters. Their original names are unresolved.
    void Ext_82B8A7B0(D3DVertexShader *);
    void Ext_82B8A780(D3DPixelShader *);
    // The rope shader's singleton; the historical global name is retained.
    extern cShader *g_pReloadable;
}
#endif
