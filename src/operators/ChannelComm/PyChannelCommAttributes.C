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

#include <PyChannelCommAttributes.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <snprintf.h>

// ****************************************************************************
// Module: PyChannelCommAttributes
//
// Purpose: 
//   Attributes for ChannelComm operator
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a ChannelCommAttributes.
//
struct ChannelCommAttributesObject
{
    PyObject_HEAD
    ChannelCommAttributes *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewChannelCommAttributes(int);

std::string
PyChannelCommAttributes_ToString(const ChannelCommAttributes *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    SNPRINTF(tmpStr, 1000, "%snumInX = %d\n", prefix, atts->GetNumInX());
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%snumInY = %d\n", prefix, atts->GetNumInY());
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%svelocity = \"%s\"\n", prefix, atts->GetVelocity().c_str());
    str += tmpStr;
    return str;
}

static PyObject *
ChannelCommAttributes_Notify(PyObject *self, PyObject *args)
{
    ChannelCommAttributesObject *obj = (ChannelCommAttributesObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ChannelCommAttributes_SetNumInX(PyObject *self, PyObject *args)
{
    ChannelCommAttributesObject *obj = (ChannelCommAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the numInX in the object.
    obj->data->SetNumInX((int)ival);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ChannelCommAttributes_GetNumInX(PyObject *self, PyObject *args)
{
    ChannelCommAttributesObject *obj = (ChannelCommAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetNumInX()));
    return retval;
}

/*static*/ PyObject *
ChannelCommAttributes_SetNumInY(PyObject *self, PyObject *args)
{
    ChannelCommAttributesObject *obj = (ChannelCommAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the numInY in the object.
    obj->data->SetNumInY((int)ival);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ChannelCommAttributes_GetNumInY(PyObject *self, PyObject *args)
{
    ChannelCommAttributesObject *obj = (ChannelCommAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetNumInY()));
    return retval;
}

/*static*/ PyObject *
ChannelCommAttributes_SetVelocity(PyObject *self, PyObject *args)
{
    ChannelCommAttributesObject *obj = (ChannelCommAttributesObject *)self;

    char *str;
    if(!PyArg_ParseTuple(args, "s", &str))
        return NULL;

    // Set the velocity in the object.
    obj->data->SetVelocity(std::string(str));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ChannelCommAttributes_GetVelocity(PyObject *self, PyObject *args)
{
    ChannelCommAttributesObject *obj = (ChannelCommAttributesObject *)self;
    PyObject *retval = PyString_FromString(obj->data->GetVelocity().c_str());
    return retval;
}



PyMethodDef PyChannelCommAttributes_methods[CHANNELCOMMATTRIBUTES_NMETH] = {
    {"Notify", ChannelCommAttributes_Notify, METH_VARARGS},
    {"SetNumInX", ChannelCommAttributes_SetNumInX, METH_VARARGS},
    {"GetNumInX", ChannelCommAttributes_GetNumInX, METH_VARARGS},
    {"SetNumInY", ChannelCommAttributes_SetNumInY, METH_VARARGS},
    {"GetNumInY", ChannelCommAttributes_GetNumInY, METH_VARARGS},
    {"SetVelocity", ChannelCommAttributes_SetVelocity, METH_VARARGS},
    {"GetVelocity", ChannelCommAttributes_GetVelocity, METH_VARARGS},
    {NULL, NULL}
};

//
// Type functions
//

static void
ChannelCommAttributes_dealloc(PyObject *v)
{
   ChannelCommAttributesObject *obj = (ChannelCommAttributesObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static int
ChannelCommAttributes_compare(PyObject *v, PyObject *w)
{
    ChannelCommAttributes *a = ((ChannelCommAttributesObject *)v)->data;
    ChannelCommAttributes *b = ((ChannelCommAttributesObject *)w)->data;
    return (*a == *b) ? 0 : -1;
}

PyObject *
PyChannelCommAttributes_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "numInX") == 0)
        return ChannelCommAttributes_GetNumInX(self, NULL);
    if(strcmp(name, "numInY") == 0)
        return ChannelCommAttributes_GetNumInY(self, NULL);
    if(strcmp(name, "velocity") == 0)
        return ChannelCommAttributes_GetVelocity(self, NULL);

    return Py_FindMethod(PyChannelCommAttributes_methods, self, name);
}

int
PyChannelCommAttributes_setattr(PyObject *self, char *name, PyObject *args)
{
    // Create a tuple to contain the arguments since all of the Set
    // functions expect a tuple.
    PyObject *tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, args);
    Py_INCREF(args);
    PyObject *obj = NULL;

    if(strcmp(name, "numInX") == 0)
        obj = ChannelCommAttributes_SetNumInX(self, tuple);
    else if(strcmp(name, "numInY") == 0)
        obj = ChannelCommAttributes_SetNumInY(self, tuple);
    else if(strcmp(name, "velocity") == 0)
        obj = ChannelCommAttributes_SetVelocity(self, tuple);

    if(obj != NULL)
        Py_DECREF(obj);

    Py_DECREF(tuple);
    if( obj == NULL)
        PyErr_Format(PyExc_RuntimeError, "Unable to set unknown attribute: '%s'", name);
    return (obj != NULL) ? 0 : -1;
}

static int
ChannelCommAttributes_print(PyObject *v, FILE *fp, int flags)
{
    ChannelCommAttributesObject *obj = (ChannelCommAttributesObject *)v;
    fprintf(fp, "%s", PyChannelCommAttributes_ToString(obj->data, "").c_str());
    return 0;
}

PyObject *
ChannelCommAttributes_str(PyObject *v)
{
    ChannelCommAttributesObject *obj = (ChannelCommAttributesObject *)v;
    return PyString_FromString(PyChannelCommAttributes_ToString(obj->data,"").c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *ChannelCommAttributes_Purpose = "Attributes for ChannelComm operator";
#else
static char *ChannelCommAttributes_Purpose = "Attributes for ChannelComm operator";
#endif

//
// The type description structure
//
static PyTypeObject ChannelCommAttributesType =
{
    //
    // Type header
    //
    PyObject_HEAD_INIT(&PyType_Type)
    0,                                   // ob_size
    "ChannelCommAttributes",                    // tp_name
    sizeof(ChannelCommAttributesObject),        // tp_basicsize
    0,                                   // tp_itemsize
    //
    // Standard methods
    //
    (destructor)ChannelCommAttributes_dealloc,  // tp_dealloc
    (printfunc)ChannelCommAttributes_print,     // tp_print
    (getattrfunc)PyChannelCommAttributes_getattr, // tp_getattr
    (setattrfunc)PyChannelCommAttributes_setattr, // tp_setattr
    (cmpfunc)ChannelCommAttributes_compare,     // tp_compare
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
    (reprfunc)ChannelCommAttributes_str,        // tp_str
    0,                                   // tp_getattro
    0,                                   // tp_setattro
    0,                                   // tp_as_buffer
    Py_TPFLAGS_CHECKTYPES,               // tp_flags
    ChannelCommAttributes_Purpose,              // tp_doc
    0,                                   // tp_traverse
    0,                                   // tp_clear
    0,                                   // tp_richcompare
    0                                    // tp_weaklistoffset
};

//
// Helper functions for object allocation.
//

static ChannelCommAttributes *defaultAtts = 0;
static ChannelCommAttributes *currentAtts = 0;

static PyObject *
NewChannelCommAttributes(int useCurrent)
{
    ChannelCommAttributesObject *newObject;
    newObject = PyObject_NEW(ChannelCommAttributesObject, &ChannelCommAttributesType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new ChannelCommAttributes(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new ChannelCommAttributes(*defaultAtts);
    else
        newObject->data = new ChannelCommAttributes;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapChannelCommAttributes(const ChannelCommAttributes *attr)
{
    ChannelCommAttributesObject *newObject;
    newObject = PyObject_NEW(ChannelCommAttributesObject, &ChannelCommAttributesType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (ChannelCommAttributes *)attr;
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
ChannelCommAttributes_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewChannelCommAttributes(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef ChannelCommAttributesMethods[] = {
    {"ChannelCommAttributes", ChannelCommAttributes_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *ChannelCommAttributesObserver = 0;

std::string
PyChannelCommAttributes_GetLogString()
{
    std::string s("ChannelCommAtts = ChannelCommAttributes()\n");
    if(currentAtts != 0)
        s += PyChannelCommAttributes_ToString(currentAtts, "ChannelCommAtts.");
    return s;
}

static void
PyChannelCommAttributes_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("ChannelCommAtts = ChannelCommAttributes()\n");
        s += PyChannelCommAttributes_ToString(currentAtts, "ChannelCommAtts.");
        cb(s);
    }
}

void
PyChannelCommAttributes_StartUp(ChannelCommAttributes *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PyChannelCommAttributes_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(ChannelCommAttributesObserver == 0)
    {
        ChannelCommAttributesObserver = new ObserverToCallback(subj,
            PyChannelCommAttributes_CallLogRoutine, (void *)data);
    }

}

void
PyChannelCommAttributes_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete ChannelCommAttributesObserver;
    ChannelCommAttributesObserver = 0;
}

PyMethodDef *
PyChannelCommAttributes_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return ChannelCommAttributesMethods;
}

bool
PyChannelCommAttributes_Check(PyObject *obj)
{
    return (obj->ob_type == &ChannelCommAttributesType);
}

ChannelCommAttributes *
PyChannelCommAttributes_FromPyObject(PyObject *obj)
{
    ChannelCommAttributesObject *obj2 = (ChannelCommAttributesObject *)obj;
    return obj2->data;
}

PyObject *
PyChannelCommAttributes_New()
{
    return NewChannelCommAttributes(0);
}

PyObject *
PyChannelCommAttributes_Wrap(const ChannelCommAttributes *attr)
{
    return WrapChannelCommAttributes(attr);
}

void
PyChannelCommAttributes_SetParent(PyObject *obj, PyObject *parent)
{
    ChannelCommAttributesObject *obj2 = (ChannelCommAttributesObject *)obj;
    obj2->parent = parent;
}

void
PyChannelCommAttributes_SetDefaults(const ChannelCommAttributes *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new ChannelCommAttributes(*atts);
}

