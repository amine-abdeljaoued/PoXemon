#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Player.h"
#include "Backpack.h"
#include "Opponent.h"

class StateFunctions1 {
public:
	char mode;
    // all
    StateFunctions1();
    void initialise(char& game_mode, Opponent& opponent, Player& player, sf::RenderWindow& window, sf::Font& font);

	//starting state (where we choose outr pokemon)
	sf::Text choose_pokemon;
	sf::Text run_text;
	sf::Sprite run_sprite;
	sf::Text opp_name;
	sf::Text opp_name_shadow;
	sf::Text opp_lvl;
	void initialize_state1(char& game_mode, sf::Sprite& opp_sprite, std::string& opp_n, int& opp_lvl, sf::RenderWindow& window, Pokemon_Button* buttons[], sf::Sprite& running_sprite, sf::Font& ffont);
	void update_state1(sf::RenderWindow& window, sf::Clock& clock, Pokemon_Button* buttons[], int& clicked_button);
	void draw_state1(sf::RenderWindow& window, Pokemon_Button* buttons[]);

    // menu
    sf::RectangleShape start_button;
	sf::RectangleShape info_button;
	sf::Text start_text;
	sf::Text info_text;
	sf::Text intro_text;
    sf::Sprite opp;
	sf::Sprite star;
	sf::Texture star_texture;

    void initialise_background(sf::RenderWindow& window, std::string path, sf::Sprite& background, sf::Texture& texture);
    void initialise_buttons(sf::RenderWindow& window, sf::Font& font);
    void draw1(sf::RenderWindow& window);

    // How to play
    sf::Texture how_texture;
    sf::Texture quit_texture;
    sf::Sprite how_to;
    sf::Sprite quit;

    void initialise_howto(sf::RenderWindow& window);
    /* void howtoplay(sf::RenderWindow& window, float& deltaTime); */
    void draw_how_to(sf::RenderWindow& window);

    // Countdown
    sf::Text text;
    sf::Font font;
    bool draw_count;
    int max_char_size = 150; // how big our fountsize of the countdown is

    void initialise_countdown(sf::RenderTarget& window);
    void draw_blurry_background(sf::RenderWindow& window, sf::Sprite& background, Backpack& bag, Player& player,
            Opponent& opponent, sf::Shader*shader);
    int countdown(sf::RenderWindow& window, float deltatime, sf::Time time); // shows the countdown
    void shrink_text(sf::Text& text, float deltatime);
};

class StateFunctions56 {
public:
    StateFunctions56();
    bool onquit;
    bool offquit;
    void fall(Pokemon* eevee, float& groundY, float& deltaTime);
    void initialize_state_5_6(char game_mode, Pokemon* poke, sf::Font font, sf::Text& text_fainted, sf::Text& choose_pokemon, sf::Text& leave_fight,
        sf::RenderWindow& target, Pokemon_Button* buttons[], sf::Sprite& running_sprite);
    void const draw_state_5_6(char game_mode,  sf::Font& font, sf::Text& text_fainted, sf::Text choose_pokemon, sf::Text leave_fight,
        sf::RenderWindow& target, Pokemon_Button* buttons[], sf::Sprite& running_sprite);
    void update_state_5_6(char game_mode, sf::RenderWindow& window, Pokemon_Button* buttons[], int& clicked_button, sf::Sprite& running_sprite );
    void initialize_state7(bool won, sf::Text& lost_fight, sf::Font& font, sf::RenderWindow& window);
    void initialize_state_8(Pokemon* poke, sf::Font& font, sf::Text& text_fainted, sf::RenderWindow& window);
	bool check_leave(sf::Sprite &arrow_sprite, sf::RenderWindow& window); // used to update the leave button (used in states 7,8,11)

};
