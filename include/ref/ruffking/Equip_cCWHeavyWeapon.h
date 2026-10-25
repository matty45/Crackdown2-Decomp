
class Equip::cCWHeavyWeapon : public Equip::cCWWeapon { /* Size=0xad0 */
  /* 0x0000: fields for Equip::cCWWeapon */
  /* 0x0ac0 */ protected: bool m_bSpawnProjectile;
  /* 0x0ac4 */ protected: float m_fLastWeaponSoundTime;
  public: static const char m_cCWHeavyWeapon_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcCWHeavyWeaponClass;
  public: static const char* pcCWHeavyWeaponClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCWHeavyWeapon(const Equip::cCWHeavyWeapon&);
  public: cCWHeavyWeapon(GOM::cObjectPrototype*);
  public: virtual ~cCWHeavyWeapon();
  public: float RetInitProjVelocity() const;
  public: float RetWeaponSoundVolume() const;
  public: const Fun_Runtime::cString& RetProjectileSpawnName() const;
  public: virtual bool IsTargetTooClose(CHARACTER::cCharacter*, cGameBase*, const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&) const;
  public: virtual bool IsTargetAreaClear(CHARACTER::cCharacter*, cGameBase*, const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&) const;
  public: virtual bool IsTargetBlocked(CHARACTER::cCharacter*, cGameBase*, const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&, Fun_Runtime::Vec3&, cGameBase*&, unsigned char&) const;
  public: unsigned char RetExplosiveLevel() const;
  public: unsigned char RetExplosiveLevelForOwner(const cNonGameBase*) const;
  public: virtual bool GetTargetAttackPoint(Fun_Runtime::Vec3&);
  public: virtual void RenderDebugPage(int, int);
  public: virtual void ShowAccuracyCone();
  protected: virtual void HandleAttributes(GOM::cObjectPrototype*);
  protected: virtual bool BeginAttack();
  protected: virtual Equip::cHWProjectile* FireProjectile(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&);
  protected: Equip::cHWProjectile* SpawnProjectile(const Fun_Runtime::Mtx*, cGameBase*) const;
  public: Equip::cCWHeavyWeapon& operator=(const Equip::cCWHeavyWeapon&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
