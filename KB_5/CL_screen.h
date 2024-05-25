#include <sstream>
#include <iomanip>
#include <string>
#include <bitset>
#include "CL_base.h"
using namespace std;
class CL_screen : public CL_base
{
public:
	CL_screen(CL_base* p_head_obj, string s_name);
	void handler_screen_from_all(string msg);
};
