
class Anim::cJumpAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataJump { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataJump */
  public: static const char* pcJumpAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cJumpAnimationProfile(const Anim::cJumpAnimationProfile&);
  public: cJumpAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cJumpAnimationProfile();
  public: Anim::cJumpAnimationProfile& operator=(const Anim::cJumpAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
