#pragma once

#include "game.h"

using namespace std;

template<class PrinterT, class ReaderT, class GameControlT>
class GameManager {
    public:
        GameManager(Game& m_game, string control_filename): m_game(m_game), m_game_printer(PrinterT()), m_game_read(ReaderT()){
            try{
                m_game_control = GameControlT();
                m_game_control.load(control_filename);
            } catch (exception& e) {
                cout<<e.what()<<" Буду установленны настройки по умолчанию";
                m_game_control.setDefault();
            }
        }

        void play(){
            try{
                setNewGame();
            }
            catch(exception& e) {
                cout<<"Ошибка при вводе кораблей. Выход.\n";
                return;
            }
            printHelp();
            while (true){
                m_game_printer.printPlayer(m_game.getPlayer());
                m_game_printer.printEnemy(m_game.getEnemy());
                m_game.startGame();
                
                while (!m_game.isEnemyWin() && !m_game.isPlayerWin()){
                    char command = m_game_read.getCommand();
                    string parsed = m_game_control.parseCommand(command);
                    if (parsed == "help")
                        printHelp();
                    else if (parsed == "attack"){
                        bool use_skill = false;
                        vector<size_t> skill_coords = {0, 0};
                        cout<<"Использовать скилл? (y/n) ";
                        char command2 =m_game_read.getCommand();
                        if (command2 == 'y')
                            use_skill = true;
                        if (use_skill){
                            cout<<"Введите координаты скилла: ";
                            skill_coords = m_game_read.getCoords();
                        }
                        vector<size_t> attack_coords = {0, 0};
                        cout<<"Введите координаты атаки: ";
                        attack_coords = m_game_read.getCoords();
                        this->m_game.playerTurn(attack_coords[0], attack_coords[1], use_skill, skill_coords[0], skill_coords[1]);
                        this->m_game.enemyTurn();
                        m_game_printer.printPlayer(m_game.getPlayer());
                        m_game_printer.printEnemy(m_game.getEnemy());
                    }
                    else if (parsed == "load"){
                        string filename = m_game_read.getFilename();
                        m_game.load(filename);
                    }
                    else if (parsed == "save"){
                        string filename = m_game_read.getFilename();
                        m_game.save(filename);
                    }
                    else{
                        cout<<"Неверная команда\n";
                        continue;
                    }
                }

                if (m_game.isPlayerWin() && m_game.isEnemyWin()){
                    cout<<"Ничья. Перезагрузка\n";
                    try{
                        setNewGame();
                    }
                    catch(exception& e) {
                        cout<<"Ошибка при вводе кораблей. Выход.\n";
                        return;
                    }
                }
                else if (m_game.isPlayerWin()){
                    cout<<"Победа. Загрузка нового противника\n";
                    setNewEnemy();
                }
                else if (m_game.isEnemyWin()){
                    cout<<"Проигрыш. Перезагрузка\n";
                    try{
                        setNewGame();
                    }
                    catch(exception& e) {
                        cout<<"Ошибка при вводе кораблей. Выход.\n";
                        return;
                    }
                }
            }
        }

    private:

        void setNewEnemy(){
            vector<unsigned short int> ship_lens;
            ShipsManager ships = m_game.getEnemyShips();
            for (size_t i = 0; i < ships.len(); ++i){
                ship_lens.push_back(ships.getShip(i).len());
            }
            random_device rd;
            default_random_engine engine(rd());
            size_t field_width = m_game.getEnemy().getWidth();
            size_t field_height = m_game.getEnemy().getHeight();
            Battleground enemy(field_width, field_height); 
            shared_ptr<ShipsManager> enemy_ships = make_shared<ShipsManager>(ShipsManager(ship_lens.size(), ship_lens));
            shared_ptr<Battleground> enemy_field = make_shared<Battleground>(enemy);

            for (size_t i = 0; i < enemy_ships->len(); ++i){
                try{
                    enemy_field->placeShip(engine()%field_width, engine()%field_height, enemy_ships->getShip(i), static_cast<Ship::Orientation>(engine() % 2));
                }
                catch (exception& e){
                    continue;
                }
            }

            m_game.newEnemy(enemy_field, enemy_ships);
        }

        void setNewGame(){
            vector<size_t> ships = m_game_read.getShips();
            vector<size_t> battleground = m_game_read.battlegroundSize();
            if (battleground[0] == 0 || battleground[0] == 0)
                throw logic_error("Размер поля не может быть равен нулю!");
            Battleground playing_battleground(battleground[0], battleground[1]);
            Battleground enemy_playing_battleground(battleground[0], battleground[1]);
            vector<unsigned short int> ship_lens;
            for (size_t i = 0; i < 4; ++i){
                for (size_t j = 0; j < ships[i]; ++j){
                    ship_lens.push_back(i + 1);
                }
            }
            ShipsManager player_ships(ship_lens.size(), ship_lens);
            ShipsManager enemy_shipss(ship_lens.size(), ship_lens);

            shared_ptr<Battleground> player_battleground = make_shared<Battleground>(playing_battleground);
            shared_ptr<Battleground> enemy_battleground = make_shared<Battleground>(enemy_playing_battleground);
            shared_ptr<ShipsManager> player_ships_p = make_shared<ShipsManager>(player_ships);
            shared_ptr<ShipsManager> enemy_ships = make_shared<ShipsManager>(enemy_shipss);

            random_device rd;
            default_random_engine engine(rd());

            for (size_t i = 0; i < player_ships.len(); ++i){
                try{
                    player_battleground->placeShip(engine()%battleground[0], engine()%battleground[1], player_ships_p->getShip(i), static_cast<Ship::Orientation>(engine() % 2));
                    enemy_battleground->placeShip(engine()%battleground[0], engine()%battleground[1], enemy_ships->getShip(i), static_cast<Ship::Orientation>(engine() % 2));
                }
                catch (exception& e){
                    continue;
                }
            }

            m_game.newRound(player_battleground, enemy_battleground, player_ships_p, enemy_ships);
        }
        void printHelp(){
            cout<<"Справка:\n";
            cout<<"Справка -- "<<m_game_control.getCommandKey("help")<<endl;
            cout<<"Загрузка -- "<<m_game_control.getCommandKey("load")<<endl;
            cout<<"Сохранение -- "<<m_game_control.getCommandKey("save")<<endl;
            cout<<"Атаковать -- "<<m_game_control.getCommandKey("attack")<<endl;
        }

        Game& m_game;
        PrinterT m_game_printer;
        ReaderT m_game_read;
        GameControlT m_game_control;
};