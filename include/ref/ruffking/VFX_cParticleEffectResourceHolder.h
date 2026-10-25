
class VFX::cParticleEffectResourceHolder : public cNonGameBase { /* Size=0xc0 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac */ private: Fun_Runtime::cVector<char const *,Fun_Runtime::cAllocator<char const *,3,&VFX::cParticleEffectResourceHolder::m_vResources_FL> > m_vResources;
  /* 0x00bc */ private: float m_fDefaultPriority;
  public: static const char m_cParticleEffectResourceHolder_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcParticleEffectResourceHolderClass;
  public: static const char* pcParticleEffectResourceHolderClassID;
  
  private: void ProcessResource(const RWS::RWSGUID&);
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cParticleEffectResourceHolder(const VFX::cParticleEffectResourceHolder&);
  public: cParticleEffectResourceHolder(const RWS::CAttributePacket&);
  public: virtual ~cParticleEffectResourceHolder();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: VFX::cParticleEffectResourceHolder& operator=(const VFX::cParticleEffectResourceHolder&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  private: static Fun_Runtime::cFileLine m_vResources_FL();
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
