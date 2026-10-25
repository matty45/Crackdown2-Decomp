
class AI::cCellStrongholdMission : public AI::cMission { /* Size=0x410 */
  /* 0x0000: fields for AI::cMission */
  /* 0x03c0 */ private: float m_fCurrResetTime;
  /* 0x03c4 */ private: float m_fResetTimer;
  /* 0x03c8 */ private: GameManagement::cCampaignPlayerSpawnGroup* m_pSpawnGroup;
  /* 0x03cc */ private: VEHICLE_CONTROL::cVehicleCollectionZone* m_pCollectionZone;
  /* 0x03d0 */ private: ZoneManager::cPlayerTriggerBase* m_pContainmentZone;
  /* 0x03e0 */ private: Fun_Runtime::cVectorip<AI::cMission *,5> m_vMissions;
  public: static const char m_cCellStrongholdMission_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcCellStrongholdMissionClass;
  public: static const char* pcCellStrongholdMissionClassID;
  private: static bool m_bDebugInfo;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCellStrongholdMission(const AI::cCellStrongholdMission&);
  public: cCellStrongholdMission(const RWS::CAttributePacket&);
  public: virtual ~cCellStrongholdMission();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void TickUpdate(float);
  public: virtual void Activate();
  public: virtual void Deactivate();
  public: virtual void GetSaveStateForMissionState(unsigned char&, unsigned char&);
  public: virtual void OnLeaveGlobalMissionState(AI::cMission::etGlobalMissionState);
  public: virtual void OnEnterGlobalMissionState(AI::cMission::etGlobalMissionState);
  public: virtual void ResetMission();
  public: virtual void OnEnterMissionState(unsigned char);
  public: virtual void OnLeaveMissionState(unsigned char);
  public: virtual void CalculateLOD(int);
  public: ZoneManager::cPlayerTriggerBase* RetContainmentZone();
  public: bool IsActive();
  public: void ChildComplete(AI::cTacticalObjective*);
  public: void ChildReset(AI::cTacticalObjective*);
  public: void AddVOAMessage(const wchar_t*);
  public: void AddMapMarkers();
  public: void RemoveMapMarkers(AI::cTacticalObjective*);
  public: unsigned int RetNumCompletedTO();
  public: unsigned int RetTotalNumTO();
  public: virtual bool IsLocalPlayerNearby() const;
  public: virtual void RenderDebugPage(int&, int&);
  public: virtual bool DebugPageEnter();
  public: virtual const char* RetMenuText(unsigned char);
  public: void RenderDebugInfo();
  protected: void ExitState();
  protected: void EnterState(AI::cCellStrongholdMission::eCSMState);
  protected: void Update();
  protected: void AddVOA();
  public: AI::cCellStrongholdMission& operator=(const AI::cCellStrongholdMission&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static void ShowDebug();
};
