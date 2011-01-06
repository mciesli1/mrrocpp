#if !defined(_ECP_ST_SERVOMOVE)
#define _ECP_ST_SERVOMOVE

/*!
 * @file
 * @brief File contains servomove declaration
 * @author Marcin Cieslik
 *
 * @ingroup subtasks
 */

#include "base/ecp/ecp_sub_task.h"
#include "base/ecp/ecp_task.h"

//rzeczy od mateusza
#include "../servovision/defines.h"

//rzeczy od mateusza
#include <boost/shared_ptr.hpp>
#include "base/lib/logger.h"
#include "application/servovision/single_visual_servo_manager.h"
#include "application/servovision/ib_eih_visual_servo.h"
#include "application/servovision/visual_servo_regulator_p.h"
#include "application/servovision/cubic_constraint.h"
#include "application/servovision/object_reached_termination_condition.h"

using mrrocpp::ecp::common::generator::single_visual_servo_manager;
using mrrocpp::ecp::common::generator::visual_servo_manager;
using namespace mrrocpp::ecp::servovision;
using boost::shared_ptr;

namespace mrrocpp {
namespace ecp {
namespace common {


namespace sub_task {

/*!
 * @brief subtask to execute moving of servo based on barcode localization
 *
 * @author Marcin Cieslik
 * @ingroup subtasks
 */
class servomove : public sub_task
{

private:
	shared_ptr<single_visual_servo_manager> sm;
	shared_ptr<visual_servo> vs;
	shared_ptr<visual_servo_regulator> reg;
	shared_ptr<termination_condition> term_cond;
public:

	/**
	 * @brief Constructor
	 * @param _ecp_t ecp task object reference.
	 */
	servomove(task::task &_ecp_t);
	/**
	 * @brief Conditional execution of the subtask
	 */
	void conditional_execution();
};

} // namespace task
} // namespace common
} // namespace ecp
} // namespace mrrocpp


#endif
