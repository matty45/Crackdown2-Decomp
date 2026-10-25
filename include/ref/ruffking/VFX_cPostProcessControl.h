
class VFX::cPostProcessControl : public RWS::CAttributeHandler, public RWS::CEventHandler { /* Size=0x1c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  public: static const char* pcPostProcessControlClassID;
  
  public: cPostProcessControl(const VFX::cPostProcessControl&);
  public: cPostProcessControl(const RWS::CAttributePacket&);
  public: virtual ~cPostProcessControl();
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: VFX::cPostProcessControl& operator=(const VFX::cPostProcessControl&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
