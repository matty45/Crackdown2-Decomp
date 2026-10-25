
class Prop::cHingedSpawnDoor : public Prop::cHingedProp, public AI::cPathObjectOwner { /* Size=0xf40 */
  /* 0x0000: fields for Prop::cHingedProp */
  /* 0x0f20: fields for AI::cPathObjectOwner */
  /* 0x0f38 */ protected: bool m_bIsDynamicObs;
  public: static const char m_cHingedSpawnDoor_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcHingedSpawnDoorClass;
  public: static const char* pcHingedSpawnDoorClassID;
  protected: static Fun_Runtime::cStateNameRegistrar STATE_SpawnDoor_Registrar;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cHingedSpawnDoor(const Prop::cHingedSpawnDoor&);
  public: cHingedSpawnDoor(GOM::cObjectPrototype*);
  public: virtual ~cHingedSpawnDoor();
  public: virtual void TickUpdate(float);
  public: virtual bool CreatePathObject();
  public: virtual void DestroyPathObject();
  public: virtual void OnEnterGraph(AI::cStreamingGraph*);
  public: virtual void OnExitGraph(AI::cStreamingGraph*);
  public: virtual unsigned char GetCost(Kaim::CEntity*, Kaim::CEdge&, Kaim::CConstraint&, float&);
  public: virtual unsigned char CanGoFromTo(Kaim::CEntity&, const Kaim::CVector&, const Kaim::CVector&);
  public: virtual bool IsAIEntityOwner(Kaim::CEntity*);
  public: virtual bool ShouldHaveObjectPathPhantom();
  public: Prop::cHingedSpawnDoor::cHingedSpawnDoorPrototype* RetHingedSDoorPrototype() const;
  protected: virtual Fun_Runtime::State* RetSTATE_SpawnDoor() const;
  protected: virtual Fun_Runtime::State* RetSTATE_SpawnDoor();
  protected: virtual void GoToInitialState();
  protected: virtual void GoToSpawnDoorState();
  public: virtual bool IsInSpawnDoorState();
  public: Prop::cHingedSpawnDoor& operator=(const Prop::cHingedSpawnDoor&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  protected: static Fun_Runtime::State* StaticRetSTATE_SpawnDoor();
};
