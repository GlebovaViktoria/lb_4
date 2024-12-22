#pragma once

#include <vector>
#include <iostream>
#include <string>

using namespace std;


class Reader{
    public:
        vector<size_t> getCoords(){
            size_t x = 0, y = 0;
            cin>>x>>y;
            return vector<size_t>{x, y};
        }
        vector<size_t> battlegroundSize(){
            size_t x = 0, y = 0;
            cout<<"Введите размеры поля: ";
            cin>>x>>y;
            return vector<size_t>{x, y};
        }
        char getCommand(){
            char c;
            cin>>c;
            return c;
        }
        vector<size_t> getShips(){
            size_t a=0, b=0, c=0, d=0;
            cout<<"Введите кол-во кораблей длинны 1 2 3 4: ";
            cin>>a>>b>>c>>d;
            return vector<size_t>{a, b, c, d};
        }
        string getFilename(){
            string s;
            cout<<"Введите название файла: ";
            cin>>s;
            return s;
        }
};