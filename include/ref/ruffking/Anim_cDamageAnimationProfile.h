
class Anim::cDamageAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cDamageProfileData { /* Size=0x8c */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cDamageProfileData */
  public: static const char* pcDamageAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cDamageAnimationProfile(const Anim::cDamageAnimationProfile&);
  public: cDamageAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cDamageAnimationProfile();
  public: Anim::cDamageAnimationProfile& operator=(const Anim::cDamageAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
