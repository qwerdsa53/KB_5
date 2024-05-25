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
	this->GetRoot()->DeleteLinks(this);
	for (auto sub : this->p_sub_obj)
		delete sub;
}
CL_base* CL_base::GetRoot() {
	if (p_head_obj)
		p_head_obj->GetRoot();
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

CL_base* CL_base::FindOnTree(string name) {
	CL_base* cur = this;
	while (cur->p_head_obj != nullptr) {
		cur = cur->p_head_obj;
	}
	return cur->FindOnBranch(name);
}

CL_base* CL_base::FindOnBranch(string name) {
	queue<CL_base*> q;
	CL_base* pFound = nullptr;
	q.push(this);
	while (!q.empty()) {
		if (q.front()->get_name() == name) {
			if (pFound == nullptr)
				pFound = q.front();
			else
				return nullptr;
		}
		for (auto sub : q.front()->p_sub_obj)
			q.push(sub);
		q.pop();
	}
	return pFound;
}


void CL_base::print_tree(int level) {
	if(level == 0)
		cout  << string(level * 4, ' ') << this->s_name;
	else
		cout << endl << string(level * 4, ' ') << this->s_name;

	for (auto sub : this->p_sub_obj)
		sub->print_tree(level + 1);
}
void CL_base::print_tree_ready(int level) {
	cout << endl << string(level * 4, ' ') << this->s_name
		<< (this->readyInd == 0 ? " is not ready" : " is ready");
	for (auto sub : this->p_sub_obj)
		sub->print_tree_ready(level + 1);
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
CL_base* CL_base::FindObjByPath(string path) {
	CL_base* pCur = this, * pRoot = this->GetRoot();
	if (path == "/")
		return pRoot;
	if (path == ".")
		return this;
	if (path.substr(0, 2) == "//")
		return this->FindOnTree(path.substr(2));
	if (path.substr(0, 1) == ".")
		return this->FindOnBranch(path.substr(1));
	if (path[0] == '/') {
		pCur = pRoot;
		path = path.substr(1);
	}
	size_t pos = 0;
	while ((pos = path.find('/')) != string::npos) {
		pCur = pCur->get_sub_obj(path.substr(0, pos));
		if (!pCur)
			return nullptr;
		path.erase(0, pos + 1);
	}
	return pCur->get_sub_obj(path);
}
bool CL_base::SetNewHead(CL_base* pNewHead) {
	if (pNewHead && pNewHead != this && !pNewHead->get_sub_obj(this->s_name) && this->p_head_obj)
	{
		CL_base* pCur = pNewHead;
		while (pCur) {
			pCur = pCur->p_head_obj;
			if (pCur == this)
				return false;
		}
		vector<CL_base*> curVec = this->p_head_obj->p_sub_obj;
		curVec.erase(find(curVec.begin(), curVec.end(), this));
		this->p_head_obj->p_sub_obj = curVec;
		pNewHead->p_sub_obj.push_back(this);
		this->p_head_obj = pNewHead;
		return true;
	}
	return false;
}
void CL_base::DeleteSub(string name) {
	CL_base* pSub = this->get_sub_obj(name);
	if (pSub) {
		vector<CL_base*> curVec = this->p_sub_obj;
		curVec.erase(find(curVec.begin(), curVec.end(), pSub));
		this->p_sub_obj = curVec;
		delete pSub;
	}
}
string CL_base::GetPath() {
	return this->p_head_obj ? this->p_head_obj->p_head_obj ? this->p_head_obj->GetPath() + "/" + this->s_name : this->p_head_obj->GetPath() + this->s_name : "/";
}

void CL_base::SetConnection(TYPE_SIGNAL pSignal, CL_base* pTarget, TYPE_HANDLER pHandler) {
	for (const auto& obj : connections) {
		if (obj->Signal == pSignal && obj->Target == pTarget && obj->Handler == pHandler)
			return;//соединение уже существует
	}
	//добавление нового соединения
	this->connections.push_back(new Connection{ pSignal, pHandler, pTarget });
}

void CL_base::DeleteConnection(TYPE_SIGNAL pSignal, CL_base* pTarget, TYPE_HANDLER pHandler) {
	remove_if(this->connections.begin(), this->connections.end(), [&](Connection* connection) {
		if (connection->Signal == pSignal && connection->Target == pTarget && connection->Handler == pHandler) {
			delete connection;
			return true;
		}
		return false;
		});
}

void CL_base::EmitSignal(TYPE_SIGNAL pSignal, string message) {
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
	//удаление соединений где Target равен pTargetЮ из текущего объекта
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
	CL_base* reader = this->get_sub_obj("Reader");
	CL_base* cancel = this->get_sub_obj("Cancel");
	CL_base* calc = this->get_sub_obj("Calc");
	CL_base* screen = this->get_sub_obj("Screen");
	reader->set_ready_ind(1);
	cancel->set_ready_ind(1);
	calc->set_ready_ind(1);
	screen->set_ready_ind(1);
}