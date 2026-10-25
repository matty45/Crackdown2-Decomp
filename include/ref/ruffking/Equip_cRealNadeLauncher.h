
class Equip::cRealNadeLauncher : public Equip::cCWHeavyWeapon { /* Size=0xad0 */
  /* 0x0000: fields for Equip::cCWHeavyWeapon */
  public: static const char m_cRealNadeLauncher_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcRealNadeLauncherClass;
  public: static const char* pcRealNadeLauncherClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: Equip::cRealNadeLauncher::cRealNadeLauncherPrototype* RetRealNadeLauncherPrototype();
  public: virtual void TickUpdate(float);
  public: cRealNadeLauncher(const Equip::cRealNadeLauncher&);
  public: cRealNadeLauncher(GOM::cObjectPrototype*);
  public: virtual ~cRealNadeLauncher();
  public: virtual bool BeginAttack();
  public: void LaunchNade(PHYSICS::cDynamicBody*);
  public: Equip::cRealNadeLauncher& operator=(const Equip::cRealNadeLauncher&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
