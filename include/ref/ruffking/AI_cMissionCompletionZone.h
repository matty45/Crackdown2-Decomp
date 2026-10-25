
class AI::cMissionCompletionZone : public ZoneManager::cPlayerTriggerZone { /* Size=0xf0 */
  /* 0x0000: fields for ZoneManager::cPlayerTriggerZone */
  /* 0x00e0 */ private: AI::cMission* m_pMission;
  /* 0x00e4 */ private: unsigned int m_nCompletionDuration;
  /* 0x00e8 */ private: unsigned int m_nEnteredTime;
  public: static const int s_nDefaultEnteredTime;
  public: static const char* pcMissionCompletionZoneClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cMissionCompletionZone(const AI::cMissionCompletionZone&);
  public: cMissionCompletionZone(const RWS::CAttributePacket&);
  public: virtual ~cMissionCompletionZone();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void OnPlayerEnter(CHARACTER::cCharacter*);
  public: virtual void OnPlayerLeave(CHARACTER::cCharacter*);
  public: AI::cMission* RetMission() const;
  public: unsigned int RetEnteredTime() const;
  public: unsigned int RetCompletionDuration() const;
  public: unsigned int RetCompletionGameTime() const;
  public: virtual void DebugDrawTriggerZone();
  public: AI::cMissionCompletionZone& operator=(const AI::cMissionCompletionZone&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
