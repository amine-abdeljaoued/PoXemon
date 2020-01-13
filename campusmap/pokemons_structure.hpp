#include <iostream>
#include <map>
#include <string>
#include<list>
#include <map>

// All the information to create and randomly choose pokemons

struct Pokemon_info {
	float height;
	float velocity;
	std::string name;
	int health;
	int level;
	int index;
	float ptype;
};

const std::map<int, std::string> Air_Pokemons = {
		{1,"Abata"},
		{2,"Kangascuno"},
		{3,"Marodactyl"},
		{4,"Pulple"},
		{5,"Wapefet"},
	};

const std::map<int, std::string> Earth_Pokemons = {
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
	
const std::map<int, std::string> Water_Pokemons = {
		{1,"Molag"},
		{2,"Auron"},
		{3,"Golnite"},
		{4,"Warmau"},
		{5,"Mepowat"},
	};

const std::map<int, std::string> Fire_Pokemons = {
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

const std::map<int, std::string> Grass_Pokemons = { //air and earth pokemons
	{1,"Taukazam"},
	{2,"Churita"},
	{3,"Gixeor"},
	{4,"Sandlax"},
	{5,"Seemar"},
	{6,"Venion"},
	{7,"Vewaro"},
	{8,"Withuble"},
	{9,"Ganstakabra"},
	{10,"Abata"},
	{11,"Kangascuno"},
	{12,"Marodactyl"},
	{13,"Pulple"},
	{14,"Wapefet"},
};


const std::map<std::string, Pokemon_info> Pokemons = {
	//Air
	{"Abata", { 220.f, 750.f, "abata", 100, 1, 0, 30}},
	{"Kangascuno", { 200.f, 700.f, "kangascuno", 100, 1, 0, 30}},
	{"Marodactyl", { 200.f, 700.f, "marodactyl",100, 1, 0, 30 }},
	{"Pulple", { 200.f, 700.f, "pulple" ,100, 1, 0, 30}},
	{"Wapefet", { 120.f, 600.f, "wapefet",100, 1, 0, 30}},

	//Earth
	{"Taukazam", { 170.f, 650.f, "taukazam" ,100, 1, 0, 10}},
	{"Churita", { 100.f, 600.f,  "churita", 100, 1, 0, 10}},
	{"Gixeor", { 100.f, 600.f, "gixeor" ,100, 1, 0, 10 }},
	{"Sandlax", { 100.f, 600.f, "sandlax",100, 1, 0, 10}},
	{"Seemar", { 100.f, 600.f, "seemar",100, 1, 0, 10}},
	{"Venion", { 100.f, 600.f, "venion",100, 1, 0, 10 }},
	{"Vewaro", { 100.f, 600.f, "vewaro",100, 1, 0, 10}},
	{"Withuble", { 100.f, 600.f, "withuble",100, 1, 0, 10 }},
	{"Ganstakabra", { 50.f, 550.f, "ganstakabra", 100, 1, 0, 10 }},
	
	//Water
	{"Molag", { 270.f, 700.f, "molag", 100, 1, 0, 20 }},
	{"Auron", { 200.f, 620.f, "auron", 100, 1, 0, 20 }},
	{"Golnite", { 200.f, 620.f, "golnite", 100, 1, 0, 20 }},
	{"Warmau", { 200.f, 620.f, "warmau", 100, 1, 0, 20 }},
	{"Mepowat", { 200.f, 620.f, "mepowat" ,100, 1, 0, 20 }},

	//Fire
	{"Poras", { 270.f, 800.f, "poras",100, 1, 0, 40 }},
	{"Arfau", { 220.f, 700.f, "arfau",100, 1, 0, 40  }},
	{"Lowtor", { 220.f, 700.f, "lowtor" ,100, 1, 0, 40 }},
	{"Pikalee", { 220.f, 700.f, "pikalee" ,100, 1, 0, 40}},
	{"Ponag", { 220.f, 650.f, "ponag", 100, 1, 0, 40 }},
	{"Qulyd", { 220.f, 650.f, "qulyd",100, 1, 0, 40}},
	{"Ronew", { 220.f, 650.f, "ronew" ,100, 1, 0, 40}},
	{"Twobee", { 220.f, 650.f, "twobee" ,100, 1, 0, 40 }},
	{"Raporoy", { 130.f, 540.f, "raporoy" ,100, 1, 0, 40 }}
};


