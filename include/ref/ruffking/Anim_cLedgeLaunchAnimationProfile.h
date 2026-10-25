
class Anim::cLedgeLaunchAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataLedgeLaunch { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataLedgeLaunch */
  public: static const char* pcLedgeLaunchAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cLedgeLaunchAnimationProfile(const Anim::cLedgeLaunchAnimationProfile&);
  public: cLedgeLaunchAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cLedgeLaunchAnimationProfile();
  public: Anim::cLedgeLaunchAnimationProfile& operator=(const Anim::cLedgeLaunchAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
