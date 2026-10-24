
class Editor::cGUIDLinkerBase { /* Size=0x4 */
  
  protected: virtual ~cGUIDLinkerBase();
  protected: void* FindEntityInMap(const RWS::RWSGUID&);
  public: cGUIDLinkerBase(const Editor::cGUIDLinkerBase&);
  public: cGUIDLinkerBase();
  public: Editor::cGUIDLinkerBase& operator=(const Editor::cGUIDLinkerBase&);
  public: void __local_vftable_ctor_closure();
  protected: virtual void* __vecDelDtor(unsigned int);
};
