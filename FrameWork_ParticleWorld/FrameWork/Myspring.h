#pragma once
#include "pfgen.h"
using namespace cyclone;
class Myspring : public ParticleForceGenerator {
	Particle* other;	//스프링이 적용될 파티클
	double springConstant;	//스프링 상수
	double restLength;	//rest길이
public:
	Myspring(Particle* p, double springConstant, double restLenght);
	virtual void updateForce(Particle* p, double duration);
};
