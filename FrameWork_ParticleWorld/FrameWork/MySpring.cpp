#include "Myspring.h"
#include <iostream>
using namespace cyclone;

Myspring::Myspring(Particle* p, double springConstant, double restLenght) {
	other = new Particle();
	other = p;
	this->springConstant = springConstant;
	this->restLength = restLenght;
}

 void Myspring::updateForce(Particle* p, double duration) {

	 cyclone::Vector3 force;

	 cyclone::Vector3 pos = p->getPosition();
	 cyclone::Vector3 pos2 = other->getPosition();

	 cyclone::Vector3 d = pos - pos2;
	 double l = d.magnitude();

	 d.normalise();
	 force = d * -springConstant * (l - restLength);

	p->addForce(force);
}