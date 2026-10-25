
class CHARACTER::cAgentTintProfile : public RWS::CAttributeHandler { /* Size=0x18 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  private: static _XMCOLOR ms_anPalette[9];
  public: static const char* pcAgentTintProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAgentTintProfile(const CHARACTER::cAgentTintProfile&);
  public: cAgentTintProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cAgentTintProfile();
  public: CHARACTER::cAgentTintProfile& operator=(const CHARACTER::cAgentTintProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static _XMCOLOR RetTintColour(CHARACTER::eAgentTint);
};
