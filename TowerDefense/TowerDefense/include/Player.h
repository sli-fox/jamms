#pragma once
#include <iostream>

class Player {

public:
	Player();
	Player(std::string name);
	virtual ~Player();

	std::string getName() const;
	int getCash() const;
	int getHighScore() const;

	void earnCash(int cash);
	void spendCash(int cash);
	void gainPoints(int points);
	void losePoints(int points);
	void setHighScore(int score);
	
private:
	std::string name;
	int cash; // utilized for buying towers
	int points; // acquired during gameplay for defeating critters
	int highScore;
};