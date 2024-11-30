#include "Constant.h"

class Signal
{
    bool State;
    int SignalId;
    sf::Texture SignalTextureRed;
    sf::Texture SignalTextureYellow;
    sf::Texture SignalTextureGreen;
    sf::Sprite SignalSprite;

public:
    Signal *next;
    Signal(int id)
    {
        if (!SignalTextureGreen.loadFromFile(GreenImagePath))
        {
            std::cerr << "Failed to load map image!" << std::endl;
        }
        if (!SignalTextureRed.loadFromFile(RedImagePath))

        {
            std::cerr << "Failed to load map image!" << std::endl;
        }
        if (!SignalTextureYellow.loadFromFile(YellowImagePath))
        {
            std::cerr << "Failed to load map image!" << std::endl;
        }
        SignalId = id;
        if (SignalId == 1)
        {
            State = true;
            SignalSprite.setTexture(SignalTextureGreen);
        }
        else
        {
            SignalSprite.setTexture(SignalTextureRed);
            State = false;
        }
        SignalSprite.setTexture(SignalTextureRed);
        SignalSprite.setScale(0.3, 0.3);
        next = NULL;
    } // parameterized constructor

    void changeState()
    {
        State = !State;
        if (SignalSprite.getTexture() == &SignalTextureRed)
        {
            SignalSprite.setTexture(SignalTextureYellow);
            SignalSprite.setTexture(SignalTextureGreen);
        }
        else
        {
            SignalSprite.setTexture(SignalTextureRed);
        }
    } // changeState

    void setSpritePosition(float a, float b)
    {
        SignalSprite.setPosition(a, b);
    } // setSpritePosition

    void setSpriteRotation(float a)
    {
        SignalSprite.setRotation(a);
    } // setSpriteRotation

    int getSignalId()
    {
        return SignalId;
    } // getSignalId

    void onPriority()
    {
        State = true;
        SignalSprite.setTexture(SignalTextureGreen);
    } // onPriority

    void onOff()
    {
        State = false;
        SignalSprite.setTexture(SignalTextureRed);
    } // onOff

    sf::Sprite getSignalSprite()
    {
        return SignalSprite;
    } // getSprite
};