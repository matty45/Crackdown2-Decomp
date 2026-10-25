
class Anim::cLandVehicleAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cLandVehicleProfileData { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cLandVehicleProfileData */
  public: static const char* pcLandVehicleAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cLandVehicleAnimationProfile(const Anim::cLandVehicleAnimationProfile&);
  public: cLandVehicleAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cLandVehicleAnimationProfile();
  public: Anim::cLandVehicleAnimationProfile& operator=(const Anim::cLandVehicleAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
