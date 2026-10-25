
class GameManagement::cCHordeWave : public RWS::CAttributeHandler { /* Size=0x44 */
  /* 0x0000: fields for RWS::CAttributeHandler */
  /* 0x0018 */ private: Editor::cGUIDEventHandler<GameManagement::cCHordeWave> m_EventHandler;
  /* 0x002c */ public: GameManagement::cCHordeCaptureZone** m_apCaptureZones;
  /* 0x0030 */ public: unsigned int m_nNumCaptureZones;
  /* 0x0034 */ public: unsigned char m_nARLevel;
  /* 0x0035 */ public: unsigned char m_nARGangFlags;
  /* 0x0038 */ public: float m_fTOD;
  /* 0x003c */ public: unsigned char m_nCrowdFlags;
  /* 0x0040 */ public: CHARACTER::cGameDamageProfile* m_pDamageProfile;
  public: static const char* pcCHordeWaveClassID;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: cCHordeWave(const GameManagement::cCHordeWave&);
  public: cCHordeWave(const RWS::CAttributePacket&);
  public: virtual ~cCHordeWave();
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: GameManagement::cCHordeWave& operator=(const GameManagement::cCHordeWave&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static const char* RetRWSClassName();
};
