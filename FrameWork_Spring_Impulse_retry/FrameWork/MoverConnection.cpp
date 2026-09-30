#include "MoverConnection.h"

MoverConnection::MoverConnection() {
	Mover* m1 = new Mover(Vector3(0, 2, 0));
	Mover* m2 = new Mover(Vector3(5, 2, 5));

	m_movers.push_back(m1);
	m_movers.push_back(m2);

	//Contact에서 중력 및 스프링 처리?

	m_movers[0]->setConnection(m_movers[1]);
	m_movers[1]->setConnection(m_movers[0]);
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
	
}