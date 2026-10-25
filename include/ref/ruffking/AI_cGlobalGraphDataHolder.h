
class AI::cGlobalGraphDataHolder : public RWS::CAttributeHandler { /* Size=0x18 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  public: static const char* pcGlobalGraphDataHolderClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGlobalGraphDataHolder(const AI::cGlobalGraphDataHolder&);
  public: cGlobalGraphDataHolder(const RWS::CAttributePacket&);
  private: void RegisterGraph(AI::eGlobalGraphType, const RWS::RWSGUID&);
  public: virtual ~cGlobalGraphDataHolder();
  public: AI::cGlobalGraphDataHolder& operator=(const AI::cGlobalGraphDataHolder&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
