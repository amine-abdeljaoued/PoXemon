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
		float height;
		float velocity;
		std::string name;
		int health;
		int level;
		int index;
		float ptype;
		
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
	Pokemons["Abata"] = { 220.f, 750.f, "abata", 90, 1, 0, 30};
	Pokemons["Kangascuno"] = { 200.f, 700.f, "kangascuno", 85, 1, 0, 30};
	Pokemons["Marodactyl"] = { 200.f, 700.f, "marodactyl",85, 1, 0, 30 };
	Pokemons["Pulple"] = { 200.f, 700.f, "pulple" ,85, 1, 0, 30};
	
	Pokemons["Wapefet"] = { 120.f, 600.f, "wapefet",60, 1, 0, 30};

	//Earth
	Pokemons["Taukazam"] = { 170.f, 650.f, "taukazam" ,180, 1, 0, 10};
	
	Pokemons["Churita"] = { 100.f, 600.f,  "churita", 160, 1, 0, 10};
	Pokemons["Gixeor"] = { 100.f, 600.f, "gixeor" ,160, 1, 0, 10 };
	Pokemons["Sandlax"] = { 100.f, 600.f, "sandlax",160, 1, 0, 10};
	Pokemons["Seemar"] = { 100.f, 600.f, "seemar",160, 1, 0, 10};
	Pokemons["Venion"] = { 100.f, 600.f, "venion",160, 1, 0, 10 };
	Pokemons["Vewaro"] = { 100.f, 600.f, "vewaro",160, 1, 0, 10};
	Pokemons["Withuble"] = { 100.f, 600.f, "withuble",160, 1, 0, 10 };

	Pokemons["Ganstakabra"] = { 50.f, 550.f, "ganstakabra", 110, 1, 0, 10 };
	
	//Water
	Pokemons["Molag"] = { 270.f, 700.f, "molag", 160, 1, 0, 20 };

	Pokemons["Auron"] = { 200.f, 620.f, "auron", 110, 1, 0, 20 };
	Pokemons["Golnite"] = { 200.f, 620.f, "golnite", 110, 1, 0, 20 };
	Pokemons["Warmau"] = { 200.f, 620.f, "warmau", 110, 1, 0, 20 };
	Pokemons["Mepowat"] = { 200.f, 620.f, "mepowat" ,110, 1, 0, 20 };

	//Fire
	Pokemons["Poras"] = { 270.f, 800.f, "poras",170, 1, 0, 40 };

	Pokemons["Arfau"] = { 220.f, 700.f, "arfau",120, 1, 0, 40  };
	Pokemons["Lowtor"] = { 220.f, 700.f, "lowtor" ,120, 1, 0, 40 };
	Pokemons["Pikalee"] = { 220.f, 700.f, "pikalee" ,120, 1, 0, 40};
	Pokemons["Ponag"] = { 220.f, 650.f, "ponag", 120, 1, 0, 40 };
	Pokemons["Qulyd"] = { 220.f, 650.f, "qulyd",120, 1, 0, 40};
	Pokemons["Ronew"] = { 220.f, 650.f, "ronew" ,120, 1, 0, 40};
	Pokemons["Twobee"] = { 220.f, 650.f, "twobee" ,120, 1, 0, 40 };

	Pokemons["Raporoy"] = { 130.f, 540.f, "raporoy" ,80, 1, 0, 40 };

	std::cout << Pokemons["Raporoy"].path << "\n";
	return 0;
}

