#ifndef MAP_H
#define MAP_H

#include "eye.cpp"

class Map
{
public:
    Map(int lev);
    ~Map();

    void drawBG(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window, Player &player);

    bool update(Player &player);
    sf::FloatRect getBB(int bbToGet);

    void setPlatformPositions();

    sf::Sprite getSprite(int i);

    int platformsToDraw;
    bool headCollected;
    bool exitLocked;

    void loadLevelCoordinates();

    sf::FloatRect getHeadPosition();

private:
    sf::Texture platformBgTextures[20];
    sf::Texture platformTextures[20];
    sf::Texture platformFgTextures[20];
    sf::Texture mapBackgroundTexture;

    sf::Sprite platformBgSprites[50];
    sf::Sprite platformSprites[50];
    sf::Sprite platformFgSprites[50];
    sf::Sprite mapBackgroundSprite;

    sf::FloatRect platformBB[20];

    int cellPlatformAmount[4];

    sf::Vector2f mapOrigin;

    sf::Vector2i levelCoordinates[50];

    sf::Texture collectableHeadTexture;
    sf::Sprite collectableHeadSprite;

    sf::FloatRect collectableHeadBB;

    Eye eye[4];

    sf::Texture exitDoorClosed;
    sf::Texture exitDoorOpen;
    sf::Sprite exitDoor;
    sf::FloatRect exitDoorBB;

    sf::View viewONE, viewTWO, viewTHREE, viewFOUR;

    int level;


};

#endif //MAP_H
