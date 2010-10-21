/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.01  */

/* Standard headers */
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <strings.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include <csignal>
#include <sys/netmgr.h>
#include <cerrno>
#include <process.h>
#include <cmath>

#include <boost/bind.hpp>

#include "base/lib/sr/srlib.h"

#include "ui/src/ui_class.h"
// #include "ui/src/ui.h"
// Konfigurator.
#include "base/lib/configurator.h"
#include "ui/src/ui_ecp_r_tfg_and_conv.h"

#include "robot/spkm/const_spkm.h"
/* Local headers */
#include "ablibs.h"
#include "abimport.h"
#include "proto.h"

extern ui::common::Interface interface;

int EDP_spkm_create(PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo)

{

	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;
	if (interface.spkm->state.edp.state == 0) {
		interface.spkm->create_thread();
		interface.spkm->eb.command(boost::bind(EDP_spkm_create_int, widget, apinfo, cbinfo));
	}
	return (Pt_CONTINUE);

}

int EDP_spkm_create_int(PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo)

{

	//	sleep(10);
	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;

	set_ui_state_notification(UI_N_PROCESS_CREATION);

	try { // dla bledow robot :: ECP_error

		// dla robota spkm
		if (interface.spkm->state.edp.state == 0) {

			interface.spkm->state.edp.state = 0;
			interface.spkm->state.edp.is_synchronised = false;

			std::string tmp_string("/dev/name/global/");
			tmp_string += interface.spkm->state.edp.hardware_busy_attach_point;

			std::string tmp2_string("/dev/name/global/");
			tmp2_string += interface.spkm->state.edp.network_resourceman_attach_point;

			// sprawdzenie czy nie jest juz zarejestrowany zarzadca zasobow
			if (((!(interface.spkm->state.edp.test_mode)) && (access(tmp_string.c_str(), R_OK) == 0))
					|| (access(tmp2_string.c_str(), R_OK) == 0)) {
				interface.ui_msg->message(lib::NON_FATAL_ERROR, "edp_spkm already exists");
			} else if (interface.check_node_existence(interface.spkm->state.edp.node_name, "edp_spkm")) {

				interface.spkm->state.edp.node_nr
						= interface.config->return_node_number(interface.spkm->state.edp.node_name);
				{
					boost::unique_lock <boost::mutex> lock(interface.process_creation_mtx);
					interface.spkm->ui_ecp_robot
							= new ui::tfg_and_conv::EcpRobot(*interface.config, *interface.all_ecp_msg, lib::spkm::ROBOT_NAME);

				}

				interface.spkm->state.edp.pid = interface.spkm->ui_ecp_robot->ecp->get_EDP_pid();

				if (interface.spkm->state.edp.pid < 0) {

					interface.spkm->state.edp.state = 0;
					fprintf(stderr, "edp spawn failed: %s\n", strerror(errno));
					delete interface.spkm->ui_ecp_robot;
				} else { // jesli spawn sie powiodl

					interface.spkm->state.edp.state = 1;

					interface.spkm->connect_to_reader();

					// odczytanie poczatkowego stanu robota (komunikuje sie z EDP)
					lib::controller_state_t robot_controller_initial_state_tmp;

					interface.spkm->ui_ecp_robot->get_controller_state(robot_controller_initial_state_tmp);

					//interface.spkm->state.edp.state = 1; // edp wlaczone reader czeka na start

					interface.spkm->state.edp.is_synchronised = robot_controller_initial_state_tmp.is_synchronised;
				}
			}
		}

	} // end try

	CATCH_SECTION_UI

	interface.manage_interface();

	return 1;
}

int EDP_spkm_slay(PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo)

{

	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;

	interface.spkm->EDP_slay_int();
	return (Pt_CONTINUE);

}

