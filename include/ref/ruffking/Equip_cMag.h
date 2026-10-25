
class Equip::cMag : public Equip::cCWSatchelCharge { /* Size=0xbb0 */
  /* 0x0000: fields for Equip::cCWSatchelCharge */
  /* 0x0b80 */ private: Fun_Runtime::cSafeDeletablePointer<Equip::cMag> m_pNextLink;
  /* 0x0b90 */ private: Fun_Runtime::cSafeDeletablePointer<Equip::cMag> m_pPrevLink;
  /* 0x0ba0 */ private: unsigned int m_nReplicatedNextLinkID;
  /* 0x0ba4 */ private: unsigned int m_nReplicatedPrevLinkID;
  /* 0x0ba8 */ private: VFX::cParticleEffectInstance* m_pActiveMagVFX;
  /* 0x0bac */ private: VFX::cParticleEffectInstance* m_pBeamMagVFX;
  public: static const char m_cMag_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcMagClass;
  public: static const char* pcMagClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cMag(const Equip::cMag&);
  public: cMag(GOM::cObjectPrototype*);
  public: virtual Fun_Runtime::RetVal Term();
  public: void SetNextLink(Equip::cMag*);
  public: virtual void NowStuck();
  public: virtual void Unstick();
  public: virtual void UpdateRenderMatrix();
  protected: virtual void TickUpdate(float);
  protected: virtual unsigned char RetExplosiveLevelForOwner(const cNonGameBase*) const;
  protected: virtual void Launched(cGameBase*);
  protected: virtual void NotifyTracked(Equip::cEquipment*);
  protected: virtual void OnAttachedToObject(Equip::cSatchelChargeTarget*, const Fun_Runtime::Mtx&);
  protected: virtual void OnDetachedFromObject();
  protected: virtual bool CanAttachToBody(PHYSICS::cBody*) const;
  private: Equip::cMag::cMagPrototype* RetMagPrototype();
  private: void UpdateMagVFX();
  private: Fun_Runtime::Vec3 CalculateMagForce(Equip::cMag*);
  private: virtual void ReplicateInitialFields();
  private: virtual void ReplicateFields();
  private: void ProxyFixupLinks();
  private: void UpdateReplicatedLinkIDs();
  private: void DrawDebugLinks();
  public: virtual ~cMag();
  public: Equip::cMag& operator=(const Equip::cMag&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  protected: static PHYSICS::cNetDynamicBody* RetAttachDBFromMag(Equip::cMag*);
};
