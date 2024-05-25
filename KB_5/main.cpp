#include "CL_application.h"
int main()
{
	CL_application application(nullptr);
	application.build_tree_obj();
	return(application.exec_app());
}