// -------------------------------------------------------------------------
//                            ecp_g_legobrick.h dla QNX6
// Generator dla zadania legobrick
// 
// -------------------------------------------------------------------------

#if !defined(_ECP_GEN_LEGOBRICK_CONV_H)
#define _ECP_GEN_LEGOBRICK_CONV_H
#include "sys/time.h"

#include "common/com_buf.h"		// trajectory_description

#include "ecp/common/ecp_generator.h"

namespace mrrocpp {
namespace ecp {
namespace conveyor {

// --------------------------------------------------------------------------
// Generator trajektorii prostoliniowej dla zadan yoyka z wodzeniem za nos
class conveyor_incremental_move: public common::generator::ecp_generator {
	double move_length;
	double current_pose;
	double next_pose;
	double begin_pose;
	int stepno;
	int first;
	int step;
	struct timeval acctime;
public:	
	trajectory_description td;
	
	// konstruktor
	conveyor_incremental_move(common::task::ecp_task& _ecp_task, double inc_move);  
	
	virtual bool first_step ();

	virtual bool next_step ();

}; // end:
// --------------------------------------------------------------------------

} // namespace conveyor
} // namespace ecp
} // namespace mrrocpp

#endif
