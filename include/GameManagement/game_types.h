// STAND-IN for the reference etGameModeType used by game-mode trigger interfaces.
// eGMT_Invalid is our name for the -1 used by CD2 constructor 0x82883AB8 and
// RetGameType (0x82883D68); the remaining enumerators are not recovered.
#ifndef GAMEMANAGEMENT_GAME_TYPES_H
#define GAMEMANAGEMENT_GAME_TYPES_H
namespace GameManagement { enum etGameModeType { eGMT_Invalid = -1 }; }
#endif
