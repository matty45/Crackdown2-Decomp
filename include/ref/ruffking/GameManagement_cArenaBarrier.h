
class GameManagement::cArenaBarrier : public RWS::CAttributeHandler { /* Size=0x20 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: VFX::BarrierMesh* m_pBarrierMesh;
  /* 0x001c */ private: const VFX::cBarrierSettings* m_pBarrierSettings;
  public: static const char* pcArenaBarrierClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cArenaBarrier(const GameManagement::cArenaBarrier&);
  public: cArenaBarrier(const RWS::CAttributePacket&);
  public: virtual ~cArenaBarrier();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void Create();
  public: virtual void Destroy();
  public: VFX::BarrierMesh* GetBarrierMesh() const;
  public: const VFX::cBarrierSettings* GetBarrierSettings() const;
  public: GameManagement::cArenaBarrier& operator=(const GameManagement::cArenaBarrier&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
