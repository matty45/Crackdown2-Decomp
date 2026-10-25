
class Vehicle::cEightWheelerProfile : public Vehicle::cLandVehicleProfile { /* Size=0xd60 */
  /* 0x0000: fields for Vehicle::cLandVehicleProfile */
  /* 0x0d50 */ protected: RWS::CEventId m_Msg_Data_Modified;
  public: static const char* pcEightWheelerProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cEightWheelerProfile(const Vehicle::cEightWheelerProfile&);
  public: cEightWheelerProfile(const RWS::CAttributePacket&);
  public: virtual ~cEightWheelerProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void SetupMultiAxles();
  public: virtual bool HandleDataInNewDesignBuild();
  public: Vehicle::cEightWheelerProfile& operator=(const Vehicle::cEightWheelerProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
