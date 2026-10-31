#include "UI/cUIControl.h"

#include "rws/classfactory.h"

namespace UI
{
    static const char *const pcUIControlClassID = "cUIControl";

    static void ApplyGamma(int) {}
    static void ApplyMusicVolume(int) {}
    static void ApplySFXVolume(int) {}
    static void ApplyVoiceVolume(int) {}
    static void ApplyNPCVoiceVolume(int) {}
    static void ApplyHUDOpacity(int) {}
    static void ApplyDynamicSetting(char) {}
    static void ApplyVOSetting(bool) {}
    static void ApplySubtitles(bool) {}
    static void ApplyDynamicRange(bool) {}
    static void ApplyInvertAxis(bool) {}
    static void ApplyLeftHanded(bool) {}

    const char *cUIControl::RetClassName() const
    {
        return pcUIControlClassID;
    }

    cUIControl::cUIControl()
    {
        mGamma.mApplyFunc = ApplyGamma;
        mMusicVolume.mApplyFunc = ApplyMusicVolume;
        mSFXVolume.mApplyFunc = ApplySFXVolume;
        mVoiceVolume.mApplyFunc = ApplyVoiceVolume;
        mNPCVoiceVolume.mApplyFunc = ApplyNPCVoiceVolume;
        mHudOpacity.mApplyFunc = ApplyHUDOpacity;
        mDynamicSetting.mApplyFunc = ApplyDynamicSetting;
        mOriginalVO.mApplyFunc = ApplyVOSetting;
        mSubtitles.mApplyFunc = ApplySubtitles;
        mDynamicRange.mApplyFunc = ApplyDynamicRange;
        mInvertYAxis.mApplyFunc = ApplyInvertAxis;
        mLeftHanded.mApplyFunc = ApplyLeftHanded;

        m_pInstance = this;

        mNameFadeInTime = 0.2f;
        mNameFadeOutTime = 2.0f;
        mNameDisplayTime = 5.0f;
        mNamePlayerTargetedTime = 2.0f;
        mNameHeightAboveHead = 16.0f;
        m_DigiPrinterSpeed = 60.0f;
        m_DigiPrinterTipDelay = 0.2f;
        m_AutoSaveMinDisplayTime = 0.9f;
        m_GammaLogoAlpha = 50;
    }

    cUIControl::~cUIControl()
    {
        m_pInstance = 0;
    }

    RWS::CAttributeHandler *cUIControl::MakeNew(const RWS::CAttributePacket &packet, bool bGlobal)
    {
        return new cUIControl();
    }

    void cUIControl::HandleAttributes(const RWS::CAttributePacket &attr)
    {
    }

    void cUIControl::Load(SaveGame::cLoadStream *pStream)
    {
    }

    void cUIControl::Save(SaveGame::cSaveStream *pStream)
    {
    }

    void cUIControl::ApplyOptions()
    {
        mGamma.mApplyFunc(mGamma.mCurrent);
        mMusicVolume.mApplyFunc(mMusicVolume.mCurrent);
        mSFXVolume.mApplyFunc(mSFXVolume.mCurrent);
        mVoiceVolume.mApplyFunc(mVoiceVolume.mCurrent);
        mNPCVoiceVolume.mApplyFunc(mNPCVoiceVolume.mCurrent);
        mDynamicSetting.mApplyFunc(mDynamicSetting.mCurrent);
        mOriginalVO.mApplyFunc(mOriginalVO.mCurrent);
        mSubtitles.mApplyFunc(mSubtitles.mCurrent);
        mDynamicRange.mApplyFunc(mDynamicRange.mCurrent);
        mHudOpacity.mApplyFunc(mHudOpacity.mCurrent);
        mInvertYAxis.mApplyFunc(mInvertYAxis.mCurrent);
        mLeftHanded.mApplyFunc(mLeftHanded.mCurrent);
    }

    void cUIControl::RestoreDefaultOptions()
    {
    }

    void cUIControl::OverrideDefaultSubtitlesBasedOnLanguage()
    {
    }

    cUIControl *cUIControl::Instance()
    {
        return m_pInstance;
    }

    float cUIControl::DigiPrinterSpeed() const { return m_DigiPrinterSpeed; }
    float cUIControl::DigiPrinterTipDelay() const { return m_DigiPrinterTipDelay; }
    float cUIControl::AutoSaveMinDisplayTime() const { return m_AutoSaveMinDisplayTime; }
    int cUIControl::GammaLogoAlpha() const { return m_GammaLogoAlpha; }
    float cUIControl::TickerScrollSpeed() const { return m_TickerScrollSpeed; }

    cUIControl *cUIControl::m_pInstance = 0;

    static RWS::CClassFactory::CRegistrar cUIControlRegistrar(
        "cUIControl", cUIControl::MakeNew, 0xD0, false);
}