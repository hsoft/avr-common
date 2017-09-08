#include <Python.h>
#include "timer.h"
#include "sim.h"

bool set_timer0_target(unsigned long ticks)
{
    return true;
}

bool set_timer1_target(unsigned long ticks)
{
    PyObject *pModule, *pResult;

    SIM_LOCKGIL;
    pModule = PyImport_AddModule("__main__");
    pResult = PyObject_CallMethod(pModule, "set_timer1_target", "l", ticks);
    SIM_ERRCHECK(pResult);
    Py_DECREF(pResult);
    SIM_UNLOCKGIL;
    return true;
}

void set_timer1_mode(TIMER_MODE mode)
{
    PyObject *pModule, *pResult;

    SIM_LOCKGIL;
    pModule = PyImport_AddModule("__main__");
    pResult = PyObject_CallMethod(pModule, "set_timer1_mode", "b", mode);
    SIM_ERRCHECK(pResult);
    Py_DECREF(pResult);
    SIM_UNLOCKGIL;
}

unsigned long get_timer1_rescaled_tcnt()
{
    PyObject *pModule, *pResult;
    long result;

    SIM_LOCKGIL;
    pModule = PyImport_AddModule("__main__");
    pResult = PyObject_CallMethod(pModule, "get_timer1_ticks", "");
    SIM_ERRCHECK(pResult);
    result = PyLong_AsLong(pResult);
    Py_DECREF(pResult);
    SIM_UNLOCKGIL;
    return result;
}

unsigned long ticks_to_msecs(unsigned long ticks)
{
    // If we have F_CPU/1000 ticks per msecs, we can divide ticks by (F_CPU/1000) to get msecs
    return ticks / (F_CPU / 1000);
}
