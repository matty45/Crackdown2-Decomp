
class Anim::cNPCBargeAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataNPCBarge { /* Size=0x50 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataNPCBarge */
  public: static const char* pcNPCBargeAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cNPCBargeAnimationProfile(const Anim::cNPCBargeAnimationProfile&);
  public: cNPCBargeAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cNPCBargeAnimationProfile();
  public: Anim::cNPCBargeAnimationProfile& operator=(const Anim::cNPCBargeAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
