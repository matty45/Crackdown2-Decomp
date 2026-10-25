
class AI::cPlayerRejectionZone : public ZoneManager::cPlayerTriggerZone { /* Size=0x100 */
  /* 0x0000: fields for ZoneManager::cPlayerTriggerZone */
  /* 0x00e0 */ public: Editor::cGUIDEventHandler<AI::cPlayerRejectionZone> m_EventHandler;
  /* 0x00f4 */ private: float m_fTimer;
  /* 0x00f8 */ private: float m_fCurrentTimer;
  /* 0x00fc */ private: float m_fImpulse;
  public: static const char* pcPlayerRejectionZoneClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPlayerRejectionZone(const AI::cPlayerRejectionZone&);
  public: cPlayerRejectionZone(const RWS::CAttributePacket&);
  public: virtual ~cPlayerRejectionZone();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void OnPlayerEnter(CHARACTER::cCharacter*);
  public: virtual void OnPlayerLeave(CHARACTER::cCharacter*);
  public: virtual void DebugDrawTriggerZone();
  public: virtual bool DoCollision(CHARACTER::cCharacter*);
  public: AI::cPlayerRejectionZone& operator=(const AI::cPlayerRejectionZone&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
