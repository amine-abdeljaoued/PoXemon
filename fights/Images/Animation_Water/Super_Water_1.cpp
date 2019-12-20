#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <string>


void main(int argc, char** argv[]) {

	sf::RenderWindow window(sf::VideoMode(1400, 700), "My window");

	sf::Texture super_rock_1;
	super_rock_1.loadFromFile("Rock_Super_1.png");
	sf::Texture super_rock_2;
	super_rock_2.loadFromFile("Rock_Super2_1.png");
	sf::Texture super_rock_3;
	super_rock_3.loadFromFile("Rock_Super3_1.png");

	sf::Texture BackgroundTexture;
	BackgroundTexture.loadFromFile("grassbg.png");
	sf::Sprite background(BackgroundTexture);
	background.setScale(1400/background.getLocalBounds().width, 700/background.getLocalBounds().height);
	

	////////////////////////////

	sf::Sprite Super_Rock_1a(super_rock_1);
	sf::Sprite Super_Rock_2a(super_rock_2);
	sf::Sprite Super_Rock_3a(super_rock_3);

	sf::Sprite Super_Rock_1b(super_rock_1);
	sf::Sprite Super_Rock_1c(super_rock_1);
	sf::Sprite Super_Rock_1d(super_rock_1);
	sf::Sprite Super_Rock_1e(super_rock_1);
	sf::Sprite Super_Rock_1f(super_rock_1);

	/////////////////////////

	Super_Rock_1a.setScale(sf::Vector2f(2.f, 2.f));
	Super_Rock_2a.setScale(sf::Vector2f(2.f, 2.f));
	Super_Rock_3a.setScale(sf::Vector2f(4.f, 4.f));
	
	Super_Rock_1b.setScale(sf::Vector2f(2.f, 2.f));
	Super_Rock_1c.setScale(sf::Vector2f(2.f, 2.f));
	Super_Rock_1d.setScale(sf::Vector2f(2.f, 2.f));
	Super_Rock_1e.setScale(sf::Vector2f(2.f, 2.f));
	Super_Rock_1f.setScale(sf::Vector2f(2.f, 2.f));

	////////////////////////

	Super_Rock_1a.setOrigin(-60.f, -400.f);
	Super_Rock_1b.setOrigin(-160.f, -400.f);
	Super_Rock_1c.setOrigin(-260.f, -400.f);
	Super_Rock_1d.setOrigin(-360.f, -400.f);
	Super_Rock_1e.setOrigin(-460.f, -400.f);
	Super_Rock_1f.setOrigin(-560.f, -400.f);
	
	
	////////////////////////////

	sf::Vector2f increment(0.f, 0.1);
	
	sf::Vector2f incrementa_temp(0.f, 5);
	sf::Vector2f incrementb_temp(0.f, 5);
	sf::Vector2f incrementc_temp(0.f, 5);
	sf::Vector2f incrementd_temp(0.f, 5);
	sf::Vector2f incremente_temp(0.f, 5);
	sf::Vector2f incrementf_temp(0.f, 5);

	//////////////////

	double multa = 0.993;
	double multb = 0.993;
	double multc = 0.993;
	double multd = 0.993;
	double multe = 0.993;
	double multf = 0.993;

	

	bool firsta = true;
	bool firstb = true;
	bool firstc = true;
	bool firstd = true;
	bool firste = true;
	bool firstf = true;

	///////////////////////////////

	sf::Texture super_water_1;
	super_water_1.loadFromFile("super_water_1.png");

	sf::Sprite Super_Water_1a(super_water_1);
	sf::Sprite Super_Water_1b(super_water_1);
	sf::Sprite Super_Water_1c(super_water_1);

	Super_Water_1a.setScale(sf::Vector2f(2.f, 2.f));
	Super_Water_1b.setScale(sf::Vector2f(2.f, 2.f));
	Super_Water_1c.setScale(sf::Vector2f(2.f, 2.f));

	Super_Water_1a.setOrigin(1350.f, -200.f);
	Super_Water_1b.setOrigin(550.f, -250.f);
	Super_Water_1c.setOrigin(800.f, -150.f);

	sf::Vector2f incrementa(7.f, 0.f);
	sf::Vector2f incrementb(5.f, 0.f);
	sf::Vector2f incrementc(4.f, 0.f);

	sf::Vector2f end(1400.f, 0.f);
	int counter = 0;

	///////////////////////////////////

	bool attack_water = false;
	bool attack_earth = false;

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					attack_earth = true;
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					attack_water = true;
				}
			}
		}

		if (attack_water) {
			if (Super_Water_1a.getPosition().x + incrementa.x > 4000) {
				Super_Water_1a.setPosition(650.f, -150.f);
				counter = counter + 1;
				if (counter == 4) { attack_water = false; }
			}
			else { Super_Water_1a.setPosition(Super_Water_1a.getPosition() + incrementa); }

			if (Super_Water_1b.getPosition().x + incrementb.x > 3400) {
				Super_Water_1b.setPosition(5000.f, -80.f);
				if (counter < 3) { Super_Water_1b.setPosition(550.f, -150.f); }
			}
			else { Super_Water_1b.setPosition(Super_Water_1b.getPosition() + incrementb); }

			if (Super_Water_1c.getPosition().x + incrementc.x > 3400) {
				Super_Water_1c.setPosition(6000.f, -50.f);
				if (counter < 3) { Super_Water_1c.setPosition(600.f, -50.f); }
			}
			else { Super_Water_1c.setPosition(Super_Water_1c.getPosition() + incrementc); }
		}

		if (attack_earth) {
			
			if (firsta && Super_Rock_1a.getPosition().y < -550) {
				Super_Rock_1a = Super_Rock_2a;
				Super_Rock_1a.setPosition(130.f, 200.f);
				firsta = false;
				
			}
			if (not firsta) {
				if (Super_Rock_1a.getPosition().y < 100){
				Super_Rock_1a = Super_Rock_3a;
				Super_Rock_1a.setPosition(130.f, 100.f);
				incrementa_temp = -increment;
				multa = 1.01;
				}

				if (firstb && Super_Rock_1b.getPosition().y < -550) {
					Super_Rock_1b = Super_Rock_2a;
					Super_Rock_1b.setPosition(320.f, 200.f);
					firstb = false;

				}
				if (not firstb) {
					if (Super_Rock_1b.getPosition().y < 100) {
						Super_Rock_1b = Super_Rock_3a;
						Super_Rock_1b.setPosition(320.f, 100.f);
						incrementb_temp = -increment;
						multb = 1.01;
					}
					if (firstc && Super_Rock_1c.getPosition().y < -550) {
						Super_Rock_1c = Super_Rock_2a;
						Super_Rock_1c.setPosition(510.f, 200.f);
						firstc = false;

					}
					if (not firstc) {
						if (Super_Rock_1c.getPosition().y < 100) {
							Super_Rock_1c = Super_Rock_3a;
							Super_Rock_1c.setPosition(510, 100.f);
							incrementc_temp = -increment;
							multc = 1.01;
						}
						if (firstd && Super_Rock_1d.getPosition().y < -550) {
							Super_Rock_1d = Super_Rock_2a;
							Super_Rock_1d.setPosition(730.f, 200.f);
							firstd = false;

						}
						if (not firstd) {
							if (Super_Rock_1d.getPosition().y < 100) {
								Super_Rock_1d = Super_Rock_3a;
								Super_Rock_1d.setPosition(730, 100.f);
								incrementd_temp = -increment;
								multd = 1.01;
							}

							if (firste && Super_Rock_1e.getPosition().y < -550) {
								Super_Rock_1e = Super_Rock_2a;
								Super_Rock_1e.setPosition(930.f, 200.f);
								firste = false;

							}
							if (not firste) {
								if (Super_Rock_1e.getPosition().y < 100) {
									Super_Rock_1e = Super_Rock_3a;
									Super_Rock_1e.setPosition(930, 100.f);
									incremente_temp = -increment;
									multe = 1.01;
								}

								if (firstf && Super_Rock_1f.getPosition().y < -550) {
									Super_Rock_1f = Super_Rock_2a;
									Super_Rock_1f.setPosition(1100.f, 200.f);
									firstf = false;

								}
								if (not firstf) {
									if (Super_Rock_1f.getPosition().y < 100) {
										Super_Rock_1f = Super_Rock_3a;
										Super_Rock_1f.setPosition(1100, 100.f);
										incrementf_temp = -increment;
										multf = 1.01;
									}
									if (Super_Rock_1f.getPosition().y > 900) {
										
										attack_earth = false;
									}
								}

							}
						}
					}

				}
				
			}


			Super_Rock_1a.setPosition(Super_Rock_1a.getPosition() - incrementa_temp);
			incrementa_temp.y = incrementa_temp.y * multa;
			
		}
			

		window.clear(sf::Color(0, 0, 0, 255));
		window.draw(background);


		if (attack_earth) {
			sf::RectangleShape overlay;
			overlay.setPosition(sf::Vector2f(0, 0));
			overlay.setSize(sf::Vector2f(1400, 700));
			overlay.setFillColor(sf::Color(50, 50, 15, 128));
			window.draw(overlay);
			window.draw(Super_Rock_1a);
			if (not firsta) {
				Super_Rock_1b.setPosition(Super_Rock_1b.getPosition() - incrementb_temp);
				incrementb_temp.y = incrementb_temp.y * multb;
				window.draw(Super_Rock_1b);
			}
			if (not firstb) {
				Super_Rock_1c.setPosition(Super_Rock_1c.getPosition() - incrementc_temp);
				incrementc_temp.y = incrementc_temp.y * multc;
				window.draw(Super_Rock_1c);
			}
			if (not firstc) {
				Super_Rock_1d.setPosition(Super_Rock_1d.getPosition() - incrementd_temp);
				incrementd_temp.y = incrementd_temp.y * multd;
				window.draw(Super_Rock_1d);
			}
			if (not firstd) {
				Super_Rock_1e.setPosition(Super_Rock_1e.getPosition() - incremente_temp);
				incremente_temp.y = incremente_temp.y * multe;
				window.draw(Super_Rock_1e);
			}
			if (not firste) {
				Super_Rock_1f.setPosition(Super_Rock_1f.getPosition() - incrementf_temp);
				incrementf_temp.y = incrementf_temp.y * multf;
				window.draw(Super_Rock_1f);

			}
		}
		
		if (attack_water) {
			sf::RectangleShape overlay;
			overlay.setPosition(sf::Vector2f(0, 0));
			overlay.setSize(sf::Vector2f(1400, 700));
			overlay.setFillColor(sf::Color(40, 90, 90, 128));
			window.draw(overlay);
			window.draw(Super_Water_1a);
			window.draw(Super_Water_1b);
			window.draw(Super_Water_1c);
		}



		window.display();


	}
}
