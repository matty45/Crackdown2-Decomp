
class Anim::cEquipmentCarryAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataEquipmentCarry { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataEquipmentCarry */
  public: static const char* pcEquipmentCarryAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cEquipmentCarryAnimationProfile(const Anim::cEquipmentCarryAnimationProfile&);
  public: cEquipmentCarryAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cEquipmentCarryAnimationProfile();
  public: Anim::cEquipmentCarryAnimationProfile& operator=(const Anim::cEquipmentCarryAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
