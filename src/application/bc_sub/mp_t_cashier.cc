/*!
 * @file
 * @brief File contains cashier mp_task class definition of barcode localization and reading application.
 * @author Marcin Cieslik
 *
 */

#include <iostream>
#include <sstream>

#include "base/mp/mp_task.h"
#include "base/mp/MP_main_error.h"
#include "mp_t_cashier.h"
#include "base/lib/mrmath/mrmath.h"

#include "robot/irp6_tfg/dp_tfg.h"

#include "application/bc_sub/ecp_mp_st_servomove.h"
#include "application/bc_sub/ecp_mp_st_codescan.h"

#include "generator/ecp/ecp_mp_g_tfg.h"

#include "robot/irp6ot_m/mp_r_irp6ot_m.h"
#include "robot/irp6p_m/mp_r_irp6p_m.h"
#include "robot/irp6ot_tfg/mp_r_irp6ot_tfg.h"
#include "robot/irp6p_tfg/mp_r_irp6p_tfg.h"

namespace mrrocpp {
namespace mp {
namespace task {

task* return_created_mp_task(lib::configurator &_config)
{
	return new cashier(_config);
}

cashier::cashier(lib::configurator &_config) :
	task(_config)
{
}

// powolanie robotow w zaleznosci od zawartosci pliku konfiguracyjnego
void cashier::create_robots()
{
	ACTIVATE_MP_ROBOT(irp6ot_tfg);
	ACTIVATE_MP_ROBOT(irp6ot_m);
	ACTIVATE_MP_ROBOT(irp6p_tfg);
	ACTIVATE_MP_ROBOT(irp6p_m);
}

void cashier::main_task_algorithm(void)
{

	sr_ecp_msg->message("MAIN TASK ALGORITHM");

	lib::robot_name_t manipulator_name;
	lib::robot_name_t gripper_name;

	// ROBOT IRP6_ON_TRACK

		manipulator_name = lib::irp6p_m::ROBOT_NAME;
		if (config.value <int> ("is_irp6p_tfg_active", lib::UI_SECTION)) {
			gripper_name = lib::irp6p_tfg::ROBOT_NAME;
		}
		else;


	sr_ecp_msg->message("MP: PRZED SUB-ami");
	set_next_ecps_state(ecp_mp::sub_task::ECP_ST_SERVOMOVE, (int) 5, "", 0, 1, manipulator_name.c_str());
	run_extended_empty_gen_and_wait(1, 1, manipulator_name.c_str(), manipulator_name.c_str());

	set_next_ecps_state(ecp_mp::sub_task::ECP_ST_CODESCAN, (int) 5, "", 0, 1, manipulator_name.c_str());
	run_extended_empty_gen_and_wait(1, 1, manipulator_name.c_str(), manipulator_name.c_str());
	sr_ecp_msg->message("MP: PO SUBACH");

}

} // namespace task
} // namespace mp
} // namespace mrrocpp
