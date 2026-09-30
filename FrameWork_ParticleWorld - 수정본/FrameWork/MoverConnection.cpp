#include "MoverConnection.h"

MoverConnection::MoverConnection() {
	m_forces = new ParticleForceRegistry();
	m_gravity = new ParticleGravity(Vector3(0, -9.8, 0));


	//°ø»ý¼º 
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
}

void MoverConnection::update(float duration) {
	m_forces->updateForces(duration);

	for (unsigned int i = 0; i < m_movers.size(); i++) {
		m_movers[i]->update(duration);
	}
}