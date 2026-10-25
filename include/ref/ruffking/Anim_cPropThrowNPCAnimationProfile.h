
class Anim::cPropThrowNPCAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataPropThrowNPC { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataPropThrowNPC */
  public: static const char* pcPropThrowNPCAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cPropThrowNPCAnimationProfile(const Anim::cPropThrowNPCAnimationProfile&);
  public: cPropThrowNPCAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cPropThrowNPCAnimationProfile();
  public: Anim::cPropThrowNPCAnimationProfile& operator=(const Anim::cPropThrowNPCAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
