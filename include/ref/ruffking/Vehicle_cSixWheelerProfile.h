
class Vehicle::cSixWheelerProfile : public Vehicle::cLandVehicleProfile { /* Size=0xd70 */
  /* 0x0000: fields for Vehicle::cLandVehicleProfile */
  /* 0x0d50 */ public: Vehicle::tCollisionRamp m_CollisionRamp;
  /* 0x0d64 */ protected: RWS::CEventId m_Msg_Data_Modified;
  public: static const char* pcSixWheelerProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSixWheelerProfile(const Vehicle::cSixWheelerProfile&);
  public: cSixWheelerProfile(const RWS::CAttributePacket&);
  public: virtual ~cSixWheelerProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual void SetupMultiAxles();
  public: Vehicle::cSixWheelerProfile& operator=(const Vehicle::cSixWheelerProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
