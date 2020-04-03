#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class GameManager {
private:
	bool game_over = false;

	GameManager() {}
	static GameManager* instance;
public:
	static GameManager* Instance() {
		if (!instance) {
			instance = new GameManager();
		}
		return instance;
	}

	bool GetGameOver() {
		return game_over;
	}
	void GameOver() {
		game_over = true;
	}
};

#endif GAME_MANAGER_H
