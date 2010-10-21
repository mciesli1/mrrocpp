// ------------------------------------------------------------------------
//
//                     EFFECTOR CONTROL PROCESS (lib::ECP) - main()
//
// Ostatnia modyfikacja: 2006
// ------------------------------------------------------------------------

#include <cstdio>
#include <cstring>
#include <iostream>
#include <dlfcn.h>


#include "base/lib/typedefs.h"
#include "base/lib/impconst.h"
#include "base/lib/com_buf.h"
#include "base/lib/sr/srlib.h"
#include "robot/irp6ot_m/ecp_r_irp6ot_m.h"
#include "robot/irp6p_m/ecp_r_irp6p_m.h"
#include "robot/irp6m/ecp_r_irp6m.h"

#include "application/teach-dll/ecp_t_teach.h"
#include "application/teach-dll/ecp_g_teach.h"

#include "base/ecp/ecp_robot.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace task {

using std::cout;
using std::cerr;


// KONSTRUKTORY
teach::teach(lib::configurator &_config) : task(_config)
{
    if (config.section_name == ECP_SECTION)
    {
        ecp_m_robot = new irp6ot_m::robot (*this);
    }
    else if (config.section_name == lib::irp6p_m::ECP_SECTION)
    {
        ecp_m_robot = new irp6p_m::robot (*this);
    }
    else if (config.section_name == ECP_SECTION)
    {
        ecp_m_robot = new irp6m::robot (*this);
    }
    else {
    	fprintf(stderr, "unknown robot \"%s\" in teach task\n", config.section_name.c_str());
    	throw(robot::ECP_main_error(lib::FATAL_ERROR, 0));
    }

    cout << "C++ dlopen demo\n\n";
     // load the triangle library
     void* gener = dlopen("./generator.so", RTLD_LAZY);
     if (!gener) {
         cerr << "Cannot load library: " << dlerror() << '\n';
   //      return 1;
     }

     // load the symbols
     generator::create_t* create_gener = (generator::create_t*) dlsym(gener, "create");
     generator::destroy_t* destroy_gener = (generator::destroy_t*) dlsym(gener, "destroy");
     if (!create_gener || !destroy_gener) {
         cerr << "Cannot load symbols: " << dlerror() << '\n';
 //        return 1;
     }

     // create an instance of the class
     tig = create_gener(*this);

     /*
     // destroy the class
     destroy_gener(teach_gen);

     // unload the triangle library
     dlclose(gener);
*/

    sr_ecp_msg->message("ecp loaded");
}


void teach::main_task_algorithm(void)
{


    switch (ecp_m_robot->robot_name)
    {
    case lib::irp6ot_m::ROBOT_NAME:
        sr_ecp_msg->message("ecp teach irp6ot");
        break;
    case lib::irp6p_m::ROBOT_NAME:
        sr_ecp_msg->message("ecp teach irp6p");
        break;
    default:
        fprintf(stderr, "%s:%d unknown robot type\n", __FILE__, __LINE__);
    }

    if ( operator_reaction ("Teach in? ") )
    {
    	tig->flush_pose_list(); // Usuniecie listy pozycji, o ile istnieje
    	tig->teach (lib::ECP_MOTOR, "Teach-in the trajectory\n");
    }

    if ( operator_reaction ("Save trajectory? ") )
    {
    	tig->save_file (lib::ECP_MOTOR);
    }

    if ( operator_reaction ("Load trajectory? ") )
    {
    	tig->load_file_from_ui ();
    }

    // Aktualnie petla wykonuje sie jednokrotnie, gdyby MP przejal sterowanie
    // to petle mozna przerwac przez STOP lub przez polecenie lib::END_MOTION wydane
    // przez MP
    //  printf("w ecp for\n");
    tig->Move();
    // 	 printf("w ecp for za move\n");
    // Oczekiwanie na STOP
    ecp_termination_notice();
}

task* return_created_ecp_task (lib::configurator &_config)
{
	return new teach(_config);
}

} // namespace task
} // namespace common
} // namespace ecp
} // namespace mrrocpp

