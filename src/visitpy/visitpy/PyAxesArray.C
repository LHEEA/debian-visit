/*****************************************************************************
*
* Copyright (c) 2000 - 2017, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#include <PyAxesArray.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <snprintf.h>
#include <PyAxisAttributes.h>

// ****************************************************************************
// Module: PyAxesArray
//
// Purpose: 
//   Contains the properties for the array axes.
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a AxesArray.
//
struct AxesArrayObject
{
    PyObject_HEAD
    AxesArray *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewAxesArray(int);

std::string
PyAxesArray_ToString(const AxesArray *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    if(atts->GetVisible())
        SNPRINTF(tmpStr, 1000, "%svisible = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%svisible = 0\n", prefix);
    str += tmpStr;
    if(atts->GetTicksVisible())
        SNPRINTF(tmpStr, 1000, "%sticksVisible = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%sticksVisible = 0\n", prefix);
    str += tmpStr;
    if(atts->GetAutoSetTicks())
        SNPRINTF(tmpStr, 1000, "%sautoSetTicks = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%sautoSetTicks = 0\n", prefix);
    str += tmpStr;
    if(atts->GetAutoSetScaling())
        SNPRINTF(tmpStr, 1000, "%sautoSetScaling = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%sautoSetScaling = 0\n", prefix);
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%slineWidth = %d\n", prefix, atts->GetLineWidth());
    str += tmpStr;
    { // new scope
        std::string objPrefix(prefix);
        objPrefix += "axes.";
        str += PyAxisAttributes_ToString(&atts->GetAxes(), objPrefix.c_str());
    }
    return str;
}

static PyObject *
AxesArray_Notify(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
AxesArray_SetVisible(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the visible in the object.
    obj->data->SetVisible(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
AxesArray_GetVisible(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetVisible()?1L:0L);
    return retval;
}

/*static*/ PyObject *
AxesArray_SetTicksVisible(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the ticksVisible in the object.
    obj->data->SetTicksVisible(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
AxesArray_GetTicksVisible(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetTicksVisible()?1L:0L);
    return retval;
}

/*static*/ PyObject *
AxesArray_SetAutoSetTicks(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the autoSetTicks in the object.
    obj->data->SetAutoSetTicks(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
AxesArray_GetAutoSetTicks(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetAutoSetTicks()?1L:0L);
    return retval;
}

/*static*/ PyObject *
AxesArray_SetAutoSetScaling(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the autoSetScaling in the object.
    obj->data->SetAutoSetScaling(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
AxesArray_GetAutoSetScaling(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetAutoSetScaling()?1L:0L);
    return retval;
}

/*static*/ PyObject *
AxesArray_SetLineWidth(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the lineWidth in the object.
    obj->data->SetLineWidth(ival);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
AxesArray_GetLineWidth(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetLineWidth()));
    return retval;
}

/*static*/ PyObject *
AxesArray_SetAxes(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;

    PyObject *newValue = NULL;
    if(!PyArg_ParseTuple(args, "O", &newValue))
        return NULL;
    if(!PyAxisAttributes_Check(newValue))
    {
        fprintf(stderr, "The axes field can only be set with AxisAttributes objects.\n");
        return NULL;
    }

    obj->data->SetAxes(*PyAxisAttributes_FromPyObject(newValue));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
AxesArray_GetAxes(PyObject *self, PyObject *args)
{
    AxesArrayObject *obj = (AxesArrayObject *)self;
    // Since the new object will point to data owned by this object,
    // we need to increment the reference count.
    Py_INCREF(self);

    PyObject *retval = PyAxisAttributes_Wrap(&obj->data->GetAxes());
    // Set the object's parent so the reference to the parent can be decref'd
    // when the child goes out of scope.
    PyAxisAttributes_SetParent(retval, self);

    return retval;
}



PyMethodDef PyAxesArray_methods[AXESARRAY_NMETH] = {
    {"Notify", AxesArray_Notify, METH_VARARGS},
    {"SetVisible", AxesArray_SetVisible, METH_VARARGS},
    {"GetVisible", AxesArray_GetVisible, METH_VARARGS},
    {"SetTicksVisible", AxesArray_SetTicksVisible, METH_VARARGS},
    {"GetTicksVisible", AxesArray_GetTicksVisible, METH_VARARGS},
    {"SetAutoSetTicks", AxesArray_SetAutoSetTicks, METH_VARARGS},
    {"GetAutoSetTicks", AxesArray_GetAutoSetTicks, METH_VARARGS},
    {"SetAutoSetScaling", AxesArray_SetAutoSetScaling, METH_VARARGS},
    {"GetAutoSetScaling", AxesArray_GetAutoSetScaling, METH_VARARGS},
    {"SetLineWidth", AxesArray_SetLineWidth, METH_VARARGS},
    {"GetLineWidth", AxesArray_GetLineWidth, METH_VARARGS},
    {"SetAxes", AxesArray_SetAxes, METH_VARARGS},
    {"GetAxes", AxesArray_GetAxes, METH_VARARGS},
    {NULL, NULL}
};

//
// Type functions
//

static void
AxesArray_dealloc(PyObject *v)
{
   AxesArrayObject *obj = (AxesArrayObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static int
AxesArray_compare(PyObject *v, PyObject *w)
{
    AxesArray *a = ((AxesArrayObject *)v)->data;
    AxesArray *b = ((AxesArrayObject *)w)->data;
    return (*a == *b) ? 0 : -1;
}

PyObject *
PyAxesArray_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "visible") == 0)
        return AxesArray_GetVisible(self, NULL);
    if(strcmp(name, "ticksVisible") == 0)
        return AxesArray_GetTicksVisible(self, NULL);
    if(strcmp(name, "autoSetTicks") == 0)
        return AxesArray_GetAutoSetTicks(self, NULL);
    if(strcmp(name, "autoSetScaling") == 0)
        return AxesArray_GetAutoSetScaling(self, NULL);
    if(strcmp(name, "lineWidth") == 0)
        return AxesArray_GetLineWidth(self, NULL);
    if(strcmp(name, "axes") == 0)
        return AxesArray_GetAxes(self, NULL);

    return Py_FindMethod(PyAxesArray_methods, self, name);
}

int
PyAxesArray_setattr(PyObject *self, char *name, PyObject *args)
{
    // Create a tuple to contain the arguments since all of the Set
    // functions expect a tuple.
    PyObject *tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, args);
    Py_INCREF(args);
    PyObject *obj = NULL;

    if(strcmp(name, "visible") == 0)
        obj = AxesArray_SetVisible(self, tuple);
    else if(strcmp(name, "ticksVisible") == 0)
        obj = AxesArray_SetTicksVisible(self, tuple);
    else if(strcmp(name, "autoSetTicks") == 0)
        obj = AxesArray_SetAutoSetTicks(self, tuple);
    else if(strcmp(name, "autoSetScaling") == 0)
        obj = AxesArray_SetAutoSetScaling(self, tuple);
    else if(strcmp(name, "lineWidth") == 0)
        obj = AxesArray_SetLineWidth(self, tuple);
    else if(strcmp(name, "axes") == 0)
        obj = AxesArray_SetAxes(self, tuple);

    if(obj != NULL)
        Py_DECREF(obj);

    Py_DECREF(tuple);
    if( obj == NULL)
        PyErr_Format(PyExc_RuntimeError, "Unable to set unknown attribute: '%s'", name);
    return (obj != NULL) ? 0 : -1;
}

static int
AxesArray_print(PyObject *v, FILE *fp, int flags)
{
    AxesArrayObject *obj = (AxesArrayObject *)v;
    fprintf(fp, "%s", PyAxesArray_ToString(obj->data, "").c_str());
    return 0;
}

PyObject *
AxesArray_str(PyObject *v)
{
    AxesArrayObject *obj = (AxesArrayObject *)v;
    return PyString_FromString(PyAxesArray_ToString(obj->data,"").c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *AxesArray_Purpose = "Contains the properties for the array axes.";
#else
static char *AxesArray_Purpose = "Contains the properties for the array axes.";
#endif

//
// The type description structure
//
static PyTypeObject AxesArrayType =
{
    //
    // Type header
    //
    PyObject_HEAD_INIT(&PyType_Type)
    0,                                   // ob_size
    "AxesArray",                    // tp_name
    sizeof(AxesArrayObject),        // tp_basicsize
    0,                                   // tp_itemsize
    //
    // Standard methods
    //
    (destructor)AxesArray_dealloc,  // tp_dealloc
    (printfunc)AxesArray_print,     // tp_print
    (getattrfunc)PyAxesArray_getattr, // tp_getattr
    (setattrfunc)PyAxesArray_setattr, // tp_setattr
    (cmpfunc)AxesArray_compare,     // tp_compare
    (reprfunc)0,                         // tp_repr
    //
    // Type categories
    //
    0,                                   // tp_as_number
    0,                                   // tp_as_sequence
    0,                                   // tp_as_mapping
    //
    // More methods
    //
    0,                                   // tp_hash
    0,                                   // tp_call
    (reprfunc)AxesArray_str,        // tp_str
    0,                                   // tp_getattro
    0,                                   // tp_setattro
    0,                                   // tp_as_buffer
    Py_TPFLAGS_CHECKTYPES,               // tp_flags
    AxesArray_Purpose,              // tp_doc
    0,                                   // tp_traverse
    0,                                   // tp_clear
    0,                                   // tp_richcompare
    0                                    // tp_weaklistoffset
};

//
// Helper functions for object allocation.
//

static AxesArray *defaultAtts = 0;
static AxesArray *currentAtts = 0;

static PyObject *
NewAxesArray(int useCurrent)
{
    AxesArrayObject *newObject;
    newObject = PyObject_NEW(AxesArrayObject, &AxesArrayType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new AxesArray(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new AxesArray(*defaultAtts);
    else
        newObject->data = new AxesArray;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapAxesArray(const AxesArray *attr)
{
    AxesArrayObject *newObject;
    newObject = PyObject_NEW(AxesArrayObject, &AxesArrayType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (AxesArray *)attr;
    newObject->owns = false;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

///////////////////////////////////////////////////////////////////////////////
//
// Interface that is exposed to the VisIt module.
//
///////////////////////////////////////////////////////////////////////////////

PyObject *
AxesArray_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewAxesArray(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef AxesArrayMethods[] = {
    {"AxesArray", AxesArray_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *AxesArrayObserver = 0;

std::string
PyAxesArray_GetLogString()
{
    std::string s("AxesArray = AxesArray()\n");
    if(currentAtts != 0)
        s += PyAxesArray_ToString(currentAtts, "AxesArray.");
    return s;
}

static void
PyAxesArray_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("AxesArray = AxesArray()\n");
        s += PyAxesArray_ToString(currentAtts, "AxesArray.");
        cb(s);
    }
}

void
PyAxesArray_StartUp(AxesArray *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PyAxesArray_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(AxesArrayObserver == 0)
    {
        AxesArrayObserver = new ObserverToCallback(subj,
            PyAxesArray_CallLogRoutine, (void *)data);
    }

}

void
PyAxesArray_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete AxesArrayObserver;
    AxesArrayObserver = 0;
}

PyMethodDef *
PyAxesArray_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return AxesArrayMethods;
}

bool
PyAxesArray_Check(PyObject *obj)
{
    return (obj->ob_type == &AxesArrayType);
}

AxesArray *
PyAxesArray_FromPyObject(PyObject *obj)
{
    AxesArrayObject *obj2 = (AxesArrayObject *)obj;
    return obj2->data;
}

PyObject *
PyAxesArray_New()
{
    return NewAxesArray(0);
}

PyObject *
PyAxesArray_Wrap(const AxesArray *attr)
{
    return WrapAxesArray(attr);
}

void
PyAxesArray_SetParent(PyObject *obj, PyObject *parent)
{
    AxesArrayObject *obj2 = (AxesArrayObject *)obj;
    obj2->parent = parent;
}

void
PyAxesArray_SetDefaults(const AxesArray *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new AxesArray(*atts);
}

