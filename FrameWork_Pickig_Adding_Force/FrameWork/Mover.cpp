#include "Mover.h"
#include "MyGlWindow.h"
#include <gl/glut.h>
using namespace cyclone;

void Mover:: checkEdges() {
	float MAX_xVal = 100.0f - size;
	float MIN_xVal =  size - 100.0f;
	float MAX_zVal = 100.0f - size;
	float MIN_zVal =  size - 100.0f;

	m_particle->getPosition(&m_position);
	m_particle->getVelocity(&m_velocity);
	
	//개인
	if (m_position.y <= size) {	//바닥에 닿았다면  튀어오르게
		m_particle->setPosition(m_position.x, size, m_position.z);
		m_particle->setVelocity(m_velocity.x, m_velocity.y * -1.0f, m_velocity.z); //속도, 방향 변경
	}
	if (m_position.x >= MAX_xVal)	//벽에 닿았다면 튀어오르게
	{
		m_particle->setPosition(MAX_xVal, m_position.y, m_position.z);
		m_particle->setVelocity(m_velocity.x * -1.0f, m_velocity.y, m_velocity.z);
	}
	if (m_position.z >= MAX_zVal)	//벽에 닿았다면 튀어오르게
	{
		m_particle->setPosition(m_position.x, m_position.y, MAX_zVal);
		m_particle->setVelocity(m_velocity.x, m_velocity.y, m_velocity.z * -1.0f);
	}
	if (m_position.z <= MIN_zVal)	//벽에 닿았다면 튀어오르게
	{
		m_particle->setPosition(m_position.x, m_position.y, MIN_zVal);
		m_particle->setVelocity(m_velocity.x, m_velocity.y, m_velocity.z * -1.0f);
	}
	if (m_position.x <= MIN_xVal)	//벽에 닿았다면 튀어오르게
	{
		m_particle->setPosition(MIN_xVal, m_position.y, m_position.z);
		m_particle->setVelocity(m_velocity.x * -1.0f, m_velocity.y, m_velocity.z);
	}
}

Mover::Mover() {
	m_particle = new Particle(); //클래스 동적 할당?

	m_gravity = new ParticleGravity(Vector3(0, -9.8, 0));
	m_drag = new ParticleDrag(0.1, 0.1);
	m_forces = new ParticleForceRegistry();	//여러 힘을 저장하는 컨테이너

	

	size = 2.0f; //공 크기

	//파티클을 사용해 바운스 만든다
	
	m_particle->setPosition(5, 20, 0);	//초기 위치
	m_particle->setVelocity(0, 0, 0);	//초기 속도
	m_particle->setMass(10.0f);	//질량
	m_particle->setDamping(1.0f);	//댐핑
	m_particle->setAcceleration(Vector3(0,0,0));	//초기 가속도

	m_forces->add(m_particle, m_gravity);
	m_forces->add(m_particle, m_drag);


};

void Mover:: update(float duration) {
	//cyclone::Vector3 wind(1.0f, 0, 0);	// x축으로 부는 바람
	//m_particle->addForce(wind);//공간 안에 힘 부여. 중력가속도 + 힘으로 공이 튀겨진다.
	
	m_forces->updateForces(duration);	//particleForceRegistry 업데이트
	m_particle->integrate(duration); //적분
	checkEdges();
}
void Mover:: stop() {

}
void Mover:: draw(int shadow) {
	//m_particle->getPosition(&m_position);		//현재 파티클의 위치를 얻은 후 position으로 설정

	float size = 2.0f;
	cyclone::Vector3 position;
	m_particle->getPosition(&position);

	if (shadow) {
		glColor3f(0.1f, 0.1f, 0.1f);
	}
	else {
		glColor3f(1.0f, 0.0f, 0.0f);
		glLoadName(1);
	}
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(size, 30, 30);
	glPopMatrix();
	
}