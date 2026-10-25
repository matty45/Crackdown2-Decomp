
class Anim::cEquipmentThrowAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataEquipmentThrow { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataEquipmentThrow */
  public: static const char* pcEquipmentThrowAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cEquipmentThrowAnimationProfile(const Anim::cEquipmentThrowAnimationProfile&);
  public: cEquipmentThrowAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cEquipmentThrowAnimationProfile();
  public: Anim::cEquipmentThrowAnimationProfile& operator=(const Anim::cEquipmentThrowAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
