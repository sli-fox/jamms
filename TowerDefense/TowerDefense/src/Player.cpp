#include "..\include\Player.h"

Player::Player() {

}

Player::Player(std::string name) : _name(name){
	this->_cash = 0;
	this->_points = 0;
	this->_high_score = 0;
	this->_lives = 20;
}

Player::~Player() {

}

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