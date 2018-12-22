#pragma once
#include "Bunny.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <SDL2/SDL.h>
//#include <linux/input.h>
//#include <Windows.h>

class Game
{
public:
	Game();

	bool Initialize();
	void Welcome();
	void RunLoop();
	void Shutdown();
	std::vector<Bunny> BunnyList;
	std::vector<Bunny> DeadBuns;


private:
	bool m_Rdy2Mingle;
	bool m_IsRunning;
	int m_SlowBreeding;
	int m_TurnNumber;
	int m_CullRecharge;
	std::string DeathPhrase();

	void Wait();

	

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void BunnyCulling(std::vector<Bunny>& alive, std::vector<Bunny>& dead);
	void GenderCheck(std::vector<Bunny>& alive);
	bool BreedingStatus(std::vector<Bunny>& alive);
	void SpreadDisease(std::vector<Bunny>& alive);
	void DisplayBuns(std::vector<Bunny>& alive, std::vector<Bunny>& dead);
	void RemoveOldBuns(std::vector<Bunny>& alive, std::vector<Bunny>& dead);
	void AgeUp(std::vector<Bunny>& alive);
	void CheckGameState(std::vector<Bunny>& alive, std::vector<Bunny>& dead);
	void Breed(std::vector<Bunny>& alive);
};
