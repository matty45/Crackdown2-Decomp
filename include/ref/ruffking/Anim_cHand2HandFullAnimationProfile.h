
class Anim::cHand2HandFullAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataHand2HandFull { /* Size=0x3ee0 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x0040: fields for Anim::cProfileDataHand2HandFull */
  public: static const char* pcHand2HandFullAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cHand2HandFullAnimationProfile(const Anim::cHand2HandFullAnimationProfile&);
  public: cHand2HandFullAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cHand2HandFullAnimationProfile();
  public: Anim::cHand2HandFullAnimationProfile& operator=(const Anim::cHand2HandFullAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
