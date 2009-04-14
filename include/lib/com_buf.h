////////////////////////////////////////////////////////////////////////////////
/*! \file     include/lib/com_buf.h
 *
 *  Data structures for IPC.
 *
 *  \author   tkornuta
 *  \date     2006-11-29
 *  \URL: https://segomo.elka.pw.edu.pl/svn/mrrocpp/base/trunk/include/lib/com_buf.h $
 *  $LastChangedRevision$
 *  $LastChangedDate$
 *  $LastChangedBy$
 *
 *  \todo <ul>
 *          <li>Translate to English where necessary.</li>
 *          <li>Write detailed comments.</li>
 *          <li>Suplement comments for those consts, variables and structures
 *              that are not commented at all.</li>
 *          <li>Clean up the commented fragments of code.</li>
 *        </ul>
 */
////////////////////////////////////////////////////////////////////////////////

#ifndef __COM_BUF_H
#define __COM_BUF_H

#include "lib/typedefs.h"
#include "lib/impconst.h"
#include "messip/messip.h"


//------------------------------------------------------------------------------
/*!
 *  Type of command sent from MP to ECP.
 */
enum MP_COMMAND {
	INVALID_COMMAND,
	START_TASK,
	NEXT_POSE,
	END_MOTION,
	NEXT_STATE,
	STOP
};

//------------------------------------------------------------------------------
/*!
 *  Type of reply from ECP to the MP command.
 */
enum ECP_REPLY {
	INCORRECT_MP_COMMAND,
	ERROR_IN_ECP,
	ECP_ACKNOWLEDGE,
	TASK_TERMINATED
};

//------------------------------------------------------------------------------
/*!
 *  Type of arm position definition.
 */
enum POSE_SPECIFICATION {
	INVALID_END_EFFECTOR,
	FRAME,
	XYZ_ANGLE_AXIS,
	XYZ_EULER_ZYZ,
	JOINT,
	MOTOR,
	PF_VELOCITY
};

//------------------------------------------------------------------------------
/*!
 *  Reply types from UI to ECP and commands from UI (pressing a button).
 */
enum UI_TO_ECP_COMMAND {
	INVALID_REPLY,
	NEXT,
	QUIT,
	ANSWER_YES,
	ANSWER_NO,
	FILE_LOADED,
	FILE_SAVED,

	/*! Commands from Force Control window. */
	FC_ADD_MACROSTEP,
	FC_CALIBRATE_SENSOR,
	FC_CHANGE_CONTROL,
	FC_MOVE_ROBOT,
	FC_SAVE_TRAJECTORY,
	FC_NEW_TRAJECTORY,
	FC_EXIT,
	FC_GET_DATA,

	/*! Commands from Trajectory Render window. */
	TR_LOAD_TRAJECTORY,
	TR_PAUSE_MOVE,
	TR_START_MOVE,
	TR_STOP_MOVE,
	TR_EXIT,
	TR_ZERO_POSITION,
	TR_SAVE_READINGS,
	TR_CALIBRATE_DIGITAL_SCALES_SENSOR,
	TR_CALIBRATE_FORCE_SENSOR,
	TR_TRY_MOVE_AGAIN,

	/*! Replies from the options window. */
	OPTION_ONE,
	OPTION_TWO,
	OPTION_THREE,
	OPTION_FOUR,

	/*!
	 *  Commands from the window
	 *  MAM_wnd_manual_moves_automatic_measures.
	 */
	MAM_START,
	MAM_STOP,
	MAM_CLEAR,
	MAM_SAVE,
	MAM_EXIT,
	MAM_CALIBRATE
};

//------------------------------------------------------------------------------
/*!
 *  Types of ECP to UI commands.
 */
enum ECP_TO_UI_COMMAND {
	C_INVALID_END_EFFECTOR,
	C_FRAME,
	C_XYZ_ANGLE_AXIS,
	C_XYZ_EULER_ZYZ,
	C_JOINT,
	C_MOTOR,
	YES_NO,
	DOUBLE_NUMBER,
	INTEGER_NUMBER,
	SAVE_FILE,
	LOAD_FILE,
	MESSAGE,
	OPEN_FORCE_SENSOR_MOVE_WINDOW,
	OPEN_TRAJECTORY_REPRODUCE_WINDOW,
	TR_REFRESH_WINDOW,
	TR_DANGEROUS_FORCE_DETECTED,
	CHOOSE_OPTION,
	MAM_OPEN_WINDOW,
	MAM_REFRESH_WINDOW
};


//------------------------------------------------------------------------------
/*! Length of a message sent from ECP to MP or UI */
#define MSG_LENGTH 60

//------------------------------------------------------------------------------
/*!
 *  ECP to UI message.
 */
struct ECP_message
{
	msg_header_t hdr;
	/*! Type of message. */
	ECP_TO_UI_COMMAND ecp_message;
	/*! Robot name. */
	ROBOT_ENUM robot_name;
	/*! Number of options - from 2 to 4 - - for CHOOSE_OPTION mode. */
	BYTE nr_of_options;

	//----------------------------------------------------------
	union{
		/*! A comment for the command. */
		char string[MSG_LENGTH];

		//------------------------------------------------------
		struct
		{
			double robot_position[MAX_SERVOS_NR];
			double sensor_reading[MAX_SERVOS_NR];
		}
		/*! Robot positions + Sensor readings. */
		RS;
		//------------------------------------------------------
		struct
		{
			double robot_position[MAX_SERVOS_NR];
			double digital_scales_sensor_reading[6];
			double force_sensor_reading[6];
		}
		/*! Robot positions + 2 * (Sensor readings). */
		R2S;
		//------------------------------------------------------
		struct
		{
			double robot_position[MAX_SERVOS_NR];
			double sensor_reading[6];
			int measure_number;
		}
		/*! Robot positions + Sensor readings + Measure number. */
		MAM;
	};
};

//------------------------------------------------------------------------------
/*!
 *  UI to ECP reply.
 */
struct UI_reply
{
	msg_header_t hdr;
	UI_TO_ECP_COMMAND reply;
	int integer_number;
	double double_number;
	double coordinates[MAX_SERVOS_NR];
	char path[80];
	char filename[20];
};

//------------------------------------------------------------------------------
/*!
 *  Message from UI to ECP.
 */
struct UI_ECP_message
{
	msg_header_t hdr;
	UI_TO_ECP_COMMAND command;

	union {
		/*! The name of the file. */
		char filename[100];
		/*! Time of the robot's motion. */
		int motion_time;
		/*! (axis - 1..6) && (+/- left/right). */
		short move_type;
		/*! Change of control type. */
		POSE_SPECIFICATION ps;
	};
};

//------------------------------------------------------------------------------
/*!
 *  Trajectory description for a chosen type of interpolation.
 *
 *  @warning  Enum type POSE_SPECIFICATION moved to the front
 *            of the file, because it is used in this structure.
 *            Connected with C_MOTOR and C_JOINT etc. - watch out for the indexes.
 *  @see      POSE_SPECIFICATION  C_MOTOR  C_JOINT.
 */
struct trajectory_description
{
	/*! Robot arm representation. */
	POSE_SPECIFICATION arm_type;
	/*! Number of interpolation nodes. */
	int interpolation_node_no;
	/*! Number of steps for a single internode. */
	int internode_step_no;
	/*! Step in which the read position is returned. */
	int value_in_step_no;
	/*! Coordinates increment table. */
	double coordinate_delta[MAX_SERVOS_NR];
};

//------------------------------------------------------------------------------
/*!
 *  Types of processes in MRROC++.
 */
enum PROCESS_TYPE {
	UNKNOWN_PROCESS_TYPE,
	EDP,
	ECP,
	MP,
	VSP,
	UI
};

//------------------------------------------------------------------------------
/*!
 *  Definitions for available values of set_type i get_type.
 *  @author yoyek
 */
#define CONTROLLER_STATE_DV                     0x08
#define ARM_DV                                  0x04
#define RMODEL_DV                               0x02
#define OUTPUTS_DV                              0x01
#define NOTHING_DV                              0x00

//------------------------------------------------------------------------------
/*! Error numbers generated in EDP.	*/
#define OK                                      0x0000000000000000ULL

#define INVALID_INSTRUCTION_TYPE                0x0100000000000000ULL
#define INVALID_REPLY_TYPE                      0x0200000000000000ULL
#define INVALID_SET_RMODEL_TYPE                 0x0300000000000000ULL
#define INVALID_GET_RMODEL_TYPE                 0x0400000000000000ULL
#define ERROR_IN_RMODEL_REQUEST                 0x0500000000000000ULL
#define INVALID_HOMOGENEOUS_MATRIX              0x0600000000000000ULL

#define QUERY_EXPECTED                          0x1000000000000000ULL
#define QUERY_NOT_EXPECTED                      0x1100000000000000ULL
#define NO_VALID_END_EFFECTOR_POSE              0x1200000000000000ULL
#define INVALID_MOTION_TYPE                     0x1300000000000000ULL
#define INVALID_MOTION_PARAMETERS               0x1400000000000000ULL
#define INVALID_SET_END_EFFECTOR_TYPE           0x1500000000000000ULL
#define INVALID_GET_END_EFFECTOR_TYPE           0x1600000000000000ULL
#define STRANGE_GET_ARM_REQUEST                 0x1700000000000000ULL

//------------------------------------------------------------------------------
/*! Range exceeding error codes (nonfatal) - drive shaft. */
#define BEYOND_UPPER_LIMIT_AXIS_0               0x2000000000000000ULL
#define BEYOND_UPPER_LIMIT_AXIS_1               0x2100000000000000ULL
#define BEYOND_UPPER_LIMIT_AXIS_2               0x2200000000000000ULL
#define BEYOND_UPPER_LIMIT_AXIS_3               0x2300000000000000ULL
#define BEYOND_UPPER_LIMIT_AXIS_4               0x2400000000000000ULL
#define BEYOND_UPPER_LIMIT_AXIS_5               0x2500000000000000ULL
#define BEYOND_UPPER_LIMIT_AXIS_6               0x2600000000000000ULL
#define BEYOND_UPPER_LIMIT_AXIS_7               0x2700000000000000ULL

#define BEYOND_LOWER_LIMIT_AXIS_0               0x2800000000000000ULL
#define BEYOND_LOWER_LIMIT_AXIS_1               0x2900000000000000ULL
#define BEYOND_LOWER_LIMIT_AXIS_2               0x2A00000000000000ULL
#define BEYOND_LOWER_LIMIT_AXIS_3               0x2B00000000000000ULL
#define BEYOND_LOWER_LIMIT_AXIS_4               0x2C00000000000000ULL
#define BEYOND_LOWER_LIMIT_AXIS_5               0x2D00000000000000ULL
#define BEYOND_LOWER_LIMIT_AXIS_6               0x2E00000000000000ULL
#define BEYOND_LOWER_LIMIT_AXIS_7               0x2F00000000000000ULL

//------------------------------------------------------------------------------
/*! Range exceeding error codes (nonfatal) - internal coordinates. */
#define BEYOND_UPPER_D0_LIMIT                   0x3000000000000000ULL
#define BEYOND_UPPER_THETA1_LIMIT               0x3100000000000000ULL
#define BEYOND_UPPER_THETA2_LIMIT               0x3200000000000000ULL
#define BEYOND_UPPER_THETA3_LIMIT               0x3300000000000000ULL
#define BEYOND_UPPER_THETA4_LIMIT               0x3400000000000000ULL
#define BEYOND_UPPER_THETA5_LIMIT               0x3500000000000000ULL
#define BEYOND_UPPER_THETA6_LIMIT               0x3600000000000000ULL
#define BEYOND_UPPER_THETA7_LIMIT               0x3700000000000000ULL


#define BEYOND_LOWER_D0_LIMIT                   0x3800000000000000ULL
#define BEYOND_LOWER_THETA1_LIMIT               0x3900000000000000ULL
#define BEYOND_LOWER_THETA2_LIMIT               0x3A00000000000000ULL
#define BEYOND_LOWER_THETA3_LIMIT               0x3B00000000000000ULL
#define BEYOND_LOWER_THETA4_LIMIT               0x3C00000000000000ULL
#define BEYOND_LOWER_THETA5_LIMIT               0x3D00000000000000ULL
#define BEYOND_LOWER_THETA6_LIMIT               0x3E00000000000000ULL
#define BEYOND_LOWER_THETA7_LIMIT               0x3F00000000000000ULL

#define OUT_OF_WORKSPACE                        0x4100000000000000ULL
#define SINGULAR_POSE                           0x4200000000000000ULL

//------------------------------------------------------------------------------
/*! Standard mathematical functions - argument out of domain. */
#define ACOS_DOMAIN_ERROR                       0x4300000000000000ULL
#define ASIN_DOMAIN_ERROR                       0x4400000000000000ULL
#define ATAN2_DOMAIN_ERROR                      0x4500000000000000ULL
#define SQRT_DOMAIN_ERROR                       0x4600000000000000ULL
#define UNKNOWN_MATH_ERROR                      0x4700000000000000ULL

#define UNKNOWN_INSTRUCTION                     0x4800000000000000ULL
#define NOT_IMPLEMENTED_YET                     0x4900000000000000ULL

#define NOT_YET_SYNCHRONISED                    0x5200000000000000ULL
#define ALREADY_SYNCHRONISED                    0x5300000000000000ULL
#define UNKNOWN_SYNCHRO_ERROR                   0x5400000000000000ULL
#define INVALID_KINEMATIC_MODEL_NO              0x5500000000000000ULL
#define INVALID_KINEMATIC_CORRECTOR_NO          0x5600000000000000ULL
#define EDP_UNIDENTIFIED_ERROR                  0x5700000000000000ULL


#define NOT_A_NUMBER_JOINT_VALUE_D0             0x6000000000000000ULL
#define NOT_A_NUMBER_JOINT_VALUE_THETA1         0x6100000000000000ULL
#define NOT_A_NUMBER_JOINT_VALUE_THETA2         0x6200000000000000ULL
#define NOT_A_NUMBER_JOINT_VALUE_THETA3         0x6300000000000000ULL
#define NOT_A_NUMBER_JOINT_VALUE_THETA4         0x6400000000000000ULL
#define NOT_A_NUMBER_JOINT_VALUE_THETA5         0x6500000000000000ULL
#define NOT_A_NUMBER_JOINT_VALUE_THETA6         0x6600000000000000ULL
#define NOT_A_NUMBER_JOINT_VALUE_THETA7         0x6700000000000000ULL

//------------------------------------------------------------------------------
/*! Errors detected by SERVO_GROUP. */
#define SERVO_ERROR_IN_PASSIVE_LOOP             0x0004000000000000ULL
/*! Wrong command from EDP_MASTER. */
#define UNIDENTIFIED_SERVO_COMMAND              0x0008000000000000ULL
#define SERVO_ERROR_IN_PHASE_1                  0x000C000000000000ULL
#define SERVO_ERROR_IN_PHASE_2                  0x0010000000000000ULL

//------------------------------------------------------------------------------
/*! Errors detected in servo synchronization. */
#define SYNCHRO_SWITCH_EXPECTED                 0x0014000000000000ULL
#define SYNCHRO_ERROR                           0x0018000000000000ULL
#define SYNCHRO_DELAY_ERROR                     0x001C000000000000ULL

//------------------------------------------------------------------------------
/*! Error classes. */
enum ERROR_CLASS {
	NEW_MESSAGE,
	SYSTEM_ERROR,
	FATAL_ERROR,
	NON_FATAL_ERROR
};

//------------------------------------------------------------------------------
/*! Detailed errors generated by ECP and MP. */
#define INVALID_MP_COMMAND                       0x1ULL
#define INVALID_POSE_SPECIFICATION               0x2ULL
#define INVALID_RMODEL_TYPE                      0x3ULL
#define INVALID_ECP_COMMAND                      0x4ULL
#define INVALID_EDP_REPLY                        0x5ULL
#define ECP_ERRORS                               0x6ULL
#define INVALID_COMMAND_TO_EDP                   0x7ULL
#define ECP_UNIDENTIFIED_ERROR                   0x8ULL
#define MP_UNIDENTIFIED_ERROR                    0x9ULL
#define EDP_ERROR                                0xAULL
#define NON_EXISTENT_DIRECTORY                   0xBULL
#define NON_EXISTENT_FILE                        0xCULL
#define READ_FILE_ERROR                          0xDULL
#define NON_TRAJECTORY_FILE                      0xEULL
#define NON_COMPATIBLE_LISTS                     0xFULL
#define ECP_STOP_ACCEPTED                       0x10ULL
#define MAX_ACCELERATION_EXCEEDED               0x11ULL
#define MAX_VELOCITY_EXCEEDED                   0x12ULL
#define NOT_ENOUGH_MEMORY                       0x13ULL
#define INVALID_TIME_SPECIFICATION              0x14ULL
#define INVALID_ECP_PULSE_IN_MP_START_ALL       0x16ULL
#define INVALID_ECP_PULSE_IN_MP_EXECUTE_ALL     0x17ULL
#define INVALID_ECP_PULSE_IN_MP_TERMINATE_ALL   0x18ULL

//------------------------------------------------------------------------------
/*! Detailed errors generated by ECP and MP to VSP - type SYSTEM_ERROR. */
#define CANNOT_SPAWN_VSP                        0x20ULL
#define CANNOT_LOCATE_DEVICE                    0x21ULL
#define CANNOT_READ_FROM_DEVICE                 0x22ULL
#define CANNOT_WRITE_TO_DEVICE                  0x23ULL
#define DEVICE_ALREADY_EXISTS                   0x24ULL

/*! Detailed errors generated by ECP and MP to VSP - type FATAL_ERROR. */
#define BAD_VSP_REPLY                           0x25ULL

/*! Detailed errors generated by ECP and MP to VSP - type NON_FATAL_ERROR. */
#define INVALID_VSP_REPLY                       0x26ULL

/*! Detailed errors generated by ECP and MP to VSP - other errors. */
#define VSP_UNIDENTIFIED_ERROR                  0x27ULL

/*! Detailed errors generated by ECP and MP to VSP - in a trajectory generator. */
#define DANGEROUS_FORCE_DETECTED                0x28ULL
#define SAVE_FILE_ERROR                         0x29ULL
#define NAME_ATTACH_ERROR                       0x2AULL

//------------------------------------------------------------------------------
/*! Detailed errors generated by VSP - type SYSTEM_ERROR. */
#define DISPATCH_ALLOCATION_ERROR                0x1ULL
#define DEVICE_EXISTS                            0x2ULL
#define DEVICE_CREATION_ERROR                    0x3ULL
#define DISPATCH_LOOP_ERROR                      0x4ULL

/*! Detailed errors generated by VSP - type FATAL_ERROR. */
#define SENSOR_NOT_CONFIGURED                    0x5ULL
#define READING_NOT_READY                        0x6ULL

/*! Detailed errors generated by VSP - type NON_FATAL_ERROR. */
#define INVALID_COMMAND_TO_VSP                   0x7ULL

/*! Detailed errors generated by VSP - type FATAL_ERROR in cyclic buffer. */
#define CYCLIC_BUFFER_PARSE_ERROR               0x08ULL
#define CYCLIC_BUFFER_UNDERRUN                  0x09ULL
#define CYCLIC_BUFFER_OVERFLOW                  0x10ULL

/*!
 *  Detailed errors generated by VSP - errors concerning CRS
 *  (finding a solutions for the Rubic's cube).
 */
#define RCS_INVALID_STATE                       0x10ULL
#define RCS_EXCEPTION                           0x11ULL

//------------------------------------------------------------------------------
enum GRIPPER_STATE_ENUM {
	GRIPPER_START_STATE,
	GRIPPER_EXPAND_STATE,
	GRIPPER_NARROW_STATE,
	GRIPPER_BLOCKED_AFTER_EXPAND_STATE,
	GRIPPER_BLOCKED_AFTER_NARROW_STATE,
	GRIPPER_BLOCKED_STATE
};

//------------------------------------------------------------------------------
enum INSTRUCTION_TYPE {
	INVALID,
	SET,
	GET,
	SET_GET,
	SYNCHRO,
	QUERY
};

//------------------------------------------------------------------------------
enum RMODEL_SPECIFICATION {
	INVALID_RMODEL,
	TOOL_FRAME, TOOL_XYZ_ANGLE_AXIS, TOOL_XYZ_EULER_ZYZ, TOOL_AS_XYZ_EULER_ZY,
	ARM_KINEMATIC_MODEL,
	SERVO_ALGORITHM,
	FORCE_TOOL,
	FORCE_BIAS
};

//------------------------------------------------------------------------------
enum MOTION_TYPE {
	ABSOLUTE, RELATIVE
};

//------------------------------------------------------------------------------
// MOTOR_INTERPOLATED_MOTION TASK_COORDINATES_INTERPOLATED_MOTION
enum INTERPOLATION_TYPE
{
	MIM, TCIM
};

//------------------------------------------------------------------------------
enum REPLY_TYPE {
	ERROR,
	ACKNOWLEDGE,
	SYNCHRO_OK,
	ARM,
	RMODEL,
	INPUTS,
	ARM_RMODEL,
	ARM_INPUTS,
	RMODEL_INPUTS,
	ARM_RMODEL_INPUTS,
	CONTROLLER_STATE
};

//------------------------------------------------------------------------------
/*! @todo Rename from "behavior". */
enum BEHAVIOUR_SPECIFICATION {
	UNGUARDED_MOTION,
	GUARDED_MOTION,
	CONTACT
};

//------------------------------------------------------------------------------
/*! Structure for error codes. */
struct edp_error
{
	uint64_t error0;
	uint64_t error1;
};

//------------------------------------------------------------------------------
enum SERVO_COMMAND {
	MOVE,
	READ,
	SYNCHRONISE,
	SERVO_ALGORITHM_AND_PARAMETERS
};


//------------------------------------------------------------------------------
/*! Structure of a command from EDP_MASTER to SERVO_GROUP. */
struct edp_master_command
{
	/*! Code for the instruction sent to SERVO_GROUP. */
	SERVO_COMMAND instruction_code;
	//*! A byte for calculating the length of the command */
	//BYTE address_byte;
	union {
		//------------------------------------------------------
		struct
		{
			/*! Number of steps for a macrostep. */
			WORD number_of_steps;
			/*!
			 *  Number of steps after which the information about the previously
			 *  realized position is to be sent.
			 *  Information is sent to EDP_MASTER using READING_BUFFER.
			 *  After k steps SERVO has the position from the k-1 step.
			 */
			WORD return_value_in_step_no;
			/*! Length of a macrostep (given value of a macrostep - increase). */
			double macro_step[MAX_SERVOS_NR];
			/*! Given absolute position at the end of a macrostep. */
			double abs_position [MAX_SERVOS_NR];
			//*! Byte for calculating the command's length. */
			// BYTE address_byte;
		}
		move;
		//------------------------------------------------------
		struct
		{
			/*! Servo algorithm numbers. */
			BYTE servo_algorithm_no[MAX_SERVOS_NR];
			/*! Numbers fo servo algorithm parameters set. */
			BYTE servo_parameters_no[MAX_SERVOS_NR];
			//*! Byte for calculating the command's length. */
			// BYTE address_byte;
		}
		servo_alg_par;

	} parameters;
};

//------------------------------------------------------------------------------
/*! Structure of a reply from SERVO_GROUP to EDP_MASTER. */
struct servo_group_reply
{
	/*! Error code. */
	edp_error error;
	/*! Position increment of the motor shaft reached since the last reading. */
	double position[MAX_SERVOS_NR];
	/*! Absolute position of the joints (in radians). */
	double abs_position[MAX_SERVOS_NR];
	/*! Given values for PWM fill (Phase Wave Modulation) - (usualy unnecessary). */
	int16_t PWM_value[MAX_SERVOS_NR];
	/*! Control current - (usualy unnecessary). */
	int16_t current[MAX_SERVOS_NR];
	/*! Numbers for the regulation algorithms in use. */
	BYTE algorithm_no[MAX_SERVOS_NR];
	BYTE algorithm_parameters_no[MAX_SERVOS_NR];
	/*! Gripper regulator state. */
	short gripper_reg_state;
};


//------------------------------------------------------------------------------
//                                  c_buffer
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/*! rmodel */
typedef union c_buffer_rmodel
{
	//----------------------------------------------------------
	struct
	{
		/*! Tool trihedron ralative to the collar. */
		frame_tab tool_frame;
		//*! Byte for calculating the command's length. */
		//	BYTE address_byte;
	}
	tool_frame_def;
	//----------------------------------------------------------
	struct
	{
		/*! XYZ + tool orientation relative to the collar. */
		double tool_coordinates[6];
		//*! Byte for calculating the command's length. */
		// 	BYTE address_byte;
	}
	tool_coordinate_def;
	//----------------------------------------------------------
	struct
	{
		/*! Parameter set number for the kinematic model. */
		BYTE kinematic_model_no;
		//*! Byte for calculating the command's length. */
		// 	BYTE address_byte;
	}
	kinematic_model;
	//----------------------------------------------------------
	struct
	{
		/*! Numbers for the servo-regulation algorithms. */
		BYTE servo_algorithm_no[MAX_SERVOS_NR];
		/*! Parameter set numbers for the servo-regulation algorithms. */
		BYTE servo_parameters_no[MAX_SERVOS_NR];
		//*! Byte for calculating the command's length. */
		// 	BYTE address_byte;
	}
	servo_algorithm;
	//----------------------------------------------------------
	struct
	{
		double position[3];
		double weight;
	}
	force_tool;

} c_buffer_rmodel_t;


//------------------------------------------------------------------------------
/*! arm */
typedef union c_buffer_arm
{
	struct
	{
		/*! A get_state command variant. */
		int command;
	}
	get_state_def;
	//----------------------------------------------------------
	struct
	{
		/*!  End's trihedron ralative to the base system. */
		frame_tab arm_frame;
		/*! XYZ + end's orientation relative to the base system. */
		double arm_coordinates[MAX_SERVOS_NR];
		/*! Given torque. */
		double desired_torque[MAX_SERVOS_NR];
		double inertia[6],
		reciprocal_damping[6];
		double force_xyz_torque_xyz[6];
		BEHAVIOUR_SPECIFICATION behaviour[6];
		/*! Dilation degree of the gripper. */
		double gripper_coordinate;
		//*! Byte for calculating the command's length. */
		// 	BYTE address_byte;
	}
	pf_def;
	//----------------------------------------------------------
	struct
	{
		/*! MAC7. */
		char text[MAX_TEXT];
		/*! MAC7. */
		char prosody[MAX_PROSODY];
		//*! Byte for calculating the command's length. */
		// 	BYTE address_byte;
	}
	text_def;

} c_buffer_arm_t;


//------------------------------------------------------------------------------
struct c_buffer
{

	/*! Type of the instruction. */
	INSTRUCTION_TYPE instruction_type;
	/*! Type of the SET instruction. */
	BYTE set_type;
	/*! Type of the GET instruction. */
	BYTE get_type;
	/*! Tool definition type - setting. */
	RMODEL_SPECIFICATION set_rmodel_type;
	/*! Tool definition type - reading. */
	RMODEL_SPECIFICATION get_rmodel_type;
	/*! Definition type of the end-effector's given position. */
	POSE_SPECIFICATION set_arm_type;
	/*! Definition type of the end-effector's read position. */
	POSE_SPECIFICATION get_arm_type;
	/*! Binary outputs values. */
	WORD output_values;
	//*! Byte for calculating the command's length. */
	//BYTE address_byte;

	/*! Type of interpolation. */
	INTERPOLATION_TYPE interpolation_type;

	/*! Type of motion - means of describing the shift. */
	MOTION_TYPE motion_type;
	/*! Number of steps for a given shift (macrostep). */
	WORD motion_steps;
	/*!
	 *  Number of steps for the 1st movemement phase.
	 *  Krok, w ktorym ma zostac przekazana informacja
	 *  o realizacji pierwszej fazy ruchu:
	 *  0 < value_in_step_no <= motion_steps + 1 .
	 *
	 *  Dla value_in_step_no = motion_steps
	 *  wiadomosc dotrze po zrealizowaniu makrokroku,
	 *  ale informacja o polozeniu bedzie dotyczyc
	 *  realizacji przedostatniego kroku makrokroku.
	 *
	 *  Dla value_in_step_no = motion_steps + 1
	 *  wiadomosc dotrze po zrealizowaniu jednego kroku
	 *  obiegu petli ruchu jalowego po zakonczeniu makrokroku,
	 *  ale informacja o polozeniu bedzie dotyczyc
	 *  realizacji calego makrokroku.
	 *
	 *  Dla value_in_step_no < motion_steps
	 *  wiadomosc dotrze przed zrealizowaniem makrokroku
	 *  i informacja o polozeniu bedzie dotyczyc
	 *  realizacji srodkowej fazy makrokroku.
	 */
	WORD value_in_step_no;
	c_buffer_rmodel_t rmodel;
	c_buffer_arm_t arm;

	//-----------------------------------------------------
	//                      METHODS
	//-----------------------------------------------------
	c_buffer (void);  // by W odkomentowane
	/*!
	 *  Oczytac wejscia?
	 *  @todo Translate to English.
	 */
	bool is_get_controller_state() const;
	/*!
	 *  Oczytac wejscia?
	 *  @todo Translate to English.
	 */
	bool is_get_inputs() const;
	/*!
	 *  Odczytac narzedzie?
	 *  @todo Translate to English.
	 */
	bool is_get_rmodel() const;
	/*!
	 *  Odczytac polozenie ramienia?
	 *  @todo Translate to English.
	 */
	bool is_get_arm() const;
	/*!
	 *  Ustawic wyjscia?
	 *  @todo Translate to English.
	 */
	bool is_set_outputs() const;
	/*!
	 *  Zmienic narzedzie?
	 *  @todo Translate to English.
	 */
	bool is_set_rmodel() const;
	/*!
	 *  Zmienic polozenie ramienia?
	 *  @todo Translate to English.
	 */
	bool is_set_arm() const;
};

//------------------------------------------------------------------------------
//                                  r_buffer
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/*! rmodel */
typedef union r_buffer_rmodel
{
	//----------------------------------------------------------
	struct
	{
		/*!
		 *  Macierz reprezentujaca narzedzie wzgledem konca lancucha kinematycznego.
		 *  @todo Translate to English.
		 */
		frame_tab tool_frame;
		//*! Byte for calculating the command's length. */
		// 	BYTE address_byte;
	}
	tool_frame_def;
	//----------------------------------------------------------
	struct
	{
		/*!
		 *  XYZ + orientacja narzedzia wzgledem kolnierza.
		 *  @todo Translate to English.
		 */
		double tool_coordinates[6];
		//*! Byte for calculating the command's length. */
		// 	BYTE address_byte;
	}
	tool_coordinate_def;
	//----------------------------------------------------------
	struct
	{
		/*!
		 *  Numer modelu kinematyki.
		 *  @todo Translate to English.
		 */
		BYTE kinematic_model_no;

		//*! Byte for calculating the command's length. */
		// 	BYTE address_byte;
	}
	kinematic_model;
	//----------------------------------------------------------
	struct
	{
		/*!
		 *  Numery algorytmow serworegulacji.
		 *  @todo Translate to English.
		 */
		BYTE servo_algorithm_no[MAX_SERVOS_NR];
		/*!
		 *  Numery zestawu parametrow algorytmow serworegulacji.
		 *  @todo Translate to English.
		 */
		BYTE servo_parameters_no[MAX_SERVOS_NR];
	}
	servo_algorithm;
	//----------------------------------------------------------
	struct
	{
		double position[3];
		double weight;
	}
	force_tool;

} r_buffer_rmodel_t;


//------------------------------------------------------------------------------
typedef struct _controller_state_t
{
	/*! Is robot synchronised? */
	bool is_synchronised;
	/*!
	 *  Czy wzmacniacze mocy sa zasilane?
	 *  @todo Translate to English.
	 */
	bool is_power_on;
	/*!
	 *  Czy szafa jest w���aczona?
	 *  @todo Translate to English.
	 *        Change the "wardrobe" thing for God's sake !!!
	 */
	bool is_wardrobe_on;
	/*!
	 *  Czy karta kontrolera robota jest w zamontowana w komputerze?
	 *  @todo Translate to English.
	 */
	bool is_controller_card_present;
	/*!
	 *  Czy wyzerowano sterowanie na silnikach po awarii sprzetowej?
	 *  @todo Translate to English.
	 */
	bool is_robot_blocked;
}
controller_state_t;

//------------------------------------------------------------------------------
/*! arm */
typedef union r_buffer_arm
{
	struct
	{
		/*! Given values for PWM fill (Phase Wave Modulation) - (usualy unnecessary). */
		int16_t PWM_value[MAX_SERVOS_NR];
		/*! Control current - (usualy unnecessary). */
		int16_t current[MAX_SERVOS_NR];
		/*!
		 *  Macierz reprezentujaca koncowke wzgledem bazy manipulatora.
		 *  @todo Translate to English.
		 */
		frame_tab arm_frame;
		/*!
		 *  XYZ + orientacja koncowki wzgledem ukladu bazowego.
		 *  @todo Translate to English.
		 */
		double arm_coordinates[MAX_SERVOS_NR];
		double force_xyz_torque_xyz[6];
		/*!
		 *  Stan w ktorym znajduje sie regulator chwytaka.
		 *  @todo Translate to English.
		 */
		short gripper_reg_state;
		/*!
		 *  Stopien rozwarcia chwytaka.
		 *  @todo Translate to English.
		 */
		double gripper_coordinate;
		//*! Byte for calculating the command's length. */
		// 	BYTE address_byte;

	}
	pf_def;
	//----------------------------------------------------------
	struct
	{
		/*!
		 *  Czy mowi?
		 *  @todo Translate to English.
		 */
		int speaking;
		//*! Byte for calculating the command's length. */
		// 	BYTE address_byte;
	}
	text_def;

} r_buffer_arm_t;

//------------------------------------------------------------------------------
struct r_buffer
{
	/*! Type of the reply. */
	REPLY_TYPE reply_type;
	/*! Number of the error (if it occured). */
	edp_error error_no;
	/*!
	 *  Sposob zdefiniowania narzedzia przy jego odczycie.
	 *  @todo Translate to English.
	 */
	RMODEL_SPECIFICATION rmodel_type;
	/*!
	 *  Sposob  zdefiniowania polozenia zadanego koncowki.
	 *  @todo Translate to English.
	 */
	POSE_SPECIFICATION arm_type;
	/*!
	 *  Wartosci wejsc binarnych.
	 *  @todo Translate to English.
	 */
	WORD input_values;
	/*! Analog input. */
	BYTE analog_input[8];
	controller_state_t controller_state;
	/*! Number of the servo step. */
	unsigned long servo_step;
	/*! Byte for calculating the command's length. */
	BYTE address_byte;
	/*! Given values for PWM fill (Phase Wave Modulation) - (usualy unnecessary). */
	int16_t PWM_value[MAX_SERVOS_NR];
	/*! Control current - (usualy unnecessary). */
	int16_t current[MAX_SERVOS_NR];
	r_buffer_rmodel_t rmodel;
	r_buffer_arm_t arm;

	//-----------------------------------------------------
	//                      METHODS
	//-----------------------------------------------------
	r_buffer (void); // W odkomentowane
} __attribute__((__packed__));

//------------------------------------------------------------------------------
/*! Target position for the mobile robot. */
class playerpos_goal_t
{
private:
	double x, y, t;

public:
	void forward(double length);
	void turn(double angle);
	void setGoal(double _x, double _y, double _z);

	double getX() const;
	double getY() const;
	double getT() const;

	playerpos_goal_t(double _x, double _y, double _t);
	playerpos_goal_t();
};

//------------------------------------------------------------------------------
/*!
 *  Zlecenie zmiany stanu ECP skojarzone z NEXT_STATE.
 *  @todo Translate to English.
 */
struct ecp_next_state_t
{
	int mp_2_ecp_next_state;
	int mp_2_ecp_next_state_variant;
	char mp_2_ecp_next_state_string[MP_2_ECP_STRING_SIZE];

	/*! Target position for the mobile robot. */
	playerpos_goal_t playerpos_goal;
};

//------------------------------------------------------------------------------
struct ecp_command_buffer
{
#ifndef USE_MESSIP_SRR
	/*! This is a message buffer, so it needs a message header */
	struct _pulse hdr;
#endif
	c_buffer instruction;
};



//------------------------------------------------------------------------------
/*! MP to ECP command. */
struct MP_COMMAND_PACKAGE
{
	msg_header_t hdr;
	MP_COMMAND command;
	ecp_next_state_t ecp_next_state;
	c_buffer instruction;
};

//------------------------------------------------------------------------------
#ifndef SPEECH_RECOGNITION_TEXT_LEN
#define SPEECH_RECOGNITION_TEXT_LEN 256
#endif

//------------------------------------------------------------------------------
/*! ECP to MP reply. */
struct ECP_REPLY_PACKAGE
{
	ECP_REPLY reply;
	r_buffer reply_package;
	char commandRecognized[SPEECH_RECOGNITION_TEXT_LEN];
};
// ------------------------------------------------------------------------

/*
// by Y
inline void lib::copy_frame(frame_tab destination_frame, frame_tab source_frame)
{
  for (int   column = 0; column < 4; column++)
    for (int row = 0; row < 3; row++)
      destination_frame[column][row] = source_frame[column][row];
}
 */

#endif