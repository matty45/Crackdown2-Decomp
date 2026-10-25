
class VFX::cBeamData : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x88 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ public: Fun_Runtime::cStringc m_sName;
  /* 0x0034 */ public: float m_fBeamWidth;
  /* 0x0038 */ public: float m_fBeamHeight;
  /* 0x003c */ public: float m_fSpotWidth;
  /* 0x0040 */ public: float m_fSpotHeight;
  /* 0x0044 */ public: float m_fPulseWidth;
  /* 0x0048 */ public: float m_fPulseHeight;
  /* 0x004c */ public: float m_fPulseLength;
  /* 0x0050 */ public: float m_fInitVelocity;
  /* 0x0054 */ public: float m_fBeamTileLength;
  /* 0x0058 */ public: float m_fSpotTileLength;
  /* 0x005c */ public: float m_fSpotSpeedModifier;
  /* 0x0060 */ public: float m_fPulseEmissionIntervalMin;
  /* 0x0064 */ public: float m_fPulseEmissionIntervalMax;
  /* 0x0068 */ public: float m_fPulseVelocityMin;
  /* 0x006c */ public: float m_fPulseVelocityMax;
  /* 0x0070 */ public: unsigned long m_BeamColour1;
  /* 0x0074 */ public: unsigned long m_BeamColour2;
  /* 0x0078 */ public: unsigned long m_SpotColour1;
  /* 0x007c */ public: unsigned long m_SpotColour2;
  /* 0x0080 */ public: unsigned long m_PulseColour1;
  /* 0x0084 */ public: unsigned long m_PulseColour2;
  public: static const char* pcBeamDataClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cBeamData(const VFX::cBeamData&);
  public: cBeamData(const RWS::CAttributePacket&);
  public: cBeamData();
  public: virtual ~cBeamData();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: VFX::cBeamData& operator=(const VFX::cBeamData&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
