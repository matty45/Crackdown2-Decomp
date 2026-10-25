
class Anim::cEquipmentSwapAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataEquipmentSwap { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataEquipmentSwap */
  public: static const char* pcEquipmentSwapAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cEquipmentSwapAnimationProfile(const Anim::cEquipmentSwapAnimationProfile&);
  public: cEquipmentSwapAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cEquipmentSwapAnimationProfile();
  public: Anim::cEquipmentSwapAnimationProfile& operator=(const Anim::cEquipmentSwapAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
