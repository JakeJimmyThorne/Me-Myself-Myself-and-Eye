#include <SFML/Graphics.hpp>
#include <iostream>

#include "math.h"

void saveOptions(sf::Text options[4]);
void bigEyeUpdate(sf::Vector2f newPos, sf::Vector2f &currPos);

bool mainmenu(sf::RenderWindow &window, sf::View &view)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Event event;

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

	sf::SoundBuffer menuSoundBuffer[2];
	sf::Sound menuSounds[2];

	sf::Music menuMusic;

	menuSoundBuffer[0].loadFromFile("");
	menuSoundBuffer[1].loadFromFile("");
	menuMusic.openFromFile("data/sound/intro.ogg");

	for(int i = 0; i < 2; i++)
    {
        menuSounds[i].setBuffer(menuSoundBuffer[i]);
        menuSounds[i].setVolume(1);
    }

    menuMusic.setLoop(true);
    //menuMusic.setVolume(1);

	const int OPTIONS = 4;

    sf::Texture playTexture;
    playTexture.loadFromFile("data/textures/titlePlay.png");
    sf::Sprite playSprite;
	sf::FloatRect playTextBB;

	sf::Texture titleTexture;
    titleTexture.loadFromFile("data/textures/titleName.png");
    sf::Sprite titleSprite;
	sf::FloatRect titleTextBB;

	sf::Texture exitTexture;
	exitTexture.loadFromFile("data/textures/titleExit.png");
	sf::Sprite exitSprite;
	sf::FloatRect exitTextBB;

	sf::Font font;
    if(!font.loadFromFile("visitor.ttf"))
        return 0;

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("data/textures/menuBackground.png");

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

	playSprite.setTexture(playTexture);
	playSprite.setPosition(600,850);

	titleSprite.setTexture(titleTexture);
	titleSprite.setPosition(1350,85);

	exitSprite.setTexture(exitTexture);
	exitSprite.setPosition(1000,900);

	sf::Text optionsText[OPTIONS];
	sf::Text optionsToggle[OPTIONS];
	sf::FloatRect optionsBB[OPTIONS];

    optionsText[0].setString("Colour blind mode");
    optionsText[1].setString("Fullscreen");
    optionsText[2].setString("Master volume");
    optionsText[3].setString("Hardmode");

	for(int i = 0; i < OPTIONS; i++)
    {
        optionsText[i].setFont(font);
        optionsText[i].setColor(sf::Color::White);
        optionsText[i].setCharacterSize(32);
        optionsText[i].setPosition(20,20 + i * 32);

        if(txt[i] == "0" && i != 2)
            optionsToggle[i].setString("N");
        else if(txt[i] == "1" && i != 2)
            optionsToggle[i].setString("Y");

        optionsToggle[i].setFont(font);
        optionsToggle[i].setColor(sf::Color::White);
        optionsToggle[i].setCharacterSize(32);
        optionsToggle[i].setPosition(300,20 + i * 32);

        optionsBB[i] = optionsToggle[i].getGlobalBounds();
    }

	bool inMenu = true;
	bool lastClick = false;
	bool lastClick2 = false;

	menuMusic.play();

	sf::Texture bigEyeTexture;
	bigEyeTexture.loadFromFile("data/textures/bigEye.png");
	bigEyeTexture.setSmooth(true);

	sf::Sprite bigEyeSprite;
	bigEyeSprite.setTexture(bigEyeTexture);
	bigEyeSprite.setOrigin(166/2,162/2);
	bigEyeSprite.setPosition(1077,341);

	sf::Vector2f twoPos[2];
	bool eyeSwitch = false;
	twoPos[0] = sf::Vector2f(1027,331);
	twoPos[1] = sf::Vector2f(1101,351);

	while(window.isOpen())
	{
	    window.setView(view);

		mousePosition = sf::Mouse::getPosition(window);
		playTextBB = playSprite.getGlobalBounds();
		titleTextBB = titleSprite.getGlobalBounds();
		exitTextBB = exitSprite.getGlobalBounds();

		for(int i = 0; i < OPTIONS; i++)
        {
            optionsBB[i] = optionsToggle[i].getGlobalBounds();
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            return true;
        }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !lastClick)
        {
			lastClick = true;

			if(playTextBB.contains(mousePosition.x, mousePosition.y))
            {
                saveOptions(optionsToggle);
                return true;
            }

			if(exitTextBB.contains(mousePosition.x, mousePosition.y))
            {
                return false;
            }
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            lastClick = false;

        if(playTextBB.contains(mousePosition.x, mousePosition.y))
        {
            playSprite.setColor(sf::Color::Yellow);
            eyeSwitch = false;
            bigEyeSprite.setRotation(0);
        }

        else
            playSprite.setColor(sf::Color::White);

        if(exitTextBB.contains(mousePosition.x, mousePosition.y))
        {
            exitSprite.setColor(sf::Color::Yellow);
            eyeSwitch = true;
            if(bigEyeSprite.getRotation() < 10)
                bigEyeSprite.rotate(2);
        }

        else
            exitSprite.setColor(sf::Color::White);

        for(int i = 0; i < OPTIONS; i++)
        {
            if(optionsBB[i].contains(mousePosition.x, mousePosition.y))
            {
                optionsToggle[i].setColor(sf::Color::Red);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !lastClick2)
                {
                    if(optionsToggle[i].getString() == "N")
                        optionsToggle[i].setString("Y");
                    else
                        optionsToggle[i].setString("N");

                    lastClick2 = true;
                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    lastClick2 = false;
            }
            else
                optionsToggle[i].setColor(sf::Color::White);
        }



		window.clear();
		window.draw(backgroundSprite);
		window.draw(playSprite);
		window.draw(titleSprite);
		window.draw(exitSprite);

		window.draw(bigEyeSprite);

        if(!eyeSwitch)
        {
            sf::Vector2f temp = bigEyeSprite.getPosition();
            bigEyeUpdate(twoPos[0],temp);
            bigEyeSprite.setPosition(temp);
        }
        else
        {
            sf::Vector2f temp = bigEyeSprite.getPosition();
            bigEyeUpdate(twoPos[1],temp);
            bigEyeSprite.setPosition(temp);
        }

		for(int i = 0; i < OPTIONS; i++)
        {
            window.draw(optionsToggle[i]);
            window.draw(optionsText[i]);
        }

		window.display();
	}


    return true;
}

void bigEyeUpdate(sf::Vector2f newPos, sf::Vector2f &currPos)
{
    float angleOfAttack = atan2((newPos.y - currPos.y),
                                newPos.x - currPos.x);

    sf::Vector2f velocity = sf::Vector2f(cos(angleOfAttack) * 0.1,
                                sin(angleOfAttack) * 0.1);

    currPos += velocity;
}

void saveOptions(sf::Text options[4])
{
    std::ofstream myfile ("options.txt");

    int newOptions[4];

    for(int i = 0; i < 4; i++)
    {
        if(i != 2)
            newOptions[i] = options[i].getString() == "Y" ? 1 : 0;
    }

    myfile << newOptions[0] << "\n";
    myfile << newOptions[1] << "\n";
    myfile << newOptions[2] << "\n";
    myfile << newOptions[3] << "\n";

    myfile.close();
}
