#include <Python.h>
#include "sim.h"

void _delay_us(unsigned int usecs)
{
    PyObject *pModule, *pResult;

    SIM_LOCKGIL;
    pModule = PyImport_AddModule("__main__");
    pResult = PyObject_CallMethod(pModule, "delay", "i", usecs);
    SIM_ERRCHECK(pResult);
    Py_DECREF(pResult);
    SIM_UNLOCKGIL;
}

void _delay_ms(unsigned int msecs)
{
    _delay_us(msecs * 1000);
}

bool timer1_interrupt_check()
{
    PyObject *pModule, *pResult;
    long result;

    SIM_LOCKGIL;
    pModule = PyImport_AddModule("__main__");
    pResult = PyObject_CallMethod(pModule, "timer1_interrupt_check", "");
    SIM_ERRCHECK(pResult);
    result = PyLong_AsLong(pResult);
    Py_DECREF(pResult);
    SIM_UNLOCKGIL;
    return result;
}

void sim_stop()
{
    PyObject *pModule, *pResult;

    SIM_LOCKGIL;
    pModule = PyImport_AddModule("__main__");
    pResult = PyObject_CallMethod(pModule, "stop", "");
    SIM_ERRCHECK(pResult);
    Py_DECREF(pResult);
    SIM_UNLOCKGIL;
}
