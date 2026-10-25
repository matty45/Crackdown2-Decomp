
class Equip::cLightAttachmentData : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy { /* Size=0x38 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001c: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c */ private: float m_fConeAngle;
  /* 0x0020 */ private: float m_fConeLength;
  /* 0x0024 */ private: float m_fPowerTime;
  /* 0x0028 */ private: float m_fRechargeTime;
  /* 0x002c */ private: char m_nLightID;
  /* 0x002d */ private: bool m_bInfinitePower;
  /* 0x0030 */ private: RWS::CEventId m_RetrieveLightData;
  public: static const char* pcLightAttachmentDataClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cLightAttachmentData(const Equip::cLightAttachmentData&);
  public: cLightAttachmentData(const RWS::CAttributePacket&);
  public: cLightAttachmentData();
  public: virtual ~cLightAttachmentData();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: float RetConeAngle() const;
  public: float RetConeLength() const;
  public: float RetPowerTime() const;
  public: float RetRechargeTime() const;
  public: char RetLightID() const;
  public: bool IsInfinitePower() const;
  public: Equip::cLightAttachmentData& operator=(const Equip::cLightAttachmentData&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
