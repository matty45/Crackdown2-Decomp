
class GameManagement::cCheckpointArena : public GameManagement::cGameModeArena { /* Size=0x10c */
  /* 0x0000: fields for GameManagement::cGameModeArena */
  /* 0x00f8 */ protected: Fun_Runtime::cVector<GameManagement::cGameModeCheckpoint *,Fun_Runtime::cAllocator<GameManagement::cGameModeCheckpoint *,3,&GameManagement::cCheckpointArena::tCheckpointPointList_FL> > m_vCheckpoints;
  /* 0x0108 */ protected: GameManagement::cGameModeStartZone* m_pStartTriggerZone;
  public: static const char* pcCheckpointArenaClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCheckpointArena(const GameManagement::cCheckpointArena&);
  public: cCheckpointArena(const RWS::CAttributePacket&);
  public: virtual void OnShutDownLevel();
  public: virtual bool IsCheckpointArena() const;
  public: virtual GameManagement::cGameModeStartZone* RetStartZone() const;
  public: virtual unsigned int RetNumCheckpoints() const;
  public: virtual GameManagement::cGameModeCheckpoint* RetCheckpoint(unsigned int) const;
  public: virtual void AddStartZone(GameManagement::cGameModeStartZone*);
  public: virtual void AddCheckpoint(GameManagement::cGameModeCheckpoint*);
  public: virtual ~cCheckpointArena();
  public: GameManagement::cCheckpointArena& operator=(const GameManagement::cCheckpointArena&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static Fun_Runtime::cFileLine tCheckpointPointList_FL();
};
