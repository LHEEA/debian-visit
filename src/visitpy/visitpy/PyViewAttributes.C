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

#include <PyViewAttributes.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <snprintf.h>

// ****************************************************************************
// Module: PyViewAttributes
//
// Purpose: 
//   This class contains the view attributes.
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a ViewAttributes.
//
struct ViewAttributesObject
{
    PyObject_HEAD
    ViewAttributes *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewViewAttributes(int);

std::string
PyViewAttributes_ToString(const ViewAttributes *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    {   const double *viewNormal = atts->GetViewNormal();
        SNPRINTF(tmpStr, 1000, "%sviewNormal = (", prefix);
        str += tmpStr;
        for(int i = 0; i < 3; ++i)
        {
            SNPRINTF(tmpStr, 1000, "%g", viewNormal[i]);
            str += tmpStr;
            if(i < 2)
            {
                SNPRINTF(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        SNPRINTF(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    {   const double *focus = atts->GetFocus();
        SNPRINTF(tmpStr, 1000, "%sfocus = (", prefix);
        str += tmpStr;
        for(int i = 0; i < 3; ++i)
        {
            SNPRINTF(tmpStr, 1000, "%g", focus[i]);
            str += tmpStr;
            if(i < 2)
            {
                SNPRINTF(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        SNPRINTF(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    {   const double *viewUp = atts->GetViewUp();
        SNPRINTF(tmpStr, 1000, "%sviewUp = (", prefix);
        str += tmpStr;
        for(int i = 0; i < 3; ++i)
        {
            SNPRINTF(tmpStr, 1000, "%g", viewUp[i]);
            str += tmpStr;
            if(i < 2)
            {
                SNPRINTF(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        SNPRINTF(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    SNPRINTF(tmpStr, 1000, "%sviewAngle = %g\n", prefix, atts->GetViewAngle());
    str += tmpStr;
    if(atts->GetSetScale())
        SNPRINTF(tmpStr, 1000, "%ssetScale = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%ssetScale = 0\n", prefix);
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%sparallelScale = %g\n", prefix, atts->GetParallelScale());
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%snearPlane = %g\n", prefix, atts->GetNearPlane());
    str += tmpStr;
    SNPRINTF(tmpStr, 1000, "%sfarPlane = %g\n", prefix, atts->GetFarPlane());
    str += tmpStr;
    {   const double *imagePan = atts->GetImagePan();
        SNPRINTF(tmpStr, 1000, "%simagePan = (", prefix);
        str += tmpStr;
        for(int i = 0; i < 2; ++i)
        {
            SNPRINTF(tmpStr, 1000, "%g", imagePan[i]);
            str += tmpStr;
            if(i < 1)
            {
                SNPRINTF(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        SNPRINTF(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    SNPRINTF(tmpStr, 1000, "%simageZoom = %g\n", prefix, atts->GetImageZoom());
    str += tmpStr;
    if(atts->GetPerspective())
        SNPRINTF(tmpStr, 1000, "%sperspective = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%sperspective = 0\n", prefix);
    str += tmpStr;
    {   const double *windowCoords = atts->GetWindowCoords();
        SNPRINTF(tmpStr, 1000, "%swindowCoords = (", prefix);
        str += tmpStr;
        for(int i = 0; i < 4; ++i)
        {
            SNPRINTF(tmpStr, 1000, "%g", windowCoords[i]);
            str += tmpStr;
            if(i < 3)
            {
                SNPRINTF(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        SNPRINTF(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    {   const double *viewportCoords = atts->GetViewportCoords();
        SNPRINTF(tmpStr, 1000, "%sviewportCoords = (", prefix);
        str += tmpStr;
        for(int i = 0; i < 4; ++i)
        {
            SNPRINTF(tmpStr, 1000, "%g", viewportCoords[i]);
            str += tmpStr;
            if(i < 3)
            {
                SNPRINTF(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        SNPRINTF(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    SNPRINTF(tmpStr, 1000, "%seyeAngle = %g\n", prefix, atts->GetEyeAngle());
    str += tmpStr;
    return str;
}

static PyObject *
ViewAttributes_Notify(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_SetViewNormal(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double *dvals = obj->data->GetViewNormal();
    if(!PyArg_ParseTuple(args, "ddd", &dvals[0], &dvals[1], &dvals[2]))
    {
        PyObject     *tuple;
        if(!PyArg_ParseTuple(args, "O", &tuple))
            return NULL;

        if(PyTuple_Check(tuple))
        {
            if(PyTuple_Size(tuple) != 3)
                return NULL;

            PyErr_Clear();
            for(int i = 0; i < PyTuple_Size(tuple); ++i)
            {
                PyObject *item = PyTuple_GET_ITEM(tuple, i);
                if(PyFloat_Check(item))
                    dvals[i] = PyFloat_AS_DOUBLE(item);
                else if(PyInt_Check(item))
                    dvals[i] = double(PyInt_AS_LONG(item));
                else if(PyLong_Check(item))
                    dvals[i] = PyLong_AsDouble(item);
                else
                    dvals[i] = 0.;
            }
        }
        else
            return NULL;
    }

    // Mark the viewNormal in the object as modified.
    obj->data->SelectViewNormal();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetViewNormal(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    // Allocate a tuple the with enough entries to hold the viewNormal.
    PyObject *retval = PyTuple_New(3);
    const double *viewNormal = obj->data->GetViewNormal();
    for(int i = 0; i < 3; ++i)
        PyTuple_SET_ITEM(retval, i, PyFloat_FromDouble(viewNormal[i]));
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetFocus(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double *dvals = obj->data->GetFocus();
    if(!PyArg_ParseTuple(args, "ddd", &dvals[0], &dvals[1], &dvals[2]))
    {
        PyObject     *tuple;
        if(!PyArg_ParseTuple(args, "O", &tuple))
            return NULL;

        if(PyTuple_Check(tuple))
        {
            if(PyTuple_Size(tuple) != 3)
                return NULL;

            PyErr_Clear();
            for(int i = 0; i < PyTuple_Size(tuple); ++i)
            {
                PyObject *item = PyTuple_GET_ITEM(tuple, i);
                if(PyFloat_Check(item))
                    dvals[i] = PyFloat_AS_DOUBLE(item);
                else if(PyInt_Check(item))
                    dvals[i] = double(PyInt_AS_LONG(item));
                else if(PyLong_Check(item))
                    dvals[i] = PyLong_AsDouble(item);
                else
                    dvals[i] = 0.;
            }
        }
        else
            return NULL;
    }

    // Mark the focus in the object as modified.
    obj->data->SelectFocus();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetFocus(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    // Allocate a tuple the with enough entries to hold the focus.
    PyObject *retval = PyTuple_New(3);
    const double *focus = obj->data->GetFocus();
    for(int i = 0; i < 3; ++i)
        PyTuple_SET_ITEM(retval, i, PyFloat_FromDouble(focus[i]));
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetViewUp(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double *dvals = obj->data->GetViewUp();
    if(!PyArg_ParseTuple(args, "ddd", &dvals[0], &dvals[1], &dvals[2]))
    {
        PyObject     *tuple;
        if(!PyArg_ParseTuple(args, "O", &tuple))
            return NULL;

        if(PyTuple_Check(tuple))
        {
            if(PyTuple_Size(tuple) != 3)
                return NULL;

            PyErr_Clear();
            for(int i = 0; i < PyTuple_Size(tuple); ++i)
            {
                PyObject *item = PyTuple_GET_ITEM(tuple, i);
                if(PyFloat_Check(item))
                    dvals[i] = PyFloat_AS_DOUBLE(item);
                else if(PyInt_Check(item))
                    dvals[i] = double(PyInt_AS_LONG(item));
                else if(PyLong_Check(item))
                    dvals[i] = PyLong_AsDouble(item);
                else
                    dvals[i] = 0.;
            }
        }
        else
            return NULL;
    }

    // Mark the viewUp in the object as modified.
    obj->data->SelectViewUp();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetViewUp(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    // Allocate a tuple the with enough entries to hold the viewUp.
    PyObject *retval = PyTuple_New(3);
    const double *viewUp = obj->data->GetViewUp();
    for(int i = 0; i < 3; ++i)
        PyTuple_SET_ITEM(retval, i, PyFloat_FromDouble(viewUp[i]));
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetViewAngle(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the viewAngle in the object.
    obj->data->SetViewAngle(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetViewAngle(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetViewAngle());
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetSetScale(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the setScale in the object.
    obj->data->SetSetScale(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetSetScale(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetSetScale()?1L:0L);
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetParallelScale(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the parallelScale in the object.
    obj->data->SetParallelScale(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetParallelScale(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetParallelScale());
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetNearPlane(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the nearPlane in the object.
    obj->data->SetNearPlane(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetNearPlane(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetNearPlane());
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetFarPlane(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the farPlane in the object.
    obj->data->SetFarPlane(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetFarPlane(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetFarPlane());
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetImagePan(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double *dvals = obj->data->GetImagePan();
    if(!PyArg_ParseTuple(args, "dd", &dvals[0], &dvals[1]))
    {
        PyObject     *tuple;
        if(!PyArg_ParseTuple(args, "O", &tuple))
            return NULL;

        if(PyTuple_Check(tuple))
        {
            if(PyTuple_Size(tuple) != 2)
                return NULL;

            PyErr_Clear();
            for(int i = 0; i < PyTuple_Size(tuple); ++i)
            {
                PyObject *item = PyTuple_GET_ITEM(tuple, i);
                if(PyFloat_Check(item))
                    dvals[i] = PyFloat_AS_DOUBLE(item);
                else if(PyInt_Check(item))
                    dvals[i] = double(PyInt_AS_LONG(item));
                else if(PyLong_Check(item))
                    dvals[i] = PyLong_AsDouble(item);
                else
                    dvals[i] = 0.;
            }
        }
        else
            return NULL;
    }

    // Mark the imagePan in the object as modified.
    obj->data->SelectImagePan();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetImagePan(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    // Allocate a tuple the with enough entries to hold the imagePan.
    PyObject *retval = PyTuple_New(2);
    const double *imagePan = obj->data->GetImagePan();
    for(int i = 0; i < 2; ++i)
        PyTuple_SET_ITEM(retval, i, PyFloat_FromDouble(imagePan[i]));
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetImageZoom(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the imageZoom in the object.
    obj->data->SetImageZoom(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetImageZoom(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetImageZoom());
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetPerspective(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the perspective in the object.
    obj->data->SetPerspective(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetPerspective(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetPerspective()?1L:0L);
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetWindowCoords(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double *dvals = obj->data->GetWindowCoords();
    if(!PyArg_ParseTuple(args, "dddd", &dvals[0], &dvals[1], &dvals[2], &dvals[3]))
    {
        PyObject     *tuple;
        if(!PyArg_ParseTuple(args, "O", &tuple))
            return NULL;

        if(PyTuple_Check(tuple))
        {
            if(PyTuple_Size(tuple) != 4)
                return NULL;

            PyErr_Clear();
            for(int i = 0; i < PyTuple_Size(tuple); ++i)
            {
                PyObject *item = PyTuple_GET_ITEM(tuple, i);
                if(PyFloat_Check(item))
                    dvals[i] = PyFloat_AS_DOUBLE(item);
                else if(PyInt_Check(item))
                    dvals[i] = double(PyInt_AS_LONG(item));
                else if(PyLong_Check(item))
                    dvals[i] = PyLong_AsDouble(item);
                else
                    dvals[i] = 0.;
            }
        }
        else
            return NULL;
    }

    // Mark the windowCoords in the object as modified.
    obj->data->SelectWindowCoords();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetWindowCoords(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    // Allocate a tuple the with enough entries to hold the windowCoords.
    PyObject *retval = PyTuple_New(4);
    const double *windowCoords = obj->data->GetWindowCoords();
    for(int i = 0; i < 4; ++i)
        PyTuple_SET_ITEM(retval, i, PyFloat_FromDouble(windowCoords[i]));
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetViewportCoords(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double *dvals = obj->data->GetViewportCoords();
    if(!PyArg_ParseTuple(args, "dddd", &dvals[0], &dvals[1], &dvals[2], &dvals[3]))
    {
        PyObject     *tuple;
        if(!PyArg_ParseTuple(args, "O", &tuple))
            return NULL;

        if(PyTuple_Check(tuple))
        {
            if(PyTuple_Size(tuple) != 4)
                return NULL;

            PyErr_Clear();
            for(int i = 0; i < PyTuple_Size(tuple); ++i)
            {
                PyObject *item = PyTuple_GET_ITEM(tuple, i);
                if(PyFloat_Check(item))
                    dvals[i] = PyFloat_AS_DOUBLE(item);
                else if(PyInt_Check(item))
                    dvals[i] = double(PyInt_AS_LONG(item));
                else if(PyLong_Check(item))
                    dvals[i] = PyLong_AsDouble(item);
                else
                    dvals[i] = 0.;
            }
        }
        else
            return NULL;
    }

    // Mark the viewportCoords in the object as modified.
    obj->data->SelectViewportCoords();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetViewportCoords(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    // Allocate a tuple the with enough entries to hold the viewportCoords.
    PyObject *retval = PyTuple_New(4);
    const double *viewportCoords = obj->data->GetViewportCoords();
    for(int i = 0; i < 4; ++i)
        PyTuple_SET_ITEM(retval, i, PyFloat_FromDouble(viewportCoords[i]));
    return retval;
}

/*static*/ PyObject *
ViewAttributes_SetEyeAngle(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the eyeAngle in the object.
    obj->data->SetEyeAngle(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ViewAttributes_GetEyeAngle(PyObject *self, PyObject *args)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetEyeAngle());
    return retval;
}



PyMethodDef PyViewAttributes_methods[VIEWATTRIBUTES_NMETH] = {
    {"Notify", ViewAttributes_Notify, METH_VARARGS},
    {"SetViewNormal", ViewAttributes_SetViewNormal, METH_VARARGS},
    {"GetViewNormal", ViewAttributes_GetViewNormal, METH_VARARGS},
    {"SetFocus", ViewAttributes_SetFocus, METH_VARARGS},
    {"GetFocus", ViewAttributes_GetFocus, METH_VARARGS},
    {"SetViewUp", ViewAttributes_SetViewUp, METH_VARARGS},
    {"GetViewUp", ViewAttributes_GetViewUp, METH_VARARGS},
    {"SetViewAngle", ViewAttributes_SetViewAngle, METH_VARARGS},
    {"GetViewAngle", ViewAttributes_GetViewAngle, METH_VARARGS},
    {"SetSetScale", ViewAttributes_SetSetScale, METH_VARARGS},
    {"GetSetScale", ViewAttributes_GetSetScale, METH_VARARGS},
    {"SetParallelScale", ViewAttributes_SetParallelScale, METH_VARARGS},
    {"GetParallelScale", ViewAttributes_GetParallelScale, METH_VARARGS},
    {"SetNearPlane", ViewAttributes_SetNearPlane, METH_VARARGS},
    {"GetNearPlane", ViewAttributes_GetNearPlane, METH_VARARGS},
    {"SetFarPlane", ViewAttributes_SetFarPlane, METH_VARARGS},
    {"GetFarPlane", ViewAttributes_GetFarPlane, METH_VARARGS},
    {"SetImagePan", ViewAttributes_SetImagePan, METH_VARARGS},
    {"GetImagePan", ViewAttributes_GetImagePan, METH_VARARGS},
    {"SetImageZoom", ViewAttributes_SetImageZoom, METH_VARARGS},
    {"GetImageZoom", ViewAttributes_GetImageZoom, METH_VARARGS},
    {"SetPerspective", ViewAttributes_SetPerspective, METH_VARARGS},
    {"GetPerspective", ViewAttributes_GetPerspective, METH_VARARGS},
    {"SetWindowCoords", ViewAttributes_SetWindowCoords, METH_VARARGS},
    {"GetWindowCoords", ViewAttributes_GetWindowCoords, METH_VARARGS},
    {"SetViewportCoords", ViewAttributes_SetViewportCoords, METH_VARARGS},
    {"GetViewportCoords", ViewAttributes_GetViewportCoords, METH_VARARGS},
    {"SetEyeAngle", ViewAttributes_SetEyeAngle, METH_VARARGS},
    {"GetEyeAngle", ViewAttributes_GetEyeAngle, METH_VARARGS},
    {NULL, NULL}
};

//
// Type functions
//

static void
ViewAttributes_dealloc(PyObject *v)
{
   ViewAttributesObject *obj = (ViewAttributesObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static int
ViewAttributes_compare(PyObject *v, PyObject *w)
{
    ViewAttributes *a = ((ViewAttributesObject *)v)->data;
    ViewAttributes *b = ((ViewAttributesObject *)w)->data;
    return (*a == *b) ? 0 : -1;
}

PyObject *
PyViewAttributes_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "viewNormal") == 0)
        return ViewAttributes_GetViewNormal(self, NULL);
    if(strcmp(name, "focus") == 0)
        return ViewAttributes_GetFocus(self, NULL);
    if(strcmp(name, "viewUp") == 0)
        return ViewAttributes_GetViewUp(self, NULL);
    if(strcmp(name, "viewAngle") == 0)
        return ViewAttributes_GetViewAngle(self, NULL);
    if(strcmp(name, "setScale") == 0)
        return ViewAttributes_GetSetScale(self, NULL);
    if(strcmp(name, "parallelScale") == 0)
        return ViewAttributes_GetParallelScale(self, NULL);
    if(strcmp(name, "nearPlane") == 0)
        return ViewAttributes_GetNearPlane(self, NULL);
    if(strcmp(name, "farPlane") == 0)
        return ViewAttributes_GetFarPlane(self, NULL);
    if(strcmp(name, "imagePan") == 0)
        return ViewAttributes_GetImagePan(self, NULL);
    if(strcmp(name, "imageZoom") == 0)
        return ViewAttributes_GetImageZoom(self, NULL);
    if(strcmp(name, "perspective") == 0)
        return ViewAttributes_GetPerspective(self, NULL);
    if(strcmp(name, "windowCoords") == 0)
        return ViewAttributes_GetWindowCoords(self, NULL);
    if(strcmp(name, "viewportCoords") == 0)
        return ViewAttributes_GetViewportCoords(self, NULL);
    if(strcmp(name, "eyeAngle") == 0)
        return ViewAttributes_GetEyeAngle(self, NULL);

    return Py_FindMethod(PyViewAttributes_methods, self, name);
}

int
PyViewAttributes_setattr(PyObject *self, char *name, PyObject *args)
{
    // Create a tuple to contain the arguments since all of the Set
    // functions expect a tuple.
    PyObject *tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, args);
    Py_INCREF(args);
    PyObject *obj = NULL;

    if(strcmp(name, "viewNormal") == 0)
        obj = ViewAttributes_SetViewNormal(self, tuple);
    else if(strcmp(name, "focus") == 0)
        obj = ViewAttributes_SetFocus(self, tuple);
    else if(strcmp(name, "viewUp") == 0)
        obj = ViewAttributes_SetViewUp(self, tuple);
    else if(strcmp(name, "viewAngle") == 0)
        obj = ViewAttributes_SetViewAngle(self, tuple);
    else if(strcmp(name, "setScale") == 0)
        obj = ViewAttributes_SetSetScale(self, tuple);
    else if(strcmp(name, "parallelScale") == 0)
        obj = ViewAttributes_SetParallelScale(self, tuple);
    else if(strcmp(name, "nearPlane") == 0)
        obj = ViewAttributes_SetNearPlane(self, tuple);
    else if(strcmp(name, "farPlane") == 0)
        obj = ViewAttributes_SetFarPlane(self, tuple);
    else if(strcmp(name, "imagePan") == 0)
        obj = ViewAttributes_SetImagePan(self, tuple);
    else if(strcmp(name, "imageZoom") == 0)
        obj = ViewAttributes_SetImageZoom(self, tuple);
    else if(strcmp(name, "perspective") == 0)
        obj = ViewAttributes_SetPerspective(self, tuple);
    else if(strcmp(name, "windowCoords") == 0)
        obj = ViewAttributes_SetWindowCoords(self, tuple);
    else if(strcmp(name, "viewportCoords") == 0)
        obj = ViewAttributes_SetViewportCoords(self, tuple);
    else if(strcmp(name, "eyeAngle") == 0)
        obj = ViewAttributes_SetEyeAngle(self, tuple);

    if(obj != NULL)
        Py_DECREF(obj);

    Py_DECREF(tuple);
    if( obj == NULL)
        PyErr_Format(PyExc_RuntimeError, "Unable to set unknown attribute: '%s'", name);
    return (obj != NULL) ? 0 : -1;
}

static int
ViewAttributes_print(PyObject *v, FILE *fp, int flags)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)v;
    fprintf(fp, "%s", PyViewAttributes_ToString(obj->data, "").c_str());
    return 0;
}

PyObject *
ViewAttributes_str(PyObject *v)
{
    ViewAttributesObject *obj = (ViewAttributesObject *)v;
    return PyString_FromString(PyViewAttributes_ToString(obj->data,"").c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *ViewAttributes_Purpose = "This class contains the view attributes.";
#else
static char *ViewAttributes_Purpose = "This class contains the view attributes.";
#endif

//
// The type description structure
//
static PyTypeObject ViewAttributesType =
{
    //
    // Type header
    //
    PyObject_HEAD_INIT(&PyType_Type)
    0,                                   // ob_size
    "ViewAttributes",                    // tp_name
    sizeof(ViewAttributesObject),        // tp_basicsize
    0,                                   // tp_itemsize
    //
    // Standard methods
    //
    (destructor)ViewAttributes_dealloc,  // tp_dealloc
    (printfunc)ViewAttributes_print,     // tp_print
    (getattrfunc)PyViewAttributes_getattr, // tp_getattr
    (setattrfunc)PyViewAttributes_setattr, // tp_setattr
    (cmpfunc)ViewAttributes_compare,     // tp_compare
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
    (reprfunc)ViewAttributes_str,        // tp_str
    0,                                   // tp_getattro
    0,                                   // tp_setattro
    0,                                   // tp_as_buffer
    Py_TPFLAGS_CHECKTYPES,               // tp_flags
    ViewAttributes_Purpose,              // tp_doc
    0,                                   // tp_traverse
    0,                                   // tp_clear
    0,                                   // tp_richcompare
    0                                    // tp_weaklistoffset
};

//
// Helper functions for object allocation.
//

static ViewAttributes *defaultAtts = 0;
static ViewAttributes *currentAtts = 0;

static PyObject *
NewViewAttributes(int useCurrent)
{
    ViewAttributesObject *newObject;
    newObject = PyObject_NEW(ViewAttributesObject, &ViewAttributesType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new ViewAttributes(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new ViewAttributes(*defaultAtts);
    else
        newObject->data = new ViewAttributes;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapViewAttributes(const ViewAttributes *attr)
{
    ViewAttributesObject *newObject;
    newObject = PyObject_NEW(ViewAttributesObject, &ViewAttributesType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (ViewAttributes *)attr;
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
ViewAttributes_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewViewAttributes(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef ViewAttributesMethods[] = {
    {"ViewAttributes", ViewAttributes_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *ViewAttributesObserver = 0;

std::string
PyViewAttributes_GetLogString()
{
    std::string s("ViewAtts = ViewAttributes()\n");
    if(currentAtts != 0)
        s += PyViewAttributes_ToString(currentAtts, "ViewAtts.");
    return s;
}

static void
PyViewAttributes_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("ViewAtts = ViewAttributes()\n");
        s += PyViewAttributes_ToString(currentAtts, "ViewAtts.");
        cb(s);
    }
}

void
PyViewAttributes_StartUp(ViewAttributes *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PyViewAttributes_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(ViewAttributesObserver == 0)
    {
        ViewAttributesObserver = new ObserverToCallback(subj,
            PyViewAttributes_CallLogRoutine, (void *)data);
    }

}

void
PyViewAttributes_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete ViewAttributesObserver;
    ViewAttributesObserver = 0;
}

PyMethodDef *
PyViewAttributes_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return ViewAttributesMethods;
}

bool
PyViewAttributes_Check(PyObject *obj)
{
    return (obj->ob_type == &ViewAttributesType);
}

ViewAttributes *
PyViewAttributes_FromPyObject(PyObject *obj)
{
    ViewAttributesObject *obj2 = (ViewAttributesObject *)obj;
    return obj2->data;
}

PyObject *
PyViewAttributes_New()
{
    return NewViewAttributes(0);
}

PyObject *
PyViewAttributes_Wrap(const ViewAttributes *attr)
{
    return WrapViewAttributes(attr);
}

void
PyViewAttributes_SetParent(PyObject *obj, PyObject *parent)
{
    ViewAttributesObject *obj2 = (ViewAttributesObject *)obj;
    obj2->parent = parent;
}

void
PyViewAttributes_SetDefaults(const ViewAttributes *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new ViewAttributes(*atts);
}

