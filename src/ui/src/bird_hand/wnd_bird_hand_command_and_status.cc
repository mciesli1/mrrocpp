/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.01  */

#include "ui/src/bird_hand/ui_ecp_r_bird_hand.h"
#include "ui/src/bird_hand/ui_r_bird_hand.h"
#include "ui/src/bird_hand/wnd_bird_hand_command_and_status.h"
#include "robot/bird_hand/const_bird_hand.h"
#include "ui/src/ui_class.h"

/* Local headers */
#include "../ablibs.h"
#include "../abimport.h"
#include "../gcc_ntox86/proto.h"

namespace mrrocpp {
namespace ui {
namespace bird_hand {

//
//
// KLASA UiRobotBirdHand
//
//


WndCommandAndStatus::WndCommandAndStatus(common::Interface& _interface, UiRobot& _bird_hand) :
	interface(_interface), bird_hand(_bird_hand), is_open(false)
{

}

int WndCommandAndStatus::get_command()
{

	try {

		mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

		// odczyt ilosci krokow i ecp_query step

		int* motion_steps, *ecp_query_step;

		PtGetResource(ABW_motion_steps_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &motion_steps, 0);
		PtGetResource(ABW_ecp_query_step_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &ecp_query_step, 0);

		bhcs.motion_steps = *motion_steps;
		bhcs.ecp_query_step = *ecp_query_step;

		get_thumb_f_0_command();
		get_thumb_f_1_command();

		get_index_f_0_command();
		get_index_f_1_command();
		get_index_f_2_command();

		get_ring_f_0_command();
		get_ring_f_1_command();
		get_ring_f_2_command();

		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		/*
		 ss << bhcs.index_f[0].profile_type << " " << bhcs.motion_steps << "  "
		 << bhcs.ecp_query_step;
		 */
		/*
		 ss << bhcs.index_f[0].desired_position << " "
		 << bhcs.index_f[0].desired_torque << "  "
		 << bhcs.index_f[0].reciprocal_of_damping;

		 interface.ui_msg->message(ss.str().c_str());
		 */
		bird_hand.ui_ecp_robot->bird_hand_command_data_port->set();
		bird_hand.ui_ecp_robot->execute_motion();

	} // end try
	CATCH_SECTION_UI

	return 1;
}

int WndCommandAndStatus::set_status()
{

	try {

		//	mrrocpp::lib::bird_hand::status &bhsrs = bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->data;

		bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->set_request();
		bird_hand.ui_ecp_robot->execute_motion();
		bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->get();

		set_thumb_f_0_status();
		set_thumb_f_1_status();

		set_index_f_0_status();
		set_index_f_1_status();
		set_index_f_2_status();

		set_ring_f_0_status();
		set_ring_f_1_status();
		set_ring_f_2_status();

	} // end try
	CATCH_SECTION_UI

	return 1;
}

int WndCommandAndStatus::copy_command()
{

	copy_thumb_f_0_command();
	copy_thumb_f_1_command();

	copy_index_f_0_command();
	copy_index_f_1_command();
	copy_index_f_2_command();

	copy_ring_f_0_command();
	copy_ring_f_1_command();
	copy_ring_f_2_command();
	return 1;
}

//
//
// thumb_f_0
//
//


int WndCommandAndStatus::get_variant_thumb_f_0_command()
{

	unsigned long *flags;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	PtGetResource(ABW_thumb_f_0_absolute_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.thumb_f[0].profile_type = lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION;
	}

	PtGetResource(ABW_thumb_f_0_relative_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.thumb_f[0].profile_type = lib::bird_hand::MACROSTEP_POSITION_INCREMENT;
	}

	PtGetResource(ABW_thumb_f_0_velocity_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.thumb_f[0].profile_type = lib::bird_hand::SIGLE_STEP_POSTION_INCREMENT;
	}

	return 1;

}

int WndCommandAndStatus::get_thumb_f_0_command()
{

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	double* tmp_double;

	PtGetResource(ABW_thumb_f_0_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.thumb_f[0].desired_position = *tmp_double;

	PtGetResource(ABW_thumb_f_0_desired_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.thumb_f[0].desired_torque = *tmp_double;

	PtGetResource(ABW_thumb_f_0_recip_of_damping_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.thumb_f[0].reciprocal_of_damping = *tmp_double;

	get_variant_thumb_f_0_command();

	return 1;

}

int WndCommandAndStatus::set_thumb_f_0_status()
{

	mrrocpp::lib::bird_hand::status &bhsrs = bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->data;

	PtSetResource(ABW_thumb_f_0_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.thumb_f[0].meassured_position, 0);
	PtSetResource(ABW_thumb_f_0_current_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.thumb_f[0].meassured_torque, 0);
	PtSetResource(ABW_thumb_f_0_meassured_current_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.thumb_f[0].meassured_current, 0);

	if (bhsrs.thumb_f[0].lower_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_thumb_f_0_limit_1_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_0_limit_1_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[0].lower_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_thumb_f_0_limit_2_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_0_limit_2_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[0].upper_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_thumb_f_0_limit_3_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_0_limit_3_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[0].upper_limit_of_absolute_value_of_computed_position_increment) {
		interface.set_toggle_button(ABW_thumb_f_0_limit_4_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_0_limit_4_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[0].upper_limit_of_absolute_value_of_desired_position_increment) {
		interface.set_toggle_button(ABW_thumb_f_0_limit_5_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_0_limit_5_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[0].upper_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_thumb_f_0_limit_6_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_0_limit_6_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[0].upper_limit_of_absolute_value_of_meassured_torque) {
		interface.set_toggle_button(ABW_thumb_f_0_limit_7_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_0_limit_7_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[0].upper_limit_of_meassured_current) {
		interface.set_toggle_button(ABW_thumb_f_0_limit_8_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_0_limit_8_wnd_bird_hand_command_and_status);
	}

	return 1;

}

int WndCommandAndStatus::copy_thumb_f_0_command()
{

	double* tmp_double;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	get_variant_thumb_f_0_command();

	if (bhcs.thumb_f[0].profile_type == lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION) {

		PtGetResource(ABW_thumb_f_0_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

		double set_double = *tmp_double;

		PtSetResource(ABW_thumb_f_0_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &set_double, 0);

	}
	return 1;
}

//
//
// thumb_f_1
//
//


int WndCommandAndStatus::get_variant_thumb_f_1_command()
{

	unsigned long *flags;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	PtGetResource(ABW_thumb_f_1_absolute_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.thumb_f[1].profile_type = lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION;
	}

	PtGetResource(ABW_thumb_f_1_relative_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.thumb_f[1].profile_type = lib::bird_hand::MACROSTEP_POSITION_INCREMENT;
	}

	PtGetResource(ABW_thumb_f_1_velocity_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.thumb_f[1].profile_type = lib::bird_hand::SIGLE_STEP_POSTION_INCREMENT;
	}

	return 1;

}

int WndCommandAndStatus::get_thumb_f_1_command()
{

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	double* tmp_double;

	PtGetResource(ABW_thumb_f_1_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.thumb_f[1].desired_position = *tmp_double;

	PtGetResource(ABW_thumb_f_1_desired_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.thumb_f[1].desired_torque = *tmp_double;

	PtGetResource(ABW_thumb_f_1_recip_of_damping_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.thumb_f[1].reciprocal_of_damping = *tmp_double;

	get_variant_thumb_f_1_command();

	return 1;

}

int WndCommandAndStatus::set_thumb_f_1_status()
{

	mrrocpp::lib::bird_hand::status &bhsrs = bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->data;

	PtSetResource(ABW_thumb_f_1_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.thumb_f[1].meassured_position, 0);
	PtSetResource(ABW_thumb_f_1_current_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.thumb_f[1].meassured_torque, 0);
	PtSetResource(ABW_thumb_f_1_meassured_current_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.thumb_f[1].meassured_current, 0);

	if (bhsrs.thumb_f[1].lower_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_thumb_f_1_limit_1_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_1_limit_1_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[1].lower_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_thumb_f_1_limit_2_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_1_limit_2_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[1].upper_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_thumb_f_1_limit_3_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_1_limit_3_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[1].upper_limit_of_absolute_value_of_computed_position_increment) {
		interface.set_toggle_button(ABW_thumb_f_1_limit_4_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_1_limit_4_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[1].upper_limit_of_absolute_value_of_desired_position_increment) {
		interface.set_toggle_button(ABW_thumb_f_1_limit_5_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_1_limit_5_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[1].upper_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_thumb_f_1_limit_6_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_1_limit_6_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[1].upper_limit_of_absolute_value_of_meassured_torque) {
		interface.set_toggle_button(ABW_thumb_f_1_limit_7_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_1_limit_7_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.thumb_f[1].upper_limit_of_meassured_current) {
		interface.set_toggle_button(ABW_thumb_f_1_limit_8_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_thumb_f_1_limit_8_wnd_bird_hand_command_and_status);
	}

	return 1;

}

int WndCommandAndStatus::copy_thumb_f_1_command()
{

	double* tmp_double;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	get_variant_thumb_f_1_command();

	if (bhcs.thumb_f[1].profile_type == lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION) {

		PtGetResource(ABW_thumb_f_1_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

		double set_double = *tmp_double;

		PtSetResource(ABW_thumb_f_1_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &set_double, 0);

	}
	return 1;
}

//
//
// index_f_0
//
//


int WndCommandAndStatus::get_variant_index_f_0_command()
{

	unsigned long *flags;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	PtGetResource(ABW_index_f_0_absolute_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.index_f[0].profile_type = lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION;
	}

	PtGetResource(ABW_index_f_0_relative_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.index_f[0].profile_type = lib::bird_hand::MACROSTEP_POSITION_INCREMENT;
	}

	PtGetResource(ABW_index_f_0_velocity_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.index_f[0].profile_type = lib::bird_hand::SIGLE_STEP_POSTION_INCREMENT;
	}

	return 1;

}

int WndCommandAndStatus::get_index_f_0_command()
{

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	double* tmp_double;

	PtGetResource(ABW_index_f_0_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.index_f[0].desired_position = *tmp_double;

	PtGetResource(ABW_index_f_0_desired_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.index_f[0].desired_torque = *tmp_double;

	PtGetResource(ABW_index_f_0_recip_of_damping_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.index_f[0].reciprocal_of_damping = *tmp_double;

	get_variant_index_f_0_command();

	return 1;

}

int WndCommandAndStatus::set_index_f_0_status()
{

	mrrocpp::lib::bird_hand::status &bhsrs = bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->data;

	PtSetResource(ABW_index_f_0_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.index_f[0].meassured_position, 0);
	PtSetResource(ABW_index_f_0_current_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.index_f[0].meassured_torque, 0);
	PtSetResource(ABW_index_f_0_meassured_current_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.index_f[0].meassured_current, 0);

	if (bhsrs.index_f[0].lower_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_index_f_0_limit_1_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_0_limit_1_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[0].lower_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_index_f_0_limit_2_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_0_limit_2_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[0].upper_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_index_f_0_limit_3_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_0_limit_3_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[0].upper_limit_of_absolute_value_of_computed_position_increment) {
		interface.set_toggle_button(ABW_index_f_0_limit_4_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_0_limit_4_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[0].upper_limit_of_absolute_value_of_desired_position_increment) {
		interface.set_toggle_button(ABW_index_f_0_limit_5_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_0_limit_5_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[0].upper_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_index_f_0_limit_6_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_0_limit_6_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[0].upper_limit_of_absolute_value_of_meassured_torque) {
		interface.set_toggle_button(ABW_index_f_0_limit_7_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_0_limit_7_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[0].upper_limit_of_meassured_current) {
		interface.set_toggle_button(ABW_index_f_0_limit_8_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_0_limit_8_wnd_bird_hand_command_and_status);
	}

	return 1;

}

int WndCommandAndStatus::copy_index_f_0_command()
{

	double* tmp_double;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	get_variant_index_f_0_command();

	if (bhcs.index_f[0].profile_type == lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION) {

		PtGetResource(ABW_index_f_0_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

		double set_double = *tmp_double;

		PtSetResource(ABW_index_f_0_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &set_double, 0);

	}
	return 1;
}

//
//
// index_f_1
//
//


int WndCommandAndStatus::get_variant_index_f_1_command()
{

	unsigned long *flags;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	PtGetResource(ABW_index_f_1_absolute_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.index_f[1].profile_type = lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION;
	}

	PtGetResource(ABW_index_f_1_relative_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.index_f[1].profile_type = lib::bird_hand::MACROSTEP_POSITION_INCREMENT;
	}

	PtGetResource(ABW_index_f_1_velocity_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.index_f[1].profile_type = lib::bird_hand::SIGLE_STEP_POSTION_INCREMENT;
	}

	return 1;

}

int WndCommandAndStatus::get_index_f_1_command()
{

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	double* tmp_double;

	PtGetResource(ABW_index_f_1_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.index_f[1].desired_position = *tmp_double;

	PtGetResource(ABW_index_f_1_desired_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.index_f[1].desired_torque = *tmp_double;

	PtGetResource(ABW_index_f_1_recip_of_damping_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.index_f[1].reciprocal_of_damping = *tmp_double;

	get_variant_index_f_1_command();

	return 1;

}

int WndCommandAndStatus::set_index_f_1_status()
{

	mrrocpp::lib::bird_hand::status &bhsrs = bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->data;

	PtSetResource(ABW_index_f_1_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.index_f[1].meassured_position, 0);
	PtSetResource(ABW_index_f_1_current_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.index_f[1].meassured_torque, 0);
	PtSetResource(ABW_index_f_1_meassured_current_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.index_f[1].meassured_current, 0);

	if (bhsrs.index_f[1].lower_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_index_f_1_limit_1_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_1_limit_1_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[1].lower_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_index_f_1_limit_2_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_1_limit_2_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[1].upper_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_index_f_1_limit_3_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_1_limit_3_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[1].upper_limit_of_absolute_value_of_computed_position_increment) {
		interface.set_toggle_button(ABW_index_f_1_limit_4_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_1_limit_4_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[1].upper_limit_of_absolute_value_of_desired_position_increment) {
		interface.set_toggle_button(ABW_index_f_1_limit_5_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_1_limit_5_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[1].upper_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_index_f_1_limit_6_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_1_limit_6_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[1].upper_limit_of_absolute_value_of_meassured_torque) {
		interface.set_toggle_button(ABW_index_f_1_limit_7_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_1_limit_7_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[1].upper_limit_of_meassured_current) {
		interface.set_toggle_button(ABW_index_f_1_limit_8_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_1_limit_8_wnd_bird_hand_command_and_status);
	}

	return 1;

}

int WndCommandAndStatus::copy_index_f_1_command()
{

	double* tmp_double;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	get_variant_index_f_1_command();

	if (bhcs.index_f[1].profile_type == lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION) {

		PtGetResource(ABW_index_f_1_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

		double set_double = *tmp_double;

		PtSetResource(ABW_index_f_1_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &set_double, 0);

	}
	return 1;
}

//
//
// index_f_2
//
//


int WndCommandAndStatus::get_variant_index_f_2_command()
{

	unsigned long *flags;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	PtGetResource(ABW_index_f_2_absolute_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.index_f[2].profile_type = lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION;
	}

	PtGetResource(ABW_index_f_2_relative_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.index_f[2].profile_type = lib::bird_hand::MACROSTEP_POSITION_INCREMENT;
	}

	PtGetResource(ABW_index_f_2_velocity_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.index_f[2].profile_type = lib::bird_hand::SIGLE_STEP_POSTION_INCREMENT;
	}

	return 1;

}

int WndCommandAndStatus::get_index_f_2_command()
{

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	double* tmp_double;

	PtGetResource(ABW_index_f_2_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.index_f[2].desired_position = *tmp_double;

	PtGetResource(ABW_index_f_2_desired_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.index_f[2].desired_torque = *tmp_double;

	PtGetResource(ABW_index_f_2_recip_of_damping_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.index_f[2].reciprocal_of_damping = *tmp_double;

	get_variant_index_f_2_command();

	return 1;

}

int WndCommandAndStatus::set_index_f_2_status()
{

	mrrocpp::lib::bird_hand::status &bhsrs = bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->data;

	PtSetResource(ABW_index_f_2_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.index_f[2].meassured_position, 0);
	PtSetResource(ABW_index_f_2_current_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.index_f[2].meassured_torque, 0);
	PtSetResource(ABW_index_f_2_meassured_current_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.index_f[2].meassured_current, 0);

	if (bhsrs.index_f[2].lower_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_index_f_2_limit_1_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_2_limit_1_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[2].lower_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_index_f_2_limit_2_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_2_limit_2_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[2].upper_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_index_f_2_limit_3_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_2_limit_3_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[2].upper_limit_of_absolute_value_of_computed_position_increment) {
		interface.set_toggle_button(ABW_index_f_2_limit_4_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_2_limit_4_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[2].upper_limit_of_absolute_value_of_desired_position_increment) {
		interface.set_toggle_button(ABW_index_f_2_limit_5_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_2_limit_5_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[2].upper_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_index_f_2_limit_6_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_2_limit_6_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[2].upper_limit_of_absolute_value_of_meassured_torque) {
		interface.set_toggle_button(ABW_index_f_2_limit_7_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_2_limit_7_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.index_f[2].upper_limit_of_meassured_current) {
		interface.set_toggle_button(ABW_index_f_2_limit_8_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_index_f_2_limit_8_wnd_bird_hand_command_and_status);
	}

	return 1;

}

int WndCommandAndStatus::copy_index_f_2_command()
{

	double* tmp_double;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	get_variant_index_f_2_command();

	if (bhcs.index_f[2].profile_type == lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION) {

		PtGetResource(ABW_index_f_2_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

		double set_double = *tmp_double;

		PtSetResource(ABW_index_f_2_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &set_double, 0);

	}
	return 1;
}

//
//
// ring_f_0
//
//


int WndCommandAndStatus::get_variant_ring_f_0_command()
{

	unsigned long *flags;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	PtGetResource(ABW_ring_f_0_absolute_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.ring_f[0].profile_type = lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION;
	}

	PtGetResource(ABW_ring_f_0_relative_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.ring_f[0].profile_type = lib::bird_hand::MACROSTEP_POSITION_INCREMENT;
	}

	PtGetResource(ABW_ring_f_0_velocity_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.ring_f[0].profile_type = lib::bird_hand::SIGLE_STEP_POSTION_INCREMENT;
	}

	return 1;

}

int WndCommandAndStatus::get_ring_f_0_command()
{

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	double* tmp_double;

	PtGetResource(ABW_ring_f_0_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.ring_f[0].desired_position = *tmp_double;

	PtGetResource(ABW_ring_f_0_desired_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.ring_f[0].desired_torque = *tmp_double;

	PtGetResource(ABW_ring_f_0_recip_of_damping_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.ring_f[0].reciprocal_of_damping = *tmp_double;

	get_variant_ring_f_0_command();

	return 1;

}

int WndCommandAndStatus::set_ring_f_0_status()
{

	mrrocpp::lib::bird_hand::status &bhsrs = bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->data;

	PtSetResource(ABW_ring_f_0_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.ring_f[0].meassured_position, 0);
	PtSetResource(ABW_ring_f_0_current_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.ring_f[0].meassured_torque, 0);
	PtSetResource(ABW_ring_f_0_meassured_current_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.ring_f[0].meassured_current, 0);

	if (bhsrs.ring_f[0].lower_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_ring_f_0_limit_1_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_0_limit_1_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[0].lower_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_ring_f_0_limit_2_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_0_limit_2_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[0].upper_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_ring_f_0_limit_3_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_0_limit_3_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[0].upper_limit_of_absolute_value_of_computed_position_increment) {
		interface.set_toggle_button(ABW_ring_f_0_limit_4_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_0_limit_4_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[0].upper_limit_of_absolute_value_of_desired_position_increment) {
		interface.set_toggle_button(ABW_ring_f_0_limit_5_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_0_limit_5_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[0].upper_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_ring_f_0_limit_6_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_0_limit_6_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[0].upper_limit_of_absolute_value_of_meassured_torque) {
		interface.set_toggle_button(ABW_ring_f_0_limit_7_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_0_limit_7_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[0].upper_limit_of_meassured_current) {
		interface.set_toggle_button(ABW_ring_f_0_limit_8_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_0_limit_8_wnd_bird_hand_command_and_status);
	}

	return 1;

}

int WndCommandAndStatus::copy_ring_f_0_command()
{

	double* tmp_double;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	get_variant_ring_f_0_command();

	if (bhcs.ring_f[0].profile_type == lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION) {

		PtGetResource(ABW_ring_f_0_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

		double set_double = *tmp_double;

		PtSetResource(ABW_ring_f_0_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &set_double, 0);

	}
	return 1;
}

//
//
// ring_f_1
//
//


int WndCommandAndStatus::get_variant_ring_f_1_command()
{

	unsigned long *flags;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	PtGetResource(ABW_ring_f_1_absolute_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.ring_f[1].profile_type = lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION;
	}

	PtGetResource(ABW_ring_f_1_relative_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.ring_f[1].profile_type = lib::bird_hand::MACROSTEP_POSITION_INCREMENT;
	}

	PtGetResource(ABW_ring_f_1_velocity_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.ring_f[1].profile_type = lib::bird_hand::SIGLE_STEP_POSTION_INCREMENT;
	}

	return 1;

}

int WndCommandAndStatus::get_ring_f_1_command()
{

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	double* tmp_double;

	PtGetResource(ABW_ring_f_1_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.ring_f[1].desired_position = *tmp_double;

	PtGetResource(ABW_ring_f_1_desired_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.ring_f[1].desired_torque = *tmp_double;

	PtGetResource(ABW_ring_f_1_recip_of_damping_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.ring_f[1].reciprocal_of_damping = *tmp_double;

	get_variant_ring_f_1_command();

	return 1;

}

int WndCommandAndStatus::set_ring_f_1_status()
{

	mrrocpp::lib::bird_hand::status &bhsrs = bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->data;

	PtSetResource(ABW_ring_f_1_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.ring_f[1].meassured_position, 0);
	PtSetResource(ABW_ring_f_1_current_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.ring_f[1].meassured_torque, 0);
	PtSetResource(ABW_ring_f_1_meassured_current_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.ring_f[1].meassured_current, 0);

	if (bhsrs.ring_f[1].lower_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_ring_f_1_limit_1_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_1_limit_1_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[1].lower_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_ring_f_1_limit_2_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_1_limit_2_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[1].upper_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_ring_f_1_limit_3_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_1_limit_3_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[1].upper_limit_of_absolute_value_of_computed_position_increment) {
		interface.set_toggle_button(ABW_ring_f_1_limit_4_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_1_limit_4_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[1].upper_limit_of_absolute_value_of_desired_position_increment) {
		interface.set_toggle_button(ABW_ring_f_1_limit_5_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_1_limit_5_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[1].upper_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_ring_f_1_limit_6_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_1_limit_6_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[1].upper_limit_of_absolute_value_of_meassured_torque) {
		interface.set_toggle_button(ABW_ring_f_1_limit_7_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_1_limit_7_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[1].upper_limit_of_meassured_current) {
		interface.set_toggle_button(ABW_ring_f_1_limit_8_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_1_limit_8_wnd_bird_hand_command_and_status);
	}

	return 1;

}

int WndCommandAndStatus::copy_ring_f_1_command()
{

	double* tmp_double;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	get_variant_ring_f_1_command();

	if (bhcs.ring_f[1].profile_type == lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION) {

		PtGetResource(ABW_ring_f_1_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

		double set_double = *tmp_double;

		PtSetResource(ABW_ring_f_1_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &set_double, 0);

	}
	return 1;
}

//
//
// ring_f_2
//
//


int WndCommandAndStatus::get_variant_ring_f_2_command()
{

	unsigned long *flags;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	PtGetResource(ABW_ring_f_2_absolute_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.ring_f[2].profile_type = lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION;
	}

	PtGetResource(ABW_ring_f_2_relative_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.ring_f[2].profile_type = lib::bird_hand::MACROSTEP_POSITION_INCREMENT;
	}

	PtGetResource(ABW_ring_f_2_velocity_variant_wnd_bird_hand_command_and_status, Pt_ARG_FLAGS, &flags, 0);

	if (*flags & Pt_SET) {
		bhcs.ring_f[2].profile_type = lib::bird_hand::SIGLE_STEP_POSTION_INCREMENT;
	}

	return 1;

}

int WndCommandAndStatus::get_ring_f_2_command()
{

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	double* tmp_double;

	PtGetResource(ABW_ring_f_2_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.ring_f[2].desired_position = *tmp_double;

	PtGetResource(ABW_ring_f_2_desired_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.ring_f[2].desired_torque = *tmp_double;

	PtGetResource(ABW_ring_f_2_recip_of_damping_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

	bhcs.ring_f[2].reciprocal_of_damping = *tmp_double;

	get_variant_ring_f_2_command();

	return 1;

}

int WndCommandAndStatus::set_ring_f_2_status()
{

	mrrocpp::lib::bird_hand::status &bhsrs = bird_hand.ui_ecp_robot->bird_hand_status_reply_data_request_port->data;

	PtSetResource(ABW_ring_f_2_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.ring_f[2].meassured_position, 0);
	PtSetResource(ABW_ring_f_2_current_torque_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.ring_f[2].meassured_torque, 0);
	PtSetResource(ABW_ring_f_2_meassured_current_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &bhsrs.ring_f[2].meassured_current, 0);

	if (bhsrs.ring_f[2].lower_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_ring_f_2_limit_1_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_2_limit_1_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[2].lower_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_ring_f_2_limit_2_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_2_limit_2_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[2].upper_limit_of_absolute_position) {
		interface.set_toggle_button(ABW_ring_f_2_limit_3_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_2_limit_3_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[2].upper_limit_of_absolute_value_of_computed_position_increment) {
		interface.set_toggle_button(ABW_ring_f_2_limit_4_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_2_limit_4_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[2].upper_limit_of_absolute_value_of_desired_position_increment) {
		interface.set_toggle_button(ABW_ring_f_2_limit_5_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_2_limit_5_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[2].upper_limit_of_absolute_value_of_desired_torque) {
		interface.set_toggle_button(ABW_ring_f_2_limit_6_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_2_limit_6_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[2].upper_limit_of_absolute_value_of_meassured_torque) {
		interface.set_toggle_button(ABW_ring_f_2_limit_7_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_2_limit_7_wnd_bird_hand_command_and_status);
	}

	if (bhsrs.ring_f[2].upper_limit_of_meassured_current) {
		interface.set_toggle_button(ABW_ring_f_2_limit_8_wnd_bird_hand_command_and_status);

	} else {
		interface.unset_toggle_button(ABW_ring_f_2_limit_8_wnd_bird_hand_command_and_status);
	}

	return 1;

}

int WndCommandAndStatus::copy_ring_f_2_command()
{

	double* tmp_double;

	mrrocpp::lib::bird_hand::command &bhcs = bird_hand.ui_ecp_robot->bird_hand_command_data_port->data;

	get_variant_ring_f_2_command();

	if (bhcs.ring_f[2].profile_type == lib::bird_hand::MACROSTEP_ABSOLUTE_POSITION) {

		PtGetResource(ABW_ring_f_2_current_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &tmp_double, 0);

		double set_double = *tmp_double;

		PtSetResource(ABW_ring_f_2_desired_position_wnd_bird_hand_command_and_status, Pt_ARG_NUMERIC_VALUE, &set_double, 0);

	}
	return 1;
}

}
} //namespace ui
} //namespace mrrocpp
