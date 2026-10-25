
class Anim::cRunWalkAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataRunWalk { /* Size=0x1b0 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataRunWalk */
  public: static const char* pcRunWalkAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cRunWalkAnimationProfile(const Anim::cRunWalkAnimationProfile&);
  public: cRunWalkAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cRunWalkAnimationProfile();
  public: Anim::cRunWalkAnimationProfile& operator=(const Anim::cRunWalkAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
