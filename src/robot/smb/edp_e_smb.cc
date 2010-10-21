// ------------------------------------------------------------------------
// Proces:		EDP
// Plik:			edp_irp6m_effector.cc
// System:	QNX/MRROC++  v. 6.3
// Opis:		Robot IRp-6 na postumencie
//				- definicja metod klasy edp_irp6m_effector
//				- definicja funkcji return_created_efector()
//
// Autor:		tkornuta
// Data:		14.02.2007
// ------------------------------------------------------------------------

#include <cstdio>

#include "base/lib/typedefs.h"
#include "base/lib/impconst.h"
#include "base/lib/com_buf.h"
#include "base/lib/mrmath/mrmath.h"

// Klasa edp_irp6ot_effector.
#include "robot/smb/edp_e_smb.h"
#include "base/edp/reader.h"
// Kinematyki.
#include "robot/smb/kinematic_model_smb.h"
#include "base/edp/manip_trans_t.h"
#include "base/edp/vis_server.h"
#include "robot/epos/epos_gen.h"

#include "base/lib/exception.h"
using namespace mrrocpp::lib::exception;

namespace mrrocpp {
namespace edp {
namespace smb {

void effector::master_order(common::MT_ORDER nm_task, int nm_tryb)
{
	motor_driven_effector::single_thread_master_order(nm_task, nm_tryb);
}

void effector::get_controller_state(lib::c_buffer &instruction)
{

	if (robot_test_mode)
		controller_state_edp_buf.is_synchronised = true;
	//printf("get_controller_state: %d\n", controller_state_edp_buf.is_synchronised); fflush(stdout);
	reply.controller_state = controller_state_edp_buf;

	/*
	 // aktualizacja pozycji robota
	 // Uformowanie rozkazu odczytu dla SERVO_GROUP
	 sb->servo_command.instruction_code = lib::READ;
	 // Wyslanie rozkazu do SERVO_GROUP
	 // Pobranie z SERVO_GROUP aktualnej pozycji silnikow
	 //	printf("get_arm_position read_hardware\n");

	 sb->send_to_SERVO_GROUP();
	 */
	// dla pierwszego wypelnienia current_joints
	get_current_kinematic_model()->mp2i_transform(current_motor_pos, current_joints);

	{
		boost::mutex::scoped_lock lock(edp_irp6s_effector_mutex);

		// Ustawienie poprzedniej wartosci zadanej na obecnie odczytane polozenie walow silnikow
		for (int i = 0; i < number_of_servos; i++) {
			servo_current_motor_pos[i] = desired_motor_pos_new[i] = desired_motor_pos_old[i] = current_motor_pos[i];
			desired_joints[i] = current_joints[i];
		}
	}
}

// Konstruktor.
effector::effector(lib::configurator &_config) :
	motor_driven_effector(_config, lib::smb::ROBOT_NAME)
{

	number_of_servos = lib::smb::NUM_OF_SERVOS;
	//  Stworzenie listy dostepnych kinematyk.
	create_kinematic_models_for_given_robot();

	reset_variables();
}

/*--------------------------------------------------------------------------*/
void effector::move_arm(const lib::c_buffer &instruction)
{
	msg->message("move_arm");

	std::stringstream ss(std::stringstream::in | std::stringstream::out);

	switch (ecp_edp_cbuffer.variant)
	{
		/*
		 case lib::smb::CBUFFER_EPOS_GEN_PARAMETERS: {
		 // epos parameters computation basing on trajectory parameters
		 lib::epos_gen_parameters epos_gen_parameters_structure;
		 lib::epos_low_level_command epos_low_level_command_structure;

		 memcpy(&epos_gen_parameters_structure, &(ecp_edp_cbuffer.epos_gen_parameters_structure), sizeof(epos_gen_parameters_structure));

		 compute_epos_command(epos_gen_parameters_structure, epos_low_level_command_structure);

		 ss << ecp_edp_cbuffer.epos_gen_parameters_structure.dm[4];

		 msg->message(ss.str().c_str());

		 // previously computed parameters send to epos2 controllers


		 // start the trajectory execution

		 }
		 break;
		 */
		case lib::smb::CBUFFER_EPOS_CUBIC_COMMAND: {
			lib::epos::epos_cubic_command epos_cubic_command_structure;
			memcpy(&epos_cubic_command_structure, &(ecp_edp_cbuffer.epos_cubic_command_structure), sizeof(epos_cubic_command_structure));

		}
			break;
		case lib::smb::CBUFFER_EPOS_TRAPEZOIDAL_COMMAND: {
			lib::epos::epos_trapezoidal_command epos_trapezoidal_command_structure;
			memcpy(&epos_trapezoidal_command_structure, &(ecp_edp_cbuffer.epos_trapezoidal_command_structure), sizeof(epos_trapezoidal_command_structure));

		}
			break;
		case lib::smb::CBUFFER_PIN_INSERTION: {
			lib::smb::multi_pin_insertion_td multi_pin_insertion;
			memcpy(&multi_pin_insertion, &(ecp_edp_cbuffer.multi_pin_insertion), sizeof(multi_pin_insertion));
		}
			break;
		case lib::smb::CBUFFER_PIN_LOCKING: {
			lib::smb::multi_pin_locking_td multi_pin_locking;
			memcpy(&multi_pin_locking, &(ecp_edp_cbuffer.multi_pin_locking), sizeof(multi_pin_locking));
		}
			break;
		default:
			break;

	}

}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
void effector::get_arm_position(bool read_hardware, lib::c_buffer &instruction)
{
	//lib::JointArray desired_joints_tmp(lib::MAX_SERVOS_NR); // Wspolrzedne wewnetrzne -
	//	printf(" GET ARM\n");
	//	flushall();
	static int licznikaaa = (-11);

	std::stringstream ss(std::stringstream::in | std::stringstream::out);
	ss << "get_arm_position: " << licznikaaa;
	msg->message(ss.str().c_str());
	//	printf("%s\n", ss.str().c_str());


	edp_ecp_rbuffer.epos_controller[3].position = licznikaaa;

	if (licznikaaa < 10) {
		for (int i = 0; i < 6; i++) {
			edp_ecp_rbuffer.epos_controller[i].motion_in_progress = true;
		}

	} else {
		for (int i = 0; i < 6; i++) {
			edp_ecp_rbuffer.epos_controller[i].motion_in_progress = false;
		}
	}
	licznikaaa++;

	reply.servo_step = step_counter;
}
/*--------------------------------------------------------------------------*/

// Stworzenie modeli kinematyki dla robota IRp-6 na postumencie.
void effector::create_kinematic_models_for_given_robot(void)
{
	// Stworzenie wszystkich modeli kinematyki.
	add_kinematic_model(new kinematics::smb::model());
	// Ustawienie aktywnego modelu.
	set_kinematic_model(0);
}

void effector::create_threads()
{
	rb_obj = (boost::shared_ptr<common::reader_buffer>) new common::reader_buffer(*this);
	vis_obj = (boost::shared_ptr<common::vis_server>) new common::vis_server(*this);
}

void effector::instruction_deserialization()
{
	memcpy(&ecp_edp_cbuffer, instruction.arm.serialized_command, sizeof(ecp_edp_cbuffer));

}

void effector::reply_serialization(void)
{
	memcpy(reply.arm.serialized_reply, &edp_ecp_rbuffer, sizeof(edp_ecp_rbuffer));
}

}
// namespace smb


namespace common {

// Stworzenie obiektu edp_irp6m_effector.
effector* return_created_efector(lib::configurator &_config)
{
	return new smb::effector(_config);
}

} // namespace common
} // namespace edp
} // namespace mrrocpp

