#include "MoverConnection.h"

MoverConnection::MoverConnection() {
	Mover* m1 = new Mover(Vector3(0, 2, 0));
	Mover* m2 = new Mover(Vector3(5, 2, 5));
	m_movers.push_back(m1);
	m_movers.push_back(m2);

	m_gravity = new ParticleGravity(Vector3::GRAVITY);

	m_forces = new cyclone::ParticleForceRegistry();	//여러 힘을 저장하는 컨테이너


	//중력추가
	for (unsigned int i = 0; i < m_movers.size(); i++) {
		m_forces->add(m_movers[i]->m_particle, m_gravity);
	}
	//스프링 적용
	for (unsigned int i = 0; i < m_movers.size(); i++) {
		m_forces->add(m_movers[i]->m_particle, m_movers[i]->m_spring);
	}

	m_movers[0]->setConnection(m_movers[1]);
	m_movers[1]->setConnection(m_movers[0]);
	//m_movers[0] = m_movers[1];
}

MoverConnection::~MoverConnection() {

}

void MoverConnection::draw(int shadow) {
	for (unsigned int i = 0; i < m_movers.size(); i++) {
		if (!shadow) {
			glLoadName(i + 1);
		}
		m_movers[i]->draw(shadow);
	}

	//두 개의 Mover사이를 선으로 연결하기
	glBegin(GL_LINE_STRIP);
	for (unsigned int i = 0; i < m_movers.size(); i++) {
		Vector3 p = m_movers[i]->m_particle->getPosition();
		glVertex3f(p.x, p.y, p.z);
	}
	glEnd();
}

void MoverConnection::update(float duration) {
	for (unsigned int i = 0; i < m_movers.size(); i++) {
		m_movers[i]->update(duration);
	}
}