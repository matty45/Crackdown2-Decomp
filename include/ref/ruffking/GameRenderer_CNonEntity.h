
class GameRenderer::CNonEntity : public RWS::CAttributeHandler, public RWS::CSystemCommands, public RWS::DynamicAllocationPolicy { /* Size=0x1c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CSystemCommands */
  /* 0x0019: fields for RWS::DynamicAllocationPolicy */
  public: static const char* pCNonEntityClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: CNonEntity(const GameRenderer::CNonEntity&);
  public: CNonEntity(const RWS::CAttributePacket&);
  public: virtual ~CNonEntity();
  public: GameRenderer::CNonEntity& operator=(const GameRenderer::CNonEntity&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
