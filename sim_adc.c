#include <Python.h>
#include "adc.h"
#include "sim.h"

void adc_select(ADC_PIN pin)
{
}

void adc_enable()
{
}

unsigned int adc_val()
{
    PyObject *pModule, *pResult;
    long result;

    SIM_LOCKGIL;
    pModule = PyImport_AddModule("__main__");
    pResult = PyObject_CallMethod(pModule, "adcval", "");
    SIM_ERRCHECK(pResult);
    result = PyLong_AsLong(pResult);
    Py_DECREF(pResult);
    SIM_UNLOCKGIL;
    return result;
}

