
class Anim::cTransformationAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataTransformation { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataTransformation */
  public: static const char* pcTransformationAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTransformationAnimationProfile(const Anim::cTransformationAnimationProfile&);
  public: cTransformationAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cTransformationAnimationProfile();
  public: Anim::cTransformationAnimationProfile& operator=(const Anim::cTransformationAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
