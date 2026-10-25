
class PHYSICS::cSurfaceProfile : public cNonGameBase { /* Size=0xb0 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac */ protected: unsigned int m_nSurfaceIndex;
  public: static const char m_cSurfaceProfile_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcSurfaceProfileClass;
  public: static const char* pcSurfaceProfileClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSurfaceProfile(const PHYSICS::cSurfaceProfile&);
  public: cSurfaceProfile(const RWS::CAttributePacket&);
  public: virtual ~cSurfaceProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: PHYSICS::cSurfaceProfile& operator=(const PHYSICS::cSurfaceProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
