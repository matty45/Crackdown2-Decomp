
class Anim::cPropCarryNPCAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataPropCarryNPC { /* Size=0x4c */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataPropCarryNPC */
  public: static const char* pcPropCarryNPCAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPropCarryNPCAnimationProfile(const Anim::cPropCarryNPCAnimationProfile&);
  public: cPropCarryNPCAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cPropCarryNPCAnimationProfile();
  public: Anim::cPropCarryNPCAnimationProfile& operator=(const Anim::cPropCarryNPCAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
