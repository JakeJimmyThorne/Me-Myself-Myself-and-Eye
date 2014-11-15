#include "eye.h"

#include "math.h"

Eye::Eye()
{

}

Eye::~Eye()
{

}

void Eye::update(sf::Vector2f playerPos)
{

    eyeBB = eyeBallSprite.getGlobalBounds();



    if(eyeOutlineBB.intersects(eyeBB))
    {
        angleOfAttack = atan2((playerPos.y -32 - currPos.y),
                                playerPos.x +32 - currPos.x);

        velocity = sf::Vector2f(cos(angleOfAttack) * 1,
                                sin(angleOfAttack) * 1);
    }
    else
    {
        angleOfAttack = atan2((eyeOutlineSprite.getPosition().y  - currPos.y),
                                eyeOutlineSprite.getPosition().x - currPos.x);

        velocity = sf::Vector2f(cos(angleOfAttack) * 1,
                                sin(angleOfAttack) * 1);
    }


    currPos += velocity;

    eyeBallSprite.setPosition(currPos);
}

void Eye::draw(sf::RenderWindow &window)
{
    window.draw(eyeOutlineSprite);
    window.draw(eyeBallSprite);
}

void Eye::initilize(sf::Vector2f newPos)
{
    eyeBall.loadFromFile("data/textures/wallEye_pupil.png");
    eyeOutline.loadFromFile("data/textures/eyeBlank.png");

    eyeOutlineSprite.setTexture(eyeOutline);
    eyeOutlineSprite.setOrigin(16,16);
    eyeOutlineSprite.setPosition(newPos);

    eyeBallSprite.setTexture(eyeBall);
    eyeBallSprite.setPosition(eyeOutlineSprite.getPosition());
    currPos = newPos;

    eyeOutlineBB = sf::FloatRect(eyeOutlineSprite.getPosition().x + 27,
                                 eyeOutlineSprite.getPosition().y + 27,
                                 0.1,0.1);
}
