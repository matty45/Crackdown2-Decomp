
class Cam::cCameraMarker : public RWS::CAttributeHandler, public RWS::CSystemCommands, public RWS::DynamicAllocationPolicy { /* Size=0x40 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CSystemCommands */
  /* 0x0019: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c */ protected: Editor::cGUIDEventHandler<Cam::cCameraMarker> m_EventHandler;
  /* 0x0030 */ protected: Fun_Runtime::Vec3 m_vPos;
  public: static const char* pcCameraMarkerClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCameraMarker(const Cam::cCameraMarker&);
  public: cCameraMarker(const RWS::CAttributePacket&);
  public: virtual ~cCameraMarker();
  public: const Fun_Runtime::Vec3& RetPos() const;
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: Cam::cCameraMarker& operator=(const Cam::cCameraMarker&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
