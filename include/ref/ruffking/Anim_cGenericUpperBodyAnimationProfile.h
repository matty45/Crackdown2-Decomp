
class Anim::cGenericUpperBodyAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataGenericUpperBody { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataGenericUpperBody */
  public: static const char* pcGenericUpperBodyAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGenericUpperBodyAnimationProfile(const Anim::cGenericUpperBodyAnimationProfile&);
  public: cGenericUpperBodyAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cGenericUpperBodyAnimationProfile();
  public: Anim::cGenericUpperBodyAnimationProfile& operator=(const Anim::cGenericUpperBodyAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
