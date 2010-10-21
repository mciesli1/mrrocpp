/*
 * ecp_t_objectfollower_ib.cc
 *
 *  Created on: Apr 21, 2010
 *      Author: mboryn
 */

#include "ecp_t_objectfollower_ib.h"

#include "../defines.h"

#ifdef ROBOT_P
#include "robot/irp6p_m/ecp_r_irp6p_m.h"
#endif

#ifdef ROBOT_OT
#include "robot/irp6ot_m/ecp_r_irp6ot_m.h"
#endif


#include "../ecp_mp_g_visual_servo_tester.h"



using namespace mrrocpp::ecp::common::generator;
using namespace logger;

namespace mrrocpp {

namespace ecp {

namespace common {

namespace task {

ecp_t_objectfollower_ib::ecp_t_objectfollower_ib(mrrocpp::lib::configurator& configurator) :
	task(configurator)
{
#ifdef ROBOT_P
	ecp_m_robot = new ecp::irp6p_m::robot(*this);
#endif
#ifdef ROBOT_OT
	ecp_m_robot = new ecp::irp6ot_m::robot(*this);
#endif
	char config_section_name[] = { "[object_follower_ib]" };

	log_dbg_enabled = true;

	shared_ptr <position_constraint> cube(new cubic_constraint(configurator, config_section_name));

	log_dbg("ecp_t_objectfollower_ib::ecp_t_objectfollower_ib(): 1\n");
	reg = shared_ptr <visual_servo_regulator> (new regulator_p(configurator, config_section_name));

	log_dbg("ecp_t_objectfollower_ib::ecp_t_objectfollower_ib(): 2\n");
	vs = shared_ptr <visual_servo> (new ib_eih_visual_servo(reg, config_section_name, configurator));

	term_cond = shared_ptr <termination_condition> (new object_reached_termination_condition(configurator, config_section_name));

	log_dbg("ecp_t_objectfollower_ib::ecp_t_objectfollower_ib(): 3\n");
	sm = shared_ptr <single_visual_servo_manager> (new single_visual_servo_manager(*this, config_section_name, vs));

	log_dbg("ecp_t_objectfollower_ib::ecp_t_objectfollower_ib(): 4\n");
	sm->add_position_constraint(cube);

	//sm->add_termination_condition(term_cond);
	//log_dbg("ecp_t_objectfollower_ib::ecp_t_objectfollower_ib(): 5\n");

	sm->configure();
	log_dbg("ecp_t_objectfollower_ib::ecp_t_objectfollower_ib(): 6\n");
}

ecp_t_objectfollower_ib::~ecp_t_objectfollower_ib()
{
	delete ecp_m_robot;
}

void ecp_t_objectfollower_ib::main_task_algorithm(void)
{
	while (1) {
		get_next_state();
		if (mp_2_ecp_next_state_string == mrrocpp::ecp_mp::generator::ECP_GEN_VISUAL_SERVO_TEST) {
			sm->Move();
		} else {
			log("ecp_t_objectfollower_ib::main_task_algorithm(void) mp_2_ecp_next_state_string: \"%s\"\n", mp_2_ecp_next_state_string.c_str());
		}
	}

	ecp_termination_notice();
}

task* return_created_ecp_task(lib::configurator &config)
{
	return new ecp_t_objectfollower_ib(config);
}

} // namespace task

}//namespace common

}//namespace ecp

}//namespace mrrocpp
