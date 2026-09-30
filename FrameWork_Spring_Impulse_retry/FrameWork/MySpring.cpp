#include "Myspring.h"
#include <iostream>
using namespace cyclone;

Myspring::Myspring(Particle* p, double springConstant, double restLenght) {
	other = p;
	this->springConstant = springConstant;
	this->restLength = restLenght;
}

Myspring::~Myspring() {

}

 void Myspring::updateForce(Particle* p, double duration) {
	Vector3 force; //힘을 구해와서 particle에 적용할 것
	//두 파티클은 Particle * p 와 Particle * other(자기 파티클은 other)
	Vector3 pos1, pos2, start_end;
	p->getPosition(&pos1);
	other->getPosition(&pos2);
	start_end = pos2 - pos1; //두 파티클 간의 길이를 구하는 벡터
	double d = start_end.magnitude(); //두 파티클 간의 길이
	start_end.normalise();
	force = start_end * (-springConstant) * (d - restLength);

	other->addForce(force);
}