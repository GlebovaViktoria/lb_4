#pragma once


#include "battleground.h"
#include "ships_manager.h"
#include "skills_manager.h"
#include "ships_manager.h"
#include "info_holder.h"
#include <memory>

class Game;


class GameState {
    friend class Game;

    public:
        enum Turn{
            PLAYER = 0,
            ENEMY = 1
        };
        GameState(shared_ptr<Battleground> player_battleground, shared_ptr<Battleground> enemy_battleground, shared_ptr<ShipsManager> player_ships, shared_ptr<ShipsManager> enemy_ships);
        friend ostream& operator<<(ostream& os, const GameState& game_state);
        friend istream& operator>>(istream& is, GameState& game_state);

    private:
        shared_ptr<Battleground> player_battleground;
        shared_ptr<Battleground> enemy_battleground;
        shared_ptr<ShipsManager> player_ships;
        shared_ptr<ShipsManager> enemy_ships;
        InfoHolder info_holder;
        SkillsManager skills_manager;
        Turn turn = PLAYER;
        bool is_game_started = false;

        vector<pair<size_t, size_t>> getShipPositionOnBattleground(Ship& ship, Battleground& field) const;
        string ShipsManagerToString(ShipsManager& ships_manager, Battleground& field) const;
        string BattlegroundToString(Battleground& field) const;
        string SkillsManagerToString(const SkillsManager& skills_manager) const;
    
        vector<string> split(const string &s, char delim);
        vector<tuple<size_t, Ship::Orientation, vector<tuple<size_t, size_t, Segment::State>>>> StringToShips(vector<string>& lines, size_t& curr_line);
        vector<unsigned short int> getLensOfShips(vector<tuple<size_t, Ship::Orientation, vector<tuple<size_t, size_t, Segment::State>>>>& ships);
        void setCellStates(Battleground& field, vector<string>& lines, size_t& curr_line);
        void addShipsOnField(Battleground& field, ShipsManager& ships_manager, vector<tuple<size_t, Ship::Orientation, vector<tuple<size_t, size_t, Segment::State>>>>& ships);
};