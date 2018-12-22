#include "Game.h"

Game::Game()
{
	Welcome();
	m_TurnNumber = 1;
	m_CullRecharge = 15;
	m_IsRunning = true;
	m_Rdy2Mingle = false;
	m_SlowBreeding = 0;
	BunnyList.reserve(1000);
	Bunny bun0, bun1, bun2, bun3, bun4;
	BunnyList = {
		bun0,
		bun1,
		bun2,
		bun3,
		bun4
	};
	GenderCheck(BunnyList);
}


bool Game::Initialize() {
	if (m_IsRunning) {
		return true;
	}
	else {
		return false;
	}
}


void Game::RunLoop() {
	while (m_IsRunning) {

		ProcessInput();
		UpdateGame();
		GenerateOutput();

	}
}


void Game::Shutdown() {
	using namespace std::literals::chrono_literals;
	std::cout << "There are no bunnies left!\n\n";
	std::cout << "Game over.\n\n";
	std::cout << "SHUTTING DOWN. GOODBYE.\n";
	std::this_thread::sleep_for(2s);
}


void Game::ProcessInput() {

}


void Game::UpdateGame() {
	CheckGameState(BunnyList, DeadBuns);
	RemoveOldBuns(BunnyList, DeadBuns); // Figure out how to set these lists as default parameters, without the static problem
	if (BreedingStatus(BunnyList)) {
		Breed(BunnyList);
	}
	DisplayBuns(BunnyList, DeadBuns);
	SpreadDisease(BunnyList);
	AgeUp(BunnyList);
	Wait();
}


void Game::GenerateOutput() {



}

// GAME CONSTRUCTOR FUNCTIONS



void Game::Welcome() {
	using namespace std::literals::chrono_literals;
	std::cout << "WELCOME TO BUN-BUN-EXPLOSION\n\n\n";
	std::this_thread::sleep_for(2s);
	std::cout << "You get to witness the population explosion of a wild bunny colony.\n";
	std::this_thread::sleep_for(3s);

	std::cout << "Most are normal, however, some are very dangerous radioactive-vampire-mutant bunnies.\n\n";
	std::this_thread::sleep_for(3s);

	std::cout << "After each turn, you are given a few seconds to hit the spacebar to cull about half of the colony.\n\n";
	std::this_thread::sleep_for(3s);

	std::cout << "At turn 15 bunny killing missiles will be ready to fire.\n";
	std::cout << "Once used, the missiles will be unavailable for the next 10 turns.\n";
	std::this_thread::sleep_for(3s);

	std::cout << "\n\n\n";
	std::cout << "						GAME STARTING IN:";
	std::this_thread::sleep_for(1s);
	std::cout << "\n\n							3\a";
	std::this_thread::sleep_for(1s);

	std::cout << "\n\n							2\a";
	std::this_thread::sleep_for(1s);

	std::cout << "\n\n							1\a";
	std::this_thread::sleep_for(1s);
	std::cout << "\n\n-----------------------------------------------------------------------\n\n";

}


void Game::GenderCheck(std::vector<Bunny>& alive) {
	alive = BunnyList;
	int maleCount = 0;
	// Check if all initial bunnies are the same gender. If so, change the last one to the opposite gender.
	for (int i = 0; i < alive.size(); i++) {
		if (alive[i].GetGender() == 'M') {
			maleCount++;
		}
	}
	switch (maleCount) {
	case 0:
		alive.back().SetGender('M');
		alive.back().SetMutantStatus("normal");
		break;
	case 5:
		alive.back().SetGender('F');
		alive.back().SetMutantStatus("normal");
		break;
	}
}


// UPDATE GAME FUNCTIONS



void Game::CheckGameState(std::vector<Bunny>& alive, std::vector<Bunny>& dead) {
	// Display turn number
	std::cout << "Turn " << m_TurnNumber << "\n\n";

	if (BunnyList.empty()) {
		m_IsRunning = false;
	}
	else if (BunnyList.size() > 999) {
		BunnyCulling(alive, dead);
		m_SlowBreeding = 5;
	}
	if (m_SlowBreeding) {
		m_SlowBreeding -= 1;
	}
}
void Game::BunnyCulling(std::vector<Bunny>& alive, std::vector<Bunny>& dead) {
	std::cout << "\n\nA food shortage has occurred!\n";
	std::cout << "Many bunnies have died!\n\n";
	// Kill 2/3 of bunnies
	for (int i = 0; i < alive.size(); i++) {
		int chance = rand() % 3;
		if (chance == 1 || chance == 2) {
			alive.erase(alive.begin() + i);
		}
		m_SlowBreeding = 5;
	}
}


void Game::RemoveOldBuns(std::vector<Bunny>& alive, std::vector<Bunny>& dead) {
	alive = BunnyList;
	dead = DeadBuns;

	// Add old (11+) buns to deadbuns
	for (int i = 0; i < alive.size(); i++) {
		if (alive[i].GetAge() > 10 && !alive[i].GetMutantStatus()) {
			dead.push_back(alive[i]);
		}
		else if (alive[i].GetAge() > 50 && alive[i].GetMutantStatus()) {
			dead.push_back(alive[i]);
		}
	}

	// Remove bunnies that are in deadbuns from BunnyList
	for (int i = 0; i < dead.size(); i++) {
		for (int j = 0; j < alive.size(); j++) {
			if (dead[i] == alive[j]) {
				std::cout << "\nBunny " << alive[j].GetName() << DeathPhrase() << "\n\n";
				alive.erase(alive.begin() + j);
			}
		}
	}
}


bool Game::BreedingStatus(std::vector<Bunny>& alive) {
	for (int i = 0; i < alive.size(); i++) {
		if (alive[i].GetGender() == 'M' && alive[i].GetAge() >= 2) {
			m_Rdy2Mingle = true;
			return m_Rdy2Mingle;
		}
	}
	m_Rdy2Mingle = false;
	return m_Rdy2Mingle;
}


void Game::Breed(std::vector<Bunny>& alive) {
	// If there is a bunny culling, chances of breeding are reduced to 1/5 for each eligible bunny
	bool letBreed = false;
	if (!m_SlowBreeding) {
		letBreed = true;
	}
	else if (m_SlowBreeding) {
		int chance = rand() % 10;
		if (chance == 1) {
			letBreed = true;
		}
	}
	if (letBreed) {
		std::cout << "Births:\n\n";
		for (int i = 0; i < alive.size(); i++) {
			if (alive[i].GetGender() == 'F' && alive[i].GetAge() >= 2 && !alive[i].GetMutantStatus()) {
				alive[i].GiveBirth(BunnyList, i);
				std::cout << "Bunny " << alive.back().GetName() << " was born.\n";
			}
		}
		std::cout << "\n";
	}
}


void Game::DisplayBuns(std::vector<Bunny>& alive, std::vector<Bunny>& dead) {
	// Display bunny deaths, if any
	dead = DeadBuns;
	if (!dead.empty()) {
		std::cout << "Deaths:\n\n";
		for (int i = 0; i < dead.size(); i++) {
			std::cout << "Bunny " << dead[i].GetName() << DeathPhrase();
		}
		dead.clear();
	}
	// Display entire bunny colony list
	alive = BunnyList;
	for (int i = 0; i < alive.size(); i++) {
		std::cout << i << " - " << alive[i].GetName() << ", Age: " << alive[i].GetAge() <<
			", Color: " << alive[i].GetColor() <<
			", Gender: " << alive[i].GetGender() << ", Mutie?: " << alive[i].GetMutantStatus() << std::endl;
	}
}


void Game::SpreadDisease(std::vector<Bunny>& alive) {
	// Do not spread disease on first 2 turns
	// Each turn, for each radioactive vampire mutant bunny, there is a 1/3 chance that it will infect one other bunny
	if (m_TurnNumber > 2) {
		for (int i = 0; i < alive.size(); i++) {
			int unlucky = rand() % (alive.size());
			if (alive[i].GetMutantStatus()) {
				int chance = rand() % 3;
				if (chance == 1) {
					alive[unlucky].SetMutantStatus("infected");
				}
			}
		}
	}

}


void Game::AgeUp(std::vector<Bunny>& vec) {
	vec = BunnyList;
	for (int i = 0; i < vec.size(); i++) {
		vec[i].Grow();
	}
}


void Game::Wait() {
	using namespace std::literals::chrono_literals;
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (m_CullRecharge) {
		m_CullRecharge -= 1;
	}
	if (!m_CullRecharge) {
		std::cout << "\nBUNNY CULLING MISSILES ARE ARMED AND READY!\n\n";
	}
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start + 3s;
	auto current = start;

	while (current < end) 
	{
		if ((state[SDL_SCANCODE_SPACE]) && !m_CullRecharge) 
		{
			if (current < end) 
			{
				std::this_thread::sleep_for(end - current);
			}
			BunnyCulling(BunnyList, DeadBuns);
			m_CullRecharge = 10;
			break;
		}

		current = std::chrono::high_resolution_clock::now();
	}
	m_TurnNumber++;
	std::cout << "\n-----------------------------------------------------------------------\n";
}


std::string Game::DeathPhrase() {
	std::string usedPhrase;
	std::vector<std::string> phrases{
		" has been hit by a car!\n",
		" was... Well, the bunny's dead, but I'm not going into detail about this one.\n",
		" passed away, tucked warmly into his bed with his loved ones by his side. He will be missed.\n",
		" was adopted by a kind family and left the farm. He still visits from time to time.\n",
		" was adopted by a hungry family. He was never seen again.\n",
		" was beaten down by a gang of bunnies who wanted his Rolex.\n",
		" died in a jetski accident.\n",
		", the jetski enthusiast, was sentenced to life in prison for vehicular manslaughter of another bunbun.\n"
	};
	int i = rand() % (phrases.size());
	usedPhrase = phrases[i];
	return usedPhrase;
}