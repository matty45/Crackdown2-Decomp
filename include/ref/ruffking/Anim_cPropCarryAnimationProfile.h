
class Anim::cPropCarryAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataPropCarry { /* Size=0x44 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataPropCarry */
  public: static const char* pcPropCarryAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPropCarryAnimationProfile(const Anim::cPropCarryAnimationProfile&);
  public: cPropCarryAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cPropCarryAnimationProfile();
  public: Anim::cPropCarryAnimationProfile& operator=(const Anim::cPropCarryAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
