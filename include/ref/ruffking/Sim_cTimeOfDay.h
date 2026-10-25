
class Sim::cTimeOfDay : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy, public GDb::cDebugPageHandler, public SaveGame::cLoadSaveObject, public cReplicatedClass, public Network::cNetRoleObject { /* Size=0x2c0 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x0288: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c: fields for GDb::cDebugPageHandler */
  /* 0x0040: fields for SaveGame::cLoadSaveObject */
  /* 0x0050: fields for cReplicatedClass */
  /* 0x0280: fields for Network::cNetRoleObject */
  /* 0x0288 */ private: float m_fPhase;
  /* 0x028c */ private: float m_fOldPhase;
  /* 0x0290 */ private: float m_fLastPhaseStep;
  /* 0x0294 */ private: float m_fPeriod;
  /* 0x0298 */ private: bool m_bActive;
  /* 0x0299 */ private: bool m_bForceUpdatePhaseStep;
  /* 0x029c */ private: float m_fDawn;
  /* 0x02a0 */ private: float m_fDusk;
  /* 0x02a4 */ private: float m_fThreeAM;
  /* 0x02a8 */ private: float m_fNineAM;
  /* 0x02ac */ private: float m_fThreePM;
  /* 0x02b0 */ private: float m_fNinePM;
  /* 0x02b4 */ private: Fun_Runtime::cMultiSet<Sim::cTODNotification,std::less<Sim::cTODNotification>,Fun_Runtime::cAllocator<Sim::cTODNotification,3,&Sim::cTimeOfDay::tTODs_FL> > m_TODs;
  private: static Sim::cTimeOfDay* ms_pInstance;
  public: static const char* pcTimeOfDayClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTimeOfDay(const Sim::cTimeOfDay&);
  public: cTimeOfDay(const RWS::CAttributePacket&);
  public: virtual ~cTimeOfDay();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual bool IsSequential() const;
  public: void TickUpdate(float);
  public: void SetPhase(float);
  public: float RetPhase();
  public: float RetOldPhase();
  public: void SetForceUpdatePhaseStep(bool);
  public: bool RetForceUpdatePhaseStep();
  public: float RetLastPhaseStep();
  public: float RetPhaseDelta(float, float);
  public: float RetPhaseDelta();
  public: void FixupPhase(float, float);
  public: void StepPhase(float);
  public: float RetDawnPhase();
  public: float RetDuskPhase();
  public: void SetPeriod(float);
  public: float RetPeriod();
  public: void Pause(bool);
  public: void UnPause();
  public: bool IsPaused();
  public: bool IsDayTime();
  public: bool IsNightTime();
  public: unsigned int AddTimeOfDayEvent(float, bool);
  public: bool RemoveTimeOfDayEvent(unsigned int);
  public: Sim::cTODNotification* RetTimeOfDayEvent(unsigned int);
  public: virtual void Load(SaveGame::cLoadStream*);
  public: virtual void Save(SaveGame::cSaveStream*);
  public: virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
  public: virtual unsigned int GetMaxReplicatedFields() const;
  public: virtual unsigned int GetNumObjectIDBits() const;
  public: virtual void SetPingedFieldStatesForNode(unsigned char);
  public: virtual void ReplicateInitialFields();
  public: virtual void ReplicateFieldsWrite();
  public: virtual void ReplicateFieldsRead();
  public: void ForcePhaseReplication();
  public: virtual bool IsOwnedLocally();
  public: void OnHostMigrated(unsigned char);
  private: bool IsPhaseDayTime(float);
  private: bool IsPhaseNightTime(float);
  private: void TriggerDusk();
  private: void TriggerDawn();
  private: virtual void RenderDebugPage(int, int);
  public: Sim::cTimeOfDay& operator=(const Sim::cTimeOfDay&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static Sim::cTimeOfDay* RetTimeOfDayManager();
  private: static Fun_Runtime::cFileLine tTODs_FL();
};
