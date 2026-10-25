
class Vehicle::cAgencySports : public Vehicle::cAgencyCar { /* Size=0x2fc0 */
  /* 0x0000: fields for Vehicle::cAgencyCar */
  /* 0x2fb0 */ private: Vehicle::cVehicleWedge m_Wedge;
  /* 0x2fb8 */ private: float m_fCurretCombatCooldownTimer;
  public: static const char m_cAgencySports_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAgencySportsClass;
  public: static const char* pcAgencySportsClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAgencySports(const Vehicle::cAgencySports&);
  public: cAgencySports(GOM::cObjectPrototype*);
  public: virtual void TickUpdate(float);
  public: virtual void PostTickUpdate(float);
  public: virtual void ActionUpdate(float);
  public: void UpdateVehicleMelee(float);
  public: virtual void LeavePhysicalState();
  public: virtual Fun_Runtime::RetVal TermForReuse();
  private: Vehicle::cAgencySportsPrototype* RetSportsProto();
  public: virtual ~cAgencySports();
  public: Vehicle::cAgencySports& operator=(const Vehicle::cAgencySports&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
