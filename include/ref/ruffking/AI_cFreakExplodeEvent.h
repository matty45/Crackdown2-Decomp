
class AI::cFreakExplodeEvent : public AI::cBasePatrolRouteEvent { /* Size=0x90 */
  /* 0x0000: fields for AI::cBasePatrolRouteEvent */
  public: static const char m_cFreakExplodeEvent_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcFreakExplodeEventClass;
  public: static const char* pcFreakExplodeEventClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cFreakExplodeEvent(const AI::cFreakExplodeEvent&);
  public: cFreakExplodeEvent(const RWS::CAttributePacket&);
  public: virtual unsigned char RetEventType() const;
  public: virtual ~cFreakExplodeEvent();
  public: AI::cFreakExplodeEvent& operator=(const AI::cFreakExplodeEvent&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
