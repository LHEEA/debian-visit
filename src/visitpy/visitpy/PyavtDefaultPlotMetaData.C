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

#include <PyavtDefaultPlotMetaData.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <snprintf.h>

// ****************************************************************************
// Module: PyavtDefaultPlotMetaData
//
// Purpose: 
//   Contains default plot metadata attributes
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a avtDefaultPlotMetaData.
//
struct avtDefaultPlotMetaDataObject
{
    PyObject_HEAD
    avtDefaultPlotMetaData *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewavtDefaultPlotMetaData(int);

std::string
PyavtDefaultPlotMetaData_ToString(const avtDefaultPlotMetaData *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    SNPRINTF(tmpStr, 1000, "%spluginID = \"%s\"\n", prefix, atts->pluginID.c_str());
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%splotVar = \"%s\"\n", prefix, atts->plotVar.c_str());
    str += tmpStr;
    {   const stringVector &plotAttributes = atts->plotAttributes;
        SNPRINTF(tmpStr, 1000, "%splotAttributes = (", prefix);
        str += tmpStr;
        for(size_t i = 0; i < plotAttributes.size(); ++i)
        {
            SNPRINTF(tmpStr, 1000, "\"%s\"", plotAttributes[i].c_str());
            str += tmpStr;
            if(i < plotAttributes.size() - 1)
            {
                SNPRINTF(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        SNPRINTF(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    return str;
}

static PyObject *
avtDefaultPlotMetaData_Notify(PyObject *self, PyObject *args)
{
    avtDefaultPlotMetaDataObject *obj = (avtDefaultPlotMetaDataObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
avtDefaultPlotMetaData_SetPluginID(PyObject *self, PyObject *args)
{
    avtDefaultPlotMetaDataObject *obj = (avtDefaultPlotMetaDataObject *)self;

    char *str;
    if(!PyArg_ParseTuple(args, "s", &str))
        return NULL;

    // Set the pluginID in the object.
    obj->data->pluginID = std::string(str);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
avtDefaultPlotMetaData_GetPluginID(PyObject *self, PyObject *args)
{
    avtDefaultPlotMetaDataObject *obj = (avtDefaultPlotMetaDataObject *)self;
    PyObject *retval = PyString_FromString(obj->data->pluginID.c_str());
    return retval;
}

/*static*/ PyObject *
avtDefaultPlotMetaData_SetPlotVar(PyObject *self, PyObject *args)
{
    avtDefaultPlotMetaDataObject *obj = (avtDefaultPlotMetaDataObject *)self;

    char *str;
    if(!PyArg_ParseTuple(args, "s", &str))
        return NULL;

    // Set the plotVar in the object.
    obj->data->plotVar = std::string(str);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
avtDefaultPlotMetaData_GetPlotVar(PyObject *self, PyObject *args)
{
    avtDefaultPlotMetaDataObject *obj = (avtDefaultPlotMetaDataObject *)self;
    PyObject *retval = PyString_FromString(obj->data->plotVar.c_str());
    return retval;
}

/*static*/ PyObject *
avtDefaultPlotMetaData_SetPlotAttributes(PyObject *self, PyObject *args)
{
    avtDefaultPlotMetaDataObject *obj = (avtDefaultPlotMetaDataObject *)self;

    stringVector  &vec = obj->data->plotAttributes;
    PyObject     *tuple;
    if(!PyArg_ParseTuple(args, "O", &tuple))
        return NULL;

    if(PyTuple_Check(tuple))
    {
        vec.resize(PyTuple_Size(tuple));
        for(int i = 0; i < PyTuple_Size(tuple); ++i)
        {
            PyObject *item = PyTuple_GET_ITEM(tuple, i);
            if(PyString_Check(item))
                vec[i] = std::string(PyString_AS_STRING(item));
            else
                vec[i] = std::string("");
        }
    }
    else if(PyString_Check(tuple))
    {
        vec.resize(1);
        vec[0] = std::string(PyString_AS_STRING(tuple));
    }
    else
        return NULL;

    // Mark the plotAttributes in the object as modified.
    obj->data->SelectAll();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
avtDefaultPlotMetaData_GetPlotAttributes(PyObject *self, PyObject *args)
{
    avtDefaultPlotMetaDataObject *obj = (avtDefaultPlotMetaDataObject *)self;
    // Allocate a tuple the with enough entries to hold the plotAttributes.
    const stringVector &plotAttributes = obj->data->plotAttributes;
    PyObject *retval = PyTuple_New(plotAttributes.size());
    for(size_t i = 0; i < plotAttributes.size(); ++i)
        PyTuple_SET_ITEM(retval, i, PyString_FromString(plotAttributes[i].c_str()));
    return retval;
}



PyMethodDef PyavtDefaultPlotMetaData_methods[AVTDEFAULTPLOTMETADATA_NMETH] = {
    {"Notify", avtDefaultPlotMetaData_Notify, METH_VARARGS},
    {"SetPluginID", avtDefaultPlotMetaData_SetPluginID, METH_VARARGS},
    {"GetPluginID", avtDefaultPlotMetaData_GetPluginID, METH_VARARGS},
    {"SetPlotVar", avtDefaultPlotMetaData_SetPlotVar, METH_VARARGS},
    {"GetPlotVar", avtDefaultPlotMetaData_GetPlotVar, METH_VARARGS},
    {"SetPlotAttributes", avtDefaultPlotMetaData_SetPlotAttributes, METH_VARARGS},
    {"GetPlotAttributes", avtDefaultPlotMetaData_GetPlotAttributes, METH_VARARGS},
    {NULL, NULL}
};

//
// Type functions
//

static void
avtDefaultPlotMetaData_dealloc(PyObject *v)
{
   avtDefaultPlotMetaDataObject *obj = (avtDefaultPlotMetaDataObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static int
avtDefaultPlotMetaData_compare(PyObject *v, PyObject *w)
{
    avtDefaultPlotMetaData *a = ((avtDefaultPlotMetaDataObject *)v)->data;
    avtDefaultPlotMetaData *b = ((avtDefaultPlotMetaDataObject *)w)->data;
    return (*a == *b) ? 0 : -1;
}

PyObject *
PyavtDefaultPlotMetaData_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "pluginID") == 0)
        return avtDefaultPlotMetaData_GetPluginID(self, NULL);
    if(strcmp(name, "plotVar") == 0)
        return avtDefaultPlotMetaData_GetPlotVar(self, NULL);
    if(strcmp(name, "plotAttributes") == 0)
        return avtDefaultPlotMetaData_GetPlotAttributes(self, NULL);

    return Py_FindMethod(PyavtDefaultPlotMetaData_methods, self, name);
}

int
PyavtDefaultPlotMetaData_setattr(PyObject *self, char *name, PyObject *args)
{
    // Create a tuple to contain the arguments since all of the Set
    // functions expect a tuple.
    PyObject *tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, args);
    Py_INCREF(args);
    PyObject *obj = NULL;

    if(strcmp(name, "pluginID") == 0)
        obj = avtDefaultPlotMetaData_SetPluginID(self, tuple);
    else if(strcmp(name, "plotVar") == 0)
        obj = avtDefaultPlotMetaData_SetPlotVar(self, tuple);
    else if(strcmp(name, "plotAttributes") == 0)
        obj = avtDefaultPlotMetaData_SetPlotAttributes(self, tuple);

    if(obj != NULL)
        Py_DECREF(obj);

    Py_DECREF(tuple);
    if( obj == NULL)
        PyErr_Format(PyExc_RuntimeError, "Unable to set unknown attribute: '%s'", name);
    return (obj != NULL) ? 0 : -1;
}

static int
avtDefaultPlotMetaData_print(PyObject *v, FILE *fp, int flags)
{
    avtDefaultPlotMetaDataObject *obj = (avtDefaultPlotMetaDataObject *)v;
    fprintf(fp, "%s", PyavtDefaultPlotMetaData_ToString(obj->data, "").c_str());
    return 0;
}

PyObject *
avtDefaultPlotMetaData_str(PyObject *v)
{
    avtDefaultPlotMetaDataObject *obj = (avtDefaultPlotMetaDataObject *)v;
    return PyString_FromString(PyavtDefaultPlotMetaData_ToString(obj->data,"").c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *avtDefaultPlotMetaData_Purpose = "Contains default plot metadata attributes";
#else
static char *avtDefaultPlotMetaData_Purpose = "Contains default plot metadata attributes";
#endif

//
// The type description structure
//
static PyTypeObject avtDefaultPlotMetaDataType =
{
    //
    // Type header
    //
    PyObject_HEAD_INIT(&PyType_Type)
    0,                                   // ob_size
    "avtDefaultPlotMetaData",                    // tp_name
    sizeof(avtDefaultPlotMetaDataObject),        // tp_basicsize
    0,                                   // tp_itemsize
    //
    // Standard methods
    //
    (destructor)avtDefaultPlotMetaData_dealloc,  // tp_dealloc
    (printfunc)avtDefaultPlotMetaData_print,     // tp_print
    (getattrfunc)PyavtDefaultPlotMetaData_getattr, // tp_getattr
    (setattrfunc)PyavtDefaultPlotMetaData_setattr, // tp_setattr
    (cmpfunc)avtDefaultPlotMetaData_compare,     // tp_compare
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
    (reprfunc)avtDefaultPlotMetaData_str,        // tp_str
    0,                                   // tp_getattro
    0,                                   // tp_setattro
    0,                                   // tp_as_buffer
    Py_TPFLAGS_CHECKTYPES,               // tp_flags
    avtDefaultPlotMetaData_Purpose,              // tp_doc
    0,                                   // tp_traverse
    0,                                   // tp_clear
    0,                                   // tp_richcompare
    0                                    // tp_weaklistoffset
};

//
// Helper functions for object allocation.
//

static avtDefaultPlotMetaData *defaultAtts = 0;
static avtDefaultPlotMetaData *currentAtts = 0;

static PyObject *
NewavtDefaultPlotMetaData(int useCurrent)
{
    avtDefaultPlotMetaDataObject *newObject;
    newObject = PyObject_NEW(avtDefaultPlotMetaDataObject, &avtDefaultPlotMetaDataType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new avtDefaultPlotMetaData(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new avtDefaultPlotMetaData(*defaultAtts);
    else
        newObject->data = new avtDefaultPlotMetaData;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapavtDefaultPlotMetaData(const avtDefaultPlotMetaData *attr)
{
    avtDefaultPlotMetaDataObject *newObject;
    newObject = PyObject_NEW(avtDefaultPlotMetaDataObject, &avtDefaultPlotMetaDataType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (avtDefaultPlotMetaData *)attr;
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
avtDefaultPlotMetaData_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewavtDefaultPlotMetaData(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef avtDefaultPlotMetaDataMethods[] = {
    {"avtDefaultPlotMetaData", avtDefaultPlotMetaData_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *avtDefaultPlotMetaDataObserver = 0;

std::string
PyavtDefaultPlotMetaData_GetLogString()
{
    std::string s("avtDefaultPlotMetaData = avtDefaultPlotMetaData()\n");
    if(currentAtts != 0)
        s += PyavtDefaultPlotMetaData_ToString(currentAtts, "avtDefaultPlotMetaData.");
    return s;
}

static void
PyavtDefaultPlotMetaData_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("avtDefaultPlotMetaData = avtDefaultPlotMetaData()\n");
        s += PyavtDefaultPlotMetaData_ToString(currentAtts, "avtDefaultPlotMetaData.");
        cb(s);
    }
}

void
PyavtDefaultPlotMetaData_StartUp(avtDefaultPlotMetaData *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PyavtDefaultPlotMetaData_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(avtDefaultPlotMetaDataObserver == 0)
    {
        avtDefaultPlotMetaDataObserver = new ObserverToCallback(subj,
            PyavtDefaultPlotMetaData_CallLogRoutine, (void *)data);
    }

}

void
PyavtDefaultPlotMetaData_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete avtDefaultPlotMetaDataObserver;
    avtDefaultPlotMetaDataObserver = 0;
}

PyMethodDef *
PyavtDefaultPlotMetaData_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return avtDefaultPlotMetaDataMethods;
}

bool
PyavtDefaultPlotMetaData_Check(PyObject *obj)
{
    return (obj->ob_type == &avtDefaultPlotMetaDataType);
}

avtDefaultPlotMetaData *
PyavtDefaultPlotMetaData_FromPyObject(PyObject *obj)
{
    avtDefaultPlotMetaDataObject *obj2 = (avtDefaultPlotMetaDataObject *)obj;
    return obj2->data;
}

PyObject *
PyavtDefaultPlotMetaData_New()
{
    return NewavtDefaultPlotMetaData(0);
}

PyObject *
PyavtDefaultPlotMetaData_Wrap(const avtDefaultPlotMetaData *attr)
{
    return WrapavtDefaultPlotMetaData(attr);
}

void
PyavtDefaultPlotMetaData_SetParent(PyObject *obj, PyObject *parent)
{
    avtDefaultPlotMetaDataObject *obj2 = (avtDefaultPlotMetaDataObject *)obj;
    obj2->parent = parent;
}

void
PyavtDefaultPlotMetaData_SetDefaults(const avtDefaultPlotMetaData *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new avtDefaultPlotMetaData(*atts);
}

