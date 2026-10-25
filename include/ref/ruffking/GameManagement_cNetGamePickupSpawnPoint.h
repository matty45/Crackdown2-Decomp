
class GameManagement::cNetGamePickupSpawnPoint : public GameManagement::cNetGameSpawnPoint { /* Size=0xa0 */
  /* 0x0000: fields for GameManagement::cNetGameSpawnPoint */
  /* 0x0080 */ protected: unsigned short m_anPickupTypes[4];
  /* 0x0088 */ protected: unsigned char m_nNumPickupTypes;
  /* 0x008c */ protected: GameManagement::etNetGamePickupType m_eNetGamePickupType;
  /* 0x0090 */ protected: Fun_Runtime::cQNode<PHYSICS::cDynamicPickup>* m_pPickup;
  /* 0x0094 */ protected: unsigned int m_nRespawnTime;
  /* 0x0098 */ protected: unsigned int m_nRespawnDuration;
  public: static const char* pcNetGamePickupSpawnPointClassID;
  protected: static const unsigned char nMAX_TYPES;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cNetGamePickupSpawnPoint(const GameManagement::cNetGamePickupSpawnPoint&);
  public: cNetGamePickupSpawnPoint(const RWS::CAttributePacket&);
  public: virtual ~cNetGamePickupSpawnPoint();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GameManagement::etNetGamePickupType RetNetGamePickupType() const;
  public: unsigned int RetRespawnTime();
  public: bool CreatePickup(unsigned char);
  public: void DestroyPickup();
  public: void AttachPickup(Fun_Runtime::cQNode<PHYSICS::cDynamicPickup>*);
  public: void DetachPickup(Fun_Runtime::cQNode<PHYSICS::cDynamicPickup>*);
  public: void MakeAuthority();
  public: GameManagement::cNetGamePickupSpawnPoint& operator=(const GameManagement::cNetGamePickupSpawnPoint&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
