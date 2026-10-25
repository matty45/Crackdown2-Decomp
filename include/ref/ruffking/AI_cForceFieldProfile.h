
class AI::cForceFieldProfile : public RWS::CAttributeHandler, public RWS::CSystemCommands { /* Size=0xe0 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CSystemCommands */
  /* 0x0018 */ private: Editor::cGUIDEventHandler<AI::cForceFieldProfile> m_EventHandler;
  /* 0x0030 */ public: AI::cForceField m_forceField;
  public: static const char* pcForceFieldProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cForceFieldProfile(const AI::cForceFieldProfile&);
  public: cForceFieldProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cForceFieldProfile();
  public: AI::cForceFieldProfile& operator=(const AI::cForceFieldProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
