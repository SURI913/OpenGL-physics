#include "Fire.h"
#include <random.h>
#include <iostream>
using namespace cyclone;

Fire::Fire(int type, int creatCount) { //0 init Fire, 1 child Fire

	static Random crandom;
	m_particle = new Particle();

	//타입 저장
	m_type = type;

	if (creatCount == 0) {
		if (type == 0) {//초기
			//파티클 가속도
			Vector3 velocity = Vector3(0, 10, 0);
			m_particle->setVelocity(velocity);
			//파티클 초기 위치
			Vector3 position = (Vector3(5, 10, 5));
			m_particle->setPosition(position);
			m_particle->setDamping(0.99);
			m_age = 1.0f;

			//파티클 크기
			m_size = 0.5f;
			m_particle->setAcceleration(cyclone::Vector3::GRAVITY);
		}
		if (type == 1) {
			//파티클 크기
			m_size = 0.3f;

		}
	}
	if (creatCount == 1) {
		//낮게 분산되도록 생성
		if (type == 0) {//초기
			//파티클 가속도
			Vector3 velocity = crandom.randomVector(Vector3(-20, 40, -20), Vector3(20, 60, 20));
			m_particle->setVelocity(velocity);
			//파티클 초기 위치
			Vector3 position = (Vector3(5, 10, 5));
			m_particle->setPosition(position);
			m_particle->setDamping(0.99);
			m_age = crandom.randomReal(1.0, 3.0);
			//m_age = 0.5f;

			//파티클 크기
			m_size = 0.5f;
			m_particle->setAcceleration(cyclone::Vector3::GRAVITY);
		}
		if (type == 1) {
			//파티클 크기
			m_size = 0.3f;

		}
	}
	
	//파티클 색상
	m_color = crandom.randomVector(Vector3(0, 0, 0), Vector3(1, 1, 1));

	//물리적용
	m_particle->setMass(0.01f);
	m_particle->setAcceleration(cyclone::Vector3::GRAVITY);
}
Fire::~Fire() { }

bool Fire::update(float duration) {
	m_particle->integrate(duration); //적분
	m_age -= duration;
	if (m_age <= 0) {
		return true;
	}
	return false;
}
void Fire::stop() {

}
void Fire::draw(int shadow) {
	Vector3 position;
	m_particle->getPosition(&position);
	if (shadow) {
		glColor3f(0.1f, 0.1f, 0.1f);	//그림자 색상
	}
	else {
		glColor3f(float(m_color.x),float(m_color.y),float(m_color.z));	//오브젝트 색상
	}
	glPushMatrix();
	glTranslated(position.x, position.y, position.z);
	glutSolidSphere(m_size, 30, 30);
	glPopMatrix();
}

void Fire::drawHistory() {		//꼬리 그리기
	glLineWidth(2.0f);	//처음 길이
	glPushMatrix();

	glBegin(GL_LINE_STRIP);
	for (unsigned int i = 0; i < m_history.size(); i += 2) {	//그려지는 타이밍 조절?
		Vector3 pos = m_history[i];
		glVertex3f(pos.x, pos.y, pos.z);
		
	}
	glEnd();
	glPopMatrix();
	glLineWidth(1.0f);		//마지막 길이
}

void Fire::setRule(FireWorksRule* r) {
	static Random crandom;
	Vector3 velocity = crandom.randomVector(r->minVelocity, r->maxVelocity);
	m_particle->setVelocity(velocity);
	m_particle->setDamping(r->damping);
	m_age = crandom.randomReal(r->minAge, r->maxAge);
}

void Fire::putHistory() { //위치 저장
	Vector3 position;
	m_particle->getPosition(&position);
	if (m_history.size() < 3) {	
		m_history.push_back(position);
	}
	else {
		m_history.pop_front();
		m_history.push_back(position);
	}
}