
class Anim::cReactionAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataReaction { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataReaction */
  public: static const char* pcReactionAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cReactionAnimationProfile(const Anim::cReactionAnimationProfile&);
  public: cReactionAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cReactionAnimationProfile();
  public: Anim::cReactionAnimationProfile& operator=(const Anim::cReactionAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
