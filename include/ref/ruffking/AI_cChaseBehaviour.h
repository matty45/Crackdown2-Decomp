
class AI::cChaseBehaviour : public AI::NPCBehaviourSM, public cNPCArmourySetup { /* Size=0x140 */
  /* 0x0000: fields for AI::NPCBehaviourSM */
  /* 0x0110: fields for cNPCArmourySetup */
  /* 0x0110 */ protected: AI::cAIEventSubscription* m_pVehicleCollisionSub;
  /* 0x0114 */ protected: float m_fTimeFleeing;
  /* 0x0120 */ protected: Fun_Runtime::Vec3 m_vFleeDangerPosition;
  /* 0x0130 */ protected: unsigned int m_nInitialEdge;
  /* 0x0134 */ protected: bool m_bFollowMode;
  /* 0x0135 */ private: bool m_bTargetLocked;
  public: static const char* pcChaseBehaviourClassID;
  public: static const char m_cChaseBehaviour_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcChaseBehaviourClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: cChaseBehaviour(const AI::cChaseBehaviour&);
  public: cChaseBehaviour(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void OnEnterReplicatedState(unsigned char);
  public: virtual void EnterIdle();
  public: virtual void EnterChasing();
  public: virtual void EnterFollow();
  public: virtual void EnterDriveFleeing();
  public: virtual void EnterHolding();
  public: virtual void EnterDrivingTraffic();
  public: virtual void PreUpdateAllStates(float);
  public: virtual void UpdateVehicleSubs();
  public: virtual void Notify(AI::cAIEvent*);
  public: virtual void OnUpdateIdle(float);
  public: virtual void OnUpdateChasing(float);
  public: virtual void OnUpdateFollow(float);
  public: virtual void OnUpdateDriveFleeing(float);
  public: virtual void OnUpdateHolding(float);
  public: virtual void OnUpdateDrivingTraffic(float);
  public: virtual cNonGameBase* GetSpawnedAmbientTarget();
  public: virtual void OnDetectedEnemy(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnHeardSuspiciousSound(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: void SetFollowMode(bool);
  public: void SetAmbientTrafficSpawnEdge(unsigned int);
  public: bool IsTargetLocked() const;
  public: void LockTarget(bool);
  public: void SetTargetAndEnemy(CHARACTER::cCharacter*);
  public: void ClearTargetAndEnemy();
  public: virtual void RenderDebugInfo();
  protected: AI::cChaseBehaviour::cChaseBehaviourPrototype& RetChasePrototype();
  protected: virtual AI::IBehaviourState* GetState(unsigned char);
  protected: virtual unsigned int RetTargetingFlags() const;
  protected: bool TryBindAmbientTarget();
  protected: virtual void OnTargetLost();
  protected: virtual void OnTargetAcquired();
  public: virtual ~cChaseBehaviour();
  public: AI::cChaseBehaviour& operator=(const AI::cChaseBehaviour&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
