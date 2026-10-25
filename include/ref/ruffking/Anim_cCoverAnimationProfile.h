
class Anim::cCoverAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataCover { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataCover */
  public: static const char* pcCoverAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCoverAnimationProfile(const Anim::cCoverAnimationProfile&);
  public: cCoverAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cCoverAnimationProfile();
  public: Anim::cCoverAnimationProfile& operator=(const Anim::cCoverAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
