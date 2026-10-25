
class Demo::cDemoSettings : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x18 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  public: static const char* pcDemoSettingsClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cDemoSettings(const Demo::cDemoSettings&);
  public: cDemoSettings(const RWS::CAttributePacket&);
  public: virtual ~cDemoSettings();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: Demo::cDemoSettings& operator=(const Demo::cDemoSettings&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
