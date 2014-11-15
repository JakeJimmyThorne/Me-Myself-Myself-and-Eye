#ifndef STORY_H
#define STORY_H

class Story
{
public:
    Story(int storyPiece);
    ~Story();

    void update(sf::RenderWindow &window);

private:
    int panelNumber;

    sf::Time scrollingTime;
    sf::Clock scrollingClock;

    sf::Time screenTime;
    sf::Clock screenClock;

    float screenTimeF;

    float xSpeed, ySpeed;

    bool rumble;

    sf::Music tileMusic;

    sf::Sprite storyPanel;
    sf::Texture storyTexture;
    sf::Texture storyTextureMisc;

};

#endif
