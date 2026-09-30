#include "Mover.h"
#include "MyGlWindow.h"

using namespace cyclone;

void Mover::setPos(float posX, float posY, float posZ) {
	m_particle->setPosition( posX, posY, posZ);
}

void Mover::setVel(float velX, float velY, float velZ) {
	m_particle->setVelocity(velX, velY, velZ);
}

Mover :: Mover() {

	size = 2.0f; //공 크기

	//파티클을 사용해 발사체를 만든다
	m_particle = new Particle(); //클래스 동적 할당?
	m_particle->setPosition(5.0f, size, 5.0f);	//초기 위치
	m_particle->setVelocity(0.0f, 30.0f, 40.0f);	//초기 속도
	m_particle->setMass(200.0f);	//질량
	m_particle->setDamping(0.99f);	//댐핑
	m_particle->setAcceleration(0.0f, -20.0f, 0.0f);	//초기 가속도

};

void Mover:: update(float duration) {
	cyclone::Vector3 wind(1.0f, 0, 0);	// x축으로 부는 바람
	m_particle->addForce(wind);//공간 안에 힘 부여. 중력가속도 + 힘으로 공이 튀겨진다.
	
	m_particle->integrate(duration); //적분
}
void Mover:: stop() {

}
void Mover:: draw(int shadow) {
	Vector3 position;
	m_particle->getPosition(&position);		//현재 파티클의 위치를 얻은 후 position으로 설정
	if (shadow)
	{
		glTranslatef(position.x, position.y, position.z);
		glColor3f(0.1f, 0.1f, 0.1f); //그림자 색상
		glutSolidSphere(size, 30, 30); //만드는것
	}
	else
	{
		glTranslatef(position.x, position.y, position.z);
		glColor3f(1.0f, 0.0f, 0.0f); // 오브젝트 색상
		glutSolidSphere(size, 30, 30); //만드는것
	}
	
}