#include "libs.hpp"

int mainGame(int startMode)
{
    sf::RenderWindow window(sf::VideoMode(820, 697), "Barriguinha Mole Adventures", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    Map map;

	std::ifstream ifile("savestate.txt");
	if(startMode == 1 && ifile.is_open()){
		map.load(ifile);
	}

    sf::Clock deltaClock;
	while (window.isOpen())
    {
	    sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                std::ofstream ofile("savestate.txt");
                map.save(ofile);
                window.close();
                return 0;
            }

            else if (event.type == sf::Event::KeyReleased
                    && (event.key.code == sf::Keyboard::S
					|| event.key.code == sf::Keyboard::D
					|| event.key.code == sf::Keyboard::C) )
            {
                map.changeCharacterState(event);
            }

            else if (event.type == sf::Event::MouseButtonPressed 
                    && event.mouseButton.button == sf::Mouse::Button::Left
                    && !map.characterIsMoving())
            {
                auto pos = sf::Mouse::getPosition(window);
                if(map.isVertex(pos.x,pos.y))
                {
                    auto destiny = map.getIndex(pos.x, pos.y);
                    if (destiny != map.characterVertex()) {
	                    map.characterWillMove();
	                    map.setPathTo(destiny);
                    }
                }
            }
        }

        map.update(deltaClock.restart().asSeconds());

        window.clear(sf::Color::Black);
        map.draw(window);
        window.display();
    }

    return 0;
}