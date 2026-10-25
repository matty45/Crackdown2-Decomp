
class AI::cPilotRespawn : public AI::NPCBehaviour { /* Size=0x160 */
  /* 0x0000: fields for AI::NPCBehaviour */
  /* 0x0100 */ protected: unsigned char m_nState;
  /* 0x0101 */ protected: bool m_bHasDest;
  /* 0x0110 */ protected: Fun_Runtime::Vec3 m_vDest;
  /* 0x0120 */ protected: Kaim::CPath m_Path;
  /* 0x0148 */ private: float m_fWaitTime;
  /* 0x014c */ private: float m_fCurrentTimer;
  /* 0x0150 */ private: AI::cLogicalGraph* m_pLogicalGraph;
  /* 0x0154 */ private: Kaim::CSpatialGraph* m_pGlobalGraph;
  /* 0x0158 */ private: Kaim::CFindNearestData* m_pGlobalGraphFindNearestData;
  public: static const char* pcPilotRespawnClassID;
  public: static const char m_cPilotRespawn_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcPilotRespawnClass;
  private: static bool m_bRenderPath;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: cPilotRespawn(const AI::cPilotRespawn&);
  public: cPilotRespawn(GOM::cObjectPrototype*);
  public: virtual unsigned char GetStateReplicationInfo() const;
  public: virtual void OnEnterReplicatedState(unsigned char);
  public: virtual void OnEnter();
  public: virtual void OnReplicatedEnter(unsigned char);
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void Update(float);
  public: void Finished(bool);
  public: void DemoteDelivery();
  public: bool ComputePathBetween(const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&);
  public: void SetDestination(const Fun_Runtime::Vec3&);
  public: void RenderDebugPath();
  public: virtual void RenderDebugInfo();
  protected: void UpdateAwaiting();
  protected: void UpdateInbound();
  protected: void UpdateOutbound();
  protected: void EnterAwaiting();
  protected: void EnterInbound();
  protected: void EnterOutbound();
  protected: void ChangeState(char);
  protected: void EnterState(char);
  protected: void ExitState(char);
  private: AI::cPilotRespawn::cPilotRespawnPrototype& RetPrototype();
  public: virtual ~cPilotRespawn();
  public: AI::cPilotRespawn& operator=(const AI::cPilotRespawn&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static void ToggleRenderDebugPaths();
};
