#ifndef UI_cUIControl_H
#define UI_cUIControl_H

#include "rws/attributes.h"

namespace SaveGame
{
    class cLoadStream;
    class cSaveStream;
    class cLoadSaveObject
    {
    public:
        virtual ~cLoadSaveObject() {}
        virtual void Load(cLoadStream *pStream) {}
        virtual void Save(cSaveStream *pStream) {}
    };
}

namespace UI
{
    template <typename T>
    struct cOptionItem
    {
        void (*mApplyFunc)(T);
        T mDefault;
        T mCurrent;
    };

    class cUIControl : public RWS::CAttributeHandler, public SaveGame::cLoadSaveObject
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool bGlobal);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &attr);
        virtual void Load(SaveGame::cLoadStream *pStream);
        virtual void Save(SaveGame::cSaveStream *pStream);

        cUIControl();
        virtual ~cUIControl();

        static cUIControl *Instance();

        float DigiPrinterSpeed() const;
        float DigiPrinterTipDelay() const;
        float AutoSaveMinDisplayTime() const;
        int GammaLogoAlpha() const;
        float TickerScrollSpeed() const;

        void ApplyOptions();
        void RestoreDefaultOptions();
        void OverrideDefaultSubtitlesBasedOnLanguage();

        cOptionItem<int> mGamma; // 0x1C
        cOptionItem<int> mMusicVolume; // 0x28
        cOptionItem<int> mSFXVolume; // 0x34
        cOptionItem<int> mVoiceVolume; // 0x40
        cOptionItem<int> mNPCVoiceVolume; // 0x4C
        cOptionItem<int> mHudOpacity; // 0x58
        cOptionItem<char> mDynamicSetting; // 0x64
        cOptionItem<bool> mOriginalVO; // 0x6C
        cOptionItem<bool> mSubtitles; // 0x74
        cOptionItem<bool> mDynamicRange; // 0x7C
        cOptionItem<bool> mInvertYAxis; // 0x84
        cOptionItem<bool> mLeftHanded; // 0x8C
        float mNameFadeInTime; // 0x94
        float mNameFadeOutTime; // 0x98
        float mNameDisplayTime; // 0x9C
        float mNamePlayerTargetedTime; // 0xA0
        float mNameHeightAboveHead; // 0xA4
        float m_AlphaDivider; // 0xA8
        float m_ColourMultiplier; // 0xAC
        float m_BlueTintMul; // 0xB0
        float m_HexAlphaMul; // 0xB4
        float m_LoadingScreenTime; // 0xB8
        float m_DigiPrinterSpeed; // 0xBC
        float m_DigiPrinterTipDelay; // 0xC0
        float m_AutoSaveMinDisplayTime; // 0xC4
        float m_TickerScrollSpeed; // 0xC8
        int m_GammaLogoAlpha; // 0xCC

        static cUIControl *m_pInstance;

        CD2_LAYOUT_CHECKS(cUIControl,
            CD2_SIZE(cUIControl, 0xD0)
            CD2_OFFSET(cUIControl, mGamma, 0x1C)
            CD2_OFFSET(cUIControl, mMusicVolume, 0x28)
            CD2_OFFSET(cUIControl, mSFXVolume, 0x34)
            CD2_OFFSET(cUIControl, mVoiceVolume, 0x40)
            CD2_OFFSET(cUIControl, mNPCVoiceVolume, 0x4C)
            CD2_OFFSET(cUIControl, mHudOpacity, 0x58)
            CD2_OFFSET(cUIControl, mDynamicSetting, 0x64)
            CD2_OFFSET(cUIControl, mOriginalVO, 0x6C)
            CD2_OFFSET(cUIControl, mSubtitles, 0x74)
            CD2_OFFSET(cUIControl, mDynamicRange, 0x7C)
            CD2_OFFSET(cUIControl, mInvertYAxis, 0x84)
            CD2_OFFSET(cUIControl, mLeftHanded, 0x8C)
            CD2_OFFSET(cUIControl, mNameFadeInTime, 0x94)
            CD2_OFFSET(cUIControl, mNameFadeOutTime, 0x98)
            CD2_OFFSET(cUIControl, mNameDisplayTime, 0x9C)
            CD2_OFFSET(cUIControl, mNamePlayerTargetedTime, 0xA0)
            CD2_OFFSET(cUIControl, mNameHeightAboveHead, 0xA4)
            CD2_OFFSET(cUIControl, m_AlphaDivider, 0xA8)
            CD2_OFFSET(cUIControl, m_ColourMultiplier, 0xAC)
            CD2_OFFSET(cUIControl, m_BlueTintMul, 0xB0)
            CD2_OFFSET(cUIControl, m_HexAlphaMul, 0xB4)
            CD2_OFFSET(cUIControl, m_LoadingScreenTime, 0xB8)
            CD2_OFFSET(cUIControl, m_DigiPrinterSpeed, 0xBC)
            CD2_OFFSET(cUIControl, m_DigiPrinterTipDelay, 0xC0)
            CD2_OFFSET(cUIControl, m_AutoSaveMinDisplayTime, 0xC4)
            CD2_OFFSET(cUIControl, m_TickerScrollSpeed, 0xC8)
            CD2_OFFSET(cUIControl, m_GammaLogoAlpha, 0xCC))
    };
}

#endif