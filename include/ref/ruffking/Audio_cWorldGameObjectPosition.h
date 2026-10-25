
class Audio::cWorldGameObjectPosition : public RWS::CAttributeHandler, public RWS::CSystemCommands, public RWS::DynamicAllocationPolicy { /* Size=0x50 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CSystemCommands */
  /* 0x0019: fields for RWS::DynamicAllocationPolicy */
  /* 0x0020 */ private: Fun_Runtime::Vec3 m_vPosition;
  /* 0x0030 */ private: Fun_Runtime::Vec3 m_vDirection;
  /* 0x0040 */ private: bool m_bCreated;
  /* 0x0044 */ private: Audio::cWorldGameObject* m_pWorldObject;
  /* 0x0048 */ private: int m_nID;
  public: static const char m_cWorldGameObjectPosition_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcWorldGameObjectPositionClass;
  public: static const char* pcWorldGameObjectPositionClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cWorldGameObjectPosition(const Audio::cWorldGameObjectPosition&);
  public: cWorldGameObjectPosition(const RWS::CAttributePacket&);
  public: virtual ~cWorldGameObjectPosition();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: Audio::cWorldGameObjectPosition& operator=(const Audio::cWorldGameObjectPosition&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
