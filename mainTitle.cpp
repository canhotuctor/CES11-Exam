#include "libs.hpp"

int mainTitle(){
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Barriguinha Mole Adventures", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	// title screen load
	sf::Texture texture;
	if(!texture.loadFromFile("media/titleScreen.png"))
		return 20;

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale((float) window.getSize().x / (float) texture.getSize().x, (float) window.getSize().y / (float) texture.getSize().y);

	// sound stuff being loaded
	// sf::SoundBuffer buffer;
	// if(!buffer.loadFromFile("media/ehIssoMesmo.wav"))
	// 	return 20;

	// sf::Sound sound;
	// sound.setBuffer(buffer);
	// sound.play();

	// buttons and text configuration
	std::array<sf::Rect<unsigned>, 3> buttons;
	auto posInput = std::fstream("config/buttonPositions");
	if(!posInput.is_open())
		return 20;
	for (unsigned i = 0; i < 3; ++i) {
		unsigned x1, y1, x2, y2;
		posInput >> x1 >> y1 >> x2 >> y2;
		buttons[i] = {x1, y1, x2 - x1, y2 - y1};
	}
	sf::Font font;
	if(!font.loadFromFile("media/glitchyFont.ttf"))
		return 20;
	std::array<sf::Text, 3> texts;
	texts[0] = sf::Text("New Game", font, 35);
	texts[0].setFillColor(sf::Color(255,140,0,255));
	texts[0].setPosition(buttons[0].left, buttons[0].top);
	texts[1] = sf::Text("Load Game", font, 35);
	texts[1].setFillColor(sf::Color(255,140,0,255));
	texts[1].setPosition(buttons[1].left, buttons[1].top);
	texts[2] = sf::Text("Quit Game", font, 35);
	texts[2].setFillColor(sf::Color(255,140,0,255));
	texts[2].setPosition(buttons[2].left, buttons[2].top);

	auto savestateText = sf::Text("savestate not found", font, 40);
	savestateText.setFillColor(sf::Color::Red);
	savestateText.setPosition(30, 30);
	bool drawsaveText = false;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}
			// else if (event.type == sf::Event::KeyReleased
			// && event.key.code == sf::Keyboard::T){
			// 	sound.play();
			// }
			else if (event.type == sf::Event::MouseButtonReleased
			&& event.mouseButton.button == sf::Mouse::Button::Left){
				auto pos = sf::Mouse::getPosition(window);
				if(buttons[0].contains(pos.x, pos.y)){
					window.close();
					return 0;
				}
				else if(buttons[1].contains(pos.x,pos.y)){
					std::ifstream ifile("savestate.txt");
					if(ifile.is_open()){
						window.close();
						return 1;
					}
					else
						drawsaveText = true;
				}
				else if(buttons[2].contains(pos.x, pos.y)){
					window.close();
					return 2;
				}
			}
		}

		window.clear();

		window.draw(sprite);

		auto pos = sf::Mouse::getPosition(window);
		for(unsigned i = 0; i < 3; i++) {
			if(buttons[i].contains(pos.x, pos.y)) {
				window.draw(texts[i]);
			}
		}

		if(drawsaveText)
			window.draw(savestateText);

		window.display();
	}

	return 0;
}