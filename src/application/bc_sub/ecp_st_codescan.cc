/*!
 * @file
 * @brief File contains codescan definition
 * @author Marcin Cieslik
 *
 * @ingroup subtasks
 */

#include "base/lib/typedefs.h"
#include "base/lib/sr/srlib.h"
#include "ecp_st_codescan.h"
#include <iostream>



namespace mrrocpp {
namespace ecp {
namespace common {
namespace sub_task {





codescan::codescan(task::task &_ecp_t) :
	sub_task(_ecp_t)
{
	printf("TWORZE CODESCAN\n");
	std::cout<<std::endl;
		printf("B2\n");
		//vsp_fradia2 = new ecp_mp::sensor::fradia_sensor<visual_servo_types::image_based_configuration, visual_servo_types::image_based_reading>(_ecp_t.config, "[vsp_read]");
		vsp_fradia2 = new ecp_mp::sensor::fradia_sensor<lib::empty_t, mc_identification>(_ecp_t.config, "[vsp_read]");
		//sensor_m[ecp_mp::sensor::SENSOR_FRADIA] = vsp_fradia2;
		//sensor_m[ecp_mp::sensor::SENSOR_FRADIA]->configure_sensor();



		printf("B3\n");
}

void codescan::conditional_execution()
{
	int correct_counter=10; ///counts how many times barcode was read, but it wasn't correct

	printf("JESTEM W CODESCAN\n");
	std::cout<<std::endl;


	//sensor_m[ecp_mp::sensor::SENSOR_FRADIA]->get_reading_message().code_identified;
	vsp_fradia2->configure_sensor();

	vsp_fradia2->get_reading();
	while (vsp_fradia2->get_report() == lib::sensor::VSP_SENSOR_NOT_CONFIGURED)
	{
		vsp_fradia2->get_reading();
	}

	printf("ODCZYT: ");
	std::cout<<std::endl;

	bool correctness = vsp_fradia2->get_reading_message().code_identified;
	long int first_part = vsp_fradia2->get_reading_message().first_part;
	long int second_part = vsp_fradia2->get_reading_message().second_part;


	while(first_part == 0)
	{
		 vsp_fradia2->get_reading();
		 correctness = vsp_fradia2->get_reading_message().code_identified;
		 first_part = vsp_fradia2->get_reading_message().first_part;
		 second_part = vsp_fradia2->get_reading_message().second_part;


		 if(first_part!=0 && correctness ==false)  correct_counter--;
		 else;

		 if(correct_counter<=0) break;
	}

	if(correctness == false && first_part == 9999999 && second_part==999999)
	printf("No barcode was found on the image\n");
	else if(first_part == 0)
	{
	 printf("PROBA\n");


	}
	else
	{
	std::cout<<"CORRECTNESS: "<<correctness <<" IDENTIFIED CODE: "<<first_part;


	if(second_part < 1)		printf("000000");
	else if(second_part < 10)	printf("00000");
	else if(second_part < 100)	printf("0000");
	else if(second_part < 1000)	printf("000");
	else if(second_part < 10000)	printf("00");
	else if(second_part < 100000)printf("0");

	std::cout<<second_part<<std::endl;





	}
	printf("PO CODESCAN\n");
	std::cout<<std::endl;

}

} // namespace sub_task

} // namespace common
} // namespace ecp
} // namespace mrrocpp
