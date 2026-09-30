#include "Fireworks.h"
#include <random.h>
#include <iostream>
#define SIZE 5
#define SIZE_SECOND 10
using namespace cyclone;

Fireworks::Fireworks(){
	FireCountInit = 0;
	FireCountChild = 0;
	//시작과 동시에 룰 생성
	// 자식불꽃, 최소나이, 최대나이, 최소 범위, 최대 범위, 댐핑, 생성갯수
	
	//불꽃안에 불꽃
	m_rule[0].setParameters(1, 2.5f, 3.5f, Vector3(-17, -20, -17), Vector3(17, 20, 17), 0.1, 150);	//불꽃안에 불꽃
	m_rule[1].setParameters(1, 2.5f, 3.5f, Vector3(-52, -60, -52), Vector3(52, 60, 52), 0.1, 200);	//둥글게 나옴
}

Fireworks::~Fireworks() {

}

void Fireworks::update(float duration) {
	vector<Fire*>::iterator iter;	//반복연산
	vector<Fire*> remove;

	//조건에 맞을때 삭제하는 for loop
	for (iter = fireworks.begin(); iter != fireworks.end();) {
		//fireworks안의 모든 fire에 대해
		Fire* m = *iter;	//하나 하나씩 꺼내
		Vector3 pos = m->m_particle->getPosition();
		if (m->m_type == 1) {
			m->putHistory();
		}
		if (m->update(duration)) {	//m_age가 0보다 작을때
			if (m->m_type == 0 ) { //init fire이면
				remove.push_back(m); //child 생성을 위한 remove저장
			}
			iter = fireworks.erase(iter);	//fireworks에서 삭제함
		}
		else if (pos.y < 0) {
			iter = fireworks.erase(iter);	//fireworks에서 삭제함
		}
		else {
			++iter;
		}
	}

	for (iter = remove.begin(); iter != remove.end(); ++iter) {
		//fireworks안의 모든 fire에 대해
		Fire* m = *iter;	//하나 하나씩 꺼내
		creat(m);
	}

}	//Fire의 생성/ 소멸/업데이트

void Fireworks::creat() {
	static Random crandom;
	int ageDouble = 2.0f;
	if (FireCountInit == 0) {	//생성 주기 체크
		for (int i = 1; i <= SIZE; i++) {
			Fire* m = new Fire(0, FireCountInit);
			Vector3 Vel = m->m_particle->getVelocity();
			Vel *= i * 1.85;	//위치 위로 점점 이동
			m->m_particle->setVelocity(Vel);
			m->m_age += ageDouble;
			fireworks.push_back(m);
			ageDouble += 1.0f;	//늦게 터질 수록 늦게 사라지도록 조절
		}
	}
	if (FireCountInit == 1) { //수정
		for (int i = 1; i <= SIZE_SECOND; i++) {
			Fire* m = new Fire(0, FireCountInit);
			fireworks.push_back(m);
		}
	}
	FireCountInit++;
	if (FireCountInit == 2) FireCountInit = 0; //반복
}	//init Fire생성

void Fireworks::creat(Fire* parent) {
	int ageDouble = 0.2f;
	if (FireCountChild == 0) {
		for (int i = 0; i < m_rule[1].payloadCount; i++) {
			Fire* m = new Fire(1, FireCountChild);
			Vector3 pos = parent->m_particle->getPosition();
			m->m_particle->setPosition(pos);
			m->m_color = parent->m_color; //기존 색상 가져오기
			m->setRule(&m_rule[1]);	//룰 적용
			fireworks.push_back(m);
		}

		for (int i = 0; i < m_rule[0].payloadCount; i++) {
			Fire* m = new Fire(1, FireCountChild);
			Vector3 pos = parent->m_particle->getPosition();
			m->m_particle->setPosition(pos);
			m->m_color = parent->m_color * 2;	//기존 색상 보다 더 밝게
			m->setRule(&m_rule[0]);
			fireworks.push_back(m);
		}
	}
}	//Child Fire 생성

void Fireworks::draw(int shadow) {
	if (shadow) {
		for (int i = 0; i < getSize(); i++) {
			fireworks[i]->draw(1); //fireworks의 각 Fire들의 draw를 호출
		}
	}
	else {
		for (int i = 0; i < getSize(); i++) {
			fireworks[i]->draw(0); //fireworks의 각 Fire들의 draw를 호출
			if (fireworks[i]->m_type == 1) {
				fireworks[i]->drawHistory();
			}
		}
	}

}	//그리기

int Fireworks::getSize() {
	int size = fireworks.size();
	return size;
}
