#include "CL_cancel.h"
CL_cancel::CL_cancel(CL_base* p_head_obj, string s_name) : CL_base(p_head_obj, s_name) {}

void CL_cancel::handler_cancel_from_reader(string msg) {
	if (msg == "C") {
		get_head()->s_expression = "";
		get_head()->s_operation = "";
		get_head()->s_operand_2 = "";
		get_head()->i_result = 0;
	}
}