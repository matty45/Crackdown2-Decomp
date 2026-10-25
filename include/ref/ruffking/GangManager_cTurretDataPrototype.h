
class GangManager::cTurretDataPrototype : public RWS::CAttributeHandler { /* Size=0x40 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ public: GOM::cObjectPrototype* m_pTurretBasePrototype;
  /* 0x001c */ public: GOM::cObjectPrototype* m_pTurretWeaponPrototype;
  /* 0x0020 */ public: GangManager::cPedestrainDataPrototype** m_apGunners;
  /* 0x0024 */ public: int m_nNumGunners;
  /* 0x0028 */ public: int m_nGangStorageIndex;
  /* 0x002c */ public: Editor::cGUIDEventHandler<GangManager::cTurretDataPrototype> m_EventHandler;
  public: static const char* pcTurretDataPrototypeClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTurretDataPrototype(const GangManager::cTurretDataPrototype&);
  public: cTurretDataPrototype(const RWS::CAttributePacket&);
  public: virtual ~cTurretDataPrototype();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: int GetGangStorageIndex();
  public: void SetGangStorageIndex(int);
  public: GangManager::cTurretDataPrototype& operator=(const GangManager::cTurretDataPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
