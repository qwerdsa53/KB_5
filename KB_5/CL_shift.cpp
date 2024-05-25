#include "CL_shift.h"
CL_shift::CL_shift(CL_base* p_head_obj, string s_name) : CL_base(p_head_obj, s_name) {}
void CL_shift::handler_shift_from_reader(string msg) {
	if(msg == ">>")
	{
		get_head()->i_result = get_head()->i_result >> atoi((get_head()->s_operand_2).c_str());
		EmitSignal(SIGNAL_D(CL_shift::signal_shift_to_screen), std::to_string(get_head()->i_result));
	}
	else if(msg == "<<")
	{
		get_head()->i_result = get_head()->i_result << atoi((get_head()->s_operand_2).c_str());
		EmitSignal(SIGNAL_D(CL_shift::signal_shift_to_screen), std::to_string(get_head()->i_result));
	}
}
void CL_shift::signal_shift_to_screen(string& msg) {}