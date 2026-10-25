
class VFX::cOvercast : public RWS::CAttributeHandler { /* Size=0x48 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: VFX::cParameterInterpolator m_Interpolator;
  /* 0x0044 */ private: bool m_initilalFlag;
  public: static const char* pcOvercastClassID;
  public: static const unsigned int MAX_COMMAND;
  private: static VFX::cOvercast* ms_pInstance;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cOvercast(const VFX::cOvercast&);
  public: cOvercast(const RWS::CAttributePacket&);
  public: virtual ~cOvercast();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: void ChangeStatus(VFX::cParameterInterpolator::Status);
  public: VFX::cParameterInterpolator::Status GetStatus() const;
  private: void Setup();
  public: VFX::cOvercast& operator=(const VFX::cOvercast&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static VFX::cOvercast* RetInstance();
};
