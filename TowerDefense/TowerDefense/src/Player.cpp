#include "Player.h"

Player::Player() {}

Player::Player(std::string name, int cash) : _name(name), _cash(cash) {
	this->_name = name;
	this->_cash = cash;
	this->_points = 0;
	this->_high_score = 0;
	this->_lives = 20;
}

Player::~Player() {}

std::string Player::getName() const {
	return this->_name;
}

int Player::getCash() const {
	return this->_cash;
}

int Player::getHighScore() const {
	return this->_high_score;
}

int Player::getLives() const {
	return this->_lives;
}

void Player::earnCash(int cash) {
	this->_cash += cash;
}

/**
  * @brief Maintains non-negative cash value
  * @return void
  */
void Player::spendCash(int cash) {
	this->_cash = (this->_cash - cash < 0 ? 0 : this->_cash - cash);
}

void Player::gainPoints(int points) {
	this->_points += points;
}

/**
  * @brief Maintains non-negative points value
  * @return void
  */
void Player::losePoints(int points) {
	this->_points = (this->_points - points < 0 ? 0 : this->_points - points);
}

/**
  * @brief Sets new high score if greater than old one
  * @return void
  */
void Player::setHighScore(int score) {
	if(score > this->_high_score)
		this->_high_score = score; 
}

void Player::earnLives(int lives) {
	this->_lives += lives;
}

void Player::loseLives(int lives) {
	this->_lives -= lives;
}


std::string Player::getPlayerSpecs() {
	std::stringstream output;
	output << "PLAYER SPECIFICATIONS:" << std::endl;
	
	output << "Player: " << this->_name << std::endl;
	output << "Cash: " << this->_cash << std::endl;
	output << "Lives: " << this->_lives << std::endl;
	output << "Points: " << this->_points << std::endl;
	output << "High Score: " << this->_high_score << std::endl;
	return output.str();
}
