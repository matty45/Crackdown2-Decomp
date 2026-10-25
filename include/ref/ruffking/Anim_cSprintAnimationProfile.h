
class Anim::cSprintAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataSprint { /* Size=0x6c */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataSprint */
  public: static const char* pcSprintAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSprintAnimationProfile(const Anim::cSprintAnimationProfile&);
  public: cSprintAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cSprintAnimationProfile();
  public: Anim::cSprintAnimationProfile& operator=(const Anim::cSprintAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
