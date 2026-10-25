
class UI::cAgentColour : public RWS::CAttributeHandler { /* Size=0x18 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  public: static const char* pcAgentColourClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAgentColour(const UI::cAgentColour&);
  public: cAgentColour(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cAgentColour();
  public: UI::cAgentColour& operator=(const UI::cAgentColour&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
