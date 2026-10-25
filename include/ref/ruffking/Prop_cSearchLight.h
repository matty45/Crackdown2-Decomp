
class Prop::cSearchLight : public Prop::cProp { /* Size=0xee0 */
  /* 0x0000: fields for Prop::cProp */
  /* 0x0ea0 */ protected: cFrame m_Horizontal;
  /* 0x0ea8 */ protected: cFrame m_Casing;
  /* 0x0eb0 */ protected: cFrame m_Cover;
  /* 0x0eb8 */ protected: cFrame m_Light;
  /* 0x0ec0 */ protected: cFrame m_Vertical;
  /* 0x0ec8 */ protected: float m_fRotDirX;
  /* 0x0ecc */ protected: float m_fRotDirY;
  /* 0x0ed0 */ protected: float m_fRotX;
  /* 0x0ed4 */ protected: float m_fRotY;
  public: static const char m_cSearchLight_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcSearchLightClass;
  public: static const char* pcSearchLightClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cSearchLight(const Prop::cSearchLight&);
  public: cSearchLight(GOM::cObjectPrototype*);
  public: virtual ~cSearchLight();
  public: virtual bool HandlePhysicalResources(GOM::cObjectPrototype*);
  public: virtual void TickUpdate(float);
  protected: Prop::cSearchLight::cSearchLightPrototype* RetSearchLightPrototype();
  public: Prop::cSearchLight& operator=(const Prop::cSearchLight&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
