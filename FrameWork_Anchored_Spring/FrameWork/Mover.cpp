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

Mover::Mover(Vector3& p) {
	m_particle = new Particle(); //클래스 동적 할당?
	//m_spring = new MyAnchoredSpring();
	size = 2.0f; //공 크기

	//파티클을 사용해 바운스 만든다
	m_particle->setPosition(p);	//초기 위치
	m_particle->setVelocity(0, 0, 0);	//초기 속도
	m_particle->setMass(5.0f);	//질량
	m_particle->setDamping(0.8f);	//댐핑
	m_particle->setAcceleration(Vector3::GRAVITY);	//초기 가속도
	m_particle->clearAccumulator();

};

void Mover:: update(float duration) {
	m_spring->updateForce(this->m_particle, duration);
	m_particle->integrate(duration); //적분
	
	checkEdges();
}
void Mover:: stop() {

}
void Mover:: draw(int shadow) {
	float size = 2.0f;
	cyclone::Vector3 position;
	m_particle->getPosition(&position);

	if (shadow) {
		glColor3f(0.1f, 0.1f, 0.1f);
	}
	else {
		glColor3f(1.0f, 0.0f, 0.0f);
		//glLoadName(1);
	}
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(size, 30, 30);
	glPopMatrix();
	
}

void Mover::setConnection() {
	Vector3 position(5, 15, 5);
	m_spring = new MyAnchoredSpring(position, 20.0f, 3.0f); //other
}