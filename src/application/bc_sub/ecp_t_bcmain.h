#if !defined(_ECP_T_BCMAIN_H)
#define _ECP_T_BCMAIN_H

/*!
 * @file
 * @brief File contains bcmain ecp_task class declaration of barcode localization and reading application.
 * @author Marcin Cieslik
 *
 */

#include "base/ecp/ecp_task.h"

//od mateusza
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
namespace task {

/*!
 * @brief task to execute localization and read of a barcode.
 * it executes two subtasks ECP_ST_SERVOMOVE and ECP_ST_CODESCAN
 *
 * @author Marcin Cieslik
 */
class bcmain : public common::task::task
{
protected:

public:

	/**
	 * @brief Constructor
	 * @param _config configurator object reference.
	 */
	bcmain(lib::configurator &_config);
};

}
} // namespace common
} // namespace ecp
} // namespace mrrocpp

#endif
