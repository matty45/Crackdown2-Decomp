
class GangManager::cAgressiveResponseConfigData : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x44 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ public: unsigned int m_nMaxNumVehicles;
  /* 0x001c */ public: unsigned int m_nMinTimeBetweenSpawnTicks;
  /* 0x0020 */ public: unsigned int m_nMaxTimeBetweenSpawnTicks;
  /* 0x0024 */ public: float m_fMinSpawnPlayerSpeed;
  /* 0x0028 */ public: float m_fMaxSpawnPlayerSpeed;
  /* 0x002c */ public: float m_fMinAVPadding;
  /* 0x0030 */ public: float m_fMaxAVPadding;
  /* 0x0034 */ public: RWS::RWSGUID m_nGlobalPKGangGUID;
  public: static const char* pcAgressiveResponseConfigDataClassID;
  
  public: cAgressiveResponseConfigData(const GangManager::cAgressiveResponseConfigData&);
  public: cAgressiveResponseConfigData(const RWS::CAttributePacket&);
  public: virtual ~cAgressiveResponseConfigData();
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GangManager::cAgressiveResponseConfigData& operator=(const GangManager::cAgressiveResponseConfigData&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
