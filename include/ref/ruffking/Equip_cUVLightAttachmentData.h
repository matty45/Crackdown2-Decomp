
class Equip::cUVLightAttachmentData : public Equip::cLightAttachmentData { /* Size=0x3c */
  /* 0x0000: fields for Equip::cLightAttachmentData */
  /* 0x0038 */ private: float m_fUVDamage;
  public: static const char* pcUVLightAttachmentDataClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cUVLightAttachmentData(const Equip::cUVLightAttachmentData&);
  public: cUVLightAttachmentData(const RWS::CAttributePacket&);
  public: cUVLightAttachmentData();
  public: virtual ~cUVLightAttachmentData();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: float RetUVDamage() const;
  public: Equip::cUVLightAttachmentData& operator=(const Equip::cUVLightAttachmentData&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
