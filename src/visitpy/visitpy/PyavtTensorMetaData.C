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

#include <PyavtTensorMetaData.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <snprintf.h>

// ****************************************************************************
// Module: PyavtTensorMetaData
//
// Purpose: 
//   Contains tensor metadata attributes
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a avtTensorMetaData.
//
struct avtTensorMetaDataObject
{
    PyObject_HEAD
    avtTensorMetaData *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewavtTensorMetaData(int);

std::string
PyavtTensorMetaData_ToString(const avtTensorMetaData *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    str = PyavtVarMetaData_ToString(atts, prefix);

    SNPRINTF(tmpStr, 1000, "%sdim = %d\n", prefix, atts->dim);
    str += tmpStr;
    return str;
}

static PyObject *
avtTensorMetaData_Notify(PyObject *self, PyObject *args)
{
    avtTensorMetaDataObject *obj = (avtTensorMetaDataObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
avtTensorMetaData_SetDim(PyObject *self, PyObject *args)
{
    avtTensorMetaDataObject *obj = (avtTensorMetaDataObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the dim in the object.
    obj->data->dim = (int)ival;

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
avtTensorMetaData_GetDim(PyObject *self, PyObject *args)
{
    avtTensorMetaDataObject *obj = (avtTensorMetaDataObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->dim));
    return retval;
}



PyMethodDef PyavtTensorMetaData_methods[AVTTENSORMETADATA_NMETH] = {
    {"Notify", avtTensorMetaData_Notify, METH_VARARGS},
    {"SetDim", avtTensorMetaData_SetDim, METH_VARARGS},
    {"GetDim", avtTensorMetaData_GetDim, METH_VARARGS},
    {NULL, NULL}
};

static void PyavtTensorMetaData_ExtendSetGetMethodTable()
{
    static bool extended = false;
    if (extended) return;
    extended = true;

    int i = 0;
    while (PyavtTensorMetaData_methods[i].ml_name)
        i++;
    int n = i;
    while (PyavtVarMetaData_methods[i-n+1].ml_name)
    {
        PyavtTensorMetaData_methods[i] = PyavtVarMetaData_methods[i-n+1];
        i++;
    }

    PyMethodDef nullMethod = {NULL, NULL};
    PyavtTensorMetaData_methods[i] = nullMethod;
}

//
// Type functions
//

static void
avtTensorMetaData_dealloc(PyObject *v)
{
   avtTensorMetaDataObject *obj = (avtTensorMetaDataObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static int
avtTensorMetaData_compare(PyObject *v, PyObject *w)
{
    avtTensorMetaData *a = ((avtTensorMetaDataObject *)v)->data;
    avtTensorMetaData *b = ((avtTensorMetaDataObject *)w)->data;
    return (*a == *b) ? 0 : -1;
}

PyObject *
PyavtTensorMetaData_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "dim") == 0)
        return avtTensorMetaData_GetDim(self, NULL);

    if(strcmp(name, "__methods__") != 0)
    {
        PyObject *retval = PyavtVarMetaData_getattr(self, name);
        if (retval) return retval;
    }

    PyavtTensorMetaData_ExtendSetGetMethodTable();

    return Py_FindMethod(PyavtTensorMetaData_methods, self, name);
}

int
PyavtTensorMetaData_setattr(PyObject *self, char *name, PyObject *args)
{
    if (PyavtVarMetaData_setattr(self, name, args) != -1)
        return 0;
    else
        PyErr_Clear();

    // Create a tuple to contain the arguments since all of the Set
    // functions expect a tuple.
    PyObject *tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, args);
    Py_INCREF(args);
    PyObject *obj = NULL;

    if(strcmp(name, "dim") == 0)
        obj = avtTensorMetaData_SetDim(self, tuple);

    if(obj != NULL)
        Py_DECREF(obj);

    Py_DECREF(tuple);
    if( obj == NULL)
        PyErr_Format(PyExc_RuntimeError, "Unable to set unknown attribute: '%s'", name);
    return (obj != NULL) ? 0 : -1;
}

static int
avtTensorMetaData_print(PyObject *v, FILE *fp, int flags)
{
    avtTensorMetaDataObject *obj = (avtTensorMetaDataObject *)v;
    fprintf(fp, "%s", PyavtTensorMetaData_ToString(obj->data, "").c_str());
    return 0;
}

PyObject *
avtTensorMetaData_str(PyObject *v)
{
    avtTensorMetaDataObject *obj = (avtTensorMetaDataObject *)v;
    return PyString_FromString(PyavtTensorMetaData_ToString(obj->data,"").c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *avtTensorMetaData_Purpose = "Contains tensor metadata attributes";
#else
static char *avtTensorMetaData_Purpose = "Contains tensor metadata attributes";
#endif

//
// The type description structure
//
static PyTypeObject avtTensorMetaDataType =
{
    //
    // Type header
    //
    PyObject_HEAD_INIT(&PyType_Type)
    0,                                   // ob_size
    "avtTensorMetaData",                    // tp_name
    sizeof(avtTensorMetaDataObject),        // tp_basicsize
    0,                                   // tp_itemsize
    //
    // Standard methods
    //
    (destructor)avtTensorMetaData_dealloc,  // tp_dealloc
    (printfunc)avtTensorMetaData_print,     // tp_print
    (getattrfunc)PyavtTensorMetaData_getattr, // tp_getattr
    (setattrfunc)PyavtTensorMetaData_setattr, // tp_setattr
    (cmpfunc)avtTensorMetaData_compare,     // tp_compare
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
    (reprfunc)avtTensorMetaData_str,        // tp_str
    0,                                   // tp_getattro
    0,                                   // tp_setattro
    0,                                   // tp_as_buffer
    Py_TPFLAGS_CHECKTYPES,               // tp_flags
    avtTensorMetaData_Purpose,              // tp_doc
    0,                                   // tp_traverse
    0,                                   // tp_clear
    0,                                   // tp_richcompare
    0                                    // tp_weaklistoffset
};

//
// Helper functions for object allocation.
//

static avtTensorMetaData *defaultAtts = 0;
static avtTensorMetaData *currentAtts = 0;

static PyObject *
NewavtTensorMetaData(int useCurrent)
{
    avtTensorMetaDataObject *newObject;
    newObject = PyObject_NEW(avtTensorMetaDataObject, &avtTensorMetaDataType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new avtTensorMetaData(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new avtTensorMetaData(*defaultAtts);
    else
        newObject->data = new avtTensorMetaData;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapavtTensorMetaData(const avtTensorMetaData *attr)
{
    avtTensorMetaDataObject *newObject;
    newObject = PyObject_NEW(avtTensorMetaDataObject, &avtTensorMetaDataType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (avtTensorMetaData *)attr;
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
avtTensorMetaData_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewavtTensorMetaData(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef avtTensorMetaDataMethods[] = {
    {"avtTensorMetaData", avtTensorMetaData_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *avtTensorMetaDataObserver = 0;

std::string
PyavtTensorMetaData_GetLogString()
{
    std::string s("avtTensorMetaData = avtTensorMetaData()\n");
    if(currentAtts != 0)
        s += PyavtTensorMetaData_ToString(currentAtts, "avtTensorMetaData.");
    return s;
}

static void
PyavtTensorMetaData_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("avtTensorMetaData = avtTensorMetaData()\n");
        s += PyavtTensorMetaData_ToString(currentAtts, "avtTensorMetaData.");
        cb(s);
    }
}

void
PyavtTensorMetaData_StartUp(avtTensorMetaData *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PyavtTensorMetaData_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(avtTensorMetaDataObserver == 0)
    {
        avtTensorMetaDataObserver = new ObserverToCallback(subj,
            PyavtTensorMetaData_CallLogRoutine, (void *)data);
    }

}

void
PyavtTensorMetaData_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete avtTensorMetaDataObserver;
    avtTensorMetaDataObserver = 0;
}

PyMethodDef *
PyavtTensorMetaData_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return avtTensorMetaDataMethods;
}

bool
PyavtTensorMetaData_Check(PyObject *obj)
{
    return (obj->ob_type == &avtTensorMetaDataType);
}

avtTensorMetaData *
PyavtTensorMetaData_FromPyObject(PyObject *obj)
{
    avtTensorMetaDataObject *obj2 = (avtTensorMetaDataObject *)obj;
    return obj2->data;
}

PyObject *
PyavtTensorMetaData_New()
{
    return NewavtTensorMetaData(0);
}

PyObject *
PyavtTensorMetaData_Wrap(const avtTensorMetaData *attr)
{
    return WrapavtTensorMetaData(attr);
}

void
PyavtTensorMetaData_SetParent(PyObject *obj, PyObject *parent)
{
    avtTensorMetaDataObject *obj2 = (avtTensorMetaDataObject *)obj;
    obj2->parent = parent;
}

void
PyavtTensorMetaData_SetDefaults(const avtTensorMetaData *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new avtTensorMetaData(*atts);
}

