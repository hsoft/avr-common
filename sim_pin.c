#include <Python.h>
#include "pin.h"
#include "sim.h"

void pinhigh(Pin pin)
{
    pinset(pin, true);
}

void pinlow(Pin pin)
{
    pinset(pin, false);
}

void pinset(Pin pin, bool high)
{
    PyObject *pModule, *pResult;

    SIM_LOCKGIL;
    pModule = PyImport_AddModule("__main__");
    pResult = PyObject_CallMethod(pModule, "pinset", "bb", pin, high);
    SIM_ERRCHECK(pResult);
    Py_DECREF(pResult);
    SIM_UNLOCKGIL;
}

void pintoggle(Pin pin)
{
    pinset(pin, !pinishigh(pin));
}

bool pinishigh(Pin pin)
{
    PyObject *pModule, *pResult;
    long result;

    SIM_LOCKGIL;
    pModule = PyImport_AddModule("__main__");
    pResult = PyObject_CallMethod(pModule, "pinishigh", "b", pin);
    SIM_ERRCHECK(pResult);
    result = PyLong_AsLong(pResult);
    Py_DECREF(pResult);
    SIM_UNLOCKGIL;
    return result;
}

void pininputmode(Pin pin)
{
}

void pinoutputmode(Pin pin)
{
}

