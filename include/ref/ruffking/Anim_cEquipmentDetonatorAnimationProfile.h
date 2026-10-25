
class Anim::cEquipmentDetonatorAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataEquipmentDetonator { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataEquipmentDetonator */
  public: static const char* pcEquipmentDetonatorAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cEquipmentDetonatorAnimationProfile(const Anim::cEquipmentDetonatorAnimationProfile&);
  public: cEquipmentDetonatorAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cEquipmentDetonatorAnimationProfile();
  public: Anim::cEquipmentDetonatorAnimationProfile& operator=(const Anim::cEquipmentDetonatorAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
