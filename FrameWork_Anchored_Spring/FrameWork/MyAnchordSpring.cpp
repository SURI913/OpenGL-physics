#include "MyAnchordSpring.h"

MyAnchoredSpring::MyAnchoredSpring() { };

MyAnchoredSpring::MyAnchoredSpring(cyclone::Vector3 anchor, double springConstant,
    double restLenght){
    this->anchor = anchor;
    this->springConstant = springConstant;
    this->restLength = restLenght;
}

void MyAnchoredSpring::init(Vector3 anchor, double springConstant, double restLength) {
	this->anchor = anchor;
	this->springConstant = springConstant;
	this->restLength = restLength;
}

void MyAnchoredSpring::updateForce(Particle* particle, real duration) {
	Vector3 force; //힘을 구해와서 particle에 적용할 것
	//두 파티클은 Particle * p 와 Particle * other(자기 파티클은 other)
	Vector3 pos1, pos2, start_end;
	particle->getPosition(&pos1);
	start_end = pos1 - anchor; //두 파티클 간의 길이를 구하는 벡터
	double d = start_end.magnitude(); //두 파티클 간의 길이
	start_end.normalise();
	force = start_end * (-springConstant) * (d - restLength);

	particle->addForce(force);
}