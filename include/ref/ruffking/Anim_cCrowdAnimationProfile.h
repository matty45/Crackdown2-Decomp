
class Anim::cCrowdAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataCrowd { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataCrowd */
  public: static const char* pcCrowdAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCrowdAnimationProfile(const Anim::cCrowdAnimationProfile&);
  public: cCrowdAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cCrowdAnimationProfile();
  public: Anim::cCrowdAnimationProfile& operator=(const Anim::cCrowdAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
