#include "map.h"

Map::Map(int lev)
{
    level = lev;

    exitDoorClosed.loadFromFile("data/textures/exitDoor_closed.png");
    exitDoorOpen.loadFromFile("data/textures/exitDoor_open.png");

    exitDoor.setTexture(exitDoorClosed);

    if(level == 1)
    {
        mapBackgroundTexture.loadFromFile("data/textures/background.png");
        mapBackgroundSprite.setTexture(mapBackgroundTexture);

        collectableHeadTexture.loadFromFile("data/textures/totemHead_closed.png");

        platformTextures[0].loadFromFile("data/textures/platformLarge.png");
        platformTextures[0].setRepeated(true);
        platformTextures[0].setSmooth(true);

        platformsToDraw = 27;

        for(int i = 0; i < platformsToDraw; i++)
        {
            platformSprites[i].setTexture(platformTextures[0]);
        }

        collectableHeadSprite.setTexture(collectableHeadTexture);
        collectableHeadSprite.setPosition(1237,412);

        collectableHeadBB = collectableHeadSprite.getGlobalBounds();
        headCollected = false;

        viewONE.setSize(960,540);
        viewONE.setCenter(475,800);
        cellPlatformAmount[0] = 7;

        viewTWO.setSize(960,540);
        viewTWO.rotate(180);
        viewTWO.setCenter(1435,260);
        cellPlatformAmount[2] = 5;


        viewTHREE.setSize(960,540);
        viewTHREE.setCenter(475,260);
        cellPlatformAmount[3] = 6;

        viewFOUR.setSize(960,540);
        viewFOUR.setCenter(1435,800);
        cellPlatformAmount[1] = 10;

        viewONE.setViewport(sf::FloatRect(0, 0, 0.5, 0.5));
        viewTWO.setViewport(sf::FloatRect(0.5, 0, 0.5, 0.5));
        viewTHREE.setViewport(sf::FloatRect(0, 0.5, 0.5, 0.5));
        viewFOUR.setViewport(sf::FloatRect(0.5, 0.5, 0.5, 0.5));

        exitDoor.setPosition(237,152);
    }

    if(level == 2)
    {
        mapBackgroundTexture.loadFromFile("data/textures/background.png");
        mapBackgroundSprite.setTexture(mapBackgroundTexture);

        collectableHeadTexture.loadFromFile("data/textures/totemHead_closed.png");

        platformTextures[0].loadFromFile("data/textures/platformLarge.png");
        platformTextures[1].loadFromFile("data/textures/platformSmall.png");
        platformTextures[0].setSmooth(true);
        platformTextures[1].setSmooth(true);

        platformsToDraw = 19;

        for(int i = 0; i < platformsToDraw; i++)
        {
            platformSprites[i].setTexture(platformTextures[0]);
        }

        collectableHeadSprite.setTexture(collectableHeadTexture);
        collectableHeadSprite.setPosition(600,450);

        collectableHeadBB = collectableHeadSprite.getGlobalBounds();
        headCollected = false;

        viewONE.setSize(960,540);
        viewONE.setCenter(1435,800);
        cellPlatformAmount[0] = 9;

        viewTWO.setSize(960,540);
        viewTWO.setCenter(475,800);
        cellPlatformAmount[2] = 8;


        viewTHREE.setSize(960,540);
        viewTHREE.setCenter(1435,260);
        cellPlatformAmount[3] = 1;


        viewFOUR.setSize(960,540);
        viewFOUR.setCenter(475,260);
        cellPlatformAmount[1] = 0;


        // 4  3
        // 2  1

        viewONE.setViewport(sf::FloatRect(0, 0, 0.5, 0.5));
        viewTWO.setViewport(sf::FloatRect(0.5, 0, 0.5, 0.5));
        viewTHREE.setViewport(sf::FloatRect(0, 0.5, 0.5, 0.5));
        viewFOUR.setViewport(sf::FloatRect(0.5, 0.5, 0.5, 0.5));

        exitDoor.setPosition(1150,782);
    }


    for(int i = 0; i < platformsToDraw; i++)
    {
        platformSprites[i].setTexture(platformTextures[0],false);
    }

    eye[0].initilize(sf::Vector2f(rand() % 700 + 100, rand() % 400 + 60));
    eye[1].initilize(sf::Vector2f(rand() % 700 + 1060, rand() % 400 + 60));
    eye[2].initilize(sf::Vector2f(rand() % 700 + 100, rand() %  400 + 600));
    eye[3].initilize(sf::Vector2f(rand() % 700 + 1060, rand() % 400 + 600));


    exitDoorBB = exitDoor.getGlobalBounds();
    exitLocked = true;

    setPlatformPositions();
}

sf::Sprite Map::getSprite(int i)
{
    return platformSprites[i];
}

Map::~Map()
{

}

void Map::drawBG(sf::RenderWindow &window)
{
    window.draw(mapBackgroundSprite);
    return;
}

void Map::draw(sf::RenderWindow &window, Player &player)
{
    if(level == 1)
    {
        window.setView(viewONE);

        eye[2].update(sf::Vector2f(player.getX(),player.getY()));
        eye[2].draw(window);

        window.draw(exitDoor);

        player.drawPlayer(window);

        for(int i = 0; i < cellPlatformAmount[0]; i++)
        {
            //window.draw(platformBgSprites[i]);
            window.draw(platformSprites[i]);
            //window.draw(platformFgSprites[i]);
        }

        window.setView(viewFOUR);

        eye[3].update(sf::Vector2f(player.getX(),player.getY()));
        eye[3].draw(window);

        window.draw(exitDoor);

        player.drawPlayer(window);

        for(int i = 7; i < 7 + cellPlatformAmount[1]; i++)
        {
            //window.draw(platformBgSprites[i]);
            window.draw(platformSprites[i]);
            //window.draw(platformFgSprites[i]);
        }

        window.setView(viewTWO);

        eye[1].update(sf::Vector2f(player.getX(),player.getY()));
        eye[1].draw(window);

        window.draw(exitDoor);

        player.drawPlayer(window);

        if(!headCollected)
        {
            window.draw(collectableHeadSprite);
        }


        for(int i = 16; i < 16 + cellPlatformAmount[2]; i++)
        {
            //window.draw(platformBgSprites[i]);
            window.draw(platformSprites[i]);
            //window.draw(platformFgSprites[i]);
        }

        window.setView(viewTHREE);


        eye[0].update(sf::Vector2f(player.getX(),player.getY()));
        eye[0].draw(window);

        window.draw(exitDoor);

        player.drawPlayer(window);

        for(int i = 21; i < 21 + cellPlatformAmount[3]; i++)
        {
            //window.draw(platformBgSprites[i]);
            window.draw(platformSprites[i]);
            //window.draw(platformFgSprites[i]);
        }
    }

    if(level == 2)
    {

        window.setView(viewONE);

        eye[2].update(sf::Vector2f(player.getX(),player.getY()));
        eye[2].draw(window);

        window.draw(exitDoor);

        player.drawPlayer(window);

        for(int i = 0; i < cellPlatformAmount[0]; i++)
        {
            //window.draw(platformBgSprites[i]);
            window.draw(platformSprites[i]);
            //window.draw(platformFgSprites[i]);
        }

        window.setView(viewTWO);

        eye[1].update(sf::Vector2f(player.getX(),player.getY()));
        eye[1].draw(window);

        player.drawPlayer(window);




        for(int i = 9; i < 9 + cellPlatformAmount[2]; i++)
        {
            //window.draw(platformBgSprites[i]);
            window.draw(platformSprites[i]);
            //window.draw(platformFgSprites[i]);
        }

        window.setView(viewFOUR);

        eye[3].update(sf::Vector2f(player.getX(),player.getY()));
        eye[3].draw(window);

        if(!headCollected)
        {
            window.draw(collectableHeadSprite);
        }

        player.drawPlayer(window);

        window.draw(platformSprites[12]);
        window.draw(platformSprites[13]);
        window.draw(platformSprites[14]);

        window.setView(viewTHREE);

        eye[0].update(sf::Vector2f(player.getX(),player.getY()));
        eye[0].draw(window);

        window.draw(exitDoor);

        player.drawPlayer(window);

        for(int i = 17; i < 17 + cellPlatformAmount[3]; i++)
        {
            //window.draw(platformBgSprites[i]);
            window.draw(platformSprites[i]);
            //window.draw(platformFgSprites[i]);
        }
    }

    return;
}

bool Map::update(Player &player)
{
    if(!exitLocked)
        exitDoor.setTexture(exitDoorOpen);

    if(!exitLocked)
        if(player.collide(exitDoorBB))
            return true;

    /*for(int i = 0; i < platformsToDraw; i++)
    {
        platformBB[i] = platformSprites[i].getGlobalBounds();
    }*/
}

sf::FloatRect Map::getBB(int bbToGet)
{
    return platformBB[bbToGet];
}

void Map::setPlatformPositions()
{
    //space them 97 apart
    if(level == 1)
    {
        platformSprites[0].setPosition(126,944); // 1 start
        platformSprites[1].setPosition(223,944);
        platformSprites[2].setPosition(320,944);
        platformSprites[3].setPosition(432,838);
        platformSprites[4].setPosition(587,745);
        platformSprites[5].setPosition(763,677);
        platformSprites[6].setPosition(860,677); // 1 end
        platformSprites[7].setPosition(957,677); // 4 start
        platformSprites[8].setPosition(1054,677);
        platformSprites[9].setPosition(1185,747);
        platformSprites[10].setPosition(1314,822);
        platformSprites[11].setPosition(1427,906);
        platformSprites[12].setPosition(1524,906);
        platformSprites[13].setPosition(1628,816);
        platformSprites[14].setPosition(1466,656);
        platformSprites[15].setPosition(1768,608);
        platformSprites[16].setPosition(1524,480); //4 end 2 start
        platformSprites[17].setPosition(1334,444);
        platformSprites[18].setPosition(1237,444);
        platformSprites[19].setPosition(1140,444);
        platformSprites[20].setPosition(1043,444); // 2 end
        platformSprites[21].setPosition(824,391); //3 start
        platformSprites[22].setPosition(565,331);
        platformSprites[23].setPosition(468,331);
        platformSprites[24].setPosition(431,255);
        platformSprites[25].setPosition(334,255);
        platformSprites[26].setPosition(237,255);//3 end
    }

    if(level == 2)
    {
        platformSprites[0].setPosition(1800,900); // 1 start
        platformSprites[1].setPosition(1703,900);
        platformSprites[2].setPosition(1606,900);
        platformSprites[3].setPosition(1406,800);
        platformSprites[4].setPosition(1206,900);
        platformSprites[5].setPosition(1109,900);
        platformSprites[6].setPosition(960,900);
        platformSprites[7].setPosition(1150,660);
        platformSprites[8].setPosition(1022,900);// 1 end
        platformSprites[9].setPosition(650,1030); //2 start
        platformSprites[10].setPosition(450,900);
        platformSprites[11].setPosition(350,700);
        platformSprites[12].setPosition(590,500);
        platformSprites[13].setPosition(496,500);
        platformSprites[14].setPosition(650,500);
        platformSprites[15].setPosition(300,300);
        platformSprites[16].setPosition(500,120);
        platformSprites[17].setPosition(600,20); //2 end
        platformSprites[18].setPosition(1500,500); //start 3 end
    }
}

sf::FloatRect Map::getHeadPosition()
{
    return collectableHeadBB;
}
