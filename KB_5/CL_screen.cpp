#include "CL_screen.h"
CL_screen::CL_screen(CL_base* p_head_obj, string s_name) : CL_base(p_head_obj, s_name) {}

//int CL_screen::get_class_num() {
//	return 6;
//}
//
//void CL_screen::signal_f(string& msg) {
//	cout << endl << "Signal from " << GetPath();
//	msg += " (class: 6)";
//}
//
//void CL_screen::handler_f(string msg) {
//	cout << endl << "Signal to " << GetPath() << " Text:  " << msg;
//}

void CL_screen::handler_screen_from_all(string msg) {
	ostringstream ss;
	if (msg == "Off")
		return;
	if (msg == "Division by zero") {
		cout << get_head()->s_expression << "     Division by zero\n";
		get_head()->s_expression = "0";
		get_head()->i_result = 0;
		return;
	}
	if (msg == "SHOWTREE") {
		this->get_head()->print_tree();
		return;
	}
	if (msg == "Overflow") {
		cout << get_head()->s_expression << "     Overflow\n";
		get_head()->s_expression = "0";
		get_head()->i_result = 0;
		return;
	}
	if (msg == "C" || msg == "+" || msg == "-" || msg == "*" || msg == "/" || msg == "%" || msg == ">>" || msg == "<<")
		return;
	ss << uppercase << setw(4) << setfill('0') << hex << (get_head()->i_result & 0xFFFF);
	cout << get_head()->s_expression << "     HEX " << ss.str();
	cout << "  DEC " << get_head()->i_result;
	cout << "  BIN ";
	bitset<16> binary(get_head()->i_result);
	string binaryStr = binary.to_string();
	for (int i = 0; i < binaryStr.length(); i++) {
		if (i != 0 && i % 4 == 0) {
			cout << " ";
		}
		cout << binaryStr[i];
	}
	cout << endl;
}
