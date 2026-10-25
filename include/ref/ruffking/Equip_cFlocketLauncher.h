
class Equip::cFlocketLauncher : public Equip::cCWHeavyWeapon { /* Size=0xae0 */
  /* 0x0000: fields for Equip::cCWHeavyWeapon */
  /* 0x0ad0 */ private: float m_fAttackTime;
  /* 0x0ad4 */ private: unsigned char m_nBarrelID;
  public: static const char m_cFlocketLauncher_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcFlocketLauncherClass;
  public: static const char* pcFlocketLauncherClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: Equip::cFlocketLauncher::cFlocketLauncherPrototype* RetFlocketLauncherPrototype();
  public: virtual void TickUpdate(float);
  public: cFlocketLauncher(const Equip::cFlocketLauncher&);
  public: cFlocketLauncher(GOM::cObjectPrototype*);
  public: virtual ~cFlocketLauncher();
  public: virtual bool BeginAttack();
  public: Equip::cFlocketLauncher& operator=(const Equip::cFlocketLauncher&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
