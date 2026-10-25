
class Equip::cChainGun : public Equip::cCWFirearm { /* Size=0xb80 */
  /* 0x0000: fields for Equip::cCWFirearm */
  /* 0x0b70 */ private: float m_fBarrelSpeed;
  /* 0x0b74 */ private: float m_fExtendTrans;
  public: static const char m_cChainGun_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcChainGunClass;
  public: static const char* pcChainGunClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: float RetAngVel();
  public: const Equip::cChainGun::cChainGunPrototype* RetChainGunPrototype() const;
  public: Equip::cChainGun::cChainGunPrototype* RetChainGunPrototype();
  public: virtual void TickUpdate(float);
  public: cChainGun(const Equip::cChainGun&);
  public: cChainGun(GOM::cObjectPrototype*);
  public: virtual ~cChainGun();
  public: virtual float RetAttackDuration() const;
  private: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  private: void Animate(float);
  private: virtual float RetBulletDamageOverride();
  private: float RetBarrelAcceleration();
  private: const Equip::cChainGun::tChainGunLevelData* RetLevelData() const;
  public: Equip::cChainGun& operator=(const Equip::cChainGun&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
