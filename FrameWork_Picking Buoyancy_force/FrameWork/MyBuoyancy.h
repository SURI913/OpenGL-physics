#pragma once
#include "pfgen.h"
using namespace cyclone;

class MyBuoyancy : public ParticleForceGenerator
{

	double maxDepth;
	double volume;//물체의 부피
	double waterHeight;
	double liquidDensity; //액체의 밀도

public:
	MyBuoyancy(double maxDepth, double volume, double waterHeight, double liquidDensity);
	~MyBuoyancy();
	void updateForce(Particle* p, double duration);

};
