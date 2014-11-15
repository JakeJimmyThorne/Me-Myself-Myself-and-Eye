#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.cpp"

class Player : GameObject
{
public:
    Player(int level);
    ~Player();

    void updateAnimation(sf::Time dt, sf::Clock &clock);
    void update();

    void setVelocity(sf::Vector2f newVel);

    void drawPlayer(sf::RenderWindow &window);
    void initilize();

    //direction, 0 for left, 1 = jump, 2 = right, 3 = down
    void movePlayer();

    void setPlatformBB(sf::Sprite obj, int i);
    int platformAmoumt;

    int drawCharInCell = 1;
    int headCount;
    float getX();
    float getY();

    bool collide(sf::FloatRect otherObject);

private:


    sf::Time slowTime;
    sf::Clock slowClock;

    sf::Time wiggleTime[3];
    sf::Clock wiggleClock[3];

    float maxSpeed;

    sf::RectangleShape collision[4];
    sf::FloatRect collisionBB[4];

    bool canJump;
    bool canRight;
    bool canLeft;

    sf::Vector2f playerVelocity;

    int speed;

    //for heads
    float wiggleSpace;
    int wiggleIncrement[3];
    bool wiggleRight[3];
    float delay[3];

    sf::Texture headTextureActiveIdle;
    sf::Texture headTextureActiveLeft;
    sf::Texture headTextureActiveRight;
    sf::Texture headTextureClosed;
    sf::Image switchingImages;

    sf::RectangleShape headObjects[3];

    sf::IntRect animationWalking[4];
    sf::IntRect animationIdle[2];
    sf::IntRect animationJumping;
    sf::IntRect animationFalling;

    sf::IntRect animationWalkingL[4];
    sf::IntRect animationIdleL[2];
    sf::IntRect animationJumpingL;
    sf::IntRect animationFallingL;

    int lastWalkingState;
    int lastIdleState;
    int lastWalkingStateL;
    int lastIdleStateL;

    sf::Music ambientMusic;
    sf::Music idleSound;
    bool idlePlaying;
    sf::SoundBuffer playerSoundBuffer[3];

    //idling, moving, jumping
    sf::Sound playerSound[3];

    bool idling,moving,jumping;
    bool goingLeft, goingRight;

    sf::Texture totemBodyTextureL;
    sf::Time leftAniTime;
    sf::Clock leftAniClock;

    sf::FloatRect platformBB[50];

};

#endif //PLAYER_H
