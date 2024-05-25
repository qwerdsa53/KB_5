#pragma once
#include "CL_base.h"
class CL_cancel : public CL_base
{
public:
	CL_cancel(CL_base* p_head_obj, string s_name);
	void handler_cancel_from_reader(string msg);
};

