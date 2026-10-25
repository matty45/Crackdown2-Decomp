
class GameManagement::cCD1Barrier : public GameManagement::cArenaBarrier, public RWS::CSystemCommands { /* Size=0x60 */
  /* 0x0000: fields for GameManagement::cArenaBarrier */
  /* 0x0020: fields for RWS::CSystemCommands */
  /* 0x0020 */ private: Fun_Runtime::Mtx m_mXForm;
  public: static const char* pcCD1BarrierClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCD1Barrier(const GameManagement::cCD1Barrier&);
  public: cCD1Barrier(const RWS::CAttributePacket&);
  public: virtual ~cCD1Barrier();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void Create();
  public: virtual void Destroy();
  public: GameManagement::cCD1Barrier& operator=(const GameManagement::cCD1Barrier&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
