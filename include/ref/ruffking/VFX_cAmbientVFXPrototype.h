
class VFX::cAmbientVFXPrototype : public VFX::cAmbientVFXPrototypeBase { /* Size=0x68 */
  /* 0x0000: fields for VFX::cAmbientVFXPrototypeBase */
  /* 0x0030 */ public: Editor::cGUIDEventHandler<VFX::cAmbientVFXPrototype> m_EventHandler;
  /* 0x0044 */ public: float m_fInitSpawnTimeMin;
  /* 0x0048 */ public: float m_fInitSpawnTimeMax;
  /* 0x004c */ public: float m_fRandRespawnTimeMin;
  /* 0x0050 */ public: float m_fRandRespawnTimeMax;
  /* 0x0054 */ public: float m_fRandLifetimeMin;
  /* 0x0058 */ public: float m_fRandLifetimeMax;
  /* 0x005c */ public: float m_fToDStart;
  /* 0x0060 */ public: float m_fToDEnd;
  /* 0x0064 */ public: bool m_bIsExplosion;
  /* 0x0065 */ public: bool m_bRandSpawn;
  public: static const char* pcAmbientVFXPrototypeClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAmbientVFXPrototype(const VFX::cAmbientVFXPrototype&);
  public: cAmbientVFXPrototype(const RWS::CAttributePacket&);
  public: virtual ~cAmbientVFXPrototype();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: VFX::cAmbientVFXPrototype& operator=(const VFX::cAmbientVFXPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
