#if !defined(_ECP_T_MULTIPLAYER_IRP6OT_H)
#define _ECP_T_MULTIPLAYER_IRP6OT_H

#include "ecp/common/ecp_task.h"
#include "ecp/common/ecp_st_go.h"
#include "ecp/common/ecp_generator_t.h"
#include "ecp/irp6_on_track/ecp_g_vis_sac_lx.h"

class ecp_task_multiplayer_irp6ot : public ecp_task
{
private:
	//generatory
    ecp_generator_t* gt;
    ecp_smooth_generator* sg;
    bias_edp_force_generator* befg;
    weight_meassure_generator* wmg;

    //podzadania
    ecp_sub_task_gripper_opening* go_st;

   	ecp_vis_sac_lx_generator *takeg;
	ecp_tff_rubik_grab_generator *rgg;


public:
    ecp_task_multiplayer_irp6ot(configurator &_config);

    // methods for ECP template to redefine in concrete classes
    void task_initialization(void);
    void main_task_algorithm(void);
};

#endif
