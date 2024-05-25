#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <queue>
//макросы для преобразования имени метода в указатель на член-метод соотвтетсвующего типа
#define SIGNAL_D(signal_f) (TYPE_SIGNAL) (&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER) (&handler_f)
using namespace std;
class CL_base;
typedef void (CL_base::*TYPE_SIGNAL) (string& message);
typedef void (CL_base::*TYPE_HANDLER) (string message);
struct Connection {
	TYPE_SIGNAL Signal;
	TYPE_HANDLER Handler;
	CL_base* Target;
};
class CL_base
{
	string s_name;
	CL_base* p_head_obj;
	vector<CL_base*> p_sub_obj;
	int readyInd = 0;
	vector <Connection*> connections;
public:
	int i_result;
	string s_expression;
	string s_operation;
	string s_operand_2;
	CL_base(CL_base* p_head_obj, string s_name = "Base object");
	bool set_name(string);
	string get_name();
	CL_base* get_head();
	CL_base* get_root();
	CL_base* get_sub_obj(string);
	void print_tree(int level = 0);
	void set_ready_ind(int state);
	~CL_base();
	void set_connection(TYPE_SIGNAL, CL_base*, TYPE_HANDLER);
	void emit_signal(TYPE_SIGNAL, string);
	void DeleteLinks(CL_base*);
	void turn_on_tree();
};

