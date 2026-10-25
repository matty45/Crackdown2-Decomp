
class AI::cForceFieldVFXProfile : public RWS::CAttributeHandler, public RWS::CSystemCommands { /* Size=0x18 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CSystemCommands */
  public: static int ms_nOpenVFXID;
  public: static int ms_nClosedVFXID;
  public: static float ms_fVFXScaleFactor;
  public: static const char* pcForceFieldVFXProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cForceFieldVFXProfile(const AI::cForceFieldVFXProfile&);
  public: cForceFieldVFXProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cForceFieldVFXProfile();
  public: AI::cForceFieldVFXProfile& operator=(const AI::cForceFieldVFXProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
