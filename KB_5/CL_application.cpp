#include "CL_application.h"
#include <stack>
#include "CL_base.h"
CL_application::CL_application(CL_base* p_head_obj) :CL_base(p_head_obj) {}
void CL_application::build_tree_obj() {
	CL_base* p_sub = this;

	this->set_name("Systeam");

	new CL_reader(this, "Reader");
	new CL_calc(this, "Calc");
	new CL_cancel(this, "Cancel");
	new CL_screen(this, "Screen");
	new CL_shift(this, "Shift");

	this->set_connection(SIGNAL_D(CL_application::signal_app_to_reader),
		get_sub_obj("Reader"),
		HANDLER_D(CL_reader::handler_reader_from_app));
	get_sub_obj("Reader")->set_connection(SIGNAL_D(CL_reader::signal_reader_to_all),
		this,
		HANDLER_D(CL_application::handler_app_from_reader));
	get_sub_obj("Reader")->set_connection(SIGNAL_D(CL_reader::signal_reader_to_all),
		get_sub_obj("Cancel"),
		HANDLER_D(CL_cancel::handler_cancel_from_reader));
	get_sub_obj("Reader")->set_connection(SIGNAL_D(CL_reader::signal_reader_to_all),
		get_sub_obj("Calc"),
		HANDLER_D(CL_calc::handler_calc_from_reader));
	get_sub_obj("Reader")->set_connection(SIGNAL_D(CL_reader::signal_reader_to_all),
		get_sub_obj("Shift"),
		HANDLER_D(CL_shift::handler_shift_from_reader));
	get_sub_obj("Shift")->set_connection(SIGNAL_D(CL_shift::signal_shift_to_screen),
		get_sub_obj("Screen"),
		HANDLER_D(CL_screen::handler_screen_from_all));
	get_sub_obj("Calc")->set_connection(SIGNAL_D(CL_calc::signal_calc_to_screen),
		get_sub_obj("Screen"),
		HANDLER_D(CL_screen::handler_screen_from_all));
	get_sub_obj("Reader")->set_connection(SIGNAL_D(CL_reader::signal_reader_to_all),
		get_sub_obj("Screen"),
		HANDLER_D(CL_screen::handler_screen_from_all));	
}

void CL_application::signal_app_to_reader(string& msg) {}

void CL_application::handler_app_from_reader(string msg) {
	if (msg == "Off")
		s_cmd = "Off";
}

int CL_application::exec_app() {

	string msg;
	s_cmd = "";
	this->turn_on_tree();

	int i_result = 0;
	string s_expression = "";
	string s_operation = "";
	string s_operand_2 = "";

	while (s_cmd != "Off") {
		emit_signal(SIGNAL_D(CL_application::signal_app_to_reader), s_cmd);
	}
	return 0;
}