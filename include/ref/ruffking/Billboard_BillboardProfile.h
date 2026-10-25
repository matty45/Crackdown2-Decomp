
class Billboard::BillboardProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x64 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ protected: Fun_Runtime::cVector<Billboard::BillboardData *,Fun_Runtime::cAllocator<Billboard::BillboardData *,62,&Billboard::BillboardProfile::tVideoDataVec_FL> > m_vBeaconNumberVideos;
  /* 0x0028 */ protected: Fun_Runtime::cVector<Billboard::BillboardData *,Fun_Runtime::cAllocator<Billboard::BillboardData *,62,&Billboard::BillboardProfile::tVideoDataVec_FL> > m_vAgentAppreciationVideos;
  /* 0x0038 */ protected: Fun_Runtime::cVector<Billboard::BillboardData *,Fun_Runtime::cAllocator<Billboard::BillboardData *,62,&Billboard::BillboardProfile::tVideoDataVec_FL> > m_vPSAVideos;
  /* 0x0048 */ protected: Billboard::BillboardData* m_pAgentAppreciationStrengthLevel[5];
  /* 0x005c */ protected: unsigned int m_nNumBulletinPlays;
  /* 0x0060 */ protected: unsigned int m_nNumPSAPlays;
  public: static const char* pBillboardProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: BillboardProfile(const Billboard::BillboardProfile&);
  public: BillboardProfile(const RWS::CAttributePacket&);
  public: virtual ~BillboardProfile();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: Billboard::BillboardData* RetBeaconNumberVideo(unsigned int);
  public: Billboard::BillboardData* RetAgentAppreciationVideo(unsigned int);
  public: Billboard::BillboardData* RetAgentAppreciationStrengthLevel(unsigned int);
  public: Billboard::BillboardData* RetRandPSAVideo() const;
  public: unsigned int RetNumBulletinPlays() const;
  public: unsigned int RetNumPSAPlays() const;
  public: Billboard::BillboardProfile& operator=(const Billboard::BillboardProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  protected: static Fun_Runtime::cFileLine tVideoDataVec_FL();
};
