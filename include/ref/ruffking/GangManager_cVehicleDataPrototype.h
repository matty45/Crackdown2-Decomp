
class GangManager::cVehicleDataPrototype : public RWS::CAttributeHandler { /* Size=0x58 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ public: GOM::cObjectPrototype* m_pVehiclePrototype;
  /* 0x001c */ public: GOM::cObjectPrototype* m_pAttachedWeaponPrototype1;
  /* 0x0020 */ public: GOM::cObjectPrototype* m_pAttachedWeaponPrototype2;
  /* 0x0024 */ public: GangManager::cPedestrainDataPrototype** m_apDrivers;
  /* 0x0028 */ public: int m_nNumDrivers;
  /* 0x002c */ public: int m_nMinLevel;
  /* 0x0030 */ public: int m_nMaxLevel;
  /* 0x0034 */ public: float m_fProbability;
  /* 0x0038 */ public: int m_nGangStorageIndex;
  /* 0x003c */ public: bool m_bEnforcer;
  /* 0x003d */ public: bool m_bFlyingVehicle;
  /* 0x003e */ public: bool m_bHasAttachedWeapons;
  /* 0x003f */ public: bool m_bOneManVehicle;
  /* 0x0040 */ public: unsigned int m_nMaxSpeed;
  /* 0x0044 */ public: Editor::cGUIDEventHandler<GangManager::cVehicleDataPrototype> m_EventHandler;
  public: static const char* pcVehicleDataPrototypeClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cVehicleDataPrototype(const GangManager::cVehicleDataPrototype&);
  public: cVehicleDataPrototype(const RWS::CAttributePacket&);
  public: virtual ~cVehicleDataPrototype();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: int GetGangStorageIndex();
  public: void SetGangStorageIndex(int);
  public: GangManager::cVehicleDataPrototype& operator=(const GangManager::cVehicleDataPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
