
class AI::cTrainingVOARouteEvent : public AI::cTrainingRouteEvent { /* Size=0xa0 */
  /* 0x0000: fields for AI::cTrainingRouteEvent */
  /* 0x0090 */ private: AI::eTrainingVOA m_nVOATriggerID;
  public: static const char m_cTrainingVOARouteEvent_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcTrainingVOARouteEventClass;
  public: static const char* pcTrainingVOARouteEventClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTrainingVOARouteEvent(const AI::cTrainingVOARouteEvent&);
  public: cTrainingVOARouteEvent(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: unsigned int RetVOATriggerID() const;
  public: virtual ~cTrainingVOARouteEvent();
  public: AI::cTrainingVOARouteEvent& operator=(const AI::cTrainingVOARouteEvent&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
