
class AI::CellRocket : public AI::NPCArmedBehaviour, public cNPCArmourySetup { /* Size=0x150 */
  /* 0x0000: fields for AI::NPCArmedBehaviour */
  /* 0x0130: fields for cNPCArmourySetup */
  /* 0x0130 */ private: AI::cAIEventSubscription* m_nReloadSub;
  /* 0x0140 */ private: Fun_Runtime::Vec3 m_vRetreatPoint;
  public: static const char* pCellRocketClassID;
  public: static const char m_CellRocket_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pCellRocketClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: CellRocket(const AI::CellRocket&);
  public: CellRocket(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void OnDetectedEnemy(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnAttacked(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnHeardSuspiciousSound(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnCharacterEvent(unsigned char, unsigned char, unsigned char);
  public: virtual void OnAnimationEvent(unsigned char, int, short);
  public: virtual void Notify(AI::cAIEvent*);
  public: virtual void ChangeMainState(AI::NPCArmedBehaviour::eState);
  public: virtual void OnAmbient();
  public: virtual void OnAmbient(const Fun_Runtime::cVectorip<AI::cAnimParams *,10>&, float);
  public: virtual void OnIdle();
  public: virtual void OnInvestigating();
  public: virtual void OnPatrolling();
  public: virtual void OnAttacking();
  public: virtual void OnCover();
  public: virtual void OnRetreating();
  public: virtual void OnReactResupply();
  public: virtual void OnDrive();
  public: virtual void EnterSubStateAttacking();
  public: virtual void EnterSubStateInvestigating();
  public: virtual void EnterSubStateAmbient();
  public: virtual void ExitSubStateAttacking();
  public: virtual void EnterSubStateReactResupply();
  public: virtual void RenderDebugInfo();
  protected: void Idle();
  protected: void OnAnimFinished(bool);
  protected: AI::CellRocketPrototype& RetCellRocketPrototype();
  protected: void TargetDistanceCheck();
  protected: bool NeedReload();
  public: virtual ~CellRocket();
  public: AI::CellRocket& operator=(const AI::CellRocket&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
