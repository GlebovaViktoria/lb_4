#include "game.h"
#include "no_skill_exception.h"
#include "out_of_battleground_attack_exception.h"


Game::Game(shared_ptr<Battleground> player_battleground, shared_ptr<Battleground> enemy_battleground, shared_ptr<ShipsManager> player_ships, shared_ptr<ShipsManager> enemy_ships):
    game_state(player_battleground, enemy_battleground, player_ships, enemy_ships) {}

void Game::startGame(){
    this->game_state.is_game_started = true;
    this->game_state.turn = GameState::Turn::PLAYER;
}

void Game::load(string filename){
    if (this->game_state.turn != GameState::Turn::PLAYER || !this->game_state.is_game_started)
        throw logic_error("You can't load the game if it's not started or if it's not your turn!");
    ifstream load(filename);
    if (!load)
        throw logic_error("File not found!");
    load >> this->game_state;
    load.close();
}

void Game::save(string filename){
    if (this->game_state.turn != GameState::Turn::PLAYER || !this->game_state.is_game_started)
        throw logic_error("You can't save the game if it's not started or if it's not your turn!");
    ofstream save(filename);
    if (!save)
        throw logic_error("Can't create/open file!");
    save << this->game_state;
    save.close();
}

bool Game::IsGameStarted(){
    return this->game_state.is_game_started;
}

bool Game::IsPlayerTurn(){
    return this->game_state.turn == GameState::Turn::PLAYER;
}

void Game::newRound(shared_ptr<Battleground> player_battleground, shared_ptr<Battleground> enemy_battleground, shared_ptr<ShipsManager> player_ships, shared_ptr<ShipsManager> enemy_ships){
    this->game_state.player_battleground = player_battleground;
    this->game_state.enemy_battleground = enemy_battleground;
    this->game_state.player_ships = player_ships;
    this->game_state.enemy_ships = enemy_ships;
    this->game_state.info_holder = InfoHolder(this->game_state.enemy_battleground, this->game_state.enemy_ships);
    this->game_state.skills_manager = SkillsManager();
    this->startGame();
}

void Game::newEnemy(shared_ptr<Battleground> battleground, shared_ptr<ShipsManager> ships_manager){
    this->game_state.enemy_battleground = battleground;
    this->game_state.enemy_ships = ships_manager;
    this->game_state.info_holder = InfoHolder(this->game_state.enemy_battleground, this->game_state.enemy_ships);
    this->startGame();
}


void Game::enemyTurn(){
    if (this->game_state.turn != GameState::Turn::ENEMY || !this->game_state.is_game_started)
        throw logic_error("Enemy can't make a turn if it's not your turn or if the game is not started!");
    random_device rd;
    default_random_engine engine(rd());
    this->game_state.player_battleground->attackCell(
        engine() % this->game_state.player_battleground->getWidth(),
        engine() % this->game_state.player_battleground->getHeight()
    );
    this->game_state.turn = GameState::Turn::PLAYER;   
}

void Game::playerTurn(size_t x, size_t y, bool use_skill, size_t skill_x, size_t skill_y){
    if (this->game_state.turn != GameState::Turn::PLAYER || !this->game_state.is_game_started)
        throw logic_error("Player can't make a turn if it's not your turn or if the game is not started!");
    if (use_skill){
        this->game_state.info_holder.x = x;
        this->game_state.info_holder.y = y;
        try{
            this->game_state.skills_manager.usePopSkill(this->game_state.info_holder);
        }
        catch (NoSkillException& e){
            cerr << "Player doesn't have skill" << endl;
        }
    }
    try{
        this->game_state.enemy_battleground->attackCell(x, y);
    }
    catch (OutOfBattlegroundAttackException& e){
        cerr << "Cell is out of battleground" << endl;
    }
    this->game_state.skills_manager.addRandomSkills(this->game_state.player_ships->getNewDeads());
    this->game_state.turn = GameState::Turn::ENEMY;
}

bool Game::isPlayerWin(){
    return !this->game_state.enemy_battleground->isHaveAliveShips();
}

bool Game::isEnemyWin(){
    return !this->game_state.player_battleground->isHaveAliveShips();
}

Battleground Game::getPlayer(){
    return *(this->game_state.player_battleground);
}

Battleground Game::getEnemy(){
    return *(this->game_state.enemy_battleground);
}

ShipsManager Game::getEnemyShips(){
    return *(this->game_state.enemy_ships);
}