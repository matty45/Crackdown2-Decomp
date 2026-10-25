
class VEHICLE_CONTROL::cVehicleCollectionZone : public AI::cHeliCallZone { /* Size=0x1c0 */
  /* 0x0000: fields for AI::cHeliCallZone */
  /* 0x01a0 */ protected: float m_fInnerZoneRadius;
  /* 0x01a4 */ protected: float m_fInnerZoneRadiusSq;
  /* 0x01a8 */ protected: AI::cAgencyGarage* m_pAgencyGarage;
  /* 0x01ac */ protected: char m_nCallType;
  /* 0x01b0 */ protected: unsigned int m_nSpawnPointID;
  /* 0x01b4 */ protected: unsigned int m_nCallObjID;
  public: static const char m_cVehicleCollectionZone_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcVehicleCollectionZoneClass;
  public: static const char* pcVehicleCollectionZoneClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cVehicleCollectionZone(const VEHICLE_CONTROL::cVehicleCollectionZone&);
  public: cVehicleCollectionZone(const RWS::CAttributePacket&);
  public: virtual ~cVehicleCollectionZone();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void OnPlayerEnter(CHARACTER::cCharacter*);
  public: virtual void OnPlayerLeave(CHARACTER::cCharacter*);
  public: virtual void InitTriggerZone();
  public: virtual void TermTriggerZone();
  public: bool IsVehicleWithinInnerZone(Vehicle::cVehicle*);
  public: bool IsWithinInnerZone(Fun_Runtime::Vec3);
  public: bool IsTargetValid(Vehicle::cVehicle*);
  public: Vehicle::cLandVehicle* LocateFirstCollectableVehicle();
  public: void SetAgencyGarage(AI::cAgencyGarage*);
  public: void SetActiveCollectionZone();
  public: virtual bool CanLocalPlayerCall();
  public: virtual bool CanCollectVehicle();
  public: virtual void Reset();
  public: void SetCalled(AI::cDeliveryManager::DeliveryType, unsigned int, unsigned int);
  public: virtual void RegisterCalled();
  public: virtual void DebugDrawTriggerZone();
  public: VEHICLE_CONTROL::cVehicleCollectionZone& operator=(const VEHICLE_CONTROL::cVehicleCollectionZone&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static const RWS::eRenderType RetRenderType();
  public: static bool IsCollectable(Vehicle::cVehicle*);
};
