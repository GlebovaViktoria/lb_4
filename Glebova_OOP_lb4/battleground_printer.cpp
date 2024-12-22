#include "battleground_printer.h"


void BattlegroundPrinter::printEnemy(Battleground battleground){
    for (size_t y = 0; y < battleground.getHeight(); ++y){
        for (size_t x = 0; x < battleground.getWidth(); ++x){
            switch (battleground.getCell(x, y).getCondition()){
                case Cell::VisibilityCondition::SHIP:
                    switch (battleground.getCell(x, y).getSegment().getState()){
                        case Segment::State::UNDAMAGED:
                            cout<<2;
                            break;
                        case Segment::State::DAMAGED:
                            cout<<1;
                            break;
                        case Segment::State::DESTROYED:
                            cout<<0;
                            break;
                    }                        
                    break;
                
                case Cell::VisibilityCondition::HIDDEN:
                    cout<<'?';
                    break;
                
                case Cell::VisibilityCondition::EMPTY:
                    cout<<"□";
                    break;

                default:
                    break;
            }
            cout<<" ";
        }
        cout<<endl;
    }
}

void BattlegroundPrinter::printPlayer(Battleground battleground){
    for (size_t y = 0; y < battleground.getHeight(); ++y){
        for (size_t x = 0; x < battleground.getWidth(); ++x){
            if (battleground.getCell(x, y).isEmpty()){
                cout<<"□";
            }
            else{
                switch (battleground.getCell(x, y).getSegment().getState()){
                    case Segment::State::UNDAMAGED:
                        cout<<2;
                        break;
                    case Segment::State::DAMAGED:
                        cout<<1;
                        break;
                    case Segment::State::DESTROYED:
                        cout<<0;
                        break;
                }
            }
            cout<<" ";
        }
        cout<<endl;
    }
}