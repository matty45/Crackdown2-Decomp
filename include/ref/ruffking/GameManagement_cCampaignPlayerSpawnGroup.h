
class GameManagement::cCampaignPlayerSpawnGroup : public GameManagement::cGameModeSpawnPoint { /* Size=0xa0 */
  /* 0x0000: fields for GameManagement::cGameModeSpawnPoint */
  /* 0x0060 */ protected: Fun_Runtime::cVectorip<GameManagement::cCampaignPlayerSpawnPoint *,4> m_vPlayerStartPoints;
  /* 0x0080 */ protected: GameManagement::cCampaignPlayerSpawnGroup::eState m_eState;
  /* 0x0084 */ protected: Editor::cGUIDEventHandler<GameManagement::cCampaignPlayerSpawnGroup> m_EventHandler;
  public: static const char* pcCampaignPlayerSpawnGroupClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCampaignPlayerSpawnGroup(const GameManagement::cCampaignPlayerSpawnGroup&);
  public: cCampaignPlayerSpawnGroup(const RWS::CAttributePacket&);
  public: virtual ~cCampaignPlayerSpawnGroup();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GameManagement::cCampaignPlayerSpawnGroup::eState RetState() const;
  public: GameManagement::cCampaignPlayerSpawnPoint* RetPlayerSpawn(unsigned int);
  public: void EnableSpawnPoints(bool);
  public: void SetVehicleDropDenied(bool);
  public: void TestRender();
  public: GameManagement::cCampaignPlayerSpawnGroup& operator=(const GameManagement::cCampaignPlayerSpawnGroup&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
