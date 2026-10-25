
class AI::cTRCamLookAtStop : public AI::cTrainingRouteEvent { /* Size=0x90 */
  /* 0x0000: fields for AI::cTrainingRouteEvent */
  public: static const char m_cTRCamLookAtStop_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcTRCamLookAtStopClass;
  public: static const char* pcTRCamLookAtStopClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTRCamLookAtStop(const AI::cTRCamLookAtStop&);
  public: cTRCamLookAtStop(const RWS::CAttributePacket&);
  public: virtual ~cTRCamLookAtStop();
  public: AI::cTRCamLookAtStop& operator=(const AI::cTRCamLookAtStop&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
