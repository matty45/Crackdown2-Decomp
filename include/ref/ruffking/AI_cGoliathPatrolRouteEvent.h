
class AI::cGoliathPatrolRouteEvent : public AI::cBasePatrolRouteEvent { /* Size=0xa0 */
  /* 0x0000: fields for AI::cBasePatrolRouteEvent */
  /* 0x0090 */ private: GOM::cObjectPrototype* m_pThrowPrototype;
  /* 0x0094 */ private: int m_nAnimID;
  /* 0x0098 */ private: bool m_bEarlyFinishPermitted;
  public: static const char m_cGoliathPatrolRouteEvent_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcGoliathPatrolRouteEventClass;
  public: static const char* pcGoliathPatrolRouteEventClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGoliathPatrolRouteEvent(const AI::cGoliathPatrolRouteEvent&);
  public: cGoliathPatrolRouteEvent(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GOM::cObjectPrototype* RetThrowPrototype() const;
  public: int RetAnimID() const;
  public: bool IsEarlyFinishPermited() const;
  public: virtual ~cGoliathPatrolRouteEvent();
  public: AI::cGoliathPatrolRouteEvent& operator=(const AI::cGoliathPatrolRouteEvent&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
