#include "CL_base.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

CL_base::CL_base(CL_base* p_head_obj, string s_name) :p_head_obj(p_head_obj), s_name(s_name)
{
	if (p_head_obj)
		p_head_obj->p_sub_obj.push_back(this);
}
bool CL_base::set_name(string name) {
	if (this->p_head_obj) {
		for (auto sub : this->p_head_obj->p_sub_obj)
			if (sub->get_name() == name) { return false; }
	}
	this->s_name = name;
	return true;
}
CL_base::~CL_base() {
	this->get_root()->DeleteLinks(this);
	for (auto sub : this->p_sub_obj)
		delete sub;
}
CL_base* CL_base::get_root() {
	if (p_head_obj)
		p_head_obj->get_root();
	return this;
}
string CL_base::get_name() { return s_name; }
CL_base* CL_base::get_head() { return p_head_obj; }



CL_base* CL_base::get_sub_obj(string name) {
	for (auto p_sub : this->p_sub_obj) {
		if (p_sub->get_name() == name)
			return p_sub;
	}
	return nullptr;
}


void CL_base::print_tree(int level) {
	if(level == 0)
		cout  << string(level * 4, ' ') << this->s_name;
	else
		cout << endl << string(level * 4, ' ') << this->s_name;

	for (auto sub : this->p_sub_obj)
		sub->print_tree(level + 1);
}

void  CL_base::set_ready_ind(int state) {
	if (state != 0) {
		CL_base* cur = this->p_head_obj;
		while (cur != nullptr && cur->readyInd != 0)
			cur = cur->p_head_obj;
		if (cur == nullptr)
			this->readyInd = state;
	}
	else {
		this->readyInd = state;
		for (auto sub : this->p_sub_obj)
			sub->set_ready_ind(state);
	}
}

void CL_base::set_connection(TYPE_SIGNAL pSignal, CL_base* pTarget, TYPE_HANDLER pHandler) {
	for (const auto& obj : connections) {
		if (obj->Signal == pSignal && obj->Target == pTarget && obj->Handler == pHandler)
			return;//соединение уже существует
	}
	//добавление нового соединения
	this->connections.push_back(new Connection{ pSignal, pHandler, pTarget });
}


void CL_base::emit_signal(TYPE_SIGNAL pSignal, string message) {
	if (this->readyInd) {
		//вызываем сигнал для текущего объекта
		(this->*pSignal)(message);
		//вызываем сигнал для всех связанных объектов
		for (auto elem : this->connections) {
			if (elem->Signal == pSignal && elem->Target->readyInd)
				(elem->Target->*elem->Handler)(message);
		}
	}
}

void CL_base::DeleteLinks(CL_base* pTarget) {
	//удаление соединений где Target равен pTarget из текущего объекта
	remove_if(this->connections.begin(), this->connections.end(), [pTarget](Connection* connection) {
		if (connection->Target == pTarget) {
			delete connection;
			return true;
		}
		return false;
		});
	//рекурсивное удаление соединений у подчиненных объектов
	for (auto pSub : this->p_sub_obj)
		pSub->DeleteLinks(pTarget);
}

void CL_base::turn_on_tree() {
	this->set_ready_ind(1);
	this->get_sub_obj("Reader")->set_ready_ind(1);
	this->get_sub_obj("Cancel")->set_ready_ind(1);
	this->get_sub_obj("Calc")->set_ready_ind(1);
	this->get_sub_obj("Screen")->set_ready_ind(1);
	this->get_sub_obj("Shift")->set_ready_ind(1);
}