#include <SFML/Graphics.hpp>

int main(){
	double windowHeight = 400, windowWidth = 400;
	sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "smth");
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
			}
		}

		window.clear();

		window.display();
	}

	return 0;
}

