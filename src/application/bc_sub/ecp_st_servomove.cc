/*!
 * @file
 * @brief File contains servomove definition
 * @author Marcin Cieslik
 *
 * @ingroup subtasks
 */

#include "base/lib/typedefs.h"
#include "base/lib/sr/srlib.h"
#include "ecp_st_servomove.h"
#include <iostream>


using namespace mrrocpp::ecp::common::generator;
using namespace logger;





namespace mrrocpp {
namespace ecp {
namespace common {
namespace sub_task {

servomove::servomove(task::task &_ecp_t) :
	sub_task(_ecp_t)
{

	char config_section_name[] = { "[object_follower_ib]" };

	log_dbg_enabled = true;

	shared_ptr <position_constraint> cube(new cubic_constraint(_ecp_t.config, config_section_name));

	reg = shared_ptr <visual_servo_regulator> (new regulator_p(_ecp_t.config, config_section_name));

	vs = shared_ptr <visual_servo> (new ib_eih_visual_servo(reg, config_section_name, _ecp_t.config));
	term_cond = shared_ptr <termination_condition> (new object_reached_termination_condition(_ecp_t.config, config_section_name));

	sm = shared_ptr <single_visual_servo_manager> (new single_visual_servo_manager(_ecp_t, config_section_name, vs)); //tu trzeba sprawdzic czy zamiast *this cos innego przejdzie

	sm->add_position_constraint(cube);

	sm->add_termination_condition(term_cond);
	log_dbg("ecp_t_objectfollower_ib::ecp_t_objectfollower_ib(): 5\n");



printf("TWORZE SERVOMOVE\n");
}

void servomove::conditional_execution()
{
	printf("JESTEM W SERVOMOVE\n");
	std::cout<<std::endl;


	sm->configure();
	sm->Move();


	//usuniecie tych rzeczy - zeby mozna bylo juz dzialac
	sm.reset();
	term_cond.reset();
	vs.reset();
	reg.reset();

	printf("PO SERVOMOVE\n");
	std::cout<<std::endl;
}

} // namespace sub_task

} // namespace common
} // namespace ecp
} // namespace mrrocpp
