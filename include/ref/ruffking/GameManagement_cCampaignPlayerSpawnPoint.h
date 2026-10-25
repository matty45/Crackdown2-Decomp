
class GameManagement::cCampaignPlayerSpawnPoint : public GameManagement::cGameModeSpawnPoint { /* Size=0x80 */
  /* 0x0000: fields for GameManagement::cGameModeSpawnPoint */
  /* 0x0060 */ protected: unsigned int m_nPlayerID;
  /* 0x0064 */ protected: bool m_bEnabled;
  /* 0x0065 */ protected: bool m_bDenyVehicleDrop;
  /* 0x0068 */ protected: unsigned int m_nID;
  /* 0x006c */ protected: Editor::cGUIDEventHandler<GameManagement::cCampaignPlayerSpawnPoint> m_EventHandler;
  public: static const char* pcCampaignPlayerSpawnPointClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCampaignPlayerSpawnPoint(const GameManagement::cCampaignPlayerSpawnPoint&);
  public: cCampaignPlayerSpawnPoint(const RWS::CAttributePacket&);
  public: virtual ~cCampaignPlayerSpawnPoint();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: unsigned char RetPlayerID() const;
  public: void Enable(bool);
  public: bool IsEnabled() const;
  public: void SetSpawnPointID(unsigned int);
  public: unsigned int RetSpawnPointID();
  public: void SetVehicleDropDenied(bool);
  public: bool IsVehicleDropDenied() const;
  public: GameManagement::cCampaignPlayerSpawnPoint& operator=(const GameManagement::cCampaignPlayerSpawnPoint&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
