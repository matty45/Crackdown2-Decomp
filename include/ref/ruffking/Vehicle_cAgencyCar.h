
class Vehicle::cAgencyCar : public Vehicle::cCar { /* Size=0x2fb0 */
  /* 0x0000: fields for Vehicle::cCar */
  /* 0x2f70 */ protected: Vehicle::cLandVehicle::tAttachedVehicleVFX m_aFireExhaustVFX[5];
  /* 0x2f98 */ protected: float m_fFireExhaustTimer;
  /* 0x2f9c */ protected: bool m_bCanSpawnFireExhaust;
  /* 0x2fa0 */ protected: float m_fLastRPM;
  public: static const char m_cAgencyCar_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAgencyCarClass;
  public: static const char* pcAgencyCarClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAgencyCar(const Vehicle::cAgencyCar&);
  public: cAgencyCar(GOM::cObjectPrototype*);
  protected: virtual void SetAttachedVFXAlpha(float);
  protected: virtual void UpdateExhaustVFX(float);
  protected: virtual void ReleaseAttachedVFX(bool);
  public: virtual ~cAgencyCar();
  public: Vehicle::cAgencyCar& operator=(const Vehicle::cAgencyCar&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
