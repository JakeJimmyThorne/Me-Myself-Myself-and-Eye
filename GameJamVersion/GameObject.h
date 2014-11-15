#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void draw(sf::RenderWindow &window);

    void setPosition(sf::Vector2f newPos);
    sf::Vector2f getPosition();

    sf::Texture getTexture();
    void setTexture(sf::Texture &newTexture);

    sf::RectangleShape getObject();

    bool collide(sf::FloatRect otherObject);

    int objectCount();

    void setBoundingBox();
    sf::FloatRect getBoundingBox();


protected:
    sf::Texture texture;
    sf::RectangleShape object;

    sf::Vector2f positionCoords;

    sf::FloatRect boundingBox;

};

#endif // GAMEOBJECT_H
