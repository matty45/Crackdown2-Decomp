
class Anim::cRappelAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataRappel { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataRappel */
  public: static const char* pcRappelAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cRappelAnimationProfile(const Anim::cRappelAnimationProfile&);
  public: cRappelAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cRappelAnimationProfile();
  public: Anim::cRappelAnimationProfile& operator=(const Anim::cRappelAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
