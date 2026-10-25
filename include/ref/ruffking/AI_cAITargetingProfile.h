
class AI::cAITargetingProfile : public RWS::CAttributeHandler { /* Size=0x3c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: AI::tAITargetData m_TargetData;
  /* 0x0028 */ private: Editor::cGUIDEventHandler<AI::cAITargetingProfile> m_EventHandler;
  public: static const char* pcAITargetingProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAITargetingProfile(const AI::cAITargetingProfile&);
  public: cAITargetingProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: const AI::tAITargetData* RetData() const;
  public: virtual ~cAITargetingProfile();
  public: AI::cAITargetingProfile& operator=(const AI::cAITargetingProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
