#pragma once

class CritterEffect{
public:
	enum EFFECT {BURN, FREEZE, SLOW, STUN, KNOCKBACK, PETRIFY, CRUSH, POISON, SHOCK, TIMEBOMB, MOONWALK, NONE};

	CritterEffect();
	CritterEffect(int damage, float speedModifier, int stacks, float cycles);
	virtual ~CritterEffect();

	virtual int getDamage();
	virtual float getSpeedModifer();
	int getStacks();
	float getCycles();
	float getElapsedTicks();

	bool applyEffect();
	void addStacks(int stacks);
	void tick();

	virtual bool isEqual(CritterEffect* effect);

protected:
	int stacks, damage;
	float speedModifier, cycles, elapsedTicks;
	EFFECT type;
};

struct Burn : public CritterEffect {
	Burn();
	virtual ~Burn();
};

struct Freeze : public CritterEffect {
	Freeze();
	virtual ~Freeze();
	virtual int getDamage();
	virtual float getSpeedModifer();
};

struct Slowe : public CritterEffect {
	Slowe();
	virtual ~Slowe();
};

struct Stun : public CritterEffect {
	Stun();
	virtual ~Stun();
};

struct Knockback : public CritterEffect {
	Knockback();
	virtual ~Knockback();
};

struct Petrify : public CritterEffect {
	Petrify();
	virtual ~Petrify();
	virtual float getSpeedModifer();
};

struct Crush : public CritterEffect {
	Crush();
	virtual ~Crush();
	virtual int getDamage();
};

struct Poison : public CritterEffect {
	Poison();
	virtual ~Poison();
};

struct Shock : public CritterEffect {
	Shock();
	virtual ~Shock();
};

struct Moonwalk : public CritterEffect {
	Moonwalk();
	virtual ~Moonwalk();
};

