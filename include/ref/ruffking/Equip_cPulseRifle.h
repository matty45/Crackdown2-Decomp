
class Equip::cPulseRifle : public Equip::cCWWeapon { /* Size=0xb20 */
  /* 0x0000: fields for Equip::cCWWeapon */
  /* 0x0ac0 */ private: Equip::cPulse m_Pulse;
  public: static const char m_cPulseRifle_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcPulseRifleClass;
  public: static const char* pcPulseRifleClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPulseRifle(const Equip::cPulseRifle&);
  public: cPulseRifle(GOM::cObjectPrototype*);
  protected: Equip::cPulseRifle::cPulseRiflePrototype* RetForceGunPrototype() const;
  protected: virtual void TickUpdate(float);
  protected: virtual bool BeginAttack();
  protected: virtual void UpdateAttachedMuzzleEffect();
  public: virtual ~cPulseRifle();
  public: Equip::cPulseRifle& operator=(const Equip::cPulseRifle&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
