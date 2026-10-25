
class GameManagement::cCampaignGameModePrototype : public GameManagement::cGameModePrototype { /* Size=0x118 */
  /* 0x0000: fields for GameManagement::cGameModePrototype */
  /* 0x00f0 */ public: Fun_Runtime::cList<GameManagement::cCampaignPlayerSpawnPoint *,Fun_Runtime::cAllocator<GameManagement::cCampaignPlayerSpawnPoint *,3,&GameManagement::cCampaignGameModePrototype::tPlayerStartList_FL> > m_vpCampaignSpawnPoints;
  /* 0x00fc */ public: CHARACTER::cGameDamageProfile* m_pGameDamageProfiles[5];
  /* 0x0110 */ public: unsigned int m_nInitialMissionTier;
  public: static const char* pcCampaignGameModePrototypeClassID;
  public: static unsigned int ms_nDefaultMissionTier;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCampaignGameModePrototype(const GameManagement::cCampaignGameModePrototype&);
  public: cCampaignGameModePrototype(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void OnShutdownLevel();
  public: virtual GameManagement::etGameModeType RetType() const;
  public: virtual bool IsPvPGame() const;
  public: virtual bool CanHaveTeams() const;
  public: virtual bool CanHaveEndLimit() const;
  public: virtual bool CanHaveTimeLimit() const;
  public: virtual bool CanMigrateHost() const;
  public: virtual bool IsLobbyGame() const;
  public: virtual int RetMinPlayers() const;
  public: virtual int RetMaxPlayers() const;
  public: virtual int RetStringID() const;
  public: virtual bool RequiresSpawnSelection() const;
  public: virtual bool RequiresWeaponSelection() const;
  public: virtual bool RequiresVehicleSelection() const;
  public: GameManagement::cCampaignPlayerSpawnPoint* RetSpawnPoint(unsigned int);
  public: virtual GameManagement::cGameMode* CreateGameMode(GameManagement::cGameModeSession*);
  public: const CHARACTER::cGameDamageProfile* RetDamageProfile(Session::eDifficulty) const;
  public: void AddSpawnPoint(GameManagement::cCampaignPlayerSpawnPoint*);
  public: virtual ~cCampaignGameModePrototype();
  public: GameManagement::cCampaignGameModePrototype& operator=(const GameManagement::cCampaignGameModePrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static Fun_Runtime::cFileLine tPlayerStartList_FL();
};
