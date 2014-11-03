#pragma once
#include <iostream>

class Player {

public:
	Player();
	Player(std::string name);
	virtual ~Player();

	std::string getName() const;
	int getCash() const;
	int getPoints() const;
	int getHighScore() const;
	int getLives() const;

	void earnCash(int cash);
	void spendCash(int cash);
	void gainPoints(int points);
	void losePoints(int points);
	void setHighScore(int score);
	void earnLives(int lives);
	void loseLives(int lives);
	
private:
	std::string _name;
	int _cash; // utilized for buying towers
	int _points; // acquired during gameplay for defeating critters
	int _high_score;
	int _lives; // decrememnt when critters reach end of path
};