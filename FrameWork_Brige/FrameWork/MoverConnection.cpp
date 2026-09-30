#include "MoverConnection.h"
#include <iostream>

MoverConnection::MoverConnection() {
	m_forces = new ParticleForceRegistry();
	m_gravity = new ParticleGravity(Vector3(0, -9.8, 0));
	Mover* m1 = new Mover(Vector3(-5, 10, 1));
	Mover* m2 = new Mover(Vector3(-3, 9, 1));
	Mover* m3 = new Mover(Vector3(-1, 8, 1));
	Mover* m4 = new Mover(Vector3(1, 8, 1));
	Mover* m5 = new Mover(Vector3(3, 9, 1));
	Mover* m6 = new Mover(Vector3(5, 10, 1));

	Mover* m7 = new Mover(Vector3(-5, 10, -1));
	Mover* m8 = new Mover(Vector3(-3, 9, -1));
	Mover* m9 = new Mover(Vector3(-1, 8, -1));
	Mover* m10 = new Mover(Vector3(1, 8, -1));
	Mover* m11 = new Mover(Vector3(3, 9, -1));
	Mover* m12 = new Mover(Vector3(5, 10, -1));

	m_movers.push_back(m1);
	m_movers.push_back(m2);
	m_movers.push_back(m3);
	m_movers.push_back(m4);
	m_movers.push_back(m5);
	m_movers.push_back(m6);
	m_movers.push_back(m7);
	m_movers.push_back(m8);
	m_movers.push_back(m9);
	m_movers.push_back(m10);
	m_movers.push_back(m11);
	m_movers.push_back(m12);

	//m1->setConnection(m2);
	//m2->setConnection(m1);
	//m_forces->add(m1->m_particle, m1->m_spring);
	//m_forces->add(m2->m_particle, m2->m_spring);
	std::cout << "공생성" << std::endl;
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

	////두 개의 Mover사이를 선으로 연결하기
	//glBegin(GL_LINE_STRIP);
	//for (unsigned int i = 0; i < m_movers.size(); i++) {
	//	Vector3 p = m_movers[i]->m_particle->getPosition();
	//	glVertex3f(p.x, p.y, p.z);
	//}
	//glEnd();
}

void MoverConnection::update(float duration) {
	m_forces->updateForces(duration);

	for (unsigned int i = 0; i < m_movers.size(); i++) {
		m_movers[i]->update(duration);
	}
}