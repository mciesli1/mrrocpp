/*!
 * @file sr_ecp.cc
 * @brief System reporter class for ECP - definitions.
 *
 * @author Piotr Trojanek <piotr.trojanek@gmail.com>
 *
 * @ingroup LIB
 */

#include "base/lib/sr/srlib.h"

#ifndef SR_ECP_H_
#define SR_ECP_H_

namespace mrrocpp {
namespace lib {

//! SR class for use in ECP
class sr_ecp : public sr
{
public:
	/**
	 * Constructor
	 * @param process_type reporting process type
	 * @param process_name reporting process name
	 * @param sr_channel_name name of the SR communication channel
	 * @param _multi_thread flag for selecting multi-threaded variant
	 */
	sr_ecp(process_type_t process_type, const std::string & process_name, const std::string & sr_channel_name, bool _multi_thread =	false);

protected:
	//! Interpret the status code into a text message
	virtual void interpret(void);
};

} // namespace lib
} // namespace mrrocpp

#endif /* SR_ECP_H_ */
