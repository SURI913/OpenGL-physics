#include "Bridge.h"
#include <iostream>

#define SUPPORT_COUNT 12
#define ROD_COUNT 6
#define CABLE_COUNT 10


Bridge::Bridge(MoverConnection mover) {

    //공추가
    for (int i = 0; i < SUPPORT_COUNT; i++) {
        Mover* a = new Mover(mover.m_movers[i]->m_particle->getPosition());
        m_world->getParticles().push_back(a->m_particle);  //2개이상의 파티클이 존재할 경우도 하나하나씩 저장
    }

    m_world = new cyclone::ParticleWorld(12 * 10);
    supports = new cyclone::ParticleCableConstraint[SUPPORT_COUNT];
    int count = 0;
    for (int i = 0; i < 12; i++) {
        m_world->getParticles().push_back(mover.m_movers[i]->m_particle);
        supports->particle = (mover.m_movers[i]->m_particle);
        supports->anchor = Vector3(mover.m_movers[i]->m_particle->getPosition());
        real lenght;
        if (count < 6) { lenght = cyclone::real(count / 2) * 0.5f + 3.0f; }
        else { lenght = 5.5f - cyclone::real(count / 2) * 0.5f; }
        supports->maxLength = lenght;
        supports->restitution = 0.5f;
        m_world->getContactGenerators().push_back(&supports[i]);
    }

    //Rod 연결
    Rod = new cyclone::ParticleRod[ROD_COUNT];
    for (unsigned i = 0; i < ROD_COUNT; i++)
    {
        Rod[i].particle[0] = mover.m_movers[i * 2]->m_particle;
        Rod[i].particle[1] = mover.m_movers[i * 2 + 1]->m_particle;
        Rod[i].length = 2;
        m_world->getContactGenerators().push_back(&Rod[i]);
    }

    //Cable 연결
    Cable = new cyclone::ParticleCable[CABLE_COUNT];
    for (unsigned i = 0; i < CABLE_COUNT; i++)
    {
        Cable[i].particle[0] = mover.m_movers[i]->m_particle;
        Cable[i].particle[1] = mover.m_movers[i + 2]->m_particle;
        Cable[i].maxLength = 1.9f;
        Cable[i].restitution = 0.3f;
        m_world->getContactGenerators().push_back(&Cable[i]);
    }

    m_resolver = new cyclone::ParticleContactResolver(10);	//반복횟수?
    m_world = new cyclone::ParticleWorld(3, 10);  //3 : # of contacts, 10 : looping count (시뮬레이션에 따라 설정되어야 함)


    //m_world에 파티클 전부 추가?
    //for (int i = 0; i < SUPPORT_COUNT; i++) {
    //    Mover* a = new Mover(mover.m_movers[i]->m_particle->getPosition());
    //    m_world->getParticles().push_back(a->m_particle);  //2개이상의 파티클이 존재할 경우도 하나하나씩 저장
    //}

    cyclone::MyGroundContact* c = new cyclone::MyGroundContact();

    for each (Mover * m in mover.m_movers) {
        c->init(m->m_particle, 0.5);
    }
    m_world->getContactGenerators().push_back(c);

    m_resolver = new cyclone::ParticleContactResolver(10);

    std::cout << "끈연결" << std::endl;
}

void Bridge::update(float duration) {
    m_world->runPhysics(duration);
}

void Bridge::draw(int shadow)
{



    glBegin(GL_LINES);

    if (shadow)
        glColor3f(0.2, 0.2, 0.2);
    else
        glColor3f(0, 0, 1);
    for (unsigned i = 0; i < ROD_COUNT; i++)
    {
        cyclone::Particle** particles = Rod[i].particle;
        const cyclone::Vector3& p0 = particles[0]->getPosition();
        const cyclone::Vector3& p1 = particles[1]->getPosition();
        glVertex3f(p0.x, p0.y, p0.z);
        glVertex3f(p1.x, p1.y, p1.z);
    }

    if (shadow)
        glColor3f(0.2, 0.2, 0.2);
    else
        glColor3f(0, 1, 0);
    for (unsigned i = 0; i < CABLE_COUNT; i++)
    {
        cyclone::Particle** particles = Cable[i].particle;
        const cyclone::Vector3& p0 = particles[0]->getPosition();
        const cyclone::Vector3& p1 = particles[1]->getPosition();
        glVertex3f(p0.x, p0.y, p0.z);
        glVertex3f(p1.x, p1.y, p1.z);
    }

    if (shadow)
        glColor3f(0.2, 0.2, 0.2);
    else
        glColor3f(0.7f, 0.7f, 0.7f);
    for (unsigned i = 0; i < SUPPORT_COUNT; i++)
    {
        const cyclone::Vector3& p0 = supports[i].particle->getPosition();
        const cyclone::Vector3& p1 = supports[i].anchor;
        glVertex3f(p0.x, p0.y, p0.z);
        glVertex3f(p1.x, p1.y, p1.z);
    }
    glEnd();

    glLineWidth(1.0);
}