
class Equip::cUVTurret : public Equip::cCWFirearm { /* Size=0xb70 */
  /* 0x0000: fields for Equip::cCWFirearm */
  public: static const char m_cUVTurret_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcUVTurretClass;
  public: static const char* pcUVTurretClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: const Equip::cUVTurret::cUVTurretPrototype* RetUVTurretPrototype() const;
  public: cUVTurret(const Equip::cUVTurret&);
  public: cUVTurret(GOM::cObjectPrototype*);
  public: virtual ~cUVTurret();
  public: Equip::cUVTurret& operator=(const Equip::cUVTurret&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
