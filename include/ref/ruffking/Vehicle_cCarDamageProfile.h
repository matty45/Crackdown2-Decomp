
class Vehicle::cCarDamageProfile : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy { /* Size=0x230 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001c: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c */ private: RWS::CEventId m_msgReturnSelf;
  /* 0x0024 */ public: bool m_bCanBeDamaged;
  /* 0x0030 */ public: Vehicle::cDoorData m_aDoorData[4];
  /* 0x0170 */ public: Vehicle::cBonnetData m_BonnetData;
  /* 0x01b0 */ public: Vehicle::cBootData m_BootData;
  /* 0x01f0 */ public: Vehicle::cBumperData m_BumperFData;
  /* 0x0200 */ public: Vehicle::cBumperData m_BumperBData;
  /* 0x0210 */ public: Vehicle::cBodyworkData m_BodyworkData;
  /* 0x021c */ public: Vehicle::cGlassData m_GlassData;
  public: static const char* pcCarDamageProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCarDamageProfile(const Vehicle::cCarDamageProfile&);
  public: cCarDamageProfile(const RWS::CAttributePacket&);
  public: virtual ~cCarDamageProfile();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: Vehicle::cCarDamageProfile& operator=(const Vehicle::cCarDamageProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
