
class Billboard::BillboardAudioEmitter : public RWS::CSystemCommands, public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x70 */
  /* 0x0018: fields for RWS::CSystemCommands */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0019: fields for RWS::DynamicAllocationPolicy */
  /* 0x0020 */ protected: Fun_Runtime::Mtx m_Transform;
  /* 0x0060 */ protected: Billboard::BillboardAudioEmitterContainer* m_pContainer;
  public: static const char* pBillboardAudioEmitterClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: BillboardAudioEmitter(const Billboard::BillboardAudioEmitter&);
  public: BillboardAudioEmitter(const RWS::CAttributePacket&);
  public: virtual ~BillboardAudioEmitter();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: const Fun_Runtime::Mtx& RetTransform() const;
  public: Fun_Runtime::Vec3 RetPosition() const;
  public: void SetContainer(Billboard::BillboardAudioEmitterContainer*);
  public: Billboard::BillboardAudioEmitter& operator=(const Billboard::BillboardAudioEmitter&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static void InGridCallback(Billboard::BillboardAudioEmitter*);
};
