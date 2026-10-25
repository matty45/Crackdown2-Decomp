
class AI::CellTurret : public AI::NPCArmedBehaviour, public cNPCArmourySetup { /* Size=0x140 */
  /* 0x0000: fields for AI::NPCArmedBehaviour */
  /* 0x0130: fields for cNPCArmourySetup */
  /* 0x0130 */ private: AI::cAIEventSubscription* m_nTargetDiedSub;
  /* 0x0134 */ private: Fun_Runtime::cList<Activity::cSpawnPointBase *,Fun_Runtime::cAllocator<Activity::cSpawnPointBase *,39,&AI::CellTurret::tTurrets_FL> > m_lAvailableTurrets;
  public: static const char* pCellTurretClassID;
  public: static const char m_CellTurret_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pCellTurretClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: CellTurret(const AI::CellTurret&);
  public: CellTurret(GOM::cObjectPrototype*);
  public: void ClearTurrets();
  public: void AddTurret(Activity::cSpawnPointBase*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void OnDetectedEnemy(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnAttacked(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnHeardSuspiciousSound(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnCharacterEvent(unsigned char, unsigned char, unsigned char);
  public: virtual void Notify(AI::cAIEvent*);
  public: virtual void Update(float);
  public: virtual void OnReplicatedEnter(unsigned char);
  public: virtual void EnterSubStateInvestigating();
  public: virtual void OnIdle();
  public: virtual void OnInvestigating();
  public: virtual void OnPatrolling();
  public: virtual void OnAttacking();
  public: virtual void OnCover();
  public: virtual void OnAmbient();
  public: virtual void OnDrive();
  public: virtual void RenderDebugInfo();
  protected: void OnAnimFinished(const bool);
  protected: AI::CellTurretPrototype& RetTurretPrototype();
  public: virtual ~CellTurret();
  public: AI::CellTurret& operator=(const AI::CellTurret&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  private: static Fun_Runtime::cFileLine tTurrets_FL();
};
