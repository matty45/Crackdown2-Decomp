
class ZoneManager::cVOAZone : public ZoneManager::cPlayerTriggerZone { /* Size=0x100 */
  /* 0x0000: fields for ZoneManager::cPlayerTriggerZone */
  /* 0x00e0 */ private: Fun_Runtime::cStringc m_strName;
  public: static const char* pcVOAZoneClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cVOAZone(const ZoneManager::cVOAZone&);
  public: cVOAZone(const RWS::CAttributePacket&);
  public: virtual ~cVOAZone();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void OnPlayerEnter(CHARACTER::cCharacter*);
  public: virtual void OnPlayerLeave(CHARACTER::cCharacter*);
  public: virtual void Load(SaveGame::cLoadStream*);
  public: virtual void Save(SaveGame::cSaveStream*);
  public: virtual void DebugDrawTriggerZone();
  public: ZoneManager::cVOAZone& operator=(const ZoneManager::cVOAZone&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
