#include "story.h"

Story::Story(int storyPiece)
{
    switch(storyPiece)
    {
    case 1:
        storyTexture.loadFromFile("data/story/comic_page1_clean.png");
        xSpeed = 0;
        ySpeed = 0;
        break;
    case 2:
        storyTexture.loadFromFile("data/story/comic_page2a_clean.png");
        storyTextureMisc.loadFromFile("data/story/comic_page2b_clean.png");
        xSpeed = 0;
        ySpeed = 0;
        break;
    case 3:
        storyTexture.loadFromFile("data/story/comic_page3_clean.png");
        xSpeed = 0;
        ySpeed = 0;
        break;
    case 4:
        storyTexture.loadFromFile("data/story/comic_page4_clean.png");
        xSpeed = 0;
        ySpeed = 0;
        break;
    case 5:
        storyTexture.loadFromFile("data/story/comic_page5_clean.png");
        xSpeed = 0;
        ySpeed = 0;
        break;
    case 6:
        storyTexture.loadFromFile("data/story/comic_page6_clean.png");
        xSpeed = 0;
        ySpeed = 0;
        break;
    }

    panelNumber = storyPiece;

    storyPanel.setTexture(storyTexture);
    screenTime = scrollingClock.getElapsedTime();
    screenTimeF = 5;


}

Story::~Story()
{

}


void Story::update(sf::RenderWindow &window)
{
    screenTime = scrollingClock.restart();
    while(screenTime.asSeconds() < screenTimeF)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return;//window.close();

            if(event.key.code == sf::Keyboard::Escape)
                return;//window.close();
        }

        scrollingTime = scrollingClock.restart();
        screenTime = scrollingClock.getElapsedTime();

        if(panelNumber == 2)
        {
            if(screenTime.asSeconds() > 2.5)
                storyPanel.setTexture(storyTextureMisc);
        }

        storyPanel.move(xSpeed*scrollingTime.asSeconds(),ySpeed*scrollingTime.asSeconds());
        window.draw(storyPanel);

    }

    return;
}
