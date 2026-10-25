
class Prop::cSlidingDoor : public Prop::cPrismaticProp, public AI::cPathObjectOwner { /* Size=0xf60 */
  /* 0x0000: fields for Prop::cPrismaticProp */
  /* 0x0f40: fields for AI::cPathObjectOwner */
  public: static const char m_cSlidingDoor_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcSlidingDoorClass;
  public: static const char* pcSlidingDoorClassID;
  protected: static Fun_Runtime::cStateNameRegistrar STATE_Min_Registrar;
  protected: static Fun_Runtime::cStateNameRegistrar STATE_Max_Registrar;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSlidingDoor(const Prop::cSlidingDoor&);
  public: cSlidingDoor(GOM::cObjectPrototype*);
  public: virtual ~cSlidingDoor();
  public: virtual void TickUpdate(float);
  public: virtual bool CreatePathObject();
  public: virtual void DestroyPathObject();
  public: virtual void OnEnterGraph(AI::cStreamingGraph*);
  public: virtual void OnExitGraph(AI::cStreamingGraph*);
  public: virtual unsigned char GetCost(Kaim::CEntity*, Kaim::CEdge&, Kaim::CConstraint&, float&);
  public: virtual unsigned char CanGoFromTo(Kaim::CEntity&, const Kaim::CVector&, const Kaim::CVector&);
  public: virtual bool IsAIEntityOwner(Kaim::CEntity*);
  public: virtual void OnFinishedSlidingToMin();
  protected: virtual Fun_Runtime::State* RetSTATE_Min() const;
  protected: virtual Fun_Runtime::State* RetSTATE_Min();
  protected: virtual Fun_Runtime::State* RetSTATE_Max() const;
  protected: virtual Fun_Runtime::State* RetSTATE_Max();
  protected: virtual void GoToMinState();
  protected: virtual void GoToMaxState();
  public: virtual bool IsInMinState();
  public: virtual bool IsInMaxState();
  public: Prop::cSlidingDoor& operator=(const Prop::cSlidingDoor&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  protected: static Fun_Runtime::State* StaticRetSTATE_Min();
  protected: static Fun_Runtime::State* StaticRetSTATE_Max();
};
