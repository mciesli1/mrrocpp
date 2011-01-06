#if !defined(_ECP_ST_CODESCAN)
#define _ECP_ST_CODESCAN

/*!
 * @file
 * @brief File contains codescan declaration
 * @author Marcin Cieslik
 *
 * @ingroup subtasks
 */

#include "base/ecp/ecp_sub_task.h"
#include "base/ecp/ecp_task.h"

//rzeczy od mateusza
#include "../servovision/defines.h"
#include "application/servovision/single_visual_servo_manager.h"
#include "application/servovision/ib_eih_visual_servo.h"
#include "application/servovision/visual_servo_regulator_p.h"
#include "application/servovision/cubic_constraint.h"
#include "application/servovision/object_reached_termination_condition.h"

namespace mrrocpp {
namespace ecp {
namespace common {


namespace sub_task {

/*!
 * @brief Struct used in communication with FraDIA
 */
typedef struct
{
 bool code_identified;
 long int first_part;
 long int second_part;
 //char codeValues[13];
} mc_identification;


/*!
 * @brief subtask to execute scan of the barcode
 *
 * @author Marcin Cieslik
 * @ingroup subtasks
 */
class codescan : public sub_task
{

private:

	ecp_mp::sensor::fradia_sensor<lib::empty_t, mc_identification> * vsp_fradia2;
public:

	/**
	 * @brief Constructor
	 * @param _ecp_t ecp task object reference.
	 */
	codescan(task::task &_ecp_t);

	void conditional_execution();
};

} // namespace task
} // namespace common
} // namespace ecp
} // namespace mrrocpp


#endif
