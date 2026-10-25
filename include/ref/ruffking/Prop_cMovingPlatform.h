
class Prop::cMovingPlatform : public Prop::cProp { /* Size=0xeb0 */
  /* 0x0000: fields for Prop::cProp */
  /* 0x0ea0 */ private: float m_fTimer;
  /* 0x0ea4 */ private: float m_fCurrentDisplacement;
  /* 0x0ea8 */ private: Prop::cMovingPlatform::ePlatformState m_nState;
  public: static const char m_cMovingPlatform_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcMovingPlatformClass;
  public: static const char* pcMovingPlatformClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void HandleAttributes(GOM::cObjectPrototype*);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: cMovingPlatform(const Prop::cMovingPlatform&);
  public: cMovingPlatform(GOM::cObjectPrototype*);
  public: virtual ~cMovingPlatform();
  public: void SlideToMax();
  public: void SlideToMin();
  protected: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  protected: virtual Fun_Runtime::RetVal Term();
  protected: virtual void TickUpdate(float);
  protected: virtual bool EnterPhysicalState();
  protected: virtual void LeavePhysicalState();
  public: Prop::cMovingPlatform& operator=(const Prop::cMovingPlatform&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
