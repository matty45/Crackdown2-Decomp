
class Anim::cEquipmentAimAndFireAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataEquipmentAimAndFire { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataEquipmentAimAndFire */
  public: static const char* pcEquipmentAimAndFireAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cEquipmentAimAndFireAnimationProfile(const Anim::cEquipmentAimAndFireAnimationProfile&);
  public: cEquipmentAimAndFireAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cEquipmentAimAndFireAnimationProfile();
  public: Anim::cEquipmentAimAndFireAnimationProfile& operator=(const Anim::cEquipmentAimAndFireAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
