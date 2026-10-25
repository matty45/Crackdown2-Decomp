
class Anim::cPropPickUpFullAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataPropPickUpFull { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataPropPickUpFull */
  public: static const char* pcPropPickUpFullAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPropPickUpFullAnimationProfile(const Anim::cPropPickUpFullAnimationProfile&);
  public: cPropPickUpFullAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cPropPickUpFullAnimationProfile();
  public: Anim::cPropPickUpFullAnimationProfile& operator=(const Anim::cPropPickUpFullAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
