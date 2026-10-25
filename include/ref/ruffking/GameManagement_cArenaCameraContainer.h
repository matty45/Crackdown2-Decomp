
class GameManagement::cArenaCameraContainer : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy { /* Size=0x28 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::DynamicAllocationPolicy */
  /* 0x0018 */ protected: Fun_Runtime::cVector<Cam::cCameraMarker *,Fun_Runtime::cAllocator<Cam::cCameraMarker *,3,&GameManagement::cArenaCameraContainer::tCameraMarkerList_FL> > m_vCameraMarkers;
  public: static const char* pcArenaCameraContainerClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cArenaCameraContainer(const GameManagement::cArenaCameraContainer&);
  public: cArenaCameraContainer(const RWS::CAttributePacket&);
  public: virtual ~cArenaCameraContainer();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: unsigned int RetNumCameraMarkers() const;
  public: Cam::cCameraMarker* RetCameraMarker(unsigned int) const;
  public: GameManagement::cArenaCameraContainer& operator=(const GameManagement::cArenaCameraContainer&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  protected: static Fun_Runtime::cFileLine tCameraMarkerList_FL();
};
