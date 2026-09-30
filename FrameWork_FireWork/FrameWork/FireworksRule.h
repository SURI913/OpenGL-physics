#pragma once

#include<deque>
#include"particle.h"
using namespace cyclone;

class FireWorksRule {
public:
	FireWorksRule() { };
	~FireWorksRule() { };

	unsigned type;	//Fire의 타입
	real minAge;	//Fire의 최소 age
	real maxAge;	//Fire의 최대 age
	Vector3 minVelocity;	//Fire의 최소 속도
	Vector3 maxVelocity;	//Fire의 최대 속도
	real damping;	//Fire의 damping

	unsigned payloadCount;	//만일 ChildFire를 생성한다면 몇 개나 생성하나
	
	void setParameters(unsigned type, real minAge, real maxAge,
		const Vector3& minVelocity, const Vector3& maxVelocity,
		real damping, int count);

};
