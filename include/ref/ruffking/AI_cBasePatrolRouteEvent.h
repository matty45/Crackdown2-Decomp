
class AI::cBasePatrolRouteEvent : public RWS::CSystemCommands, public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy, public RWS::CEventHandler { /* Size=0x90 */
  /* 0x001c: fields for RWS::CSystemCommands */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x001d: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001d */ private: unsigned char m_EventType;
  /* 0x0020 */ private: Fun_Runtime::Mtx m_mMat;
  /* 0x0060 */ private: unsigned int m_nEventRepetitions;
  /* 0x0064 */ private: RWS::RWSGUID m_guidNextEvent;
  /* 0x0074 */ private: Editor::cGUIDEventHandler<AI::cBasePatrolRouteEvent> m_EventHandler;
  public: static const char m_cBasePatrolRouteEvent_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcBasePatrolRouteEventClass;
  public: static const char* pcBasePatrolRouteEventClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cBasePatrolRouteEvent(const AI::cBasePatrolRouteEvent&);
  public: cBasePatrolRouteEvent(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleSystemCommands(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: virtual unsigned char RetEventType() const;
  public: virtual const Fun_Runtime::Mtx& RetMatrix() const;
  public: virtual unsigned int RetNumRepetitions() const;
  public: virtual AI::cBasePatrolRouteEvent* RetNextEvent() const;
  protected: void SetEventType(unsigned char);
  private: void SetMat(const Fun_Runtime::Mtx&);
  public: virtual ~cBasePatrolRouteEvent();
  public: AI::cBasePatrolRouteEvent& operator=(const AI::cBasePatrolRouteEvent&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
