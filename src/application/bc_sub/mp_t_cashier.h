#if !defined(__MP_T_CASHIER_H)
#define __MP_T_CASHIER_H

/*!
 * @file
 * @brief File contains cashier mp_task class declaration of barcode localization and reading application.
 * @author Marcin Cieslik
 *
 */

namespace mrrocpp {
namespace mp {
namespace task {

/*!
 * @brief Task that executes barcode localization and reading process divided into subtasks
 * @author Marcin Cieslik
 */
class cashier : public task
{
protected:

public:

	/**
	 * @brief Constructor
	 * @param _config configurator object reference.
	 */
	cashier(lib::configurator &_config);
	/**
	 * @brief Function that creates robots basing on configuration file
	 * @param void
	 */
	void create_robots(void);
	/**
	 * @brief Main task algorithm
	 * @param void
	 */
	void main_task_algorithm(void);
};

} // namespace task
} // namespace mp
} // namespace mrrocpp

#endif
