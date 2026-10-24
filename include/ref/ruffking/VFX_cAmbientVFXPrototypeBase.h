
class VFX::cAmbientVFXPrototypeBase : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x30 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ public: float m_fSpawnDistanceMinSq;
  /* 0x001c */ public: float m_fSpawnDistanceMaxSq;
  /* 0x0020 */ public: float m_fScaleOverride;
  /* 0x0024 */ public: float m_fFadeOutTime;
  /* 0x0028 */ public: int m_nEffectID;
  /* 0x002c */ public: unsigned char m_nDefaultPriority;
  /* 0x002d */ public: bool m_bOnFire;
  /* 0x002e */ public: unsigned char m_nFadeMode;
  public: static const char* pcAmbientVFXPrototypeBaseClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAmbientVFXPrototypeBase(const VFX::cAmbientVFXPrototypeBase&);
  public: cAmbientVFXPrototypeBase(const RWS::CAttributePacket&);
  public: virtual ~cAmbientVFXPrototypeBase();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: VFX::cAmbientVFXPrototypeBase& operator=(const VFX::cAmbientVFXPrototypeBase&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
