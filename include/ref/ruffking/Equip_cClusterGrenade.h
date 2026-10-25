
class Equip::cClusterGrenade : public Equip::cExplosiveGrenade { /* Size=0xa80 */
  /* 0x0000: fields for Equip::cExplosiveGrenade */
  public: static const char m_cClusterGrenade_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcClusterGrenadeClass;
  public: static const char* pcClusterGrenadeClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cClusterGrenade(const Equip::cClusterGrenade&);
  public: cClusterGrenade(GOM::cObjectPrototype*);
  protected: float RetRandomBombletSpeed() const;
  protected: unsigned char RetNumBomblets() const;
  protected: GOM::cObjectPrototype* RetBombletPrototype() const;
  protected: virtual void BeginDetonation();
  public: virtual ~cClusterGrenade();
  public: Equip::cClusterGrenade& operator=(const Equip::cClusterGrenade&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
