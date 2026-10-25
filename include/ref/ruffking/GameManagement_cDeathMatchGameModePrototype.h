
class GameManagement::cDeathMatchGameModePrototype : public GameManagement::cPvPGameModePrototype { /* Size=0x188 */
  /* 0x0000: fields for GameManagement::cPvPGameModePrototype */
  /* 0x0140 */ protected: int m_aKillPoints[5];
  /* 0x0154 */ protected: int m_nH2HKillPoints[8];
  /* 0x0174 */ protected: int m_nShotExplosivePoints;
  /* 0x0178 */ protected: int m_nSuicidePoints;
  /* 0x017c */ protected: int m_nDeathPoints;
  /* 0x0180 */ protected: bool m_bHasDucks;
  public: static const char* pcDeathMatchGameModePrototypeClassID;
  
  public: cDeathMatchGameModePrototype(const GameManagement::cDeathMatchGameModePrototype&);
  public: cDeathMatchGameModePrototype(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
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
  public: virtual Fun_Runtime::cStringc RetExplosivePrototypeName() const;
  public: virtual GameManagement::cGameMode* CreateGameMode(GameManagement::cGameModeSession*);
  public: int RetKillPoints(Damage::eDamageActivator);
  public: int RetH2HKillPoints(CHARACTER::etH2HDamageTypes);
  public: int RetShotExplosiveKillPoints() const;
  public: int RetSuicidePoints() const;
  public: int RetDeathPoints() const;
  public: void SetHasDucks(bool);
  public: virtual ~cDeathMatchGameModePrototype();
  public: GameManagement::cDeathMatchGameModePrototype& operator=(const GameManagement::cDeathMatchGameModePrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
