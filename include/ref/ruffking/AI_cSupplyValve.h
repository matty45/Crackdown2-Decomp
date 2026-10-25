
class AI::cSupplyValve : public Prop::cSpinningProp { /* Size=0xec0 */
  /* 0x0000: fields for Prop::cSpinningProp */
  public: static const char m_cSupplyValve_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcSupplyValveClass;
  public: static const char* pcSupplyValveClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSupplyValve(const AI::cSupplyValve&);
  public: cSupplyValve(GOM::cObjectPrototype*);
  public: virtual ~cSupplyValve();
  public: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  public: virtual void SetSpawner(Activity::cSpawnPointBase*);
  public: virtual float TakeDamage(Damage::cDamage&);
  public: virtual void OnValveBroken();
  public: virtual bool IsUsable() const;
  public: virtual bool CanBeginInteraction() const;
  public: virtual void OnBeginInteraction();
  public: virtual void OnReceivedInteractionEvent1();
  public: virtual void OnReceivedInteractionEvent2();
  public: virtual bool IsInInteractablePosition(Fun_Runtime::Mtx&);
  public: void SpawnBreakOffVFX();
  public: virtual unsigned int RetInteractionAnimID() const;
  protected: virtual bool CanGoToInitialState() const;
  public: AI::cSupplyValve& operator=(const AI::cSupplyValve&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
