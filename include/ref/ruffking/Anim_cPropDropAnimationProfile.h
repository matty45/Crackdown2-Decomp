
class Anim::cPropDropAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataPropDrop { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataPropDrop */
  public: static const char* pcPropDropAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPropDropAnimationProfile(const Anim::cPropDropAnimationProfile&);
  public: cPropDropAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cPropDropAnimationProfile();
  public: Anim::cPropDropAnimationProfile& operator=(const Anim::cPropDropAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
