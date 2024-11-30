#include "Constant.h"

class Signal{
    bool State;
    int SignalId;
    //x-cord
    //y-cord
    sf::Texture SignalTextureRed;
    sf::Texture SignalTextureYellow;
    sf::Texture SignalTextureGreen;
    sf::Sprite SignalSprite;
    
    public:
    Signal* prev;
    Signal* next;
    Signal(){
        //SignalTexture=NULL;
        SignalSprite.setTexture(SignalTextureRed);
        prev=NULL;
        next=NULL;
        State=false;
        SignalId=NULL;
    }//constructor
    Signal(int id){
        SignalId=id;
        if(SignalId==1){
            State=true;
            SignalSprite.setTexture(SignalTextureGreen);
        }
        else{
         SignalSprite.setTexture(SignalTextureRed);
        }

    }//parameterized constructor

    void changeState(){
            State = !State; 
            if(SignalSprite.getTexture()==SignalTextureRed){
                SignalSprite.setTexture(SignalTextureYellow);
                SingalSprite.setTexture(SignalTextureGreen);
            } 
            else{
             SingalSprite.setTexture(SignalTextureRed);
            }
    }//changeState

    void setSpritePosition(float a,float b){
        SignalSprite.setPosition(x,y);
    }//setSpritePosition

    void setSpriteRotation(float a){
        SignalSprite.setRotation(a);
    }//setSpriteRotation

    int getSignalId(){
        return SignalId;
    }//getSignalId

    void onPriority(){
        State=true;
        SingalSprite.setTexture(SignalTextureGreen);
    }//onPriority

    void onOff(){
        State=false;
        SignalSprite.setTexture(SignalTextureRed);
    }//onOff


}