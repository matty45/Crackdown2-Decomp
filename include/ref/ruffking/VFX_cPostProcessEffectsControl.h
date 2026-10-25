
class VFX::cPostProcessEffectsControl : public RWS::CAttributeHandler, public RWS::CEventHandler { /* Size=0x1c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  public: static const char* pcPostProcessEffectsControlClassID;
  
  public: cPostProcessEffectsControl(const VFX::cPostProcessEffectsControl&);
  public: cPostProcessEffectsControl(const RWS::CAttributePacket&);
  public: virtual ~cPostProcessEffectsControl();
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: VFX::cPostProcessEffectsControl& operator=(const VFX::cPostProcessEffectsControl&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
