
class Anim::cReaperJumpAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataReaperJump { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataReaperJump */
  public: static const char* pcReaperJumpAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cReaperJumpAnimationProfile(const Anim::cReaperJumpAnimationProfile&);
  public: cReaperJumpAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cReaperJumpAnimationProfile();
  public: Anim::cReaperJumpAnimationProfile& operator=(const Anim::cReaperJumpAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
