
class Equip::cShrapnelGrenade : public Equip::cExplosiveGrenade { /* Size=0xa80 */
  /* 0x0000: fields for Equip::cExplosiveGrenade */
  public: static const char m_cShrapnelGrenade_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcShrapnelGrenadeClass;
  public: static const char* pcShrapnelGrenadeClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cShrapnelGrenade(const Equip::cShrapnelGrenade&);
  public: cShrapnelGrenade(GOM::cObjectPrototype*);
  public: virtual ~cShrapnelGrenade();
  protected: unsigned char RetShrapnelNumber() const;
  protected: Equip::cBulletData* RetShrapnelData() const;
  protected: virtual void BeginDetonation();
  public: Equip::cShrapnelGrenade& operator=(const Equip::cShrapnelGrenade&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
