#pragma once
#include "CL_base.h"
using namespace std;
class CL_shift : public CL_base
{
public:
	CL_shift(CL_base* p_head_obj, string s_name);
	void handler_shift_from_reader(string msg);
	void signal_shift_to_screen(string& msg);
};

