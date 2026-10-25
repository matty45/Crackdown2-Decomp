
class AudioLogic::cAudioLandVehicleProfile : public AudioLogic::cAudioBaseProfile { /* Size=0x60 */
  /* 0x0000: fields for AudioLogic::cAudioBaseProfile */
  /* 0x0044 */ public: AudioLogic::cAudioLandVehicleExtrasProfile* m_pExtrasProfile;
  /* 0x0048 */ public: float m_fFakeRevPeakRPM;
  /* 0x004c */ public: float m_fFakeRevStartDelay;
  /* 0x0050 */ public: float m_fFakeRevRampUp;
  /* 0x0054 */ public: float m_fFakeRevRampDown;
  /* 0x0058 */ public: float m_fAudioRPMMin;
  /* 0x005c */ public: float m_fAudioRPMMax;
  public: static const char m_cAudioLandVehicleProfile_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAudioLandVehicleProfileClass;
  public: static const char* pcAudioLandVehicleProfileClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAudioLandVehicleProfile(const AudioLogic::cAudioLandVehicleProfile&);
  public: cAudioLandVehicleProfile(const RWS::CAttributePacket&);
  public: virtual ~cAudioLandVehicleProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: AudioLogic::cAudioLandVehicleProfile& operator=(const AudioLogic::cAudioLandVehicleProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
