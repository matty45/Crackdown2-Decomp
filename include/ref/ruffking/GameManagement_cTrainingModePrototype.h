
class GameManagement::cTrainingModePrototype : public GameManagement::cGameModePrototype { /* Size=0x108 */
  /* 0x0000: fields for GameManagement::cGameModePrototype */
  /* 0x00f0 */ private: Editor::cGUIDEventHandler<GameManagement::cTrainingModePrototype> m_EventHandler;
  public: static const char* pcTrainingModePrototypeClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTrainingModePrototype(const GameManagement::cTrainingModePrototype&);
  public: cTrainingModePrototype(const RWS::CAttributePacket&);
  public: virtual bool IsCheckpointGame() const;
  public: virtual bool IsPvPGame() const;
  public: virtual bool CanHaveTeams() const;
  public: virtual bool CanHaveEndLimit() const;
  public: virtual bool CanHaveTimeLimit() const;
  public: virtual bool CanMigrateHost() const;
  public: virtual bool IsLobbyGame() const;
  public: virtual int RetMinPlayers() const;
  public: virtual int RetMaxPlayers() const;
  public: virtual int RetStringID() const;
  public: virtual GameManagement::cGameMode* CreateGameMode(GameManagement::cGameModeSession*);
  public: virtual GameManagement::etGameModeType RetType() const;
  public: virtual ~cTrainingModePrototype();
  public: GameManagement::cTrainingModePrototype& operator=(const GameManagement::cTrainingModePrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
