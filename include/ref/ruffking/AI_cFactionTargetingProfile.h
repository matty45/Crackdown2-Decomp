
class AI::cFactionTargetingProfile : public RWS::CAttributeHandler { /* Size=0x50 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: AI::tAIFactionTargetData m_FactionData;
  /* 0x003c */ private: Editor::cGUIDEventHandler<AI::cFactionTargetingProfile> m_EventHandler;
  public: static const char* pcFactionTargetingProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cFactionTargetingProfile(const AI::cFactionTargetingProfile&);
  public: cFactionTargetingProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: const AI::tAIFactionTargetData* RetFactionTargetData() const;
  private: void SetupTargetData(const RWS::RWSGUID, GangManager::eFactions);
  public: virtual ~cFactionTargetingProfile();
  public: AI::cFactionTargetingProfile& operator=(const AI::cFactionTargetingProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
