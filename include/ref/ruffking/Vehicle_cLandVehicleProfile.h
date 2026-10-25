
class Vehicle::cLandVehicleProfile : public Vehicle::cLandVehicleData, public PHYSICS::cRigidBodyProfile { /* Size=0xd50 */
  /* 0x0230: fields for Vehicle::cLandVehicleData */
  /* 0x0000: fields for PHYSICS::cRigidBodyProfile */
  /* 0x0d40 */ protected: float m_fRearWheelOffset;
  /* 0x0d44 */ protected: float m_fFrontWheelOffset;
  public: static const char* pcLandVehicleProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cLandVehicleProfile(const Vehicle::cLandVehicleProfile&);
  public: cLandVehicleProfile(const RWS::CAttributePacket&);
  public: virtual ~cLandVehicleProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&, unsigned char);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual bool HandleResources(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual void SetupMultiAxles();
  private: void InitEngineData(unsigned int, RWS::CAttributeCommandIterator&);
  private: void InitTransmissionData(unsigned int, RWS::CAttributeCommandIterator&);
  private: void InitAerodynamicsData(unsigned int, RWS::CAttributeCommandIterator&);
  private: void InitSteeringData(unsigned int, RWS::CAttributeCommandIterator&);
  private: void InitBrakeData(unsigned int, RWS::CAttributeCommandIterator&);
  private: void InitSuspensionData(unsigned int, RWS::CAttributeCommandIterator&);
  private: void InitWheelsData(unsigned int, RWS::CAttributeCommandIterator&);
  private: void InitLightData(unsigned int, RWS::CAttributeCommandIterator&);
  private: void InitDropShadowData(unsigned int, RWS::CAttributeCommandIterator&);
  private: void InitMisc(unsigned int, RWS::CAttributeCommandIterator&);
  private: void CalcRideHeight();
  public: Vehicle::cLandVehicleProfile& operator=(const Vehicle::cLandVehicleProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
