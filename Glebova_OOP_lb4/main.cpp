#include "segment.h"
#include "ships_manager.h"
#include "ship.h"
#include "battleground.h"
#include "info_holder.h"
#include "skills_manager.h"
#include "game.h"
#include "battleground_printer.h"
#include "reader.h"
#include "game_control.h"
#include "game_manager.h"

#include <iostream>

using namespace std;

int main(){
    try{
        random_device rd;
        default_random_engine engine(rd());

        vector<short unsigned int> lens = {1, 2, 3};
        ShipsManager player_manager(3, lens), enemy_manager(3, lens);
        Battleground battleground_player(4, 4), battleground_enemy(4, 4);

        auto battleground_player_ptr = make_shared<Battleground>(battleground_player);
        auto player_manager_ptr = make_shared<ShipsManager>(player_manager);
        auto battleground_enemy_ptr = make_shared<Battleground>(battleground_enemy);
        auto enemy_manager_ptr = make_shared<ShipsManager>(enemy_manager);

        Game game(battleground_player_ptr, battleground_enemy_ptr, player_manager_ptr, enemy_manager_ptr);
        GameManager<BattlegroundPrinter, Reader, GameControl> gm(game, "управление");
        gm.play();
        
    }
    catch(exception& e){
        cerr<<e.what()<<endl;
        return 1;
    }

    return 0;
}