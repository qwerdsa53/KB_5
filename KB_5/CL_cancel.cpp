#include "CL_cancel.h"
CL_cancel::CL_cancel(CL_base* p_head_obj, string s_name) : CL_base(p_head_obj, s_name) {}

//int CL_cancel::get_class_num() {
//	return 5;
//}
//
//void CL_cancel::signal_f(string& msg) {
//	cout << endl << "Signal from " << GetPath();
//	msg += " (class: 5)";
//}
//
//void CL_cancel::handler_f(string msg) {
//	cout << endl << "Signal to " << GetPath() << " Text:  " << msg;
//}
void CL_cancel::handler_cancel_from_reader(string msg) {
	if (msg == "C") {
		s_expression = "";
		s_operation = "";
		s_operand_2 = "";
		i_result = 0;
	}
}