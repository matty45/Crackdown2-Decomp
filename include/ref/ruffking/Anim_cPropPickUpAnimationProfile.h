
class Anim::cPropPickUpAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataPropPickUp { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataPropPickUp */
  public: static const char* pcPropPickUpAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPropPickUpAnimationProfile(const Anim::cPropPickUpAnimationProfile&);
  public: cPropPickUpAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cPropPickUpAnimationProfile();
  public: Anim::cPropPickUpAnimationProfile& operator=(const Anim::cPropPickUpAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
