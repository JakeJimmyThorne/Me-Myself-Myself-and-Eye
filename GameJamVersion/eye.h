#ifndef EYE_H
#define EYE_H

class Eye
{
public:
    Eye();
    ~Eye();

    void update(sf::Vector2f playerPos);
    void draw(sf::RenderWindow &window);

    void initilize(sf::Vector2f newPos);

private:
    sf::Texture eyeBall;
    sf::Texture eyeOutline;

    sf::FloatRect eyeBB;
    sf::FloatRect eyeOutlineBB;

    sf::Sprite eyeBallSprite;
    sf::Sprite eyeOutlineSprite;

    sf::Vector2f currPos;

    float angleOfAttack;
    sf::Vector2f velocity;
};

#endif // EYE_H
