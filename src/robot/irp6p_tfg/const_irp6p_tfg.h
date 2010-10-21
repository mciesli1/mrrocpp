#if !defined(_IRP6P_TFG_CONST_H)
#define _IRP6P_TFG_CONST_H

/*!
 * @file
 * @brief File contains constants and structures for IRp6 postument two finger gripper
 * @author twiniars <twiniars@ia.pw.edu.pl>, Warsaw University of Technology
 *
 * @ingroup irp6p_tfg
 */

#include "base/lib/impconst.h"

namespace mrrocpp {
namespace lib {
namespace irp6p_tfg {

/*!
 * @brief IRp6 postument two finger gripper robot label
 * @ingroup irp6p_tfg
 */
const robot_name_t ROBOT_NAME = "ROBOT_IRP6P_TFG";

/*!
 * @brief configuration file EDP IRp6 postument two finger gripper section string
 * @ingroup irp6p_tfg
 */
const std::string EDP_SECTION = "[edp_irp6p_tfg]";

/*!
 * @brief configuration file ECP IRp6 postument two finger gripper section string
 * @ingroup irp6p_tfg
 */
const std::string ECP_SECTION = "[ecp_irp6p_tfg]";

/*!
 * @brief IRp6 postument two finger gripper total number of servos
 * @ingroup irp6p_tfg
 */
const int NUM_OF_SERVOS = 1;

}
} // namespace lib
} // namespace mrrocpp

#endif /* _IRP6P_TFG_CONST_H */
