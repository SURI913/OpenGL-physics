#include "MoverConnection.h"

MoverConnection::MoverConnection() {
	m_movers = new Mover(Vector3(0, 2, 0));

	m_gravity = new ParticleGravity(Vector3::GRAVITY);

	m_forces = new cyclone::ParticleForceRegistry();	//여러 힘을 저장하는 컨테이너

	//중력추가
		m_forces->add(m_movers->m_particle, m_gravity);
	//스프링 적용
		m_forces->add(m_movers->m_particle, m_movers->m_spring);

	m_movers->setConnection();
}

MoverConnection::~MoverConnection() {

}

void MoverConnection::draw(int shadow) {
	for (unsigned int i = 0; i < 2; i++) {
		if (!shadow) {
			glLoadName(i + 1);
		}
		m_movers->draw(shadow);
	}

	//두 사이를 선으로 연결하기, 스프링
	glBegin(GL_LINE_STRIP);
	Vector3 p = m_movers->m_particle->getPosition();
	Vector3 position(5, 15, 5);
	glVertex3f(p.x, p.y, p.z);
	glVertex3f(position.x, position.y, position.z);
	glEnd();
}

void MoverConnection::update(float duration) {
		m_movers->update(duration);
}