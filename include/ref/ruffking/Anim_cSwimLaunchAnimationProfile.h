
class Anim::cSwimLaunchAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataSwimLaunch { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataSwimLaunch */
  public: static const char* pcSwimLaunchAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSwimLaunchAnimationProfile(const Anim::cSwimLaunchAnimationProfile&);
  public: cSwimLaunchAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cSwimLaunchAnimationProfile();
  public: Anim::cSwimLaunchAnimationProfile& operator=(const Anim::cSwimLaunchAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
