
class Anim::cEquipmentThrowNPCFullAnimationProfile : public Anim::cSpecificAnimationProfile, public Anim::cProfileDataEquipmentThrowNPCFull { /* Size=0x40 */
  /* 0x0000: fields for Anim::cSpecificAnimationProfile */
  /* 0x003c: fields for Anim::cProfileDataEquipmentThrowNPCFull */
  public: static const char* pcEquipmentThrowNPCFullAnimationProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cEquipmentThrowNPCFullAnimationProfile(const Anim::cEquipmentThrowNPCFullAnimationProfile&);
  public: cEquipmentThrowNPCFullAnimationProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cEquipmentThrowNPCFullAnimationProfile();
  public: Anim::cEquipmentThrowNPCFullAnimationProfile& operator=(const Anim::cEquipmentThrowNPCFullAnimationProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
