
class RWS::CEventHandler { /* Size=0x4 */
  
  private: CEventHandler(const RWS::CEventHandler&);
  public: CEventHandler();
  public: virtual ~CEventHandler();
  public: virtual int RetUniqueID();
  public: virtual bool IsMaster();
  public: virtual unsigned int RetMasterNetCommID();
  public: virtual void SendEventToNetComm(RWS::CMsg&);
  public: virtual void HandleEvents(RWS::CMsg&);
  public: void ReplaceLinkedMsg(RWS::CEventId&, const char*, const char*);
  public: void LinkMsg(RWS::CEventId&, const char*, unsigned short);
  public: bool IsLinked(RWS::CEventId&);
  public: int GetLinkedPriority(RWS::CEventId&);
  public: void UnLinkMsg(RWS::CEventId&);
  public: bool GetRegisteredMessageEventID(RWS::CMsg*, unsigned int, unsigned int);
  public: void SendMsgToEventHandler(const RWS::CEventId&, RWS::CEventHandler*);
  public: void SendMsgToEventHandler(RWS::CMsg&, RWS::CEventHandler*);
  private: RWS::CEventHandler& operator=(const RWS::CEventHandler&);
  protected: bool SendMsg(const RWS::CEventId&);
  protected: bool SendMsg(RWS::CMsg&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static void Open(unsigned int, unsigned int);
  public: static void Close();
  public: static void RegisterStreamChunkHandlers();
  public: static void UnRegisterStreamChunkHandlers();
  public: static void Purge();
  public: static void UnRegisterMsg(RWS::CEventId&);
  public: static void RegisterMsg(RWS::CEventId&, const char*, const char*);
  public: static void ReplaceRegisteredMsg(RWS::CEventId&, const char*, const char*);
  public: static void ReplaceLinkedMsg(RWS::CEventHandler&, RWS::CEventId&, const char*, const char*, unsigned short);
  public: static void SetLinkPriority(RWS::CEventHandler&, RWS::CEventId&, const char*, unsigned short);
  public: static bool LinkMsgToEventHandler(RWS::CEventHandler*, RWS::CEventId&, const char*, unsigned short);
  public: static void ProcessPendingUnlinks(RWS::CLinkedMsg*);
};
