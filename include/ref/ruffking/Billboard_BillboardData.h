
class Billboard::BillboardData : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x68 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ protected: Editor::cGUIDEventHandler<Billboard::BillboardData> m_EventHandler;
  /* 0x002c */ protected: RWS::CResource* m_pVideoResource;
  /* 0x0030 */ protected: Fun_Runtime::cStringc m_strPlayEventName;
  /* 0x004c */ protected: Fun_Runtime::cStringc m_strStopEventName;
  public: static const char* pBillboardDataClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: BillboardData(const Billboard::BillboardData&);
  public: BillboardData(const RWS::CAttributePacket&);
  public: virtual ~BillboardData();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: RWS::CResource* RetVideoResource();
  public: const char* RetPlayEvent() const;
  public: const char* RetStopEvent() const;
  public: Billboard::BillboardData& operator=(const Billboard::BillboardData&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
