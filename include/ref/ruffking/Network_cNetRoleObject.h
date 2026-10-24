
class Network::cNetRoleObject { /* Size=0x8 */
  /* 0x0004 */ protected: etNetRole m_eNetRole;
  
  public: cNetRoleObject(const Network::cNetRoleObject&);
  public: cNetRoleObject(etNetRole);
  public: cNetRoleObject();
  public: virtual ~cNetRoleObject();
  public: virtual void SetNetRole(etNetRole);
  public: etNetRole RetNetRole() const;
  public: bool IsAuthority() const;
  public: bool IsSimulated() const;
  public: bool IsDumb() const;
  public: virtual void OnEnterNetRoleAuthority(etNetRole);
  public: virtual void OnEnterNetRoleSimulated(etNetRole);
  public: virtual void OnEnterNetRoleDumb(etNetRole);
  public: virtual void OnEnterNetRoleNone(etNetRole);
  public: void DebugRenderNetRole(const Fun_Runtime::Vec3&);
  public: Network::cNetRoleObject& operator=(const Network::cNetRoleObject&);
  public: void __local_vftable_ctor_closure();
  public: virtual void* __vecDelDtor(unsigned int);
};
