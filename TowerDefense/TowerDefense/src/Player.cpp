#include "..\include\Player.h"

Player::Player() {

}

Player::Player(std::string name) : name(name){
	
}

Player::~Player() {

}

void Player::earnCash(int cash) {
	this->cash += cash;
}

void Player::spendCash(int cash) {
	this->cash = (this->cash - cash < 0 ? 0 : this->cash - cash);
}

void Player::setHighScore(int score) {
	if(score > this->highScore)
		this->highScore = score; 
}

void Player::gainPoints(int points) {
	this->points += points;
}

void Player::losePoints(int points) {
	this->points = (this->points - points < 0 ? 0 : this->points - points);
}