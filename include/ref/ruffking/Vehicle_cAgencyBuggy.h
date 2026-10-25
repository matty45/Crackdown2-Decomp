
class Vehicle::cAgencyBuggy : public Vehicle::cAgencyCar { /* Size=0x2fc0 */
  /* 0x0000: fields for Vehicle::cAgencyCar */
  /* 0x2fb0 */ private: bool m_bWeaponsInitialised;
  /* 0x2fb1 */ private: bool m_bMarkerAdded;
  public: static const char m_cAgencyBuggy_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAgencyBuggyClass;
  public: static const char* pcAgencyBuggyClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAgencyBuggy(const Vehicle::cAgencyBuggy&);
  public: cAgencyBuggy(GOM::cObjectPrototype*);
  public: virtual void TickUpdate(float);
  public: void UpdateBuggyWeapon();
  public: virtual void PostTickUpdate(float);
  public: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  public: virtual Fun_Runtime::RetVal Reinitialise(const GOM::cSpawner*);
  public: virtual Fun_Runtime::RetVal TermForReuse();
  public: virtual void ReplicateInitialFields();
  public: virtual void ReplicateFields();
  public: Vehicle::cAgencyBuggyPrototype* RetBuggyProto();
  private: virtual void UpdateWheelMatrices(hkTransform*, hkTransform*);
  private: void ShowBuggyDebug();
  protected: virtual bool GetHasDoorForSeat(unsigned char);
  protected: virtual float GetSuspensionLengthModifier();
  public: virtual ~cAgencyBuggy();
  public: Vehicle::cAgencyBuggy& operator=(const Vehicle::cAgencyBuggy&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
