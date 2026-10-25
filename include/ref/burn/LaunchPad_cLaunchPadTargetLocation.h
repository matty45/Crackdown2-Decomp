
class LaunchPad::cLaunchPadTargetLocation : public RWS::CAttributeHandler, public RWS::CSystemCommands { /* Size=0x40 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CSystemCommands */
  /* 0x0018 */ private: LaunchPad::cLaunchPadLocation* m_pLaunch;
  /* 0x001c */ private: Editor::cGUIDEventHandler<LaunchPad::cLaunchPadTargetLocation> m_EventHandler;
  /* 0x0030 */ private: Fun_Runtime::Vec3 m_vPosition;
  public: static const char* pcLaunchPadTargetLocationClassID;
  public: static unsigned int _cLaunchPadTargetLocationClassIDHash;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cLaunchPadTargetLocation(const LaunchPad::cLaunchPadTargetLocation&);
  public: cLaunchPadTargetLocation(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: void SetLaunch(LaunchPad::cLaunchPadLocation*);
  public: const Fun_Runtime::Vec3& RetPosition() const;
  public: virtual ~cLaunchPadTargetLocation();
  public: LaunchPad::cLaunchPadTargetLocation& operator=(const LaunchPad::cLaunchPadTargetLocation&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
  public: static unsigned int RetRWSClassNameHash();
};
