#pragma once
#include "pfgen.h"
namespace cyclone { //사이클론으로 감싸야지 cyclone::로 사용가능
	class Myspring : public ParticleForceGenerator {
		Particle* other;	//스프링이 적용될 파티클
		double springConstant;	//스프링 상수
		double restLength;	//rest길이
	public:
		Myspring(Particle* p, double springConstant, double restLenght);
		~Myspring();
		virtual void updateForce(Particle* p, double duration);
	};
}
