
class Anim::cEquipmentPickUpAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataEquipmentPickUp { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataEquipmentPickUp */
  public: static const char* pcEquipmentPickUpAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cEquipmentPickUpAnimationProfile(const Anim::cEquipmentPickUpAnimationProfile&);
  public: cEquipmentPickUpAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cEquipmentPickUpAnimationProfile();
  public: Anim::cEquipmentPickUpAnimationProfile& operator=(const Anim::cEquipmentPickUpAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
