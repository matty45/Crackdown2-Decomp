
class Anim::cBeaconPulseHoverAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataBeaconPulseHover { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataBeaconPulseHover */
  public: static const char* pcBeaconPulseHoverAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cBeaconPulseHoverAnimationProfile(const Anim::cBeaconPulseHoverAnimationProfile&);
  public: cBeaconPulseHoverAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cBeaconPulseHoverAnimationProfile();
  public: Anim::cBeaconPulseHoverAnimationProfile& operator=(const Anim::cBeaconPulseHoverAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
