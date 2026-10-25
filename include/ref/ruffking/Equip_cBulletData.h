
class Equip::cBulletData : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy { /* Size=0x138 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001c: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c */ public: float m_fSpread;
  /* 0x0020 */ public: float m_fSpeed;
  /* 0x0024 */ public: float m_fDamage;
  /* 0x0028 */ public: float m_fDamageAI;
  /* 0x002c */ public: float m_fDamageCriticalProps;
  /* 0x0030 */ public: float m_fBounce;
  /* 0x0034 */ public: float m_fGravity;
  /* 0x0038 */ public: float m_fLifetime;
  /* 0x003c */ public: float m_fSpiralMotion;
  /* 0x0040 */ public: float m_fDecalSize;
  /* 0x0044 */ public: bool m_fHoming;
  /* 0x0045 */ public: unsigned char m_nSubDivide;
  /* 0x0046 */ public: unsigned char m_nPassThroughs;
  /* 0x0048 */ public: float m_fMinFallOffDamage;
  /* 0x004c */ public: float m_fFallOffStartDist;
  /* 0x0050 */ public: float m_fFallOffEndDist;
  /* 0x0054 */ public: float m_fHeadDamageModifier[2];
  /* 0x005c */ public: float m_fTorsoDamageModifier[2];
  /* 0x0064 */ public: float m_fArmDamageModifier[2];
  /* 0x006c */ public: float m_fLegsDamageModifier[2];
  /* 0x0074 */ public: float m_fHeartDamageModifier[2];
  /* 0x007c */ public: bool m_bFireTracerBullet;
  /* 0x0080 */ public: float m_fTracerBulletSpeed;
  /* 0x0084 */ public: float m_fTrailWidth;
  /* 0x0088 */ public: float m_fTrailFadeTime;
  /* 0x008c */ public: float m_fTrailRepeatDistance;
  /* 0x0090 */ public: float m_fTracerWidth;
  /* 0x0094 */ public: float m_fTracerLength;
  /* 0x0098 */ public: float m_fTracerWidthLocalPlayer;
  /* 0x009c */ public: float m_fTracerLengthLocalPlayer;
  /* 0x00a0 */ public: float m_fRenderRandomFactor;
  /* 0x00a4 */ public: unsigned long m_TracerColour;
  /* 0x00a8 */ public: unsigned long m_TrailColour;
  /* 0x00ac */ public: bool m_bUseTrails;
  /* 0x00ad */ public: bool m_bUseTracers;
  /* 0x00ae */ public: bool m_bUseRandomRender;
  /* 0x00af */ public: bool m_bIsAHarpoon;
  /* 0x00b0 */ public: float m_fPropForceFraction;
  /* 0x00b4 */ public: float m_fVehicleForceFraction;
  /* 0x00b8 */ public: float m_fCharacterForceFraction;
  /* 0x00bc */ public: float m_fCharacterDeathForceFraction;
  /* 0x00c0 */ public: float m_fAttachedEffectScale;
  /* 0x00c4 */ public: int m_nAttachedEffectID;
  /* 0x00c8 */ public: Fun_Runtime::cString m_sSubdivideName;
  /* 0x00e4 */ public: int m_nSubdivisionID;
  /* 0x00e8 */ public: float m_fImpactVFXScale;
  /* 0x00ec */ public: bool m_bUseImpactLODS;
  /* 0x00f0 */ public: Projectile::ImpactLodData m_aImpactLods[3];
  /* 0x0108 */ public: unsigned char m_nExplosionType;
  /* 0x0109 */ public: unsigned char m_nExplosionLevel;
  /* 0x010c */ public: float m_fDefualtImpactLodSeperation;
  /* 0x0110 */ public: float m_fDefaultImpactLodScale;
  /* 0x0114 */ private: RWS::CEventId m_RetreveEventID;
  /* 0x011c */ private: Fun_Runtime::cStringc m_sName;
  public: static const char* pcBulletDataClassID;
  public: static const int nMaxNumImpactLODs;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cBulletData(const Equip::cBulletData&);
  public: cBulletData(const RWS::CAttributePacket&);
  public: virtual ~cBulletData();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: void SetUpSubdivisionID();
  public: bool RetCanRenderBullet() const;
  public: bool RetRenderingRandomBullets() const;
  public: float RetRenderBulletFrequency() const;
  public: Equip::cBulletData& operator=(const Equip::cBulletData&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
