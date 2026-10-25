
class AI::cTrainingRouteEvent : public AI::cBasePatrolRouteEvent { /* Size=0x90 */
  /* 0x0000: fields for AI::cBasePatrolRouteEvent */
  public: static const char m_cTrainingRouteEvent_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcTrainingRouteEventClass;
  public: static const char* pcTrainingRouteEventClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTrainingRouteEvent(const AI::cTrainingRouteEvent&);
  public: cTrainingRouteEvent(const RWS::CAttributePacket&);
  public: virtual ~cTrainingRouteEvent();
  public: AI::cTrainingRouteEvent& operator=(const AI::cTrainingRouteEvent&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
