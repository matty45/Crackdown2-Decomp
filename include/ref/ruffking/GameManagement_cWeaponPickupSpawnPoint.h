
class GameManagement::cWeaponPickupSpawnPoint : public GameManagement::cNetGameSpawnPoint { /* Size=0xd0 */
  /* 0x0000: fields for GameManagement::cNetGameSpawnPoint */
  /* 0x0080 */ private: Editor::cGUIDEventHandler<GameManagement::cWeaponPickupSpawnPoint> m_EventHandler;
  /* 0x0094 */ protected: Fun_Runtime::cStringc m_sWeaponPrototypeName;
  /* 0x00b0 */ protected: Fun_Runtime::cSafeDeletablePointer<Equip::cEquipment> m_pEquipment;
  /* 0x00c0 */ protected: unsigned int m_nAmmoCount;
  /* 0x00c4 */ protected: unsigned int m_nRespawnTimer;
  /* 0x00c8 */ protected: unsigned int m_nRespawnDuration;
  public: static const char* pcWeaponPickupSpawnPointClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cWeaponPickupSpawnPoint(const GameManagement::cWeaponPickupSpawnPoint&);
  public: cWeaponPickupSpawnPoint(const RWS::CAttributePacket&);
  public: virtual ~cWeaponPickupSpawnPoint();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool CreateWeapon(unsigned char);
  public: virtual void DestroyWeapon();
  public: void AttachWeapon(Equip::cEquipment*);
  public: void MakeAuthority();
  public: void FlagForRespawn();
  public: void SetRespawnDuration(unsigned int);
  public: GOM::cObjectPrototype* RetPrototype();
  public: Equip::cEquipment* RetWeapon();
  public: unsigned short RetAmmoCount() const;
  public: unsigned int RetRespawnTime();
  public: GameManagement::cWeaponPickupSpawnPoint& operator=(const GameManagement::cWeaponPickupSpawnPoint&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
