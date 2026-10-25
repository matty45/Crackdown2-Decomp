
class GameManagement::cGameModeSpawnPoint : public RWS::CSystemCommands, public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x60 */
  /* 0x0018: fields for RWS::CSystemCommands */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0019: fields for RWS::DynamicAllocationPolicy */
  /* 0x0020 */ protected: Fun_Runtime::Mtx m_Transform;
  public: static const char* pcGameModeSpawnPointClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGameModeSpawnPoint(const GameManagement::cGameModeSpawnPoint&);
  public: cGameModeSpawnPoint(const RWS::CAttributePacket&);
  public: cGameModeSpawnPoint();
  public: virtual ~cGameModeSpawnPoint();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: const Fun_Runtime::Mtx& RetTransform() const;
  public: Fun_Runtime::Vec3 RetPosition() const;
  public: virtual bool IsActive() const;
  public: virtual int RetArenaIndex() const;
  public: GameManagement::cGameModeSpawnPoint& operator=(const GameManagement::cGameModeSpawnPoint&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
