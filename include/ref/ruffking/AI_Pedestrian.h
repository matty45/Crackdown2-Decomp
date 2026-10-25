
class AI::Pedestrian : public AI::cPedestrianBase { /* Size=0x150 */
  /* 0x0000: fields for AI::cPedestrianBase */
  public: static const char* pPedestrianClassID;
  public: static const char m_Pedestrian_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pPedestrianClass;
  protected: static bool ms_bDisplayPedZoneLink;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: Pedestrian(const AI::Pedestrian&);
  public: Pedestrian(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void UpdateAmbient();
  public: virtual void Update(float);
  protected: virtual void EnterState(char);
  protected: virtual void ExitState(char);
  protected: virtual bool SpawnZoneIsCleared();
  protected: void DebugRenderCrowdZoneLink();
  private: AI::cPedestrianBase::cPedestrianBasePrototype& RetPedPrototype();
  public: virtual ~Pedestrian();
  public: AI::Pedestrian& operator=(const AI::Pedestrian&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static void SetPedestrianZoneLinkDebugEnabled(bool);
  public: static bool IsPedestrianZoneLinkDebugEnabled();
};
