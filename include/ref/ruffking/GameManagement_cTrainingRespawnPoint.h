
class GameManagement::cTrainingRespawnPoint : public GameManagement::cGameModeSpawnPoint { /* Size=0x80 */
  /* 0x0000: fields for GameManagement::cGameModeSpawnPoint */
  /* 0x0060 */ private: Editor::cGUIDEventHandler<GameManagement::cTrainingRespawnPoint> m_EventHandler;
  public: static const char* pcTrainingRespawnPointClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTrainingRespawnPoint(const GameManagement::cTrainingRespawnPoint&);
  public: cTrainingRespawnPoint(const RWS::CAttributePacket&);
  public: virtual ~cTrainingRespawnPoint();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GameManagement::cTrainingRespawnPoint& operator=(const GameManagement::cTrainingRespawnPoint&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
