
class UI::cUIControl : public RWS::CAttributeHandler, public SaveGame::cLoadSaveObject { /* Size=0xd0 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for SaveGame::cLoadSaveObject */
  /* 0x001c */ public: UI::cOptionItem<int> mGamma;
  /* 0x0028 */ public: UI::cOptionItem<int> mMusicVolume;
  /* 0x0034 */ public: UI::cOptionItem<int> mSFXVolume;
  /* 0x0040 */ public: UI::cOptionItem<int> mVoiceVolume;
  /* 0x004c */ public: UI::cOptionItem<int> mNPCVoiceVolume;
  /* 0x0058 */ public: UI::cOptionItem<int> mHudOpacity;
  /* 0x0064 */ public: UI::cOptionItem<char> mDynamicSetting;
  /* 0x006c */ public: UI::cOptionItem<bool> mOriginalVO;
  /* 0x0074 */ public: UI::cOptionItem<bool> mSubtitles;
  /* 0x007c */ public: UI::cOptionItem<bool> mDynamicRange;
  /* 0x0084 */ public: UI::cOptionItem<bool> mInvertYAxis;
  /* 0x008c */ public: UI::cOptionItem<bool> mLeftHanded;
  /* 0x0094 */ public: float mNameFadeInTime;
  /* 0x0098 */ public: float mNameFadeOutTime;
  /* 0x009c */ public: float mNameDisplayTime;
  /* 0x00a0 */ public: float mNamePlayerTargetedTime;
  /* 0x00a4 */ public: float mNameHeightAboveHead;
  /* 0x00a8 */ public: float m_AlphaDivider;
  /* 0x00ac */ public: float m_ColourMultiplier;
  /* 0x00b0 */ public: float m_BlueTintMul;
  /* 0x00b4 */ public: float m_HexAlphaMul;
  /* 0x00b8 */ public: float m_LoadingScreenTime;
  /* 0x00bc */ private: float m_DigiPrinterSpeed;
  /* 0x00c0 */ private: float m_DigiPrinterTipDelay;
  /* 0x00c4 */ private: float m_AutoSaveMinDisplayTime;
  /* 0x00c8 */ private: float m_TickerScrollSpeed;
  /* 0x00cc */ private: int m_GammaLogoAlpha;
  public: static const char* pcUIControlClassID;
  private: static UI::cUIControl* m_pInstance;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cUIControl(const UI::cUIControl&);
  public: cUIControl(const RWS::CAttributePacket&);
  public: virtual ~cUIControl();
  public: float DigiPrinterSpeed() const;
  public: float DigiPrinterTipDelay() const;
  public: float AutoSaveMinDisplayTime() const;
  public: int GammaLogoAlpha() const;
  public: float TickerScrollSpeed() const;
  public: void ApplyOptions();
  public: void RestoreDefaultOptions();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void Load(SaveGame::cLoadStream*);
  public: virtual void Save(SaveGame::cSaveStream*);
  private: void OverrideDefaultSubtitlesBasedOnLanguage();
  public: UI::cUIControl& operator=(const UI::cUIControl&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static UI::cUIControl* Instance();
};
