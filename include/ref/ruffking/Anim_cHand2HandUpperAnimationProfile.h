
class Anim::cHand2HandUpperAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataHand2HandUpper { /* Size=0x70 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataHand2HandUpper */
  public: static const char* pcHand2HandUpperAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cHand2HandUpperAnimationProfile(const Anim::cHand2HandUpperAnimationProfile&);
  public: cHand2HandUpperAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cHand2HandUpperAnimationProfile();
  public: Anim::cHand2HandUpperAnimationProfile& operator=(const Anim::cHand2HandUpperAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
