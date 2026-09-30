#pragma once
#include "pfgen.h"
#include "Mover.h"
#include "Bridge.h"
using namespace cyclone;

class MoverConnection {
public:
	MoverConnection();
	~MoverConnection();
	ParticleGravity* m_gravity;
	ParticleForceRegistry* m_forces;
	std::vector<Mover*> m_movers;
	Bridge* bridge;
	void update(float duration);
	void draw(int shadow);
};
