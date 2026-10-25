
class Anim::cJumpLandAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataJumpLand { /* Size=0x4c */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataJumpLand */
  public: static const char* pcJumpLandAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cJumpLandAnimationProfile(const Anim::cJumpLandAnimationProfile&);
  public: cJumpLandAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cJumpLandAnimationProfile();
  public: Anim::cJumpLandAnimationProfile& operator=(const Anim::cJumpLandAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
