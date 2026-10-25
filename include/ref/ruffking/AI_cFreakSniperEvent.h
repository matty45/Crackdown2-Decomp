
class AI::cFreakSniperEvent : public AI::cBasePatrolRouteEvent { /* Size=0x90 */
  /* 0x0000: fields for AI::cBasePatrolRouteEvent */
  public: static const char m_cFreakSniperEvent_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcFreakSniperEventClass;
  public: static const char* pcFreakSniperEventClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cFreakSniperEvent(const AI::cFreakSniperEvent&);
  public: cFreakSniperEvent(const RWS::CAttributePacket&);
  public: virtual unsigned char RetEventType() const;
  public: virtual ~cFreakSniperEvent();
  public: AI::cFreakSniperEvent& operator=(const AI::cFreakSniperEvent&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
