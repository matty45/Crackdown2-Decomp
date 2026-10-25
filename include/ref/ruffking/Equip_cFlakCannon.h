
class Equip::cFlakCannon : public Equip::cCWHeavyWeapon { /* Size=0xae0 */
  /* 0x0000: fields for Equip::cCWHeavyWeapon */
  /* 0x0ad0 */ private: float m_fAnimStartTime;
  public: static const char m_cFlakCannon_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcFlakCannonClass;
  public: static const char* pcFlakCannonClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: const Equip::cFlakCannon::cFlakCannonPrototype* RetFlakCannonPrototype() const;
  public: virtual void TickUpdate(float);
  public: cFlakCannon(const Equip::cFlakCannon&);
  public: cFlakCannon(GOM::cObjectPrototype*);
  public: virtual ~cFlakCannon();
  private: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  private: void Animate(float);
  private: virtual Equip::cHWProjectile* FireProjectile(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&);
  public: Equip::cFlakCannon& operator=(const Equip::cFlakCannon&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
