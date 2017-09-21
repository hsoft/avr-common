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

bool interrupt_check(const char *funcname)
{
    PyObject *pModule, *pResult;
    long result;

    SIM_LOCKGIL;
    pModule = PyImport_AddModule("__main__");
    pResult = PyObject_CallMethod(pModule, funcname, "");
    SIM_ERRCHECK(pResult);
    result = PyLong_AsLong(pResult);
    Py_DECREF(pResult);
    SIM_UNLOCKGIL;
    return result;
}

bool int0_interrupt_check()
{
    return interrupt_check("int0_interrupt_check");
}

bool int1_interrupt_check()
{
    return interrupt_check("int1_interrupt_check");
}

bool timer0_interrupt_check()
{
    return interrupt_check("timer0_interrupt_check");
}

bool timer1_interrupt_check()
{
    return interrupt_check("timer1_interrupt_check");
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
