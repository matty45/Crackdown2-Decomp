
class AI::cAgencyGarage : public RWS::CSystemCommands, public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy, public GDb::cDebugPageHandler, public SaveGame::cLoadSaveObject { /* Size=0x3a0 */
  /* 0x0044: fields for RWS::CSystemCommands */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x0045: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c: fields for GDb::cDebugPageHandler */
  /* 0x0040: fields for SaveGame::cLoadSaveObject */
  /* 0x0045 */ public: unsigned char m_nDebugIndex;
  /* 0x0046 */ public: bool m_bInVehicleScreen;
  /* 0x0047 */ public: bool m_bInWeaponScreen;
  /* 0x0048 */ private: Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> > m_vStoredVehicles;
  /* 0x0058 */ private: Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> > m_vStoredFirearms;
  /* 0x0068 */ private: Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> > m_vStoredExplosives;
  /* 0x0078 */ private: Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> > m_vLevelVehicles[6];
  /* 0x00d8 */ private: Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> > m_vLevelFirearms[6];
  /* 0x0138 */ private: Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> > m_vLevelExplosives[6];
  /* 0x01a0 */ private: Fun_Runtime::cVectorip<AI::cHeliCallZone *,100> m_vCallZones;
  /* 0x0340 */ private: int m_nCollectionZones;
  /* 0x0344 */ private: int m_nDropZones;
  /* 0x0348 */ private: GOM::cObjectPrototype* m_pHeliPrototype;
  /* 0x034c */ private: char m_nCurrentDrivingLevel;
  /* 0x034d */ private: char m_nCurrentFirearmsLevel;
  /* 0x034e */ private: char m_nCurrentExplosivesLevel;
  /* 0x0350 */ private: Fun_Runtime::Mtx m_mMat;
  /* 0x0390 */ private: bool m_bStoredUVWeapon;
  public: static const char m_cAgencyGarage_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAgencyGarageClass;
  public: static const char* pcAgencyGarageClassID;
  private: static VEHICLE_CONTROL::cVehicleCollectionZone* m_pActiveCollectionZone;
  public: static AI::cAgencyGarage* m_spAgencyGarage;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAgencyGarage(const AI::cAgencyGarage&);
  public: cAgencyGarage(const RWS::CAttributePacket&);
  public: virtual ~cAgencyGarage();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleSystemCommands(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: const Fun_Runtime::Mtx& RetTransform() const;
  public: void TickUpdate();
  public: void UserStoreVehicle(unsigned int);
  public: AI::cAgencyGarage::eLevel StoreVehicle(unsigned int);
  public: AI::cAgencyGarage::eLevel StoreFirearm(unsigned int);
  public: AI::cAgencyGarage::eLevel StoreExplosive(unsigned int);
  public: bool IsVehicleStored(unsigned int);
  public: bool IsFirearmStored(unsigned int);
  public: bool IsExplosiveStored(unsigned int);
  public: bool IsUVWeaponStored() const;
  public: char RetLevelVehicleUnlockedAt(unsigned int);
  public: char RetLevelFirearmUnlockedAt(unsigned int);
  public: char RetLevelExplosiveUnlockedAt(unsigned int);
  public: bool IsFirearmAvailable(unsigned int);
  public: bool IsExplosiveAvailable(unsigned int);
  public: GOM::cObjectPrototype* RetHeliPrototype();
  public: AI::cHeliCallZone* RetCallZone(unsigned int);
  public: virtual void Save(SaveGame::cSaveStream*);
  public: virtual void Load(SaveGame::cLoadStream*);
  public: virtual void RenderDebugPage(int, int);
  public: virtual void DebugPageUp();
  public: virtual void DebugPageDown();
  public: virtual void DebugPageEnter();
  private: void SetMat(const Fun_Runtime::Mtx&);
  private: void TestForStoredUVWeapons();
  public: const Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> >& RetStoredVehicles();
  public: const Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> >& RetStoredFirearms();
  public: const Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> >& RetStoredExplosives();
  public: int RetNumCollectionZones();
  public: int RetNumDropZones();
  public: void NetSendCallZoneRequest(unsigned int);
  public: void NetReceiveCallZoneRequest(SBitStream&, unsigned char);
  public: void NetSendCallZoneResponse(unsigned int, bool);
  public: void NetReceiveCallZoneResponse(SBitStream&, unsigned char);
  public: AI::cAgencyGarage& operator=(const AI::cAgencyGarage&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static void SetActiveCollectionZone(VEHICLE_CONTROL::cVehicleCollectionZone*);
  public: static VEHICLE_CONTROL::cVehicleCollectionZone* RetActiveCollectionZone();
  public: static Fun_Runtime::cFileLine vObjPrototypes_FL();
  private: static void SavePrototypes(SaveGame::cSaveStream*, const Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> >&);
  private: static void LoadPrototypes(SaveGame::cLoadStream*, Fun_Runtime::cVector<GOM::cObjectPrototype *,Fun_Runtime::cAllocator<GOM::cObjectPrototype *,39,&AI::cAgencyGarage::vObjPrototypes_FL> >&);
  public: static AI::cAgencyGarage* RetAgencyGarage();
};
