
class VFX::cVFXPriorityTable : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x18 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  public: static const char* pcVFXPriorityTableClassID;
  protected: static VFX::cVFXPriority m_aVFXPriority[75];
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cVFXPriorityTable(const VFX::cVFXPriorityTable&);
  public: cVFXPriorityTable(const RWS::CAttributePacket&);
  public: virtual ~cVFXPriorityTable();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual bool HandleDataInNewDesignBuild();
  public: VFX::cVFXPriorityTable& operator=(const VFX::cVFXPriorityTable&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static float RetPriority(VFX::eVFXType);
  public: static const VFX::cVFXPriority& RetVFXPriority(VFX::eVFXType);
};
