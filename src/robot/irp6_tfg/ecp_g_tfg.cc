/**
 * @file
 * @brief ECP force generators
 * - class declaration
 * @author yoyek
 * @date 01.01.2002
 *
 * $URL: https://segomo.elka.pw.edu.pl/svn/mrrocpp/base/trunk/src/generator/ecp/ecp_g_force.cc $
 * $LastChangedRevision: 3198 $
 * $LastChangedDate: 2009-12-16 23:17:30 +0100 (Wed, 16 Dec 2009) $
 * $LastChangedBy: yoyek $
 */

// -------------------------------------------------------------------------
//                            ecp.cc
//            Effector Control Process (lib::ECP) - force methods
// Funkcje do tworzenia procesow ECP z wykorzystaniem sily
//
// Ostatnia modyfikacja: 2004r.
// -------------------------------------------------------------------------

#include <cstdio>
#include <fstream>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <cmath>

#include "base/lib/typedefs.h"
#include "base/lib/impconst.h"
#include "base/lib/com_buf.h"

#include "base/lib/sr/srlib.h"
#include "robot/irp6_tfg/ecp_g_tfg.h"
#include "base/ecp/ecp_task.h"
#include "base/ecp/ecp_robot.h"

namespace mrrocpp {
namespace ecp {
namespace irp6_tfg {
namespace generator {

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // ///////////////////
//
// 			tfg_generator
//
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // ///////////////////


tfg::tfg(common::task::task& _ecp_task, int step) :
	generator(_ecp_task), step_no(step)
{
}

bool tfg::first_step()
{

	// parameters copying
	get_mp_ecp_command();

	sr_ecp_msg.message("tfg first step");
	the_robot->ecp_command.instruction.instruction_type = lib::GET;
	the_robot->ecp_command.instruction.get_type = ARM_DEFINITION;
	the_robot->ecp_command.instruction.set_type = ARM_DEFINITION;
	the_robot->ecp_command.instruction.set_arm_type = lib::JOINT;
	the_robot->ecp_command.instruction.get_arm_type = lib::JOINT;
	the_robot->ecp_command.instruction.motion_type = lib::ABSOLUTE;
	the_robot->ecp_command.instruction.interpolation_type = lib::MIM;
	the_robot->ecp_command.instruction.motion_steps = step_no;
	the_robot->ecp_command.instruction.value_in_step_no = step_no - 2;

	return true;
}
// --------------------------------------------------------------------------


// --------------------------------------------------------------------------
bool tfg::next_step()
{
	sr_ecp_msg.message("tfg next step");
	// static int count;
	// struct timespec start[9];
	if (check_and_null_trigger()) {
		return false;
	}

	the_robot->ecp_command.instruction.instruction_type = lib::SET;

	the_robot->ecp_command.instruction.arm.pf_def.arm_coordinates[0] = mp_ecp_command.desired_position;
	the_robot->ecp_command.instruction.motion_steps = 1000;
	the_robot->ecp_command.instruction.value_in_step_no = 998;

	std::stringstream ss(std::stringstream::in | std::stringstream::out);
	ss << "position: " << the_robot->reply_package.arm.pf_def.arm_coordinates[0] << ", node_counter:  " << node_counter;

	sr_ecp_msg.message(ss.str().c_str());

	if (node_counter == 2) {
		return false;
	}

	// 	wstawienie nowego przyrostu pozyji do przyrostowej trajektorii ruchu do zapisu do pliku
	lib::Homog_matrix tmp_matrix(the_robot->reply_package.arm.pf_def.arm_frame);

	return true;

}

void tfg::create_ecp_mp_reply()
{

}

void tfg::get_mp_ecp_command()
{
	memcpy(&mp_ecp_command, ecp_t.mp_command.ecp_next_state.mp_2_ecp_next_state_string, sizeof(mp_ecp_command));

}

} // namespace generator
} // namespace irp6_tfg
} // namespace ecp
} // namespace mrrocpp
