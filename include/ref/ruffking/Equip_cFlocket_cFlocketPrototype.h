
class Equip::cFlocket::cFlocketPrototype : public Equip::cHWProjectile::cHWProjectilePrototype { /* Size=0x350 */
  /* 0x0000: fields for Equip::cHWProjectile::cHWProjectilePrototype */
  /* 0x0310 */ public: char m_nLightID;
  /* 0x0314 */ public: float m_fLightScaleSml;
  /* 0x0318 */ public: float m_fLightScaleLge;
  /* 0x031c */ public: float m_fLightZOffset;
  /* 0x0320 */ public: float m_fLaunchOffset;
  /* 0x0324 */ public: float m_fVertAccMin;
  /* 0x0328 */ public: float m_fVertAccMax;
  /* 0x032c */ public: float m_fHorizAccMin;
  /* 0x0330 */ public: float m_fHorizAccMax;
  /* 0x0334 */ public: float m_fFlockTime;
  /* 0x0338 */ public: float m_fOscilFalloffTimeRecip;
  /* 0x033c */ public: float m_fToTargetAcc;
  /* 0x0340 */ public: float m_fVertDec;
  /* 0x0344 */ public: float m_fAirDec;
  /* 0x0348 */ public: float m_fHorizOscil;
  
  public: cFlocketPrototype(const Equip::cFlocket::cFlocketPrototype&);
  public: cFlocketPrototype(const RWS::CAttributePacket&);
  public: virtual ~cFlocketPrototype();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket&);
  public: Equip::cFlocket::cFlocketPrototype& operator=(const Equip::cFlocket::cFlocketPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
};
