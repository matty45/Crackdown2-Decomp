
class GameManagement::cCHordeCaptureZone : public GameManagement::cMultiPlayerTriggerZone, public cReplicatedClass, public Network::cNetRoleObject { /* Size=0x2d0 */
  /* 0x0000: fields for GameManagement::cMultiPlayerTriggerZone */
  /* 0x0070: fields for cReplicatedClass */
  /* 0x02a0: fields for Network::cNetRoleObject */
  /* 0x02a8 */ private: Editor::cGUIDEventHandler<GameManagement::cCHordeCaptureZone> m_EventHandler;
  /* 0x02bc */ private: GameManagement::cCHordeCaptureProfile* m_pProfile;
  /* 0x02c0 */ private: float m_fCaptureFraction;
  /* 0x02c4 */ private: float m_fEnterExitDate;
  /* 0x02c8 */ private: GameManagement::cCHordeCaptureZone::eCaptureState m_nState;
  /* 0x02cc */ private: VFX::cParticleEffectInstance* m_pVFX;
  public: static const char* pcCHordeCaptureZoneClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCHordeCaptureZone(const GameManagement::cCHordeCaptureZone&);
  public: cCHordeCaptureZone(const RWS::CAttributePacket&);
  public: virtual ~cCHordeCaptureZone();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool IsSequential() const;
  public: void Update();
  public: void Activate();
  public: void Deactivate();
  public: float RetCaptureFraction() const;
  public: bool IsComplete();
  public: GameManagement::cCHordeCaptureZone::eCaptureState RetState() const;
  private: void CreateCaptureVFX(int);
  private: void ChangeState(GameManagement::cCHordeCaptureZone::eCaptureState);
  private: virtual bool CanTrigger(PLAYER::cPlayer*);
  private: virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
  private: virtual unsigned int GetMaxReplicatedFields() const;
  private: virtual unsigned int GetNumObjectIDBits() const;
  private: virtual bool CanSendTermPacketOnNotRelevant() const;
  private: virtual void SetPingedFieldStatesForNode(unsigned char);
  private: virtual void ReplicateInitialFields();
  private: virtual void ReplicateFields();
  private: virtual void CalculateLOD(int);
  private: virtual bool IsOwnedLocally();
  public: GameManagement::cCHordeCaptureZone& operator=(const GameManagement::cCHordeCaptureZone&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
