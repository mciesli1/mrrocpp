// -------------------------------------------------------------------------
//                            generator/ecp_g_force.h dla QNX6
// Deklaracje generatorow dla procesow ECP z wykorzystaniem sily
//
// -------------------------------------------------------------------------


#if !defined(_ECP_GEN_TFG_H)
#define _ECP_GEN_TFG_H

#include "lib/impconst.h"
#include "lib/com_buf.h"

#include "ecp/common/generator/ecp_g_teach_in.h"
#include "lib/mrmath/mrmath.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

/** @addtogroup edge_following
 *
 *  @{
 */

class tfg: public common::generator::generator {
protected:

	const int step_no;

public:

	// konstruktor
	tfg(common::task::task& _ecp_task, int step);

	virtual bool first_step();

	virtual bool next_step();

}; // end:
///

/** @} */// end of edge_following


} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp

#endif