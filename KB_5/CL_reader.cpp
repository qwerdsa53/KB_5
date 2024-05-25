#include "CL_reader.h"
#include "CL_reader.h"
CL_reader::CL_reader(CL_base* p_head_obj, string s_name) : CL_base(p_head_obj, s_name) {
}

//int CL_reader::get_class_num() {
//	return 2;
//}
//void CL_reader::signal_f(string& msg) {
//	cout << endl << "Signal from " << GetPath();
//	msg += " (class: 2)";
//}
//
//void CL_reader::handler_f(string msg) {
//	cout << endl << "Signal to " << GetPath() << " Text:  " << msg;
//}

void CL_reader::handler_reader_from_app(string msg) {
	string s_cmd;
	cin >> s_cmd;

	if (s_cmd == "C" || s_cmd == "Off") {
		EmitSignal(SIGNAL_D(CL_reader::signal_reader_to_all), s_cmd);
	}
	else if (s_cmd == "+" || s_cmd == "-" || s_cmd == "*" || s_cmd == "/" || s_cmd == "%" || s_cmd == ">>" || s_cmd == "<<") {
		get_head()->s_operation = s_cmd;
		get_head()->s_expression += " " + s_cmd;

		cin >> get_head()->s_operand_2;
		get_head()->s_expression += " " + get_head()->s_operand_2;
		EmitSignal(SIGNAL_D(CL_reader::signal_reader_to_all), s_cmd);
	}
	else if (s_cmd == "SHOWTREE")
		EmitSignal(SIGNAL_D(CL_reader::signal_reader_to_all), s_cmd);
		//this->get_head()->print_tree();
	else {
		//if (stoi(s_cmd) < -32768 || stoi(s_cmd) > 32767) {
		//	EmitSignal(SIGNAL_D(CL_reader::signal_reader_to_all), "Overflow");
		//	return;
		//}
		get_head()->s_expression = s_cmd;
		get_head()->i_result = atoi((get_head()->s_expression).c_str());
	}
}
void CL_reader::signal_reader_to_all(string& msg) {}