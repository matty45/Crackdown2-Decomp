
class Vehicle::cAgencyTank : public Vehicle::cAgencyCar { /* Size=0x3040 */
  /* 0x0000: fields for Vehicle::cAgencyCar */
  /* 0x2fb0 */ private: Vehicle::cFixedVehicleTurret m_Turret;
  /* 0x3030 */ private: bool m_bMarkerAdded;
  public: static const char m_cAgencyTank_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAgencyTankClass;
  public: static const char* pcAgencyTankClassID;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cAgencyTank(const Vehicle::cAgencyTank&);
  public: cAgencyTank(GOM::cObjectPrototype*);
  public: virtual Fun_Runtime::RetVal Init(const GOM::cSpawner*);
  public: virtual Fun_Runtime::RetVal Reinitialise(const GOM::cSpawner*);
  public: virtual void TickUpdate(float);
  public: virtual void PostTickUpdate(float);
  public: virtual bool HandlePhysicalResources(GOM::cObjectPrototype*);
  public: virtual bool CheckForRocketGuns();
  public: virtual void HingedComponentBroken(Damage::cHingedComponent*);
  public: void EnableFrontDoorLights(bool);
  public: virtual void SetFromPartConstraintMask(unsigned int, unsigned char);
  public: virtual Fun_Runtime::RetVal TermForReuse();
  public: void UpdateTurret(float);
  public: void TryFireTurret(CHARACTER::cCharacter*, bool, Fun_Runtime::Vec3, Fun_Runtime::Vec3);
  public: void PlayCannonFireAudio(CHARACTER::cCharacter*);
  public: void FireTurret(CHARACTER::cCharacter*, Fun_Runtime::Vec3, Fun_Runtime::Vec3, Fun_Runtime::Mtx&);
  public: void ApplyCannonKick();
  public: void UpdateMuzzlePosition(float);
  public: virtual void UpdateTurretTransforms();
  public: void UpdateTurretAudio(Fun_Runtime::Vec3);
  public: virtual unsigned int GetMaxReplicatedFields() const;
  public: virtual void ReplicateInitialFields();
  public: virtual void ReplicateFields();
  public: Vehicle::cAgencyTankPrototype* RetTankProto();
  public: void SetupTurret();
  protected: bool AICanFire(AI::cAiPlayer*);
  public: virtual ~cAgencyTank();
  public: Vehicle::cAgencyTank& operator=(const Vehicle::cAgencyTank&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
};
