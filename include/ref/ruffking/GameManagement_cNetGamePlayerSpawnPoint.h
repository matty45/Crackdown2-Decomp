
class GameManagement::cNetGamePlayerSpawnPoint : public GameManagement::cNetGameSpawnPoint { /* Size=0x90 */
  /* 0x0000: fields for GameManagement::cNetGameSpawnPoint */
  /* 0x0080 */ protected: unsigned char m_nTeamID;
  /* 0x0084 */ protected: GameManagement::etPlayerSpawnPointType m_ePlayerSpawnPointType;
  /* 0x0088 */ protected: unsigned int m_nReactivateTime;
  public: static const char* pcNetGamePlayerSpawnPointClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cNetGamePlayerSpawnPoint(const GameManagement::cNetGamePlayerSpawnPoint&);
  public: cNetGamePlayerSpawnPoint(const RWS::CAttributePacket&);
  public: virtual ~cNetGamePlayerSpawnPoint();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: unsigned char RetTeamID() const;
  public: bool IsSoloSpawnPoint() const;
  public: bool IsTeamSpawnPoint() const;
  public: void SetInactive(unsigned int);
  public: virtual bool IsActive() const;
  public: unsigned int RetReactivateTime() const;
  public: GameManagement::cNetGamePlayerSpawnPoint& operator=(const GameManagement::cNetGamePlayerSpawnPoint&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
