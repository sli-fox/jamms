#pragma once

class CritterEffect{
public:
	CritterEffect(int damage, float speedModifier, int stacks, float cycles);
	virtual ~CritterEffect();

	int getDamage();
	float getSpeedModifer();
	int getStacks();
	float getDelay();
	float getElapsedTicks();

	bool applyEffect();
	void addStacks(int stacks);
	void tick();

	bool isEqual(CritterEffect effect);

private:
	int stacks, damage;
	float speedModifier, cycles, elapsedTicks;
	
};