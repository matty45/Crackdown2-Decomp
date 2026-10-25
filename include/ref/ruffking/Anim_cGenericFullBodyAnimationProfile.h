
class Anim::cGenericFullBodyAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataGenericFullBody { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataGenericFullBody */
  public: static const char* pcGenericFullBodyAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cGenericFullBodyAnimationProfile(const Anim::cGenericFullBodyAnimationProfile&);
  public: cGenericFullBodyAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cGenericFullBodyAnimationProfile();
  public: Anim::cGenericFullBodyAnimationProfile& operator=(const Anim::cGenericFullBodyAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
