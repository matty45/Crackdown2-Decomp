
class AI::cStreamingDataHolder : public cNonGameBase { /* Size=0xac */
  /* 0x0000: fields for cNonGameBase */
  public: static const char* pcStreamingDataHolderClassID;
  public: static const char m_cStreamingDataHolder_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcStreamingDataHolderClass;
  private: static AI::cStreamingDataHolder* s_pStreamingDataHolder;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: cStreamingDataHolder(const AI::cStreamingDataHolder&);
  public: cStreamingDataHolder(const RWS::CAttributePacket&);
  public: virtual ~cStreamingDataHolder();
  private: void ProcessResource(const RWS::RWSGUID&);
  public: AI::cStreamingDataHolder& operator=(const AI::cStreamingDataHolder&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
