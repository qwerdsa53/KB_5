#pragma once
#include "CL_base.h"
#include "CL_calc.h"
#include "CL_cancel.h"
#include "CL_reader.h"
#include "CL_screen.h"
#include "CL_shift.h"
class CL_application : public CL_base {
	string s_cmd;
public:
	CL_application(CL_base* p_head_obj);
	void build_tree_obj();
	void signal_app_to_reader(string& msg);
	void handler_app_from_reader(string msg);

	int exec_app();

};
