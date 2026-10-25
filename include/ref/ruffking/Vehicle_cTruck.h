
class Vehicle::cTruck : public Vehicle::cCar { /* Size=0x2f80 */
  /* 0x0000: fields for Vehicle::cCar */
  /* 0x2f70 */ protected: hkRigidBody* m_pWedgeRigidBody;
  public: static const char m_cTruck_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcTruckClass;
  public: static const char* pcTruckClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTruck(const Vehicle::cTruck&);
  public: cTruck(GOM::cObjectPrototype*);
  public: virtual ~cTruck();
  public: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(GOM::cObjectPrototype*);
  public: virtual bool EnterPhysicalState();
  public: virtual void LeavePhysicalState();
  public: virtual void TickUpdate(float);
  public: virtual void OverrideProfileParams();
  public: virtual void SetUpAdditionalPointsOfInterest(unsigned char);
  public: bool HasWedge();
  public: virtual void SetupWedge();
  public: void RemoveWedge();
  protected: virtual bool SpawnExhaustVFX();
  protected: virtual void UpdateWheelMatrices(hkTransform*, hkTransform*);
  protected: virtual void SetMidFrontLeftWheelMatrix(Fun_Runtime::Mtx&);
  protected: virtual void SetMidFrontRightWheelMatrix(Fun_Runtime::Mtx&);
  protected: virtual void SetMidBackLeftWheelMatrix(Fun_Runtime::Mtx&);
  protected: virtual void SetMidBackRightWheelMatrix(Fun_Runtime::Mtx&);
  protected: virtual void SetAxle(unsigned char, unsigned char, hkTransform*);
  protected: virtual void ActionUpdate(float);
  protected: void ActionUpdate2(float);
  protected: virtual void RenderDebugPage(int, int);
  public: Vehicle::cTruck& operator=(const Vehicle::cTruck&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
