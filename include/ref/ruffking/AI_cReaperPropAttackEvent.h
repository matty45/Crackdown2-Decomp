
class AI::cReaperPropAttackEvent : public AI::cBasePatrolRouteEvent { /* Size=0x90 */
  /* 0x0000: fields for AI::cBasePatrolRouteEvent */
  public: static const char m_cReaperPropAttackEvent_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcReaperPropAttackEventClass;
  public: static const char* pcReaperPropAttackEventClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cReaperPropAttackEvent(const AI::cReaperPropAttackEvent&);
  public: cReaperPropAttackEvent(const RWS::CAttributePacket&);
  public: virtual unsigned char RetEventType() const;
  public: virtual ~cReaperPropAttackEvent();
  public: AI::cReaperPropAttackEvent& operator=(const AI::cReaperPropAttackEvent&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
