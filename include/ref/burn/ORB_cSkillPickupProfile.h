
class ORB::cSkillPickupProfile : public RWS::CAttributeHandler { /* Size=0xb0 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ public: float m_fCollectedRadSq;
  /* 0x001c */ public: float m_fCollectionAcceleration;
  /* 0x0020 */ public: float m_fMinDropDistance;
  /* 0x0024 */ public: float m_fMaxDropDistance;
  /* 0x0028 */ public: float m_fTimeToDestinationPerMeter;
  /* 0x002c */ public: float m_fOneOverK;
  /* 0x0030 */ public: Fun_Runtime::Vec3 m_vecKGOver2;
  /* 0x0040 */ public: Fun_Runtime::Vec3 m_vecGravity;
  /* 0x0050 */ public: int m_nAbsorbEffectId;
  /* 0x0054 */ public: int m_nSkinGlowEffectId;
  /* 0x0058 */ public: unsigned int m_nSkinGlowFadeDuration;
  /* 0x005c */ public: ORB::tSkillPickupData m_aSkillPickupData[5];
  /* 0x00ac */ public: float m_fEffectScale;
  public: static const char* pcSkillPickupProfileClassID;
  public: static unsigned int _cSkillPickupProfileClassIDHash;
  private: static ORB::cSkillPickupProfile* ms_pSingleton;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSkillPickupProfile(const ORB::cSkillPickupProfile&);
  public: cSkillPickupProfile(const RWS::CAttributePacket&);
  public: cSkillPickupProfile();
  public: virtual ~cSkillPickupProfile();
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  private: void Initialise();
  public: ORB::cSkillPickupProfile& operator=(const ORB::cSkillPickupProfile&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static unsigned int RetRWSClassNameHash();
  public: static ORB::cSkillPickupProfile* RetSingleton();
};
