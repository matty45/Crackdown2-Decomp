
class VFX::cBloom : public cNonGameBase { /* Size=0xac */
  /* 0x0000: fields for cNonGameBase */
  public: static const char m_cBloom_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcBloomClass;
  public: static const char* pcBloomClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: cBloom(const VFX::cBloom&);
  public: cBloom(const RWS::CAttributePacket&);
  public: virtual ~cBloom();
  public: VFX::cBloom& operator=(const VFX::cBloom&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
