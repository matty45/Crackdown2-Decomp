
class GangManager::cAgressiveResponseTurretVehicleSetup : public RWS::CAttributeHandler { /* Size=0x68 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ protected: Editor::cGUIDEventHandler<GangManager::cAgressiveResponseTurretVehicleSetup> m_EventHandler;
  /* 0x002c */ protected: GangManager::tAgressiveResponseTurretTeamTemplate m_TurretTeamTemplate;
  /* 0x0060 */ protected: float m_fProbability;
  /* 0x0064 */ protected: unsigned char m_nValidFromLevel;
  /* 0x0065 */ protected: unsigned char m_nValidToLevel;
  public: static const char* pcAgressiveResponseTurretVehicleSetupClassID;
  public: static unsigned int _cAgressiveResponseTurretVehicleSetupClassIDHash;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAgressiveResponseTurretVehicleSetup(const GangManager::cAgressiveResponseTurretVehicleSetup&);
  public: cAgressiveResponseTurretVehicleSetup(const RWS::CAttributePacket&);
  public: virtual ~cAgressiveResponseTurretVehicleSetup();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GangManager::tAgressiveResponseTurretTeamTemplate* RetTemplate();
  public: unsigned char RetMinLevel();
  public: unsigned char RetMaxLevel();
  public: float RetProbability();
  protected: void ResetTemplateData();
  public: GangManager::cAgressiveResponseTurretVehicleSetup& operator=(const GangManager::cAgressiveResponseTurretVehicleSetup&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static unsigned int RetRWSClassNameHash();
};
