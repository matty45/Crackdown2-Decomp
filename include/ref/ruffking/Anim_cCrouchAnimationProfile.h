
class Anim::cCrouchAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataCrouch { /* Size=0x5c */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataCrouch */
  public: static const char* pcCrouchAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCrouchAnimationProfile(const Anim::cCrouchAnimationProfile&);
  public: cCrouchAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cCrouchAnimationProfile();
  public: Anim::cCrouchAnimationProfile& operator=(const Anim::cCrouchAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
