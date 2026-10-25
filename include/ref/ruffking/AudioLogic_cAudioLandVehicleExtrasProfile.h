
class AudioLogic::cAudioLandVehicleExtrasProfile : public AudioLogic::cAudioBaseProfile { /* Size=0x170 */
  /* 0x0000: fields for AudioLogic::cAudioBaseProfile */
  /* 0x0044 */ public: AudioEngine::cAudioGraph m_TakeoffRPMVsTime;
  /* 0x0080 */ public: AudioEngine::cAudioGraph m_GearDisengageRPMVsTime;
  /* 0x00bc */ public: AudioEngine::cAudioGraph m_GearEngageRPMVsTime;
  /* 0x00f8 */ public: AudioEngine::cAudioGraph m_GearDisengageLoadVsTime;
  /* 0x0134 */ public: AudioEngine::cAudioGraph m_GearEngageLoadVsTime;
  public: static const char m_cAudioLandVehicleExtrasProfile_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAudioLandVehicleExtrasProfileClass;
  public: static const char* pcAudioLandVehicleExtrasProfileClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAudioLandVehicleExtrasProfile(const AudioLogic::cAudioLandVehicleExtrasProfile&);
  public: cAudioLandVehicleExtrasProfile(const RWS::CAttributePacket&);
  public: virtual ~cAudioLandVehicleExtrasProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: AudioLogic::cAudioLandVehicleExtrasProfile& operator=(const AudioLogic::cAudioLandVehicleExtrasProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
