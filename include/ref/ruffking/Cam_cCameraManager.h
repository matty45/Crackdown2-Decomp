
class Cam::cCameraManager : public RWS::CEventHandler { /* Size=0x250 */
  /* 0x0000: fields for RWS::CEventHandler */
  /* 0x0004 */ private: Fun_Runtime::cVector<Cam::cCameraBase *,Fun_Runtime::cAllocator<Cam::cCameraBase *,78,&Cam::cCameraManager::vCam_FL> > m_vCameras;
  /* 0x0014 */ private: Fun_Runtime::cVector<Cam::cCameraModBase *,Fun_Runtime::cAllocator<Cam::cCameraModBase *,78,&Cam::cCameraManager::vCamMods_FL> > m_vCameraModChain;
  /* 0x0024 */ private: Cam::cCameraBase* m_pCurrentCamera;
  /* 0x0030 */ private: Cam::cCameraData m_cdFinalCameraData;
  /* 0x0230 */ private: Cam::eCameraStates m_eCurrentCameraState;
  /* 0x0234 */ private: unsigned int m_nLastTickTimeMS;
  /* 0x0238 */ private: float m_fRealDeltaTime;
  /* 0x023c */ private: bool m_bRenderDebugInfo;
  /* 0x0240 */ private: Fun_Runtime::cVector<Cam::cCameraBase *,Fun_Runtime::cAllocator<Cam::cCameraBase *,78,&Cam::cCameraManager::vDebugCams_FL> > m_vDebugCameras;
  private: static Cam::cCameraManager* sm_pInstance;
  
  public: cCameraManager(const Cam::cCameraManager&);
  public: cCameraManager();
  public: virtual ~cCameraManager();
  public: void RegisterCamera(Cam::cCameraBase*);
  public: void RemoveCamera(Cam::cCameraBase*);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: void Update();
  public: void UpdateCameras(float);
  public: void PauseCamera(bool);
  public: void SetCurrentCamera(Cam::cCameraBaseData*);
  public: void SetState(Cam::eCameraStates);
  public: void AddCamModifier(Cam::cCameraModBaseData*);
  public: void ApplyExternalInput(const Cam::sCameraInput&);
  public: void ClearModifiers(bool);
  public: Cam::cCameraData* RetFinalCamera();
  public: int RetCurrentCameraType();
  public: Cam::cCameraBase* RetCurrentCamera();
  public: bool IsCameraActive();
  public: void AddDebugCamera();
  public: void RemoveDebugCamera();
  public: void ClearDebugCameras();
  public: void ToggleRenderDebugInfo();
  private: void UpdateDebugCameras(float);
  private: void RenderDebugInfo();
  public: Cam::cCameraManager& operator=(const Cam::cCameraManager&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Cam::cCameraManager* RetInstance();
  private: static Fun_Runtime::cFileLine vCam_FL();
  private: static Fun_Runtime::cFileLine vCamMods_FL();
  protected: static Fun_Runtime::cFileLine vDebugCams_FL();
};
