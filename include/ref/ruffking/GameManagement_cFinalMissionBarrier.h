
class GameManagement::cFinalMissionBarrier : public GameManagement::cArenaBarrier, public RWS::CSystemCommands { /* Size=0x80 */
  /* 0x0000: fields for GameManagement::cArenaBarrier */
  /* 0x0020: fields for RWS::CSystemCommands */
  /* 0x0020 */ private: Fun_Runtime::Mtx m_mXForm;
  /* 0x0060 */ private: float m_fRadius;
  /* 0x0064 */ private: Editor::cGUIDEventHandler<GameManagement::cFinalMissionBarrier> m_EventHandler;
  /* 0x0078 */ private: VFX::cBarrier* m_pBarrier;
  public: static const char* pcFinalMissionBarrierClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cFinalMissionBarrier(const GameManagement::cFinalMissionBarrier&);
  public: cFinalMissionBarrier(const RWS::CAttributePacket&);
  public: virtual ~cFinalMissionBarrier();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void Create();
  public: virtual void Destroy();
  public: void SetRenderOnlyFlag(bool);
  public: VFX::cBarrier::SphereTestResult SphereTest(const PLAYER::cPlayer*) const;
  public: Fun_Runtime::Vec3 GetPos();
  public: float GetRadius();
  public: GameManagement::cFinalMissionBarrier& operator=(const GameManagement::cFinalMissionBarrier&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
