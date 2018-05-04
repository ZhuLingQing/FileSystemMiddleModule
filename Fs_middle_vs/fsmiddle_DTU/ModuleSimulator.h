#ifndef _MODULE_SIMULATOR_H_
#define _MODULE_SIMULATOR_H_

#if (defined(WIN32) && !defined(__cplusplus))
extern "C" {
#endif

#define NUM_TEST_MEASURE	10
#define NUM_TEST_FROZEN		5

#if NUM_TEST_MEASURE
	extern float test_measure[NUM_TEST_MEASURE];
#else
	extern float *test_measure;
#endif
#if NUM_TEST_FROZEN
	extern float test_frozen[NUM_TEST_FROZEN];
#else
	extern float *test_frozen;
#endif

#if (defined(WIN32) && !defined(__cplusplus))
};
#endif

#endif
