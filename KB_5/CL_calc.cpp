#include "CL_calc.h"
CL_calc::CL_calc(CL_base* p_head_obj, string s_name) : CL_base(p_head_obj, s_name) {}

//int CL_calc::get_class_num() {
//	return 3;
//}
//
//void CL_calc::signal_f(string& msg) {
//	cout << endl << "Signal from " << GetPath();
//	msg += " (class: 3)";
//}
//
//void CL_calc::handler_f(string msg) {
//	cout << endl << "Signal to " << GetPath() << " Text:  " << msg;
//}
void CL_calc::handler_calc_from_reader(string msg) {
	bool flag = false;
	int res;
	if (msg == "+")
	{
		res = get_head()->i_result + stoi(get_head()->s_operand_2);
		if(res < -32678 || res > 32678)
		{
			EmitSignal(SIGNAL_D(CL_calc::signal_calc_to_screen), "Overflow");
			return;
		}
		else {
			get_head()->i_result = get_head()->i_result + atoi((get_head()->s_operand_2).c_str());
			flag = true;
		}
	}
	else if (msg == "-")
	{	
		res = get_head()->i_result - stoi(get_head()->s_operand_2);
		if (res < -32678 || res > 32678)
		{
			EmitSignal(SIGNAL_D(CL_calc::signal_calc_to_screen), "Overflow");
			return;
		}
		else {
			get_head()->i_result = get_head()->i_result - atoi((get_head()->s_operand_2).c_str());
			flag = true;
		}
	}
	else if (msg == "*")
	{
		res = get_head()->i_result * stoi((get_head()->s_operand_2));
		if (res < -32678 || res > 32678)
		{
			EmitSignal(SIGNAL_D(CL_calc::signal_calc_to_screen), "Overflow");
			return;
		}
		else {
			get_head()->i_result = get_head()->i_result * atoi((get_head()->s_operand_2).c_str());
			flag = true;
		}
	}
	else if (msg == "/")
	{
		if (get_head()->s_operand_2 == "0") {
			EmitSignal(SIGNAL_D(CL_calc::signal_calc_to_screen), "Division by zero");
			return;
		}
		else {
			flag = true;
			get_head()->i_result = get_head()->i_result / atoi((get_head()->s_operand_2).c_str());
		}
	}
	else if (msg == "%")
	{
		flag = true;
		get_head()->i_result = get_head()->i_result % atoi((get_head()->s_operand_2).c_str());
	}
	else if (msg == "SHOWTREE") {
		EmitSignal(SIGNAL_D(CL_calc::signal_calc_to_screen), msg);
		return;
	}
	if(msg != "C" && msg != "Off" && flag)
		EmitSignal(SIGNAL_D(CL_calc::signal_calc_to_screen), std::to_string(get_head()->i_result));
}
void CL_calc::signal_calc_to_screen(string& msg) {}
