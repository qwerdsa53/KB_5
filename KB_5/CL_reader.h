#pragma once
#include "CL_base.h"
class CL_reader : public CL_base
{
public:
	CL_reader(CL_base* p_head_obj, string s_name);
	void handler_reader_from_app(string msg);
	void signal_reader_to_all(string& msg);
};

