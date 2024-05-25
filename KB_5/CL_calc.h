#pragma once
#include "CL_base.h"
class CL_calc : public CL_base
{
public:
	CL_calc(CL_base* p_head_obj, string s_name);
	void signal_f(string& msg);
	void handler_f(string msg);
	int get_class_num();

	void handler_calc_from_reader(string msg);
	void signal_calc_to_screen(string& msg);
};

