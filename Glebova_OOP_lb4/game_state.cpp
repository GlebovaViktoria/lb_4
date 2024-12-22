#include "game_state.h"


GameState::GameState(
    shared_ptr<Battleground> player_battleground, shared_ptr<Battleground> enemy_battleground,
    shared_ptr<ShipsManager> player_ships, shared_ptr<ShipsManager> enemy_ships
):  player_battleground(player_battleground), enemy_battleground(enemy_battleground), player_ships(player_ships),
    enemy_ships(enemy_ships), info_holder(enemy_battleground, enemy_ships), skills_manager(SkillsManager()) {}


vector<string> GameState::split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<pair<size_t, size_t>> GameState::getShipPositionOnBattleground(Ship& ship, Battleground& field) const{
    vector<pair<size_t, size_t>> coords;
    for (size_t x = 0; x < field.getWidth(); ++x){
        for (size_t y = 0; y < field.getHeight(); ++y){
            if (!field.getCell(x, y).isEmpty() && &field.getCell(x, y).getSegment() == &ship.getSegment(0)){
                for (size_t i = 0; i < ship.len(); ++i){
                    if (ship.getOrientation() == Ship::Orientation::VERTICAL)
                        coords.push_back(make_pair(x, y + i));
                    else
                        coords.push_back(make_pair(x + i, y));
                }
            }
        }
    }
    return coords;
}

string GameState::ShipsManagerToString(ShipsManager& ships_manager, Battleground& field) const{
    string res = to_string(ships_manager.len()) + "\n";
    for (size_t i = 0; i < ships_manager.len(); ++i){
        vector<pair<size_t, size_t>> coords = getShipPositionOnBattleground(ships_manager.getShip(i), field);
        res += to_string(ships_manager.getShip(i).len()) + " " + to_string(static_cast<int>(ships_manager.getShip(i).getOrientation())) + "$";
        for (size_t j = 0; j < coords.size(); ++j){
            res += to_string(coords[j].first) + ";" + to_string(coords[j].second) + ";" 
            + to_string(static_cast<int>(field.getCell(coords[j].first, coords[j].second).getSegment().getState())) + " ";
        }
        res += "%";
    }
    res += "\n";
    return res;
}

string GameState::BattlegroundToString(Battleground& field) const{
    string res = to_string(field.getWidth()) + " " + to_string(field.getHeight()) + "\n";
    for (size_t i = 0; i < field.getHeight(); ++i){
        for (size_t j = 0; j < field.getWidth(); ++j){
            res += to_string(static_cast<int>(field.getCell(j, i).getCondition())) + " ";
        }
        res += "\n";
    }
    return res;
}

string GameState::SkillsManagerToString(const SkillsManager& skills_manager) const{
    string res = to_string(skills_manager.size()) + "\n";
    for (auto s : skills_manager.getPrettySkills())
        res += s + "\n";
    return res;
}

ostream& operator<<(ostream& os, const GameState& game_state){
    string save = "";
    save += game_state.ShipsManagerToString(*game_state.player_ships, *game_state.player_battleground);
    save += game_state.ShipsManagerToString(*game_state.enemy_ships, *game_state.enemy_battleground);
    save += game_state.BattlegroundToString(*game_state.player_battleground);
    save += game_state.BattlegroundToString(*game_state.enemy_battleground);
    save += game_state.SkillsManagerToString(game_state.skills_manager);
    save += to_string(static_cast<int>(game_state.turn)) + " " + to_string(static_cast<int>(game_state.is_game_started)) + "\n";
    save += to_string(game_state.info_holder.x) + " " + to_string(game_state.info_holder.y) + "\n";
    os << save << hash<string>()(save);
    return os;
}


vector<tuple<size_t, Ship::Orientation, vector<tuple<size_t, size_t, Segment::State>>>> GameState::StringToShips(vector<string>& lines, size_t& curr_line){
    vector<tuple<size_t, Ship::Orientation, vector<tuple<size_t, size_t, Segment::State>>>> ships;
    size_t len = stoi(lines[curr_line]);
    vector<string> ships_str = this->split(lines[curr_line + 1], '%');

    for (size_t i = 0; i < ships_str.size(); ++i){
        vector<string> coords = this->split(ships_str[i], '$');
        vector<string> base_info = this->split(coords[0], ' ');
        size_t ship_len = stoi(base_info[0]);
        Ship::Orientation orientation = static_cast<Ship::Orientation>(stoi(base_info[1]));
        vector<tuple<size_t, size_t, Segment::State>> segments;
        if (coords.size() > 1){
            vector<string> segments_info = this->split(coords[1], ' ');
            for (size_t k = 0; k < segments_info.size(); ++k){
                vector<string> segment_info = this->split(segments_info[k], ';');
                segments.push_back(make_tuple(stoi(segment_info[0]), stoi(segment_info[1]), static_cast<Segment::State>(stoi(segment_info[2]))));
            }
        }
        ships.push_back(make_tuple(ship_len, orientation, segments));
    }
    curr_line += 2;
    return ships;
}


void GameState::addShipsOnField(Battleground& field, ShipsManager& ships_manager, vector<tuple<size_t, Ship::Orientation, vector<tuple<size_t, size_t, Segment::State>>>>& ships){
    for (size_t i = 0; i < ships.size(); ++i){
        tuple<size_t, Ship::Orientation, vector<tuple<size_t, size_t, Segment::State>>> current_ship = ships[i];
        if (get<2>(current_ship).size() != 0){
            field.placeShip(get<0>(get<2>(current_ship)[0]), get<1>(get<2>(current_ship)[0]), ships_manager.getShip(i), get<1>(current_ship));
            for (size_t j = 0; j < get<2>(current_ship).size(); ++j){
                field.getCell(get<0>(get<2>(current_ship)[j]), get<1>(get<2>(current_ship)[j])).getSegment().setState(get<2>(get<2>(current_ship)[j]));
            }
        }
    }
}


vector<unsigned short int> GameState::getLensOfShips(vector<tuple<size_t, Ship::Orientation, vector<tuple<size_t, size_t, Segment::State>>>>& ships) {
    vector<unsigned short int> len_of_ships;
    for (size_t i = 0; i < ships.size(); ++i)
        len_of_ships.push_back(get<0>(ships[i]));
    return len_of_ships;
}

void GameState::setCellStates(Battleground& field, vector<string>& lines, size_t& curr_line) {
    for (size_t i = 0; i < field.getHeight(); ++i) {
        vector<string> states = this->split(lines[curr_line + i], ' ');
        for (size_t j = 0; j < field.getWidth(); ++j) {
            field.getCell(j, i).setCondition(static_cast<Cell::VisibilityCondition>(stoi(states[j])));
        }
    }
    curr_line += field.getHeight();
}

istream& operator>>(istream& is, GameState& game_state){
    stringstream buffer;
    buffer << is.rdbuf();
    string full_save = buffer.str();
    vector<string> lines = game_state.split(full_save, '\n');

    if (lines.size() < 6)
        throw invalid_argument("Incorrect save");
    
    vector<string> save(lines.begin(), lines.end() - 1);
    string save_sum = "";
    for (auto s : save)
        save_sum += s + "\n";
    
    if (to_string(hash<string>()(save_sum)) != lines[lines.size() - 1])
        throw invalid_argument("Hash doesn't match. Save is corrupted");


    size_t curr_line = 0;
    auto player_ships = game_state.StringToShips(lines, curr_line);
    auto enemy_ships = game_state.StringToShips(lines, curr_line);
    game_state.player_ships = make_shared<ShipsManager>(ShipsManager(player_ships.size(), game_state.getLensOfShips(player_ships)));
    game_state.enemy_ships = make_shared<ShipsManager>(ShipsManager(enemy_ships.size(), game_state.getLensOfShips(enemy_ships)));
    
    auto field_data = game_state.split(lines[curr_line], ' ');
    game_state.player_battleground = make_shared<Battleground>(Battleground(stoi(field_data[0]), stoi(field_data[1])));
    game_state.addShipsOnField(*game_state.player_battleground, *game_state.player_ships, player_ships);
    game_state.player_ships->getNewDeads();
    ++curr_line;
    game_state.setCellStates(*game_state.player_battleground, lines, curr_line);

    field_data = game_state.split(lines[curr_line], ' ');
    game_state.enemy_battleground = make_shared<Battleground>(Battleground(stoi(field_data[0]), stoi(field_data[1])));
    game_state.addShipsOnField(*game_state.enemy_battleground, *game_state.enemy_ships, enemy_ships);
    game_state.enemy_ships->getNewDeads();
    ++curr_line;
    game_state.setCellStates(*game_state.enemy_battleground, lines, curr_line);
    
    vector<string> skills;
    for (size_t i = 0; i < stoi(lines[curr_line]); ++i)
        skills.push_back(lines[curr_line + 1 + i]);
    curr_line += 1 + skills.size();
    game_state.skills_manager = SkillsManager(skills);

    vector<string> info = game_state.split(lines[curr_line], ' ');
    game_state.turn = static_cast<GameState::Turn>(stoi(info[0]));
    game_state.is_game_started = static_cast<bool>(stoi(info[1]));
    ++curr_line;

    vector<string> info_holder_coords = game_state.split(lines[curr_line], ' ');
    game_state.info_holder.x = stoi(info_holder_coords[0]);
    game_state.info_holder.y = stoi(info_holder_coords[1]);
    game_state.info_holder.battleground = game_state.enemy_battleground;
    game_state.info_holder.ships_manager = game_state.enemy_ships;

    return is;
    
}
