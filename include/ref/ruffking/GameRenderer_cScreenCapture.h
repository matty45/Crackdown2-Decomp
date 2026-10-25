
class GameRenderer::cScreenCapture : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy { /* Size=0x7c */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018: fields for RWS::CEventHandler */
  /* 0x001c: fields for RWS::DynamicAllocationPolicy */
  /* 0x001c */ private: _XMFLOAT2 m_origViewWin;
  /* 0x0024 */ private: unsigned int m_nScreenTileX;
  /* 0x0028 */ private: unsigned int m_nScreenTileY;
  /* 0x002c */ private: float m_fMovieTimer;
  /* 0x0030 */ private: unsigned int m_lastMovieDir;
  /* 0x0034 */ private: Renderer::cCamera* m_pMyCamera;
  /* 0x0038 */ private: bool m_bCaptureNextFrame;
  /* 0x0039 */ private: bool m_bContinuousCapture;
  /* 0x003c */ private: unsigned int m_nCurrentFrame;
  /* 0x0040 */ private: Fun_Runtime::cString m_sBaseFilename;
  /* 0x005c */ private: Fun_Runtime::cString m_sCaptureFolder;
  /* 0x0078 */ private: bool m_bUseFrameNumInFileName;
  public: static const char* pcScreenCaptureClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cScreenCapture(const GameRenderer::cScreenCapture&);
  public: cScreenCapture(const RWS::CAttributePacket&);
  public: virtual ~cScreenCapture();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: void Update();
  public: void Capture();
  public: void Upload();
  public: void MovieCapture(float);
  public: void SetCaptureFilename(const Fun_Runtime::cString&);
  public: const Fun_Runtime::cString& GetCaptureFilename();
  public: void SetScreenTileX(unsigned int);
  public: void SetScreenTileY(unsigned int);
  public: unsigned int GetScreenTileX();
  public: unsigned int GetScreenTileY();
  public: void SetCurrentFrame(unsigned int);
  public: unsigned int GetCurrentFrame();
  public: void StopMovieCapture();
  public: void SetUseFrameNumInFileName(bool);
  private: void RenderNoHUD(unsigned int, unsigned int, unsigned int, unsigned int);
  private: void GrabBackBuffer();
  private: void SetupTileCam(unsigned int, unsigned int, unsigned int, unsigned int);
  public: GameRenderer::cScreenCapture& operator=(const GameRenderer::cScreenCapture&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
