
class GameManagement::cTeamDeathMatchGameModePrototype : public GameManagement::cDeathMatchGameModePrototype { /* Size=0x188 */
  /* 0x0000: fields for GameManagement::cDeathMatchGameModePrototype */
  public: static const char* pcTeamDeathMatchGameModePrototypeClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTeamDeathMatchGameModePrototype(const GameManagement::cTeamDeathMatchGameModePrototype&);
  public: cTeamDeathMatchGameModePrototype(const RWS::CAttributePacket&);
  public: virtual GameManagement::etGameModeType RetType() const;
  public: virtual bool CanHaveTeams() const;
  public: virtual int RetStringID() const;
  public: virtual unsigned int RetForceRespawnTime_msec() const;
  public: virtual GameManagement::cGameMode* CreateGameMode(GameManagement::cGameModeSession*);
  public: virtual ~cTeamDeathMatchGameModePrototype();
  public: GameManagement::cTeamDeathMatchGameModePrototype& operator=(const GameManagement::cTeamDeathMatchGameModePrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
