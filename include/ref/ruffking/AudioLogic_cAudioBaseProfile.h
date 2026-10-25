
class AudioLogic::cAudioBaseProfile : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy { /* Size=0x44 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001c: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c */ public: bool m_bReset;
  /* 0x0020 */ protected: Fun_Runtime::cString m_sProfileName;
  /* 0x003c */ protected: RWS::CEventId m_Msg_Return_Audio_Self;
  public: static const char* pcAudioBaseProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAudioBaseProfile(const AudioLogic::cAudioBaseProfile&);
  public: cAudioBaseProfile(const RWS::CAttributePacket&);
  public: virtual ~cAudioBaseProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual void ProcessEntity(AudioEngine::cEntity*);
  public: AudioLogic::cAudioBaseProfile* GetAudioProfile(const char*);
  public: AudioLogic::cAudioBaseProfile& operator=(const AudioLogic::cAudioBaseProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
