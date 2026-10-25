
class CHARACTER::cCharacterVFXProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0xf8 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ private: int m_aVFX[31];
  /* 0x0094 */ private: int m_anPowerUpVFX[6];
  /* 0x00ac */ private: CHARACTER::tBloodDecalData m_BloodDecalData;
  /* 0x00bc */ private: bool m_bTrailEnable;
  /* 0x00c0 */ private: float m_fTrailMinFadeTime;
  /* 0x00c4 */ private: float m_fTrailMaxFadeTime;
  /* 0x00c8 */ private: float m_fWetTimer;
  /* 0x00cc */ private: bool m_bAcidSackAlwaysOn;
  /* 0x00d0 */ private: float m_fAcidSackScale;
  /* 0x00d4 */ private: float m_fPowerDownExplosionScale;
  /* 0x00d8 */ private: float m_fPowerPlateHitScale;
  /* 0x00dc */ private: float m_fPowerPlateLandingScale;
  /* 0x00e0 */ private: Equip::cBulletData* m_pAcidBulletData;
  /* 0x00e4 */ private: Editor::cGUIDEventHandler<CHARACTER::cCharacterVFXProfile> m_EventHandler;
  public: static const char* pcCharacterVFXProfileClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCharacterVFXProfile(const CHARACTER::cCharacterVFXProfile&);
  public: cCharacterVFXProfile(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: int RetVFXID(CHARACTER::eCharVFX) const;
  public: bool RetTrailEnabled() const;
  public: float RetMinTrailFadeTime() const;
  public: float RetMaxTrailFadeTime() const;
  public: float RetWetTimer() const;
  public: float RetAcidSackScale() const;
  public: bool RetAcidSackAlwaysOn() const;
  public: float RetPowerDownExplosionScale() const;
  public: float RetPowerPlateHitScale() const;
  public: float RetPowerPlateLandingScale() const;
  public: const Equip::cBulletData* RetAcidBulletData() const;
  public: const CHARACTER::tBloodDecalData& RetBloodDecalData() const;
  public: int RetPowerUpVFXID(CHARACTER::ePowerUp) const;
  public: virtual ~cCharacterVFXProfile();
  public: CHARACTER::cCharacterVFXProfile& operator=(const CHARACTER::cCharacterVFXProfile&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
