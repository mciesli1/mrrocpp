/*
 * $Id$
 *
 *  Created on: Mar 3, 2010
 *      Author: mboryn
 */

#ifndef VISUAL_SERVO_REGULATOR_P_H_
#define VISUAL_SERVO_REGULATOR_P_H_

#include "visual_servo_regulator.h"

namespace mrrocpp {

namespace ecp {

namespace servovision {

/** @addtogroup servovision
 *  @{
 */

/**
 *
 */
class regulator_p: public visual_servo_regulator
{
public:
	regulator_p(const lib::configurator & config, const std::string& config_section_name) :
		visual_servo_regulator(config, config_section_name)
	{
		Kp = config.value <6, 6> ("regulator_kp_matrix", config_section_name);
		std::cout << "regulator_p: Kp:\n" << Kp << "\n\n";
		std::cout.flush();
	}

	virtual ~regulator_p()
	{
	}
	virtual const Eigen::Matrix <double, 6, 1> & compute_control(const Eigen::Matrix <double, 6, 1> & error, double dt)
	{
		this->computed_control = Kp * error;
		return this->computed_control;
	}
protected:
	Eigen::Matrix <double, 6, 6> Kp;
}; // class regulator_p

/** @} */

} // namespace servovision
}
}

#endif /* VISUAL_SERVO_REGULATOR_P_H_ */
