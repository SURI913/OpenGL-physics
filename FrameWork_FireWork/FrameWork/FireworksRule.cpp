#include "FireworksRule.h"

void FireWorksRule::setParameters(unsigned type, real minAge, real maxAge,
	const Vector3& minVelocity, const Vector3& maxVelocity, real damping, int count) {

	this->type = type;
	this->minAge = minAge;
	this -> maxAge = maxAge;
	this->minVelocity = minVelocity;
	this->maxVelocity = maxVelocity;
	this->damping = damping;
	this->payloadCount = count;

}