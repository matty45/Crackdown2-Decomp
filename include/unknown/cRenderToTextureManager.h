#include "rws/attributes.h"
// unknown::cRenderToTextureManager: CD2 stand-in. Constructor 0x827A9C18 calls
// cNonGameBase and installs its five interface tables. The factory allocates 0x98 bytes.
// StaticCreateClass (0x827A9B78) builds cClass(0xCBED, "cRenderToTextureManager", 0x98); 0x98 is the size its registrar gives.
#ifndef UNKNOWN_CRENDERTOTEXTUREMANAGER_H
#define UNKNOWN_CRENDERTOTEXTUREMANAGER_H

#include "fun_runtime/class.h"
#include "gom/non_game_base.h"
#include "fun_runtime/vector.h"
#include "unknown/cRenderToTextureEntry.h"

struct D3DTexture;

namespace unknown
{
    class cRenderToTextureManager : public cNonGameBase
    {
    public:
        cRenderToTextureManager(); // CD2 0x827A9C18, out of line
        virtual ~cRenderToTextureManager(); // CD2 0x827A9EA8
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 0x827A9AB0: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x827A9B68: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRenderToTextureManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // Descriptive names are ours: the constructor creates 1x1 black/white textures.
        D3DTexture *m_pBlackTexture;
        D3DTexture *m_pWhiteTexture;
        unsigned int m_word84;
        Fun_Runtime::cVector<cRenderToTextureEntry> m_Entries;
        static cRenderToTextureManager *ms_pInstance;
        // CD2: cRenderToTextureManager's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x827FBD60
        virtual int RetUniqueID(); // CEventHandler 1: 0x82604E70
    private:
        CD2_LAYOUT_CHECKS(cRenderToTextureManager,
            CD2_SIZE(cRenderToTextureManager, 0x98)
            CD2_OFFSET(cRenderToTextureManager, m_pBlackTexture, 0x7C)
            CD2_OFFSET(cRenderToTextureManager, m_pWhiteTexture, 0x80)
            CD2_OFFSET(cRenderToTextureManager, m_word84, 0x84)
            CD2_OFFSET(cRenderToTextureManager, m_Entries, 0x88))
    };
}

#endif // UNKNOWN_CRENDERTOTEXTUREMANAGER_H
