#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "mainmenu.cpp"
#include "player.cpp"
#include "map.cpp"
#include "story.cpp"


#include <time.h>

int main()
{
    srand(time(NULL));

    bool storyPane = false;
    std::string txt[200];
    std::string line;

    int incre=0;
    std::ifstream file;

    file.open("options.txt");

    if (file.is_open())
    {
        while (!file.eof())
        {
            std::getline(file,line);
            txt[incre]=line;
            incre++;
        }
    }

    file.close();

    sf::RenderWindow window(sf::VideoMode(1024,600), "GameJam", sf::Style::Close);

    std::string tempTxt = txt[1];

    if(txt[1] == "1")
        window.create(sf::VideoMode(1024,600), "GameJam", sf::Style::Fullscreen);

    sf::View view;

    view.reset(sf::FloatRect(0, 0, 1920, 1080));

    if(!mainmenu(window,view))
		return 0;

    incre=0;

    file.open("options.txt");

    if (file.is_open())
    {
        while (!file.eof())
        {
            std::getline(file,line);
            txt[incre]=line;
            incre++;
        }
    }

    file.close();

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    if(txt[1] == "1" && tempTxt == "0")
        window.create(sf::VideoMode(1024, 600), "GameJam", sf::Style::Fullscreen);
    else if(txt[1] == "0" && tempTxt == "1")
        window.create(sf::VideoMode(1024, 600), "GameJam", sf::Style::Close);

    int level = 1;
    int storySection = 1;

    //Story story(1);
    //story.update(window);
    sf::Texture storyPanelTexture[7];
    storyPanelTexture[0].loadFromFile("data/story/comic_page1_clean.png");
    storyPanelTexture[1].loadFromFile("data/story/comic_page2a_clean.png");
    storyPanelTexture[2].loadFromFile("data/story/comic_page2b_clean.png");
    storyPanelTexture[3].loadFromFile("data/story/comic_page3_clean.png");
    storyPanelTexture[4].loadFromFile("data/story/comic_page4_clean.png");
    storyPanelTexture[5].loadFromFile("data/story/comic_page5_clean.png");
    storyPanelTexture[6].loadFromFile("data/story/comic_page6_clean.png");

    sf::Sprite storyPanelSprite;
    sf::Clock scrollingClock;
    sf::Time scrollingTime;

    sf::Vector2f velocity;

    if(storySection == 1)
    {
        storyPanelSprite.setTexture(storyPanelTexture[0]);
        storyPanelSprite.setPosition(0,0);
        velocity = sf::Vector2f(-2.25,-0.03);
    }
    else if(storySection == 2)
    {
        storyPanelSprite.setTexture(storyPanelTexture[1]);
        storyPanelSprite.setOrigin(sf::Vector2f(975,540));
        storyPanelSprite.setPosition(960,540);

        velocity = sf::Vector2f(0,0);
    }
    else if(storySection == 3)
        storyPanelSprite.setTexture(storyPanelTexture[3]);
    else if(storySection == 4)
        storyPanelSprite.setTexture(storyPanelTexture[4]);
    else if(storySection == 5)
        storyPanelSprite.setTexture(storyPanelTexture[5]);
    else if(storySection == 6)
        storyPanelSprite.setTexture(storyPanelTexture[6]);

    int nextStory = 1;

    sf::Texture endingPanelTexture[4];
    sf::Sprite endingPanelSprite[4];

    sf::Music introMusic;
    introMusic.openFromFile("data/sound/comic.ogg");
    introMusic.setPlayingOffset(sf::Time(sf::seconds(7)));

    endingPanelTexture[0].loadFromFile("data/story/finalBoss_BG_idle.png");
    endingPanelTexture[1].loadFromFile("data/story/finalBoss_BG_blink.png");
    endingPanelTexture[2].loadFromFile("data/story/finalBoss_BG_roar.png");
    endingPanelTexture[3].loadFromFile("data/story/credit_screen.png");

    if(level == 1)
    {
        storyPane = true;

    }

    introMusic.play();
    if(window.isOpen())
    {
        //Map map(level);
        Map* map;
        map = new Map(level);

        //Player player(level);
        Player* player;
        player = new Player(level);
        player->initilize();
        player->platformAmoumt = map->platformsToDraw;

        sf::Clock clock;
        sf::Time dt;

        bool currentLevel = true;

        for(int i = 0; i < map->platformsToDraw; i++)
        {
            player->setPlatformBB(map->getSprite(i),i);
        }

        scrollingClock.restart();

        while (currentLevel)
        {
            window.setView(view);
            dt = clock.getElapsedTime();
            scrollingTime = scrollingClock.getElapsedTime();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    return 0;//window.close();

                if(event.key.code == sf::Keyboard::Escape)
                {
                    return 0;
                }
                if(event.key.code == sf::Keyboard::S)
                {
                    if(storyPane)
                        storyPane = false;

                    introMusic.stop();
                }

            }

            if(!storyPane)
            {
                for(int i = 0; i < map->platformsToDraw; i++)
                {
                    player->setPlatformBB(map->getSprite(i),i);
                }

                player->update();
                player->updateAnimation(dt,clock);

                if(!map->headCollected && player->collide(map->getHeadPosition()))
                {
                    map->headCollected = true;
                    map->exitLocked = false;
                    player->headCount++;
                }

                if(map->update(*player))
                {
                    if(level == 1)
                    {
                        level++;
                        map = new Map(level);
                        player = new Player(level);

                        player->initilize();
                        player->platformAmoumt = map->platformsToDraw;
                    }
                    else return 0;

                    //currentLevel = false;
                }
            }

            window.clear();

            if(!storyPane)
            {
                map->drawBG(window);
                map->draw(window,*player);
            }

            if(player->getY() > 2090)
            {
                std::cout << "you fell off the screen :'(";
                currentLevel = false;
                window.close(); //doesn't close the program
            }

            window.setView(view);

            if(storyPane)
            {
                window.clear();
                window.draw(storyPanelSprite);
                //storyPanelSprite.move(velocity);

                scrollingTime = scrollingClock.getElapsedTime();

                if(storySection == 1)
                {
                    //storyPanelSprite.setScale(1 + scrollingTime.asSeconds() * .05,
                      //                        1 + scrollingTime.asSeconds() * .05);

                    if(scrollingTime.asSeconds() > 7)
                    {
                        scrollingClock.restart();
                        scrollingTime = scrollingClock.getElapsedTime();
                        storyPanelSprite.setTexture(storyPanelTexture[1]);
                        storySection = 2;
                    }

                }

                else if(storySection == 2)
                {

                    if(scrollingTime.asSeconds() < 3)
                        //storyPanelSprite.setScale(1 + scrollingTime.asSeconds() * .05,
                          //                        1 + scrollingTime.asSeconds() * .05);

                    if(scrollingTime.asSeconds() > 4)
                        storyPanelSprite.setTexture(storyPanelTexture[2]);

                    if(scrollingTime.asSeconds() > 5)
                    {
                        scrollingClock.restart();
                        scrollingTime = scrollingClock.getElapsedTime();
                        storyPanelSprite.setTexture(storyPanelTexture[3]);
                        storySection = 3;
                    }
                }

                else if(storySection == 3)
                {
                    if(scrollingTime.asSeconds() > 4)
                    {
                        scrollingClock.restart();
                        scrollingTime = scrollingClock.getElapsedTime();
                        storyPanelSprite.setTexture(storyPanelTexture[4]);
                        storySection = 4;
                    }
                }

                else if(storySection == 4)
                {
                    if(scrollingTime.asSeconds() > 3)
                    {
                        scrollingClock.restart();
                        scrollingTime = scrollingClock.getElapsedTime();
                        storyPanelSprite.setTexture(storyPanelTexture[5]);
                        storySection = 5;
                    }
                }

                else if(storySection == 5)
                {
                    if(scrollingTime.asSeconds() > 3)
                    {
                        scrollingClock.restart();
                        scrollingTime = scrollingClock.getElapsedTime();
                        storyPanelSprite.setTexture(storyPanelTexture[6]);
                        storySection = 6;
                    }
                }

                else if(storySection == 6)
                {
                    if(scrollingTime.asSeconds() > 6)
                    {
                        scrollingClock.restart();
                        scrollingTime = scrollingClock.getElapsedTime();
                        storyPanelSprite.setTexture(storyPanelTexture[7]);
                        storyPane = false;
                    }
                }

            }


            window.display();
        }
    }

    return 0;
}
