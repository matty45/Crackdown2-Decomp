
class Anim::cStunnedAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cStunnedProfileData { /* Size=0x44 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cStunnedProfileData */
  public: static const char* pcStunnedAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cStunnedAnimationProfile(const Anim::cStunnedAnimationProfile&);
  public: cStunnedAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cStunnedAnimationProfile();
  public: Anim::cStunnedAnimationProfile& operator=(const Anim::cStunnedAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
