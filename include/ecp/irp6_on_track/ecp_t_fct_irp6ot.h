#if !defined(_ECP_T_FCT_IRP6OT_H)
#define _ECP_T_FCT_IRP6OT_H

#include "ecp/common/ecp_task.h"

class ecp_task_fct_irp6ot: public ecp_task  {

public:
	// KONSTRUKTORY
	ecp_task_fct_irp6ot(configurator &_config);

	// methods for ECP template to redefine in concrete classes
	void task_initialization(void);
	void main_task_algorithm(void);

	void catch_signal(int sig);

};

#endif
