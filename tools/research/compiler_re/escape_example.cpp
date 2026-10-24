#include "editor/guid_event_handler.h"
namespace Editor { RWS::RWSGUID g_GUIDNull; }
RWS::RWSGUID *EscapeGUIDNull() { return &Editor::g_GUIDNull; }
