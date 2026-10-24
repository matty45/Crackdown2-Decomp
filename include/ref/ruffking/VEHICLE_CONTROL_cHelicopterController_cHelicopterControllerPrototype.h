
class VEHICLE_CONTROL::cHelicopterController::cHelicopterControllerPrototype : public VEHICLE_CONTROL::cVehicleController::cVehicleControllerPrototype { /* Size=0x70 */
  /* 0x0000: fields for VEHICLE_CONTROL::cVehicleController::cVehicleControllerPrototype */
  
  public: cHelicopterControllerPrototype(const VEHICLE_CONTROL::cHelicopterController::cHelicopterControllerPrototype&);
  public: cHelicopterControllerPrototype(const RWS::CAttributePacket&);
  public: virtual ~cHelicopterControllerPrototype();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: VEHICLE_CONTROL::cHelicopterController::cHelicopterControllerPrototype& operator=(const VEHICLE_CONTROL::cHelicopterController::cHelicopterControllerPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
};
