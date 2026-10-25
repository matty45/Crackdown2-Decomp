
class AI::cTrainingTrigger : public ZoneManager::cPlayerTriggerZone { /* Size=0x110 */
  /* 0x0000: fields for ZoneManager::cPlayerTriggerZone */
  /* 0x00e0 */ private: Editor::cGUIDEventHandler<AI::cTrainingTrigger> m_EventHandler;
  /* 0x00f4 */ private: unsigned char m_nTriggerFlags;
  /* 0x00f8 */ public: float m_fMaxYScale;
  /* 0x00fc */ public: float m_fMaxXZScale;
  /* 0x0100 */ public: float m_fYOffset;
  public: static const char* pcTrainingTriggerClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTrainingTrigger(const AI::cTrainingTrigger&);
  public: cTrainingTrigger(const RWS::CAttributePacket&);
  public: virtual ~cTrainingTrigger();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void OnPlayerEnter(CHARACTER::cCharacter*);
  public: virtual void OnPlayerLeave(CHARACTER::cCharacter*);
  public: bool IsTriggered();
  public: void ClearTrigger();
  public: AI::cTrainingTrigger& operator=(const AI::cTrainingTrigger&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
