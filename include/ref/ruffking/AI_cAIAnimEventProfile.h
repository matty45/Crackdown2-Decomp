
class AI::cAIAnimEventProfile : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy, public Fun_Runtime::cRegisteredClass { /* Size=0x4c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x0020: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c: fields for Fun_Runtime::cRegisteredClass */
  /* 0x0020 */ protected: float m_fRadius;
  /* 0x0024 */ protected: AI::etAIAnimEventType m_nAIAnimEventType;
  /* 0x0028 */ protected: Fun_Runtime::cString m_sProfileName;
  /* 0x0044 */ protected: RWS::CEventId m_Msg_Return_Self;
  public: static const char m_cAIAnimEventProfile_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAIAnimEventProfileClass;
  public: static const char* pcAIAnimEventProfileClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAIAnimEventProfile(const AI::cAIAnimEventProfile&);
  public: cAIAnimEventProfile(const RWS::CAttributePacket&);
  public: virtual ~cAIAnimEventProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: float RetRadius();
  public: AI::etAIAnimEventType RetAIAnimEventType();
  public: const Fun_Runtime::cString& RetName();
  public: AI::cAIAnimEventProfile& operator=(const AI::cAIAnimEventProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
