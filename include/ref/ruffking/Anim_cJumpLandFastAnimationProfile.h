
class Anim::cJumpLandFastAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataJumpLandFast { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataJumpLandFast */
  public: static const char* pcJumpLandFastAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cJumpLandFastAnimationProfile(const Anim::cJumpLandFastAnimationProfile&);
  public: cJumpLandFastAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cJumpLandFastAnimationProfile();
  public: Anim::cJumpLandFastAnimationProfile& operator=(const Anim::cJumpLandFastAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
