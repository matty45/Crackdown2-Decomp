
class Equip::cHWProjectile::cHWProjectilePrototype : public Equip::cWeaponProjectile::cWeaponProjectilePrototype { /* Size=0x310 */
  /* 0x0000: fields for Equip::cWeaponProjectile::cWeaponProjectilePrototype */
  /* 0x02e0 */ public: unsigned int m_nCollisionFilter;
  /* 0x02e4 */ public: int m_nSmokeEffectID;
  /* 0x02e8 */ public: float m_fSmokeEffectScale;
  /* 0x02ec */ public: Fun_Runtime::cStringc m_strAudioWeaponType;
  /* 0x0308 */ public: bool m_bIsHoming;
  /* 0x0309 */ public: bool m_bAntiGravAction;
  /* 0x030c */ public: unsigned int m_nPointsPerKillOverride;
  
  public: cHWProjectilePrototype(const Equip::cHWProjectile::cHWProjectilePrototype&);
  public: cHWProjectilePrototype(const RWS::CAttributePacket&);
  public: virtual ~cHWProjectilePrototype();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual unsigned int RetPvPKillPoints() const;
  public: virtual unsigned int RetHeadShotKillPoints() const;
  public: virtual unsigned int RetArmKillPoints() const;
  public: virtual unsigned int RetLegKillPoints() const;
  public: Equip::cHWProjectile::cHWProjectilePrototype& operator=(const Equip::cHWProjectile::cHWProjectilePrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
};
