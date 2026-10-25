
class Prop::cTODSlidingDoor : public Prop::cSlidingDoor { /* Size=0xf60 */
  /* 0x0000: fields for Prop::cSlidingDoor */
  public: static const char m_cTODSlidingDoor_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcTODSlidingDoorClass;
  public: static const char* pcTODSlidingDoorClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTODSlidingDoor(const Prop::cTODSlidingDoor&);
  public: cTODSlidingDoor(GOM::cObjectPrototype*);
  public: virtual void TickUpdate(float);
  public: Prop::cTODSlidingDoorPrototype* RetTODSlidingDoorProto();
  public: virtual bool NeedsEnvironmentCollision();
  public: virtual void GoToInitialState();
  private: bool IsOpenTODPhase();
  public: virtual ~cTODSlidingDoor();
  public: Prop::cTODSlidingDoor& operator=(const Prop::cTODSlidingDoor&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
