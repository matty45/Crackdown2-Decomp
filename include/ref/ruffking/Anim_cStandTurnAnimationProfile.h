
class Anim::cStandTurnAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataStandTurn { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataStandTurn */
  public: static const char* pcStandTurnAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cStandTurnAnimationProfile(const Anim::cStandTurnAnimationProfile&);
  public: cStandTurnAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cStandTurnAnimationProfile();
  public: Anim::cStandTurnAnimationProfile& operator=(const Anim::cStandTurnAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
