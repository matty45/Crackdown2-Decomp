
class AI::PedestrianInjured : public AI::PedestrianGuard { /* Size=0x160 */
  /* 0x0000: fields for AI::PedestrianGuard */
  public: static const char* pPedestrianInjuredClassID;
  public: static const char m_PedestrianInjured_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pPedestrianInjuredClass;
  private: static Fun_Runtime::cRandGen m_sRandomGenerator;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: PedestrianInjured(const AI::PedestrianInjured&);
  public: PedestrianInjured(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: void EnterPIFlee();
  protected: virtual void EnterState(char);
  protected: virtual void ExitState(char);
  private: AI::cPedestrianBase::cPedestrianBasePrototype& RetPedPrototype();
  public: virtual ~PedestrianInjured();
  public: AI::PedestrianInjured& operator=(const AI::PedestrianInjured&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
