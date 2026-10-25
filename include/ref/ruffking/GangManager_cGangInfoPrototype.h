
class GangManager::cGangInfoPrototype : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0xb4 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ public: GangManager::eFactions m_GangAffiliation;
  /* 0x001c */ public: GangManager::GangTODData m_DaytimeData;
  /* 0x003c */ public: GangManager::GangTODData m_NighttimeData;
  /* 0x005c */ public: bool m_bUseNightData;
  /* 0x005d */ public: bool m_bUseBeaconScalars;
  /* 0x0060 */ public: float m_fBeaconNightTrafficScalars[3];
  /* 0x006c */ public: unsigned int m_nARVehicleLimits[6];
  /* 0x0084 */ public: unsigned int m_nARPedLimits[6];
  /* 0x009c */ public: Editor::cGUIDEventHandler<GangManager::cGangInfoPrototype> m_EventHandler;
  /* 0x00b0 */ public: GangManager::cGangInfo* m_pGeneratedGang;
  public: static const char* pcGangInfoPrototypeClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGangInfoPrototype(const GangManager::cGangInfoPrototype&);
  public: cGangInfoPrototype(const RWS::CAttributePacket&);
  public: virtual ~cGangInfoPrototype();
  public: void PurgeTODData(GangManager::GangTODData&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: void SetTrafficDensityForTOD(RWS::CAttributeCommandIterator&, GangManager::GangTODData&);
  public: void PopulateVehicleDataForTOD(RWS::CAttributeCommandIterator&, GangManager::GangTODData&);
  public: void PopulatePedDataForTOD(RWS::CAttributeCommandIterator&, GangManager::GangTODData&);
  public: void PopulateTurretDataForTOD(RWS::CAttributeCommandIterator&, GangManager::GangTODData&);
  public: void ClearTODData(GangManager::GangTODData&);
  public: GangManager::cGangInfoPrototype& operator=(const GangManager::cGangInfoPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
