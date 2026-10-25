
class cCrowdManager : public RWS::CAttributeHandler, public RWS::CEventHandler { /* Size=0x5c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001c */ private: cCrowdInfo mCrowds[2];
  /* 0x002c */ private: float mHourlyPhases[6];
  /* 0x0044 */ private: float mCrossoverTime;
  /* 0x0048 */ private: float mCurrentTime;
  /* 0x004c */ private: cCrowdManager::eHourlyPhase mCurrentPhase;
  /* 0x0050 */ private: bool mAllowCrossover;
  /* 0x0051 */ private: bool mTransitionToDay;
  /* 0x0052 */ private: bool mTransitionToNight;
  /* 0x0053 */ private: bool mStartImmediately;
  /* 0x0054 */ public: float m_fadeInLengthCiv;
  /* 0x0058 */ public: float m_fadeOutLengthCiv;
  public: static const char* pcCrowdManagerClassID;
  private: static cCrowdManager* mpInstance;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCrowdManager(const cCrowdManager&);
  public: cCrowdManager(const RWS::CAttributePacket&);
  public: virtual ~cCrowdManager();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: void Update();
  public: void UpdateTODPhases();
  public: void SetDayCrowd(bool);
  public: void SetNightCrowd(bool);
  public: void ResetSwitchoverTimes();
  public: bool HasTypeAppeared(eCrowdType) const;
  public: bool IsTypeAppearing(eCrowdType) const;
  public: bool HasTypeLeft(eCrowdType) const;
  public: bool IsTypeLeaving(eCrowdType) const;
  public: void SetInternalState(cCrowdInfo::eCrowdState, eManagedCrowds);
  public: cCrowdManager::eHourlyPhase CalcPhaseFromTOD() const;
  public: float TimeOfCrowdPhase(cCrowdManager::eHourlyPhase) const;
  public: float CrossoverTime() const;
  public: void SetPhaseFromTOD();
  public: cCrowdManager::eHourlyPhase RetCrowdPhase() const;
  public: bool CrossoverAllowed() const;
  public: bool AllowCrossover(bool);
  public: bool CrowdTypeActive(eCrowdType) const;
  public: bool AnythingDisappearing() const;
  public: bool AnyCrowdsActive() const;
  private: bool TimeoutPassed(float, float, float) const;
  public: cCrowdManager& operator=(const cCrowdManager&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static cCrowdManager* GetInstance();
  public: static bool Enabled();
};
