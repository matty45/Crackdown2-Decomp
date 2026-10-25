
class ZoneManager::cAmbienceZone : public ZoneManager::cPlayerTriggerZone { /* Size=0x110 */
  /* 0x0000: fields for ZoneManager::cPlayerTriggerZone */
  /* 0x00e0 */ private: Fun_Runtime::cString m_strName;
  /* 0x00fc */ private: unsigned int m_nDebugZoneColour;
  /* 0x0100 */ private: bool m_bPreviouslyEntered;
  /* 0x0101 */ private: bool m_bPreviouslyLeft;
  /* 0x0102 */ private: bool m_bIndoor;
  public: static const char* pcAmbienceZoneClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAmbienceZone(const ZoneManager::cAmbienceZone&);
  public: cAmbienceZone(const RWS::CAttributePacket&);
  public: virtual ~cAmbienceZone();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void InitTriggerZone();
  public: virtual void TermTriggerZone();
  public: virtual void OnPlayerEnter(CHARACTER::cCharacter*);
  public: virtual void OnPlayerLeave(CHARACTER::cCharacter*);
  public: virtual void DebugDrawTriggerZone();
  public: ZoneManager::cAmbienceZone& operator=(const ZoneManager::cAmbienceZone&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
