
class Audio::cVOALine : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0xf0 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ private: Fun_Runtime::cStringc m_strDynamicDialogueEvent;
  /* 0x0034 */ private: Audio::cVOALine::etMessageType m_eMessageType;
  /* 0x0038 */ private: unsigned int m_nMessageText;
  /* 0x003c */ private: UI::HUD::ControlHelper::eControlIcon m_eControlIcon;
  /* 0x0040 */ private: int m_nWeight;
  /* 0x0044 */ private: Fun_Runtime::cVector<AI::cMissionTier const *,Fun_Runtime::cAllocator<AI::cMissionTier const *,73,&Audio::cVOALine::tMissionTierList_FL> > m_MissionTiers;
  /* 0x0054 */ private: Audio::etVOALineGameMode m_eGameMode;
  /* 0x0058 */ private: Audio::etVOALineLeadershipStatus m_eLeadershipStatus;
  /* 0x005c */ private: Audio::etVOALineBeaconsActivated m_eBeaconsActivated;
  /* 0x0060 */ private: Audio::etVOALineBoolean m_aeBooleans[36];
  public: static const char m_cVOALine_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcVOALineClass;
  public: static const char* pcVOALineClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cVOALine(const Audio::cVOALine&);
  public: cVOALine(const RWS::CAttributePacket&);
  public: virtual ~cVOALine();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: const char* RetDynamicDialogueEvent() const;
  public: int RetWeight() const;
  public: bool IsSuitable(const Audio::cVOAGameState&) const;
  public: void Play() const;
  public: Audio::cVOALine& operator=(const Audio::cVOALine&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  private: static Fun_Runtime::cFileLine tMissionTierList_FL();
};
