/*!
 * @file
 * @brief File contains bcmain ecp_task class definition of barcode localization and reading application.
 * @author Marcin Cieslik
 *
 */

#include <cstdio>

#include "robot/irp6ot_m/ecp_r_irp6ot_m.h"
#include "robot/irp6p_m/ecp_r_irp6p_m.h"

#include "ecp_t_bcmain.h" //task


#include "ecp_st_servomove.h"
#include "ecp_st_codescan.h"

#include "ecp_mp_st_servomove.h"
#include "ecp_mp_st_codescan.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace task {

// KONSTRUKTORY
bcmain::bcmain(lib::configurator &_config) :
	task(_config)
{
		//ROBOTY, ALE TO JESZCZE TRZEBA UZUPENIC
		//NARAZIE TYLKO POSTUMENT UWZGLEDNIONY
		//TRZEBA ZROBIC TAK ZEBY SPRAWDZALO CO JEST W PLIKU KONFIGURACYJNYM I NA TEJ PODSTAWIE ROBILO
		ecp_m_robot = new irp6p_m::robot(*this);





		sr_ecp_msg->message("ECP_T_: Przed podzadaniami");
		// utworzenie podzadan
	{
		sub_task::sub_task* ecpst;
		ecpst = new sub_task::servomove(*this);
		subtask_m[ecp_mp::sub_task::ECP_ST_SERVOMOVE] = ecpst;

		ecpst = new sub_task::codescan(*this);
		subtask_m[ecp_mp::sub_task::ECP_ST_CODESCAN] = ecpst;

	}

	sr_ecp_msg->message("ECP_T_: Po podzadaniach");
}

task* return_created_ecp_task(lib::configurator &_config)
{
	return new common::task::bcmain(_config);
}

}
} // namespace common
} // namespace ecp
} // namespace mrrocpp
