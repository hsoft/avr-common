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
