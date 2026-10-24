
class ResourceManager::cStreamingResourceClient { /* Size=0xc */
  /* 0x0004 */ protected: float m_fStreamingPriority;
  /* 0x0008 */ protected: float m_fRenderStreamingPriority;
  
  public: cStreamingResourceClient(const ResourceManager::cStreamingResourceClient&);
  public: cStreamingResourceClient();
  public: virtual bool RequestResources(eResourcesType, bool);
  public: virtual eResourceLoadStatus CheckResources(eResourcesType);
  public: virtual bool HasLoadedResources(eResourcesType);
  public: virtual void NotifyResourceUnload(RWS::CResource&);
  public: virtual void NotifyResourceLoaded(RWS::CResource&);
  public: virtual void ReCalculateResourceState();
  public: float RetStreamingPriority();
  public: float RetRenderStreamingPriority();
  public: void ResetPriority();
  public: ResourceManager::cStreamingResourceClient& operator=(const ResourceManager::cStreamingResourceClient&);
};
