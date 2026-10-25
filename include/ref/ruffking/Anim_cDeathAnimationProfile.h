
class Anim::cDeathAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cDeathProfileData { /* Size=0x44 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cDeathProfileData */
  public: static const char* pcDeathAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cDeathAnimationProfile(const Anim::cDeathAnimationProfile&);
  public: cDeathAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cDeathAnimationProfile();
  public: Anim::cDeathAnimationProfile& operator=(const Anim::cDeathAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
