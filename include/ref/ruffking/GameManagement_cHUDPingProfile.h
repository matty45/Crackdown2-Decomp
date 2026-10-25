
class GameManagement::cHUDPingProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x18 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  public: static const char* pcHUDPingProfileClassID;
  private: static float m_aPingTime[4];
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cHUDPingProfile(const GameManagement::cHUDPingProfile&);
  public: cHUDPingProfile(const RWS::CAttributePacket&);
  public: virtual ~cHUDPingProfile();
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GameManagement::cHUDPingProfile& operator=(const GameManagement::cHUDPingProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static float RetPingTime(GameManagement::etHUDPingType);
};
