
class Vehicle::cGenericCarDamageProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x3c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ private: GOM::cObjectPrototype* m_pVehicleDebrisPrototype;
  /* 0x001c */ private: Fun_Runtime::cStringc m_sVehicleDebrisProto;
  /* 0x0038 */ private: float m_fHingeOpenFraction;
  public: static const char* pcGenericCarDamageProfileClassID;
  
  public: GOM::cObjectPrototype* RetVehicleDebrisProto();
  public: const Fun_Runtime::cStringc& RetVehicleDebrisName() const;
  public: float RetHingeOpenThreshold();
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGenericCarDamageProfile(const Vehicle::cGenericCarDamageProfile&);
  public: cGenericCarDamageProfile(const RWS::CAttributePacket&);
  public: virtual ~cGenericCarDamageProfile();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: Vehicle::cGenericCarDamageProfile& operator=(const Vehicle::cGenericCarDamageProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
