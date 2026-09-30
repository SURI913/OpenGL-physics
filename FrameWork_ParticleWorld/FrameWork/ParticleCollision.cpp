#include "ParticleCollision.h"
#include <iostream>
using namespace cyclone;

unsigned ParticleCollision::addContact(cyclone::ParticleContact* contact, unsigned limit) const
{
    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    Vector3 pos0;
    Vector3 pos1;
    particle[0]->getPosition(&pos0);
    particle[1]->getPosition(&pos1);
    

    Vector3 ContactNormal(pos0-pos1);
    float d = ContactNormal.magnitude();
    std::cout << d << std::endl;
    ContactNormal.normalise();
    contact->contactNormal = ContactNormal;//(두 방향을 테스트 해 봐서 동작하는 방향 설정)
    //연결 조건 이상함 
    if (d <= 4.0f) {
        contact->penetration = 4.0 - d;
        contact->restitution = 1.0;
    }
    else return 0;
    return 1;
}
