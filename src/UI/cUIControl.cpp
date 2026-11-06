#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "UI/cUIControl.h"
#include "UI/UI.h"
#include "rws/classfactory.h"
#include "Audio/GameAudio.h"
#include "Session/GameSession.h"
#include "XLip/XLipManager.h"
#include "GameRenderer/GammaRamp.h"
#include "Input/cGameControlManager.h"
#include "SaveGame/cSaveGameManager.h"
#include "cd2/memory.h"

namespace UI
{
    static const char *const pcUIControlClassID = "cUIControl";

    static void ApplyGamma(int value)
    {
        GameRenderer::SetGammaRamp((32.0f - static_cast<float>(value - 1)) * 2.0f * 0.03125f);
    }
    static void ApplyMusicVolume(int value) { Audio::SetMusicVolume(static_cast<float>(value)); }
    static void ApplySFXVolume(int value) { Audio::SetSFXVolume(static_cast<float>(value)); }
    static void ApplyVoiceVolume(int value) { Audio::SetVoiceVolume(static_cast<float>(value)); }
    static void ApplyNPCVoiceVolume(int value) { Audio::SetNPCVoiceVolume(static_cast<float>(value)); }
    static void ApplyHUDOpacity(int value)
    {
        SetHUDOpacity(static_cast<int>(static_cast<float>(value) * 3.125f));
    }
    static void ApplyDynamicSetting(char value)
    {
        Audio::SetDynamicRange(value, cUIControl::m_pInstance->mDynamicRange.mCurrent);
    }
    static void ApplyVOSetting(bool value)
    {
        XLip::XLipManager::GetInstance()->SetUseOriginalAudio(value);
    }
    static void ApplySubtitles(bool value) { Session::SetUsingSubtitles(value); }
    static void ApplyDynamicRange(bool value)
    {
        Audio::SetDynamicRange(cUIControl::m_pInstance->mDynamicSetting.mCurrent, value);
    }
    static void ApplyInvertAxis(bool value) { Session::SetControllerInvert(value); }
    static void ApplyLeftHanded(bool value)
    {
        Input::cGameControlManager *manager = Input::cGameControlManager::RetInstancePtr();
        Input::cGameController *controller = manager->RetPrimaryController();
        if (controller)
            controller->SetActionMap(manager->RetSPActionMap(value ? 1 : 0), 0);
    }

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
        m_AutoSaveMinDisplayTime = 3.0f;
        m_GammaLogoAlpha = 50;
        SaveGame::Register(SaveGame::eSaveType_Options, SaveGame::eSaveChunk_Options, this);
    }

    // CD2 inlines this body into the scalar deleting destructor.
    inline cUIControl::~cUIControl()
    {
        // CD2 retains the save manager before clearing the UI singleton.
        SaveGame::cSaveGameManager *manager = g_pSaveGameManager;
        m_pInstance = 0;
        manager->Unregister(SaveGame::eSaveType_Options, SaveGame::eSaveChunk_Options, this);
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
