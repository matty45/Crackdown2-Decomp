
class RPG::cRPGGlobalsInterface : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x18 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  public: static const char* pcRPGGlobalsInterfaceClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cRPGGlobalsInterface(const RPG::cRPGGlobalsInterface&);
  public: cRPGGlobalsInterface(const RWS::CAttributePacket&);
  public: virtual ~cRPGGlobalsInterface();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: RPG::cRPGGlobalsInterface& operator=(const RPG::cRPGGlobalsInterface&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
