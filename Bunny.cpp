#include "Bunny.h"

Bunny::Bunny()
{
	m_Age = 0;
	SetColor();
	SetGender();
	SetMutantStatus();
	SetName();
	m_BunID = rand() % 1001;
}

bool Bunny::operator==(const Bunny& aBunny) const {
	return (m_BunID == aBunny.m_BunID);
}

// SETTER FUNCTIONS

void Bunny::SetColor(std::string color) {
	if (color == "") {
		std::vector<std::string> colorList{
			"White",
			"Brown",
			"Black",
			"Spotted"
		};
		int i = rand() % 4;
		m_Color = colorList[i];
	}
	else {
		m_Color = color;
	}

}


void Bunny::SetGender(char gender) {
	if (gender == ' ') {
		int flip = rand() % 100;
		if (flip < 50) {
			m_Gender = 'M';
		}
		else {
			m_Gender = 'F';
		}
	}
	else {
		m_Gender = gender;
	}
}


void Bunny::SetMutantStatus(std::string status) {
	if (status == "chance") {
		int flip = rand() % 100;
		if (flip < 2) {
			m_radioactive_mutant_vampire_bunny = true;
		}
		else {
			m_radioactive_mutant_vampire_bunny = false;
		}
	}

	else if (status == "infected") {
		m_radioactive_mutant_vampire_bunny = true;
	}

	else if (status == "normal") {
		m_radioactive_mutant_vampire_bunny = false;
	}
	
}


void Bunny::SetName() {		
	std::vector<std::string> Names{	
		"ChrisJericho", "Thomas", "Sarah", "VladTheInhaler", "Herman",
		"Sherman", "German", "Maureen", "Maurice", "Jergen",
		"AntMan", "TheCherno", "Shaun", "Tatertot", "Alice", "Yui", 
		"Kyouko", "Chinatsu", "Akari", "Kosaki", "Chitoge", "Marika",
		"Tsugumi", "Ruri", "Raku", "Shuu", "Haru", "RonCarterInAlvin", 
		"Algernon", "Cadwallader", "CocoaButter", "Reuben", "Joe", "Donnie", 
		"Johnnie", "Shawnee", "Dawny", "Brawny", "Tawny", "Fawny",
		"FannieMay", "FreddieMac", "FreddieBenson", "Carly", "Sam"
	};
	int i = rand() % Names.size();
	m_Name = Names[i];
}

// GETTER FUNCTIONS

int Bunny::GetAge() {
	return m_Age;
}

std::string Bunny::GetColor() {
	return m_Color;
}

char Bunny::GetGender() {
	return m_Gender;
}

bool Bunny::GetMutantStatus() {
	return m_radioactive_mutant_vampire_bunny;
}

std::string Bunny::GetName() {
	return m_Name;
}

void Bunny::Grow() {
	m_Age++;
}

void Bunny::WasBitten() {
	m_radioactive_mutant_vampire_bunny = true;
}

void Bunny::GiveBirth(std::vector<Bunny>& alive, int momIndex) {
	Bunny newBunny;
	std::string momColor = alive[momIndex].GetColor();
	newBunny.SetColor(momColor);
	alive.push_back(newBunny);
}
