
class Vehicle::cHelicopterDamageProfile : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy { /* Size=0x110 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001c: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c */ private: RWS::CEventId m_msgReturnSelf;
  /* 0x0024 */ public: bool m_bCanBeDamaged;
  /* 0x0030 */ public: Vehicle::cDoorData m_aDoorData[1];
  /* 0x0080 */ public: Vehicle::cLegData m_aLegData[4];
  /* 0x00b0 */ public: Vehicle::cArmData m_aArmData[4];
  /* 0x00e0 */ public: Vehicle::cBodyworkData m_BodyworkData;
  /* 0x00ec */ public: Vehicle::cGlassData m_GlassData;
  /* 0x00f8 */ public: Vehicle::cBladeData m_BladeData;
  public: static const char* pcHelicopterDamageProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cHelicopterDamageProfile(const Vehicle::cHelicopterDamageProfile&);
  public: cHelicopterDamageProfile(const RWS::CAttributePacket&);
  public: virtual ~cHelicopterDamageProfile();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: Vehicle::cHelicopterDamageProfile& operator=(const Vehicle::cHelicopterDamageProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
