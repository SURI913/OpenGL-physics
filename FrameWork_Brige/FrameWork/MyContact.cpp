#include "MyContact.h"
using namespace cyclone;

MyGroundContact::MyGroundContact()
{
}
MyGroundContact::~MyGroundContact()
{
}
void MyGroundContact::init(cyclone::Particle* p, double size)
{
	if (p)
		particles.push_back(p);
	this->size = size;
}


unsigned MyGroundContact::addContact(cyclone::ParticleContact* contact, unsigned limit) const
{

	unsigned count = 0;
	for (int i = 0; i < particles.size(); i++) {
		cyclone::Particle* p = particles[i];
		cyclone::real y = p->getPosition().y;  //y위치 받아 옴

		//언제 충돌이 일어나나? (particl의 크기를 고려)
		if (y <= size) {
			//만일 충돌이 일어났다면
			Vector3 ContactNormal = Vector3::UP;
			ContactNormal.normalise();
			contact->contactNormal = ContactNormal; //y위치 - 바닥위치?
			//충돌의 대상이 되는 두 파티클 설정
			contact->particle[0] = p;
			contact->particle[1] = NULL;

			//얼마나 침투 했나?
			contact->penetration = size - y;
			contact->restitution = 1.0;

			//만일 충돌이 일어났다면 count를 증가시키고 contact++를 수행
			count++;
		}
		if (count >= limit) return count;

	}
	return count;
}

