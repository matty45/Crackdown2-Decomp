
class GameManagement::cRooftopRaceGameModePrototype : public GameManagement::cCheckpointRaceGameModePrototype { /* Size=0x140 */
  /* 0x0000: fields for GameManagement::cCheckpointRaceGameModePrototype */
  public: static const char* pcRooftopRaceGameModePrototypeClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cRooftopRaceGameModePrototype(const GameManagement::cRooftopRaceGameModePrototype&);
  public: cRooftopRaceGameModePrototype(const RWS::CAttributePacket&);
  public: virtual GameManagement::etGameModeType RetType() const;
  public: virtual int RetStartVFXType() const;
  public: virtual int RetLOD1VFXType() const;
  public: virtual int RetLOD2VFXType() const;
  public: virtual int RetEndVFXType() const;
  public: virtual int RetStringID() const;
  public: virtual RPG::eSkills RetRewardSkillType() const;
  public: virtual GameManagement::cGameMode* CreateGameMode(GameManagement::cGameModeSession*);
  public: virtual ~cRooftopRaceGameModePrototype();
  public: GameManagement::cRooftopRaceGameModePrototype& operator=(const GameManagement::cRooftopRaceGameModePrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
