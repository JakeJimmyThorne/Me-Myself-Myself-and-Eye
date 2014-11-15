#include "player.h"

Player::Player(int level)
{
    object.setSize(sf::Vector2f(64,64));

    if(level == 1)
    {
        headCount = 1;
        object.setPosition(200,830);
    }
    else if(level == 2)
    {
        headCount = 2;
        object.setPosition(1800,800);
    }


    ambientMusic.openFromFile("data/sound/mainGame.ogg");
    ambientMusic.setLoop(true);

    idleSound.openFromFile("data/sound/playerIdle.ogg");
    ambientMusic.setLoop(true);

    playerSoundBuffer[0].loadFromFile("data/sound/playerIdle.ogg");
    playerSoundBuffer[1].loadFromFile("data/sound/playerWalk.ogg");
    playerSoundBuffer[2].loadFromFile("");

    sf::Sound playerSound[3];

    for(int i = 0; i < 3; i++)
    {
        playerSound[i].setBuffer(playerSoundBuffer[i]);

        if(i == 2)
            playerSound[i].setLoop(false);
        else
            playerSound[i].setLoop(true);

        wiggleIncrement[i] = 0;

        if(i != 2)
            delay[i] = i * 0.25;
        else
            delay[i] = i * 0.3;
    }

    wiggleSpace = 5;
    wiggleRight[0] = true;
    wiggleRight[1] = true;
    wiggleRight[2] = true;


    for(int i = 0; i < 3; i++)
    {
        headObjects[i].setSize(sf::Vector2f(32,32));
    }




    for(int i = 0; i < 4; i++)
    {
        collision[i].setFillColor(sf::Color::Green);
    }

    collision[0].setSize(sf::Vector2f(object.getSize().x /2,4));
    collision[2].setSize(sf::Vector2f(object.getSize().x /2,4));

    collision[0].setOrigin(16,2);
    collision[2].setOrigin(16,2);

    collision[1].setSize(sf::Vector2f(4,object.getSize().y - 12));
    collision[3].setSize(sf::Vector2f(4,object.getSize().y - 12));

    canJump = false;
    canRight = true;
    canLeft = true;

    moving = false;
    jumping = false;
    idling = true;

    goingRight = true;
    goingLeft = false;

    texture.loadFromFile("data/textures/totemBody.png");
    totemBodyTextureL.loadFromFile("data/textures/totemBody_left.png");

    object.setTexture(&texture);

    lastWalkingState = 3;
    lastIdleState = 1;
    idlePlaying = false;

    ambientMusic.play();
}
Player::~Player()
{

}

void Player::update()
{
   // if(idling) && playerSound[0].getStatus() != sf::SoundSource::Playing)
        //idleSound.play();
    //else
        //idleSound.stop();

    //if(moving && playerSound[1].getStatus() != sf::SoundSource::Playing)
      //  playerSound[1].play();

    //if(jumping && playerSound[0].getStatus() != sf::SoundSource::Playing)
      //  playerSound[2].play();


    slowTime = slowClock.getElapsedTime();

    for(int i = 0; i < 3; i++)
    {
        wiggleTime[i] = wiggleClock[i].getElapsedTime();
    }

    if(!canJump)
        maxSpeed = 1;
    else
        maxSpeed = 3;

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && canLeft)
    {
        moving = true;
        idling = false;

        goingLeft = true;
        goingRight = false;

        if(wiggleIncrement[2] < wiggleSpace)
            wiggleIncrement[2] ++;

        if(wiggleIncrement[1] < wiggleSpace / 2)
            wiggleIncrement[1] ++;

        if(playerVelocity.x > -maxSpeed)
            playerVelocity.x -= 0.5;

        movePlayer();
        slowClock.restart();
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && canRight)
    {
        moving = true;
        idling = false;

        goingLeft = false;
        goingRight = true;

        if(wiggleIncrement[2] > -wiggleSpace)
            wiggleIncrement[2]--;

        if(wiggleIncrement[1] > -wiggleSpace + 2.5)
            wiggleIncrement[1]--;

        if(playerVelocity.x < maxSpeed)
            playerVelocity.x += 0.5;

        movePlayer();
        slowClock.restart();
    }
    else
    {
        if(playerVelocity.x > 0 && slowTime.asSeconds() < 0.5 * playerVelocity.x)
        {
            playerVelocity.x -= 0.2;
            movePlayer();
        }
        else if(playerVelocity.x < 0  && slowTime.asSeconds() < 0.5 * -playerVelocity.x)
        {
            playerVelocity.x += 0.2;
            movePlayer();
        }

        moving = false;
        idling = true;
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && canJump)
    {
        setVelocity(sf::Vector2f(playerVelocity.x, -10));

        jumping = true;
        idling = false;

        if(playerVelocity.x > 2)
            playerVelocity.x = 2;
        else if(playerVelocity.x < -2)
            playerVelocity.x = -2;

        canJump = false;
        movePlayer();
    }
    else if(!canJump)
    {
        if(playerVelocity.y < 9)
            playerVelocity.y += 0.5;

        moving = false;
        movePlayer();
    }

    collision[0].setPosition(object.getPosition().x + object.getSize().x / 2, object.getPosition().y);
    collision[2].setPosition(object.getPosition().x + object.getSize().x / 2, object.getPosition().y +
                             object.getSize().y + 1);

    collision[1].setPosition(object.getPosition().x + 12, object.getPosition().y);
    collision[3].setPosition(object.getPosition().x + object.getSize().x - 15,
                             object.getPosition().y);

    for(int i = 0; i < 3; i++)
    {
        if(wiggleTime[i].asSeconds() > 0.1 + delay[i] && !moving)
        {
            if(wiggleIncrement[i] < wiggleSpace && wiggleRight[i])
                wiggleIncrement[i]++;
            else if(wiggleIncrement[i] >= wiggleSpace && wiggleRight[i])
                wiggleRight[i] = false;

            if(wiggleIncrement[i] > -wiggleSpace && !wiggleRight[i])
                wiggleIncrement[i]--;
            else if(wiggleIncrement[i] <= -wiggleSpace && !wiggleRight[i])
                wiggleRight[i] = true;

            delay[i] = 0;

            wiggleClock[i].restart();
        }

        wiggleIncrement[0] = 0;
    }

    for(int i = 0; i < 3; i++)
    {
        headObjects[i].setPosition(object.getPosition().x + object.getSize().x/4 + wiggleIncrement[i],
                                   object.getPosition().y - 6 - i * 32);
    }

    for(int i = 0; i < 4; i++)
    {
        collisionBB[i] = collision[i].getGlobalBounds();
    }



    for(int i = 0; i < platformAmoumt; i++)
    {
       // if(platformBB[i] != NULL)
       // {
            if(collisionBB[0].intersects(platformBB[i]) && !canJump)
            {
                playerVelocity.y = 1;
                //playerVelocity.x *= 0.75;
            }

            if(collisionBB[0].intersects(platformBB[i]) && !canJump &&
               collisionBB[1].intersects(platformBB[i]))
            {
                playerVelocity.y = 1;
                //playerVelocity.x = -5;
            }

            if(collisionBB[2].intersects(platformBB[i]) && !canJump)
            {
                canJump = true;
                jumping = false;

                playerVelocity.y = 0;
                //playerVelocity.x *= 0.95;
                object.setPosition(object.getPosition().x,platformBB[i].top-object.getSize().y);
            }
            else if(!collisionBB[2].intersects(platformBB[i])&& moving)
            {
                canJump = false;
            }

            if(collisionBB[3].intersects(platformBB[i]))
            {
                canLeft = false;
                playerVelocity.x = -1;
            }
            else
                canLeft = true;

            if(collisionBB[1].intersects(platformBB[i]))
            {
                canRight = false;
                playerVelocity.x = 1;
            }
            else
                canRight = true;
       // }
    }

    if(slowTime.asSeconds() > 0.5)
        playerVelocity.x = 0;



    setBoundingBox();
}

void Player::setVelocity(sf::Vector2f newVel)
{
    playerVelocity = newVel;
    return;
}

void Player::updateAnimation(sf::Time dt, sf::Clock &clock)
{
    float bonusTime = idling ? 0.1 : 0;
    if(dt.asSeconds() > 0.15 + bonusTime)
    {

        if(goingRight)
        {
            int state;
            object.setTexture(&texture);

            for(int i = 0; i < headCount; i++)
                headObjects[i].setTexture(&headTextureActiveRight);

            if(jumping && playerVelocity.x < 0)
                object.setTextureRect(animationJumping);

            else if(jumping && playerVelocity.x > 0.2)
                object.setTextureRect(animationFalling);

            else if(idling)
            {
                switch(lastIdleState)
                {
                case 0:
                    state = 1;
                    break;
                case 1:
                    state = 0;
                    break;
                }

                object.setTextureRect(animationIdle[state]);
                lastIdleState = state;
            }
            else if(!idling)
            {
                switch(lastWalkingState)
                {
                case 0:
                    state = 1;
                    break;
                case 1:
                    state = 2;
                    break;
                case 2:
                    state = 3;
                    break;
                case 3:
                    state = 0;
                    break;
                }

                object.setTextureRect(animationWalking[state]);
                lastWalkingState = state;
            }
        }
        else if(goingLeft)
        {
            int state;
            object.setTexture(&totemBodyTextureL);

            for(int i = 0; i < headCount; i++)
                headObjects[i].setTexture(&headTextureActiveLeft);

            if(jumping && playerVelocity.x < 0)
                object.setTextureRect(animationJumpingL);

            else if(jumping && playerVelocity.x > 0.2)
                object.setTextureRect(animationFallingL);

            else if(idling)
            {
                switch(lastIdleState)
                {
                case 0:
                    state = 1;
                    break;
                case 1:
                    state = 0;
                    break;
                }

                object.setTextureRect(animationIdleL[state]);
                lastIdleState = state;
            }
            else if(!idling)
            {
                switch(lastWalkingState)
                {
                case 0:
                    state = 1;
                    break;
                case 1:
                    state = 2;
                    break;
                case 2:
                    state = 3;
                    break;
                case 3:
                    state = 0;
                    break;
                }

                object.setTextureRect(animationWalkingL[state]);
                lastWalkingState = state;
            }
        }

        if(idling)
            for(int i = 0; i < headCount; i++)
                headObjects[i].setTexture(&headTextureActiveIdle);

        clock.restart();
    }
}

void Player::drawPlayer(sf::RenderWindow &window)
{
    window.draw(object);

    for(int i = 0; i < headCount; i++)
    {
        window.draw(headObjects[i]);
    }
}

void Player::initilize()
{
    //for right movement
    animationWalking[0] = sf::IntRect(128, 0, 64, 64);
    animationWalking[1] = sf::IntRect(196, 0, 64, 64);
    animationWalking[2] = sf::IntRect(0, 64, 64, 64);
    animationWalking[3] = sf::IntRect(64, 64, 64, 64);

    animationIdle[0] = sf::IntRect(0, 0, 64, 64);
    animationIdle[1] = sf::IntRect(64, 0, 64, 64);

    animationFalling = sf::IntRect(196, 64, 64, 64);
    animationJumping = sf::IntRect(128, 64, 64, 64);

    //for left movement
    animationWalkingL[0] = sf::IntRect(64, 0, 64, 64);
    animationWalkingL[1] = sf::IntRect(0, 0, 64, 64);
    animationWalkingL[2] = sf::IntRect(196, 64, 64, 64);
    animationWalkingL[3] = sf::IntRect(128, 64, 64, 64);

    animationIdleL[0] = sf::IntRect(128, 0, 64, 64);
    animationIdleL[1] = sf::IntRect(196, 0, 64, 64);

    animationFallingL = sf::IntRect(0, 64, 64, 64);
    animationJumpingL = sf::IntRect(64, 64, 64, 64);

    headTextureActiveIdle.loadFromFile("data/textures/totemHead_openIdle.png");
    headTextureActiveLeft.loadFromFile("data/textures/totemHead_openLeft.png");
    headTextureActiveRight.loadFromFile("data/textures/totemHead_openRight.png");

    headTextureClosed.loadFromFile("data/textures/totemHead_closed.png");

    for(int i = 0; i < 3; i++)
    {
        headObjects[i].setTexture(&headTextureActiveIdle);
    }



}

    //direction, 0 for left, 1 = jump, 2 = right, 3 = down
void Player::movePlayer()
{
    object.move(playerVelocity.x,playerVelocity.y);

    return;
}

void Player::setPlatformBB(sf::Sprite obj, int i)
{
    platformBB[i] = obj.getGlobalBounds();
}


float Player::getX()
{
    return object.getPosition().x;
}

float Player::getY()
{
    return object.getPosition().y;
}

bool Player::collide(sf::FloatRect otherObject)
{
    sf::FloatRect BB = object.getGlobalBounds();

    if(BB.intersects(otherObject))
        return true;
    else return false;
}





