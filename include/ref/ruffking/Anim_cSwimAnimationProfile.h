
class Anim::cSwimAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataSwim { /* Size=0x4c */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataSwim */
  public: static const char* pcSwimAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSwimAnimationProfile(const Anim::cSwimAnimationProfile&);
  public: cSwimAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cSwimAnimationProfile();
  public: Anim::cSwimAnimationProfile& operator=(const Anim::cSwimAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
