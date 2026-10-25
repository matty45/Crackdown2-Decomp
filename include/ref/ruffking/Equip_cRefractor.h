
class Equip::cRefractor : public Equip::cCWWeapon { /* Size=0xb10 */
  /* 0x0000: fields for Equip::cCWWeapon */
  /* 0x0ac0 */ private: Equip::cRefractorBeam m_Beam;
  public: static const char m_cRefractor_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcRefractorClass;
  public: static const char* pcRefractorClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cRefractor(const Equip::cRefractor&);
  public: cRefractor(GOM::cObjectPrototype*);
  public: virtual bool BeginAttack();
  protected: virtual void UpdateAttachedMuzzleEffect();
  protected: Equip::cRefractorPrototype* RetRefractorPrototype() const;
  public: virtual ~cRefractor();
  public: Equip::cRefractor& operator=(const Equip::cRefractor&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
