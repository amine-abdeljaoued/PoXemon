#include <iostream>
#include <map>
#include <string>
#include<list>

#include <map>

/*Ok so the pokemons are initialised with the following things in the following order...
1. window (you don't need to put anything here)
2. float height: max height you can jump to (approx 200.f)
3. float velocity: speed of movement (approx 500.f-800.f)
4. Backpack_Pokemon - this is intiated like this Backpack_Pokemon(std::string name, int level, int index, int health=100, int ptype)
	( the ptype is 	10 - earth
			20 - water
			30 - air
			40 - fire )
*/

int main() {
	struct Pokemon_info {
		//float xstart; (always the same)
		//float ystart; (always the same)
		float h;
		float v;
		float hp;
		char path[50];
		float pokemon_rarity; //1-legendary, 2-mythic, 3-starter
		char pname[50];
		bool caught; //for the pokedex
	};


	std::map<int, std::string> Air_Pokemons = {
		{1,"Abata"},
		{2,"Kangascuno"},
		{3,"Marodactyl"},
		{4,"Pulple"},
		{5,"Wapefet"},

	};

	std::map<int, std::string> Earth_Pokemons = {
		{1,"Taukazam"},
		{2,"Churita"},
		{3,"Gixeor"},
		{4,"Sandlax"},
		{5,"Seemar"},

		{6,"Venion"},
		{7,"Vewaro"},
		{8,"Withuble"},
		{9,"Ganstakabra"},

	};
	
	std::map<int, std::string> Water_Pokemons = {
		{1,"Molag"},
		{2,"Auron"},
		{3,"Golnite"},
		{4,"Warmau"},
		{5,"Mepowat"},

	};

	std::map<int, std::string> Fire_Pokemons = {
		{1,"Poras"},
		{2,"Arfau"},
		{3,"Lowtor"},
		{4,"Pikalee"},
		{5,"Ponag"},
		{6,"Qulyd"},
		{7,"Ronew"},
		{8,"Twobee"},
		{9,"Raporoy"},

	};


	std::map<std::string, Pokemon_info> Pokemons;

	//Air
	Pokemons["Abata"] = { 300.f, 900.f, 90, "Images/Pokemon_Images/abata.png", 1, "Abata" ,false};
	Pokemons["Kangascuno"] = { 280.f, 850.f, 85, "Images/Pokemon_Images/kangascuno.png", 2, "Kangascuno", false };
	Pokemons["Marodactyl"] = { 280.f, 850.f, 85, "Images/Pokemon_Images/marodactyl.png", 2, "Marodactyl", false };
	Pokemons["Pulple"] = { 280.f, 850.f, 85, "Images/Pokemon_Images/pulple.png", 2, "Pulple" , false };
	
	Pokemons["Wapefet"] = { 200.f, 750.f, 60, "Images/Pokemon_Images/wapefet.png", 3, "Wapefet",false };

	//Earth
	Pokemons["Taukazam"] = { 250.f, 800.f, 180, "Images/Pokemon_Images/taukazam.png", 1, "Taukazam" ,false };
	
	Pokemons["Churita"] = { 180.f, 700.f, 160, "Images/Pokemon_Images/churita.png", 2, "Churita",false };
	Pokemons["Gixeor"] = { 180.f, 700.f, 160, "Images/Pokemon_Images/gixeor.png", 2, "Gixeor" ,false };
	Pokemons["Sandlax"] = { 180.f, 700.f, 160, "Images/Pokemon_Images/sandlax.png", 2, "Sandlax",false };
	Pokemons["Seemar"] = { 180.f, 700.f, 160, "Images/Pokemon_Images/seemar.png", 2, "Seemar",false };
	Pokemons["Venion"] = { 180.f, 700.f, 160, "Images/Pokemon_Images/venion.png", 2, "Venion",false };
	Pokemons["Vewaro"] = { 180.f, 700.f, 160, "Images/Pokemon_Images/vewaro.png", 2, "Vewaro",false };
	Pokemons["Withuble"] = { 180.f, 700.f, 160, "Images/Pokemon_Images/withuble.png", 2, "Withuble",false };

	Pokemons["Ganstakabra"] = { 120.f, 600.f, 110, "Images/Pokemon_Images/ganstakabra.png", 3, "Ganstakabra",false };
	
	//Water
	Pokemons["Molag"] = { 350.f, 850.f, 160, "Images/Pokemon_Images/molag.png", 1, "Molag",false };

	Pokemons["Auron"] = { 280.f, 720.f, 110, "Images/Pokemon_Images/auron.png", 2, "Auron",false };
	Pokemons["Golnite"] = { 280.f, 720.f, 110, "Images/Pokemon_Images/golnite.png", 2, "Golnite",false };
	Pokemons["Warmau"] = { 280.f, 720.f, 110, "Images/Pokemon_Images/warmau.png", 2, "Warmau",false };
	Pokemons["Mepowat"] = { 280.f, 720.f, 110, "Images/Pokemon_Images/mepowat.png", 2, "Mepowat" ,false };

	//Fire
	Pokemons["Poras"] = { 350.f, 950.f, 170, "Images/Pokemon_Images/poras.png", 1, "Poras",false };

	Pokemons["Arfau"] = { 310.f, 820.f, 120, "Images/Pokemon_Images/arfau.png", 2, "Arfau",false };
	Pokemons["Lowtor"] = { 310.f, 820.f, 120, "Images/Pokemon_Images/lowtor.png", 2, "Lowtor" ,false };
	Pokemons["Pikalee"] = { 310.f, 820.f, 120, "Images/Pokemon_Images/pikalee.png", 2, "Pikalee" ,false };
	Pokemons["Ponag"] = { 310.f, 820.f, 120, "Images/Pokemon_Images/ponag.png", 2, "Ponag",false };
	Pokemons["Qulyd"] = { 310.f, 820.f, 120, "Images/Pokemon_Images/qulyd.png", 2, "Qulyd",false };
	Pokemons["Ronew"] = { 310.f, 820.f, 120, "Images/Pokemon_Images/ronew.png", 2, "Ronew" ,false };
	Pokemons["Twobee"] = { 310.f, 820.f, 120, "Images/Pokemon_Images/twobee.png", 2, "Twobee" ,false };

	Pokemons["Raporoy"] = { 210.f, 620.f, 80, "Images/Pokemon_Images/raporoy.png", 2, "Raporoy" ,false };

	std::cout << Pokemons["Raporoy"].path << "\n";
	return 0;
}

