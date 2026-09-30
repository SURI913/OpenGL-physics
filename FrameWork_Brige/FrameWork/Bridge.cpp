#include "Bridge.h"
#include <iostream>

#define SUPPORT_COUNT 12
#define ROD_COUNT 6
#define CABLE_COUNT 11


Bridge::Bridge(MoverConnection mover) {
    m_world = new cyclone::ParticleWorld(SUPPORT_COUNT * 10);
    supports = new cyclone::ParticleCableConstraint[SUPPORT_COUNT];
    for (unsigned i = 0; i < SUPPORT_COUNT; i++) {
        //파티클 집어넣기
        m_world->getParticles().push_back(mover.m_movers[i]->m_particle);

        supports[i].particle = (mover.m_movers[i]->m_particle);
        Vector3 pos (mover.m_movers[i]->m_particle->getPosition());
        supports[i].anchor = Vector3(pos.x, 10, pos.z);
        real lenght;
        if (i == 6 || i ==0 || i == 5 || i ==11) { lenght = 3.0f; }
        else if (i == 7 || i == 1 || i == 4 || i == 10) { lenght = 3.5f; }
        else { lenght = 4.0f; }
        supports[i].maxLength = lenght;
        supports[i].restitution = 0.5f;
        m_world->getContactGenerators().push_back(&supports[i]);
    }

    //Rod 연결
    Rod = new cyclone::ParticleRod[ROD_COUNT];
    for (unsigned i = 0; i < ROD_COUNT; i++)
    {
        Rod[i].particle[0] = mover.m_movers[i]->m_particle;
        Rod[i].particle[1] = mover.m_movers[i +6]->m_particle;
        Rod[i].length = 2;
        m_world->getContactGenerators().push_back(&Rod[i]);
    }

    //Cable 연결
    Cable = new cyclone::ParticleCable[CABLE_COUNT];
    for (unsigned i = 0; i < CABLE_COUNT; i++)
    {
        if (i < 5 || i > 5) {
            Cable[i].particle[0] = mover.m_movers[i]->m_particle;
            Cable[i].particle[1] = mover.m_movers[i + 1]->m_particle;
        }
        else {
            Cable[i].particle[0] = mover.m_movers[i]->m_particle;
            Cable[i].particle[1] = mover.m_movers[i]->m_particle;
        }
 
        Cable[i].maxLength = 3.0f;
        Cable[i].restitution = 0.1f;
        m_world->getContactGenerators().push_back(&Cable[i]);
    }

   /* cyclone::MyGroundContact* c = new cyclone::MyGroundContact();

    for each (Mover * m in mover.m_movers) {
        c->init(m->m_particle, 0.3);
    }
    m_world->getContactGenerators().push_back(c);

    m_resolver = new cyclone::ParticleContactResolver(10);*/

    std::cout << "끈연결" << std::endl;
}

void Bridge::update(float duration) {
    m_world->runPhysics(duration);
}

void Bridge::draw(int shadow)
{
    glLineWidth(3.0);

    //if (shadow)
    //    glColor3f(0.2, 0.2, 0.2);
    //else
    //    glColor3f(0.8, 0, 0);

    //int name = 1;
    ////std::cout << "오류 없지" << std::endl;
    //cyclone::ParticleWorld::Particles& particles = m_world->getParticles();
    //for (cyclone::ParticleWorld::Particles::iterator p = particles.begin(); p != particles.end(); p++)
    //{
    //    cyclone::Particle* particle = *p;
    //    const cyclone::Vector3& pos = particle->getPosition();
    //    glPushMatrix();
    //    glTranslatef(pos.x, pos.y, pos.z);
    //    if (!shadow)
    //        glLoadName(name);
    //    glutSolidSphere(0.2f, 20, 10);
    //    glPopMatrix();
    //    name++;
    //}



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