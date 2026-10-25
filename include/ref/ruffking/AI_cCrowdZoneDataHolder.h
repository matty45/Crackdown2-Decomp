
class AI::cCrowdZoneDataHolder : public cNonGameBase { /* Size=0xac */
  /* 0x0000: fields for cNonGameBase */
  public: static const char* pcCrowdZoneDataHolderClassID;
  public: static const char m_cCrowdZoneDataHolder_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcCrowdZoneDataHolderClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: cCrowdZoneDataHolder(const AI::cCrowdZoneDataHolder&);
  public: cCrowdZoneDataHolder(const RWS::CAttributePacket&);
  public: virtual ~cCrowdZoneDataHolder();
  public: AI::cCrowdZoneDataHolder& operator=(const AI::cCrowdZoneDataHolder&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
