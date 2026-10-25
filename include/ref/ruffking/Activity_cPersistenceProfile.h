
class Activity::cPersistenceProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x18 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  public: static const char* pcPersistenceProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPersistenceProfile(const Activity::cPersistenceProfile&);
  public: cPersistenceProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual ~cPersistenceProfile();
  public: Activity::cPersistenceProfile& operator=(const Activity::cPersistenceProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
