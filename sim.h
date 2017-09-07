// In simulation, we define a F_CPU where one cycle == 1us
#define F_CPU 1000000

#define SIM_LOCKGIL PyGILState_STATE gilState = PyGILState_Ensure()
#define SIM_UNLOCKGIL PyGILState_Release(gilState)
#define SIM_ERRCHECK(x) if (x == NULL) {PyErr_Print();}
