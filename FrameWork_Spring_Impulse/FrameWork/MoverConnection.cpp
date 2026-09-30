#include "MoverConnection.h"

MoverConnection::MoverConnection() {
	m_forces = new ParticleForceRegistry();
	m_gravity = new ParticleGravity(Vector3(0, -9.8, 0));
	Mover* m1 = new Mover(Vector3(0, 2, 0));
	Mover* m2 = new Mover(Vector3(5, 2, 5));
	m_movers.push_back(m1);
	m_movers.push_back(m2);

	m1->setConnection(m2);
	m2->setConnection(m1);
	//m_forces->addForce(m1->m_particle, m1->m_spring);
	//m_forces->addForce(m2->m_particle, m2->m_spring);

	//m_forces->add(m_movers[0]->m_particle, m_movers[0]->m_spring);
	//m_forces->add(m_movers[1]->m_particle, m_movers[1]->m_spring);

	m_forces->add(m1->m_particle, m1->m_spring);
	m_forces->add(m2->m_particle, m2->m_spring);

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
	m_forces->updateForces(duration);

	for (unsigned int i = 0; i < m_movers.size(); i++) {
		m_movers[i]->update(duration);
	}
}