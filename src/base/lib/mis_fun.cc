/*!
 * @file mis_fun.cc
 * @brief Thread utility functions.
 *
 * @author Piotr Trojanek <piotr.trojanek@gmail.com>
 *
 * @ingroup LIB
 */

#include <pthread.h>
#include <cstdio>

#include "base/lib/mis_fun.h"

#if defined(linux)
#include <sys/prctl.h>
#elif defined(__FreeBSD__)
#include <pthread_np.h>
#endif

namespace mrrocpp {
namespace lib {

void set_thread_priority(pthread_t thread, int sched_priority_l)
{
	int policy;
	struct sched_param param;
	if (pthread_getschedparam(thread, &policy, &param)) {
		perror("pthread_getschedparam()");
	}

	// check priority range
	int policy_priority_min = sched_get_priority_min(policy);
	if (policy_priority_min == -1) {
		perror("sched_get_priority_min()");
	}

	int policy_priority_max = sched_get_priority_max(policy);
	if (policy_priority_max == -1) {
		perror("sched_get_priority_max()");
	}

	if ((sched_priority_l < policy_priority_min) || (sched_priority_l > policy_priority_max)) {
		// TODO: rewrite static variable with pthread_once
		static bool warned = true; // priorities warning apply only to Linux, skip for now
		if (!warned)
			fprintf(stderr, "requested thread priority (%d) not in <%d:%d> priority range\n", sched_priority_l, policy_priority_min, policy_priority_max);
		//		warned = true;
	} else {
		param.sched_priority = sched_priority_l;
		if (pthread_setschedparam(thread, policy, &param)) {
			perror("pthread_setschedparam()");
		}
	}
}

//! set the thread name for debugging
int set_thread_name(const char * newname)
{
#if defined(__QNXNTO__)
	return pthread_setname_np(pthread_self(), newname);
#elif defined(linux)
	char comm[16];
	snprintf(comm, sizeof(comm), "%s", newname);
	return prctl(PR_SET_NAME, comm, 0l, 0l, 0l);
#elif defined(__FreeBSD__)
	// FreeBSD defines this call to void
	pthread_set_name_np(pthread_self(), newname);

	return 0;
#endif
	return -1;
}

} // namespace lib
} // namespace mrrocpp
