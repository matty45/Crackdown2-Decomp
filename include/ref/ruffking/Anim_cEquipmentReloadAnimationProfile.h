
class Anim::cEquipmentReloadAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataEquipmentReload { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataEquipmentReload */
  public: static const char* pcEquipmentReloadAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cEquipmentReloadAnimationProfile(const Anim::cEquipmentReloadAnimationProfile&);
  public: cEquipmentReloadAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cEquipmentReloadAnimationProfile();
  public: Anim::cEquipmentReloadAnimationProfile& operator=(const Anim::cEquipmentReloadAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
