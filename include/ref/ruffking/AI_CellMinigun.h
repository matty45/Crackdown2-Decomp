
class AI::CellMinigun : public AI::NPCArmedBehaviour, public cNPCArmourySetup { /* Size=0x130 */
  /* 0x0000: fields for AI::NPCArmedBehaviour */
  /* 0x0130: fields for cNPCArmourySetup */
  public: static const char* pCellMinigunClassID;
  public: static const char m_CellMinigun_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pCellMinigunClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: CellMinigun(const AI::CellMinigun&);
  public: CellMinigun(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void OnDetectedEnemy(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnAttacked(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnHeardSuspiciousSound(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnAmbient();
  public: virtual void OnAmbient(const Fun_Runtime::cVectorip<AI::cAnimParams *,10>&, float);
  public: virtual void Update(float);
  public: virtual void OnIdle();
  public: virtual void OnInvestigating();
  public: virtual void OnPatrolling();
  public: virtual void OnAttacking();
  public: virtual void OnCover();
  public: virtual void OnRetreating();
  public: virtual void OnReactResupply();
  public: virtual void OnDrive();
  public: virtual void ChangeMainState(AI::NPCArmedBehaviour::eState);
  public: virtual void RenderDebugInfo();
  public: virtual void SetReactResupplyPoint(const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&);
  protected: void OnEnterState(AI::NPCArmedBehaviour::eState);
  protected: void OnExitState(AI::NPCArmedBehaviour::eState);
  protected: const AI::cPatrolRoute* RetDefaultPatrolRoute();
  protected: void ClearTargetAndEnemy();
  protected: AI::CellMinigunPrototype& RetCellMinigunPrototype();
  public: virtual ~CellMinigun();
  public: AI::CellMinigun& operator=(const AI::CellMinigun&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
