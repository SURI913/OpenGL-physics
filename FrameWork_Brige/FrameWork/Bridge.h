#pragma once

#include "core.h" 
#include "particle.h"
#include "MoverConnection.h";
#include "ParticleCollision.h"
#include "pworld.h"
#include "plinks.h"
#include <vector>
#include "MyContact.h"

using namespace cyclone;
class Bridge {
public:
	Bridge(MoverConnection mover);
	~Bridge();
	cyclone::ParticleContact  m_contact[3]; //contact 발생할 수 있는 충돌 수 = 2 (넉넉하게)

	//각종 충돌을 위한 충돌생성기 : 위에 정의한 MyGroundContact 저장 위한 컨테이너
	//그런데, 왜 type이 ParticleContactGenerator일까? => 일반적으로 상속받은 클래스의 경우 //parent 타입으로 설정함  

	std::vector<cyclone::ParticleContactGenerator*> m_contactGenerators;

	//충돌 해결기 (impulse를 계산해서 속도를 변환시키고, 위치를 변경함)
	ParticleContactResolver* m_resolver;

	ParticleWorld* m_world;

	ParticleRod* Rod;
	ParticleCable* Cable;
	ParticleCableConstraint* supports;

	void draw(int shadow);
	void update(float duration);
};
