
class AI::cMissionActivationZone : public ZoneManager::cPlayerTriggerZone { /* Size=0x100 */
  /* 0x0000: fields for ZoneManager::cPlayerTriggerZone */
  /* 0x00e0 */ public: Editor::cGUIDEventHandler<AI::cMissionActivationZone> m_EventHandler;
  public: static const char* pcMissionActivationZoneClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cMissionActivationZone(const AI::cMissionActivationZone&);
  public: cMissionActivationZone(const RWS::CAttributePacket&);
  public: virtual ~cMissionActivationZone();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void OnPlayerEnter(CHARACTER::cCharacter*);
  public: virtual void OnPlayerLeave(CHARACTER::cCharacter*);
  public: virtual void DebugDrawTriggerZone();
  public: AI::cMissionActivationZone& operator=(const AI::cMissionActivationZone&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
