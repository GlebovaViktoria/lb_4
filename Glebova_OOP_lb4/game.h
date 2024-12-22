#pragma once


#include "battleground.h"
#include "ships_manager.h"
#include "skills_manager.h"
#include "ships_manager.h"
#include "info_holder.h"
#include "game_state.h"
#include <memory> // Added include for shared_ptr


class Game {
    public:
        Game(shared_ptr<Battleground> player_battleground, shared_ptr<Battleground> enemy_battleground, shared_ptr<ShipsManager> player_ships, shared_ptr<ShipsManager> enemy_ships);
        void startGame();
        void playerTurn(size_t x, size_t y, bool use_skill=false, size_t skill_x=0, size_t skill_y=0);
        void enemyTurn();
        bool isPlayerWin();
        bool isEnemyWin();
        void newEnemy(shared_ptr<Battleground> battleground, shared_ptr<ShipsManager> ships_manager);
        void newRound(shared_ptr<Battleground> player_battleground, shared_ptr<Battleground> enemy_battleground, shared_ptr<ShipsManager> player_ships, shared_ptr<ShipsManager> enemy_ships);
        bool IsPlayerTurn();
        bool IsGameStarted();
        void save(string filename);
        void load(string filename);
        Battleground getPlayer();
        Battleground getEnemy();
        ShipsManager getEnemyShips();

    private:
        GameState game_state;
};