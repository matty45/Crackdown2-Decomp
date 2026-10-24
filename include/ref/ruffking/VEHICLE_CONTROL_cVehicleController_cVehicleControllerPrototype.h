
class VEHICLE_CONTROL::cVehicleController::cVehicleControllerPrototype : public cNonGameBase::cNonGameBasePrototype { /* Size=0x70 */
  /* 0x0000: fields for cNonGameBase::cNonGameBasePrototype */
  
  public: cVehicleControllerPrototype(const VEHICLE_CONTROL::cVehicleController::cVehicleControllerPrototype&);
  public: cVehicleControllerPrototype(const RWS::CAttributePacket&);
  public: virtual ~cVehicleControllerPrototype();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: VEHICLE_CONTROL::cVehicleController::cVehicleControllerPrototype& operator=(const VEHICLE_CONTROL::cVehicleController::cVehicleControllerPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
};
