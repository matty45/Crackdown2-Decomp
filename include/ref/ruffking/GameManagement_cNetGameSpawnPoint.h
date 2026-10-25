
class GameManagement::cNetGameSpawnPoint : public GameManagement::cGameModeSpawnPoint { /* Size=0x80 */
  /* 0x0000: fields for GameManagement::cGameModeSpawnPoint */
  /* 0x0060 */ protected: Fun_Runtime::cStringc m_sArenaName;
  /* 0x007c */ protected: int m_nArenaIndex;
  public: static const char* pcNetGameSpawnPointClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cNetGameSpawnPoint(const GameManagement::cNetGameSpawnPoint&);
  public: cNetGameSpawnPoint(const RWS::CAttributePacket&);
  public: virtual ~cNetGameSpawnPoint();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: const Fun_Runtime::cStringc& RetArenaName() const;
  public: void SetArenaIndex(int);
  public: virtual int RetArenaIndex() const;
  public: GameManagement::cNetGameSpawnPoint& operator=(const GameManagement::cNetGameSpawnPoint&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
