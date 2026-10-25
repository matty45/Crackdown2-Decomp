
class VFX::cVFXSurfaceProfile : public cNonGameBase { /* Size=0xb0 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac */ protected: unsigned int m_nSurfaceIndex;
  public: static const char m_cVFXSurfaceProfile_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcVFXSurfaceProfileClass;
  public: static const char* pcVFXSurfaceProfileClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cVFXSurfaceProfile(const VFX::cVFXSurfaceProfile&);
  public: cVFXSurfaceProfile(const RWS::CAttributePacket&);
  public: virtual ~cVFXSurfaceProfile();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: VFX::cVFXSurfaceProfile& operator=(const VFX::cVFXSurfaceProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
