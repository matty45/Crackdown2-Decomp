
class AI::cReaperJumpEvent : public AI::cBasePatrolRouteEvent { /* Size=0x90 */
  /* 0x0000: fields for AI::cBasePatrolRouteEvent */
  public: static const char m_cReaperJumpEvent_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcReaperJumpEventClass;
  public: static const char* pcReaperJumpEventClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cReaperJumpEvent(const AI::cReaperJumpEvent&);
  public: cReaperJumpEvent(const RWS::CAttributePacket&);
  public: virtual unsigned char RetEventType() const;
  public: virtual ~cReaperJumpEvent();
  public: AI::cReaperJumpEvent& operator=(const AI::cReaperJumpEvent&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
