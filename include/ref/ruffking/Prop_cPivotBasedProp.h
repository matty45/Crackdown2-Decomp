
class Prop::cPivotBasedProp : public Prop::cProp, public Fun_Runtime::cStateMachine { /* Size=0xeb0 */
  /* 0x0000: fields for Prop::cProp */
  /* 0x0ea0: fields for Fun_Runtime::cStateMachine */
  public: static const char m_cPivotBasedProp_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcPivotBasedPropClass;
  public: static const char* pcPivotBasedPropClassID;
  protected: static Fun_Runtime::cStateNameRegistrar STATE_Base_Registrar;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPivotBasedProp(const Prop::cPivotBasedProp&);
  public: cPivotBasedProp(GOM::cObjectPrototype*);
  public: virtual ~cPivotBasedProp();
  public: virtual void TickUpdate(float);
  public: virtual bool EnterPhysicalState();
  public: virtual void LeavePhysicalState();
  public: virtual void CreateConstraintData();
  public: virtual void DestroyConstraintData();
  protected: virtual Fun_Runtime::State* RetSTATE_Base() const;
  protected: virtual Fun_Runtime::State* RetSTATE_Base();
  public: Prop::cPivotBasedProp& operator=(const Prop::cPivotBasedProp&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  protected: static Fun_Runtime::State* StaticRetSTATE_Base();
};
