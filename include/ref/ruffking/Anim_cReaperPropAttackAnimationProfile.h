
class Anim::cReaperPropAttackAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataReaperPropAttack { /* Size=0x44 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataReaperPropAttack */
  public: static const char* pcReaperPropAttackAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cReaperPropAttackAnimationProfile(const Anim::cReaperPropAttackAnimationProfile&);
  public: cReaperPropAttackAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cReaperPropAttackAnimationProfile();
  public: Anim::cReaperPropAttackAnimationProfile& operator=(const Anim::cReaperPropAttackAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
