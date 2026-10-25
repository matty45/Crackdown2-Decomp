
class Anim::cJumpLaunchAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataJumpLaunch { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataJumpLaunch */
  public: static const char* pcJumpLaunchAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cJumpLaunchAnimationProfile(const Anim::cJumpLaunchAnimationProfile&);
  public: cJumpLaunchAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cJumpLaunchAnimationProfile();
  public: Anim::cJumpLaunchAnimationProfile& operator=(const Anim::cJumpLaunchAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
