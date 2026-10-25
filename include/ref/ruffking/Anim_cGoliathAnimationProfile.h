
class Anim::cGoliathAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataGoliath { /* Size=0x4c */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataGoliath */
  public: static const char* pcGoliathAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGoliathAnimationProfile(const Anim::cGoliathAnimationProfile&);
  public: cGoliathAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cGoliathAnimationProfile();
  public: Anim::cGoliathAnimationProfile& operator=(const Anim::cGoliathAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
