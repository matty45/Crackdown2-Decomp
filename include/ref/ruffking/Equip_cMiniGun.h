
class Equip::cMiniGun : public Equip::cCWFirearm { /* Size=0xb80 */
  /* 0x0000: fields for Equip::cCWFirearm */
  /* 0x0b70 */ private: float m_fBarrelSpeed;
  public: static const char m_cMiniGun_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcMiniGunClass;
  public: static const char* pcMiniGunClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: const Equip::cMiniGun::cMiniGunPrototype* RetMiniGunPrototype() const;
  public: virtual void TickUpdate(float);
  public: cMiniGun(const Equip::cMiniGun&);
  public: cMiniGun(GOM::cObjectPrototype*);
  public: virtual ~cMiniGun();
  public: virtual float RetAttackDuration() const;
  private: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  private: void Animate(float);
  private: float RetBarrelAcceleration();
  public: Equip::cMiniGun& operator=(const Equip::cMiniGun&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
