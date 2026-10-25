
class Prop::cGasCanister : public Prop::cProp { /* Size=0xeb0 */
  /* 0x0000: fields for Prop::cProp */
  /* 0x0ea0 */ private: Prop::cGasCanister::eCanisterState m_nCState;
  /* 0x0ea4 */ private: float m_fRocketTimer;
  /* 0x0ea8 */ private: unsigned int m_nNumKillsForLocalPlayer;
  /* 0x0eac */ private: bool m_bFuseAudioPlayed;
  public: static const char m_cGasCanister_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcGasCanisterClass;
  public: static const char* pcGasCanisterClassID;
  public: static Fun_Runtime::cMap<unsigned int,void (__cdecl Prop::cGasCanister::*)(ActionIO::cActionIOEventData const &),std::less<unsigned int>,Fun_Runtime::cAllocator<std::pair<unsigned int,void (__cdecl Prop::cGasCanister::*)(ActionIO::cActionIOEventData const &)>,3,&Prop::cGasCanister::cGasCanisterInputMap_FL> > sm_cGasCanisterInputMap;
  
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual void FireInputInternal(unsigned int, const ActionIO::cActionIOEventData&);
  public: void InputIgnite(const ActionIO::cActionIOEventData&);
  public: cGasCanister(const Prop::cGasCanister&);
  public: cGasCanister(GOM::cObjectPrototype*);
  public: virtual Fun_Runtime::RetVal Term();
  public: virtual void TickUpdate(float);
  public: virtual float TakeDamage(Damage::cDamage&);
  public: virtual void NotifyDetonation(cGameBase*, CHARACTER::cCharacterInterface*, unsigned char);
  public: virtual void OnExitedAV(bool);
  public: void NoteKillForLocalPlayer();
  public: unsigned int RetNumKillsForLocalPlayer() const;
  private: Prop::cGasCanisterPrototype& RetGasCanisterProto() const;
  private: Fun_Runtime::Mtx CalcValveXForm();
  private: void RockIt();
  private: bool CreateRocketVFX();
  private: virtual void SetUpPointsOfInterest();
  private: virtual void ReplicateInitialFields();
  private: virtual void ReplicateFields();
  public: virtual ~cGasCanister();
  public: Prop::cGasCanister& operator=(const Prop::cGasCanister&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cFileLine cGasCanisterInputMap_FL();
};
