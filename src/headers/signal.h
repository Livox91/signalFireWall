
#include "Constant.h"


class Signal{
    Signal* prev;
    Signal* next;
    bool State;
    int SignalId;
    //x-cord
    //y-cord
    sf::Texture SignalTexture;
    sf::Sprite SignalSprite;
    
    public:
    Signal(){
        SignalTexture=NULL;
        SignalSprite.setTexture(SignalTexture);
        prev=NULL;
        next=NULL;
        State=false;
        SignalId=NULL;
    }//constructor
    Signal(int id){
        SignalId=id;
    }

    void changeState(){
            State = !State;  
    }//changeState

    void setSpritePosition(float a,float b){
        SignalSprite.setPosition(x,y);
    }//setPosition

    void spriteRotation(float a){
        SignalSprite.setRotation(a);
    }//spriteRotation

}