
class CHARACTER::cCwCharacterStateProfile : public cNonGameBase { /* Size=0xfc */
  /* 0x0000: fields for cNonGameBase */
  /* 0x00ac */ public: CHARACTER::StateData m_StateData[1];
  /* 0x00d8 */ public: Fun_Runtime::cString m_sProfileName;
  /* 0x00f4 */ public: RWS::CEventId m_Msg_Return_Self;
  public: static const char* pcCwCharacterStateProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCwCharacterStateProfile(const CHARACTER::cCwCharacterStateProfile&);
  public: cCwCharacterStateProfile(const RWS::CAttributePacket&);
  public: cCwCharacterStateProfile();
  public: virtual ~cCwCharacterStateProfile();
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: virtual bool AllocatedFromFixedPool();
  public: CHARACTER::cCwCharacterStateProfile& operator=(const CHARACTER::cCwCharacterStateProfile&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
};
