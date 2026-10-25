
class CHARACTER::cGenCharProfile : public cNonGameBase { /* Size=0xb4 */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac */ private: RWS::CEventId m_Msg_Return_Self;
  public: static const char m_cGenCharProfile_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcGenCharProfileClass;
  public: static const char* pcGenCharProfileClassID;
  private: static float m_fTargetingCombatRadius;
  private: static float m_fTargetingCombatDotLimit;
  private: static float m_fRagdollBlendOutTime;
  private: static CHARACTER::tCharAnimEventInfo m_aAnimEventInfo[128];
  private: static unsigned short m_UpdateCount;
  private: static float m_fTimeTillCatchFire;
  private: static float m_fTimeOnFire;
  private: static float m_fTimeOnFireRandFactor;
  private: static float m_fCollisionMinForceToCauseHighImpact;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGenCharProfile(const CHARACTER::cGenCharProfile&);
  public: cGenCharProfile(const RWS::CAttributePacket&);
  public: virtual ~cGenCharProfile();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  private: AI::cAIAnimEventProfile* GetAIAnimEventProfile(const char*);
  public: CHARACTER::cGenCharProfile& operator=(const CHARACTER::cGenCharProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static float RetTargetingCombatDotLimit();
  public: static float RetTargetingCombatRadius();
  public: static float RetRagdollBlendOutTime();
  public: static AI::cAIAnimEventProfile* RetAIAnimEventProfile(short);
  public: static unsigned short RetUpdateCount();
  public: static float RetTimeTillCatchFire();
  public: static float RetTimeOnFire();
  public: static float RetTimeOnFireRandFactor();
  public: static float RetCollisionMinForceToCauseHighImpact();
};
