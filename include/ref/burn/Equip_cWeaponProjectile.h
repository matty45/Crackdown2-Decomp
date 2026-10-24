
class Equip::cWeaponProjectile : public Equip::cEquipment { /* Size=0x710 */
  /* 0x0000: fields for Equip::cEquipment */
  public: static const char m_cWeaponProjectile_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcWeaponProjectileClass;
  public: static const char* pcWeaponProjectileClassID;
  public: static unsigned int _cWeaponProjectileClassIDHash;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual void Destruct();
  public: cWeaponProjectile(const Equip::cWeaponProjectile&);
  public: cWeaponProjectile(GOM::cObjectPrototype*);
  public: virtual ~cWeaponProjectile();
  public: virtual bool PickUpRequested();
  public: Equip::cWeaponProjectile& operator=(const Equip::cWeaponProjectile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static unsigned int RetRWSClassNameHash();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static cNonGameBase* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
