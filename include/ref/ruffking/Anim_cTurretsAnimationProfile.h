
class Anim::cTurretsAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataTurrets { /* Size=0x48 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataTurrets */
  public: static const char* pcTurretsAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cTurretsAnimationProfile(const Anim::cTurretsAnimationProfile&);
  public: cTurretsAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cTurretsAnimationProfile();
  public: Anim::cTurretsAnimationProfile& operator=(const Anim::cTurretsAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
