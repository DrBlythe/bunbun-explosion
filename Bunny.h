#pragma once
#include <string>
#include <vector>

class Bunny
{
public:
	Bunny();
	int GetAge();
	std::string GetColor();
	char GetGender();
	bool GetMutantStatus();
	std::string GetName();
	

	void Grow();
	void SetColor(std::string color = "");
	void SetGender(char gender = ' ');
	void WasBitten();
	void GiveBirth(std::vector<Bunny>& alive, int momIndex);
	void SetMutantStatus(std::string status = "chance");


	//Comparison operator overload
	bool operator==(const Bunny& aBunny) const;

private:
	int m_Age;
	int m_BunID;	// A random number to use in the overloaded comparison operator
	std::string m_Color;
	char m_Gender;
	std::string m_Name;
	bool m_radioactive_mutant_vampire_bunny;

	void SetName();
	
};

