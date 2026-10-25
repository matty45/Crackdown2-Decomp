
class CHARACTER::cGameDamageProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x3c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ private: float m_fPlayerToAIDamageModifier;
  /* 0x001c */ private: float m_fAIToPlayerDamageModifier;
  /* 0x0020 */ private: float m_fAIToAIDamageModifier;
  /* 0x0024 */ private: float m_fPlayerToPlayerDamageModifier;
  /* 0x0028 */ private: Editor::cGUIDEventHandler<CHARACTER::cGameDamageProfile> m_EventHandler;
  public: static const char* pcGameDamageProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGameDamageProfile(const CHARACTER::cGameDamageProfile&);
  public: cGameDamageProfile(const RWS::CAttributePacket&);
  public: virtual ~cGameDamageProfile();
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: float RetPlayerToAIDamageModifier() const;
  public: float RetAIToPlayerDamageModifier() const;
  public: float RetAIToAIDamageModifier() const;
  public: float RetPlayerToPlayerDamageModifier() const;
  public: CHARACTER::cGameDamageProfile& operator=(const CHARACTER::cGameDamageProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
