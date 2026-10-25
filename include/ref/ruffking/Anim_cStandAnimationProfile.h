
class Anim::cStandAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataStand { /* Size=0x60 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataStand */
  public: static const char* pcStandAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cStandAnimationProfile(const Anim::cStandAnimationProfile&);
  public: cStandAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cStandAnimationProfile();
  public: Anim::cStandAnimationProfile& operator=(const Anim::cStandAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
