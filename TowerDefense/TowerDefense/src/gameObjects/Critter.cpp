#include <gameObjects/Critter.h>

Critter::Critter(){
	speedModifier = 1.0;
}

Critter::~Critter(){

}

int Critter::getId() const {
  return id;
}
int Critter::getHitPoints() const {
  return hit_points;
}
void Critter::setHitPoints(int points){
  this->hit_points = points;
}
int Critter::getStealPointsStrength() const {
  return steal_points;
} 
int Critter::getPlayerReward() const {
  return player_reward;
} 
float Critter::getSpeed() const {
	return speed * speedModifier;
}
void Critter::setSpeed(float speed) {
	this->speed = speed;
}
int Critter::getLevel() const {
  return level;
}
bool Critter::getSpecialEffectApplied() const {
	return this->specialEffectApplied;
}
void Critter::setSpecialEffectApplied(bool specialEffectsApplied) {
	this->specialEffectApplied = specialEffectsApplied;
}

void Critter::inflictDamage(int damage) {
	this->hit_points = (this->hit_points - damage <= 0 ? 0 : this->hit_points - damage);
}

void Critter::reduceSpeed(float speed) {
	this->speed = (this->speed - speed >= 10.0f ? this->speed - speed : 10.0f);
}

std::string Critter::getCritterSpecs() {
	//Since we can't cout an enum in C++, we need this Array system as a workaround (optional, but prettier at output)
	char *CritterTypeA[] = { "BLACK_CAT", "WHITE_CAT" };
	std::stringstream output;
	output << "Critter Id: " << this->id << std::endl;
	output << "Current Health: " << this->getHitPoints() << std::endl;
	output << "Max Health: " << this->max_health << std::endl;
	output << "Type: " << CritterTypeA[this->type] << std::endl;
	output << "Steal Coins: " << this->steal_points << std::endl;
	output << "Player Reward: " << this->player_reward << std::endl;
	output << "Speed: " << this->speed << std::endl;

	return output.str();
}

void Critter::addEffect(CritterEffect effect){
	bool effectApplied = false;
	std::list<CritterEffect>::iterator it;
	for(it = effectList.begin() ; it != effectList.end() ; ++it){
		if(it->isEqual(effect)){
			it->addStacks(effect.getStacks());
			effectApplied = true;
			break;
		}
	}
	if(!effectApplied)
		effectList.push_back(effect);
}

void Critter::inflictEffects(){
	if(!effectList.empty()){
		std::list<CritterEffect>::iterator it = effectList.begin();
		speedModifier = 1.0;
		while(it != effectList.end()){
			it->tick();
			if(it->applyEffect()){
				if(it->getStacks() < 0){
					effectList.erase(it++);
					continue;
				}
				/*std::cout << "critter ID: " << this->getId()
				<< ", Num of effects: " << int(effectList.size()) 
				<< ", Num of stacks: " << it->getStacks() << std::endl;
				*/
				inflictDamage(it->getDamage());
			}
			if(it->getSpeedModifer() < speedModifier)
				speedModifier = it->getSpeedModifer();
			++it;
		}
	}
}
