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

#include <ModelFitAtts.h>
#include <DataNode.h>

//
// Enum conversion methods for ModelFitAtts::Spaces
//

static const char *Spaces_strings[] = {
"VARIABLE", "NORMAL", "LOG", 
"PROBABILITY"};

std::string
ModelFitAtts::Spaces_ToString(ModelFitAtts::Spaces t)
{
    int index = int(t);
    if(index < 0 || index >= 4) index = 0;
    return Spaces_strings[index];
}

std::string
ModelFitAtts::Spaces_ToString(int t)
{
    int index = (t < 0 || t >= 4) ? 0 : t;
    return Spaces_strings[index];
}

bool
ModelFitAtts::Spaces_FromString(const std::string &s, ModelFitAtts::Spaces &val)
{
    val = ModelFitAtts::VARIABLE;
    for(int i = 0; i < 4; ++i)
    {
        if(s == Spaces_strings[i])
        {
            val = (Spaces)i;
            return true;
        }
    }
    return false;
}

//
// Enum conversion methods for ModelFitAtts::Stats
//

static const char *Stats_strings[] = {
"AVERAGE", "MIN", "MAX", 
"NONE"};

std::string
ModelFitAtts::Stats_ToString(ModelFitAtts::Stats t)
{
    int index = int(t);
    if(index < 0 || index >= 4) index = 0;
    return Stats_strings[index];
}

std::string
ModelFitAtts::Stats_ToString(int t)
{
    int index = (t < 0 || t >= 4) ? 0 : t;
    return Stats_strings[index];
}

bool
ModelFitAtts::Stats_FromString(const std::string &s, ModelFitAtts::Stats &val)
{
    val = ModelFitAtts::AVERAGE;
    for(int i = 0; i < 4; ++i)
    {
        if(s == Stats_strings[i])
        {
            val = (Stats)i;
            return true;
        }
    }
    return false;
}

//
// Enum conversion methods for ModelFitAtts::Distances
//

static const char *Distances_strings[] = {
"EUCLIDEAN", "MANHATTAN", "MAXIMUM"
};

std::string
ModelFitAtts::Distances_ToString(ModelFitAtts::Distances t)
{
    int index = int(t);
    if(index < 0 || index >= 3) index = 0;
    return Distances_strings[index];
}

std::string
ModelFitAtts::Distances_ToString(int t)
{
    int index = (t < 0 || t >= 3) ? 0 : t;
    return Distances_strings[index];
}

bool
ModelFitAtts::Distances_FromString(const std::string &s, ModelFitAtts::Distances &val)
{
    val = ModelFitAtts::EUCLIDEAN;
    for(int i = 0; i < 3; ++i)
    {
        if(s == Distances_strings[i])
        {
            val = (Distances)i;
            return true;
        }
    }
    return false;
}

// ****************************************************************************
// Method: ModelFitAtts::ModelFitAtts
//
// Purpose: 
//   Init utility for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void ModelFitAtts::Init()
{

    ModelFitAtts::SelectAll();
}

// ****************************************************************************
// Method: ModelFitAtts::ModelFitAtts
//
// Purpose: 
//   Copy utility for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void ModelFitAtts::Copy(const ModelFitAtts &obj)
{
    Vars = obj.Vars;
    numVars = obj.numVars;
    Tuples = obj.Tuples;
    StatTuples = obj.StatTuples;
    numTups = obj.numTups;
    thold = obj.thold;
    selectionType = obj.selectionType;
    distanceType = obj.distanceType;
    inputSpace = obj.inputSpace;
    modelNames = obj.modelNames;
    modelNums = obj.modelNums;

    ModelFitAtts::SelectAll();
}

// Type map format string
const char *ModelFitAtts::TypeMapFormatString = MODELFITATTS_TMFS;
const AttributeGroup::private_tmfs_t ModelFitAtts::TmfsStruct = {MODELFITATTS_TMFS};


// ****************************************************************************
// Method: ModelFitAtts::ModelFitAtts
//
// Purpose: 
//   Default constructor for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

ModelFitAtts::ModelFitAtts() : 
    AttributeSubject(ModelFitAtts::TypeMapFormatString)
{
    ModelFitAtts::Init();
}

// ****************************************************************************
// Method: ModelFitAtts::ModelFitAtts
//
// Purpose: 
//   Constructor for the derived classes of ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

ModelFitAtts::ModelFitAtts(private_tmfs_t tmfs) : 
    AttributeSubject(tmfs.tmfs)
{
    ModelFitAtts::Init();
}

// ****************************************************************************
// Method: ModelFitAtts::ModelFitAtts
//
// Purpose: 
//   Copy constructor for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

ModelFitAtts::ModelFitAtts(const ModelFitAtts &obj) : 
    AttributeSubject(ModelFitAtts::TypeMapFormatString)
{
    ModelFitAtts::Copy(obj);
}

// ****************************************************************************
// Method: ModelFitAtts::ModelFitAtts
//
// Purpose: 
//   Copy constructor for derived classes of the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

ModelFitAtts::ModelFitAtts(const ModelFitAtts &obj, private_tmfs_t tmfs) : 
    AttributeSubject(tmfs.tmfs)
{
    ModelFitAtts::Copy(obj);
}

// ****************************************************************************
// Method: ModelFitAtts::~ModelFitAtts
//
// Purpose: 
//   Destructor for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

ModelFitAtts::~ModelFitAtts()
{
    // nothing here
}

// ****************************************************************************
// Method: ModelFitAtts::operator = 
//
// Purpose: 
//   Assignment operator for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

ModelFitAtts& 
ModelFitAtts::operator = (const ModelFitAtts &obj)
{
    if (this == &obj) return *this;

    ModelFitAtts::Copy(obj);

    return *this;
}

// ****************************************************************************
// Method: ModelFitAtts::operator == 
//
// Purpose: 
//   Comparison operator == for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

bool
ModelFitAtts::operator == (const ModelFitAtts &obj) const
{
    // Create the return value
    return ((Vars == obj.Vars) &&
            (numVars == obj.numVars) &&
            (Tuples == obj.Tuples) &&
            (StatTuples == obj.StatTuples) &&
            (numTups == obj.numTups) &&
            (thold == obj.thold) &&
            (selectionType == obj.selectionType) &&
            (distanceType == obj.distanceType) &&
            (inputSpace == obj.inputSpace) &&
            (modelNames == obj.modelNames) &&
            (modelNums == obj.modelNums));
}

// ****************************************************************************
// Method: ModelFitAtts::operator != 
//
// Purpose: 
//   Comparison operator != for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

bool
ModelFitAtts::operator != (const ModelFitAtts &obj) const
{
    return !(this->operator == (obj));
}

// ****************************************************************************
// Method: ModelFitAtts::TypeName
//
// Purpose: 
//   Type name method for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

const std::string
ModelFitAtts::TypeName() const
{
    return "ModelFitAtts";
}

// ****************************************************************************
// Method: ModelFitAtts::CopyAttributes
//
// Purpose: 
//   CopyAttributes method for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

bool
ModelFitAtts::CopyAttributes(const AttributeGroup *atts)
{
    if(TypeName() != atts->TypeName())
        return false;

    // Call assignment operator.
    const ModelFitAtts *tmp = (const ModelFitAtts *)atts;
    *this = *tmp;

    return true;
}

// ****************************************************************************
// Method: ModelFitAtts::CreateCompatible
//
// Purpose: 
//   CreateCompatible method for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

AttributeSubject *
ModelFitAtts::CreateCompatible(const std::string &tname) const
{
    AttributeSubject *retval = 0;
    if(TypeName() == tname)
        retval = new ModelFitAtts(*this);
    // Other cases could go here too. 

    return retval;
}

// ****************************************************************************
// Method: ModelFitAtts::NewInstance
//
// Purpose: 
//   NewInstance method for the ModelFitAtts class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

AttributeSubject *
ModelFitAtts::NewInstance(bool copy) const
{
    AttributeSubject *retval = 0;
    if(copy)
        retval = new ModelFitAtts(*this);
    else
        retval = new ModelFitAtts;

    return retval;
}

// ****************************************************************************
// Method: ModelFitAtts::SelectAll
//
// Purpose: 
//   Selects all attributes.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

void
ModelFitAtts::SelectAll()
{
    Select(ID_Vars,          (void *)&Vars);
    Select(ID_numVars,       (void *)&numVars);
    Select(ID_Tuples,        (void *)&Tuples);
    Select(ID_StatTuples,    (void *)&StatTuples);
    Select(ID_numTups,       (void *)&numTups);
    Select(ID_thold,         (void *)&thold);
    Select(ID_selectionType, (void *)&selectionType);
    Select(ID_distanceType,  (void *)&distanceType);
    Select(ID_inputSpace,    (void *)&inputSpace);
    Select(ID_modelNames,    (void *)&modelNames);
    Select(ID_modelNums,     (void *)&modelNums);
}

///////////////////////////////////////////////////////////////////////////////
// Set property methods
///////////////////////////////////////////////////////////////////////////////

void
ModelFitAtts::SetVars(const stringVector &Vars_)
{
    Vars = Vars_;
    Select(ID_Vars, (void *)&Vars);
}

void
ModelFitAtts::SetNumVars(const intVector &numVars_)
{
    numVars = numVars_;
    Select(ID_numVars, (void *)&numVars);
}

void
ModelFitAtts::SetTuples(const doubleVector &Tuples_)
{
    Tuples = Tuples_;
    Select(ID_Tuples, (void *)&Tuples);
}

void
ModelFitAtts::SetStatTuples(const unsignedCharVector &StatTuples_)
{
    StatTuples = StatTuples_;
    Select(ID_StatTuples, (void *)&StatTuples);
}

void
ModelFitAtts::SetNumTups(const intVector &numTups_)
{
    numTups = numTups_;
    Select(ID_numTups, (void *)&numTups);
}

void
ModelFitAtts::SetThold(const doubleVector &thold_)
{
    thold = thold_;
    Select(ID_thold, (void *)&thold);
}

void
ModelFitAtts::SetSelectionType(const intVector &selectionType_)
{
    selectionType = selectionType_;
    Select(ID_selectionType, (void *)&selectionType);
}

void
ModelFitAtts::SetDistanceType(const intVector &distanceType_)
{
    distanceType = distanceType_;
    Select(ID_distanceType, (void *)&distanceType);
}

void
ModelFitAtts::SetInputSpace(const intVector &inputSpace_)
{
    inputSpace = inputSpace_;
    Select(ID_inputSpace, (void *)&inputSpace);
}

void
ModelFitAtts::SetModelNames(const stringVector &modelNames_)
{
    modelNames = modelNames_;
    Select(ID_modelNames, (void *)&modelNames);
}

void
ModelFitAtts::SetModelNums(const intVector &modelNums_)
{
    modelNums = modelNums_;
    Select(ID_modelNums, (void *)&modelNums);
}

///////////////////////////////////////////////////////////////////////////////
// Get property methods
///////////////////////////////////////////////////////////////////////////////

const stringVector &
ModelFitAtts::GetVars() const
{
    return Vars;
}

stringVector &
ModelFitAtts::GetVars()
{
    return Vars;
}

const intVector &
ModelFitAtts::GetNumVars() const
{
    return numVars;
}

intVector &
ModelFitAtts::GetNumVars()
{
    return numVars;
}

const doubleVector &
ModelFitAtts::GetTuples() const
{
    return Tuples;
}

doubleVector &
ModelFitAtts::GetTuples()
{
    return Tuples;
}

const unsignedCharVector &
ModelFitAtts::GetStatTuples() const
{
    return StatTuples;
}

unsignedCharVector &
ModelFitAtts::GetStatTuples()
{
    return StatTuples;
}

const intVector &
ModelFitAtts::GetNumTups() const
{
    return numTups;
}

intVector &
ModelFitAtts::GetNumTups()
{
    return numTups;
}

const doubleVector &
ModelFitAtts::GetThold() const
{
    return thold;
}

doubleVector &
ModelFitAtts::GetThold()
{
    return thold;
}

const intVector &
ModelFitAtts::GetSelectionType() const
{
    return selectionType;
}

intVector &
ModelFitAtts::GetSelectionType()
{
    return selectionType;
}

const intVector &
ModelFitAtts::GetDistanceType() const
{
    return distanceType;
}

intVector &
ModelFitAtts::GetDistanceType()
{
    return distanceType;
}

const intVector &
ModelFitAtts::GetInputSpace() const
{
    return inputSpace;
}

intVector &
ModelFitAtts::GetInputSpace()
{
    return inputSpace;
}

const stringVector &
ModelFitAtts::GetModelNames() const
{
    return modelNames;
}

stringVector &
ModelFitAtts::GetModelNames()
{
    return modelNames;
}

const intVector &
ModelFitAtts::GetModelNums() const
{
    return modelNums;
}

intVector &
ModelFitAtts::GetModelNums()
{
    return modelNums;
}

///////////////////////////////////////////////////////////////////////////////
// Select property methods
///////////////////////////////////////////////////////////////////////////////

void
ModelFitAtts::SelectVars()
{
    Select(ID_Vars, (void *)&Vars);
}

void
ModelFitAtts::SelectNumVars()
{
    Select(ID_numVars, (void *)&numVars);
}

void
ModelFitAtts::SelectTuples()
{
    Select(ID_Tuples, (void *)&Tuples);
}

void
ModelFitAtts::SelectStatTuples()
{
    Select(ID_StatTuples, (void *)&StatTuples);
}

void
ModelFitAtts::SelectNumTups()
{
    Select(ID_numTups, (void *)&numTups);
}

void
ModelFitAtts::SelectThold()
{
    Select(ID_thold, (void *)&thold);
}

void
ModelFitAtts::SelectSelectionType()
{
    Select(ID_selectionType, (void *)&selectionType);
}

void
ModelFitAtts::SelectDistanceType()
{
    Select(ID_distanceType, (void *)&distanceType);
}

void
ModelFitAtts::SelectInputSpace()
{
    Select(ID_inputSpace, (void *)&inputSpace);
}

void
ModelFitAtts::SelectModelNames()
{
    Select(ID_modelNames, (void *)&modelNames);
}

void
ModelFitAtts::SelectModelNums()
{
    Select(ID_modelNums, (void *)&modelNums);
}

///////////////////////////////////////////////////////////////////////////////
// Keyframing methods
///////////////////////////////////////////////////////////////////////////////

// ****************************************************************************
// Method: ModelFitAtts::GetFieldName
//
// Purpose: 
//   This method returns the name of a field given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

std::string
ModelFitAtts::GetFieldName(int index) const
{
    switch (index)
    {
    case ID_Vars:          return "Vars";
    case ID_numVars:       return "numVars";
    case ID_Tuples:        return "Tuples";
    case ID_StatTuples:    return "StatTuples";
    case ID_numTups:       return "numTups";
    case ID_thold:         return "thold";
    case ID_selectionType: return "selectionType";
    case ID_distanceType:  return "distanceType";
    case ID_inputSpace:    return "inputSpace";
    case ID_modelNames:    return "modelNames";
    case ID_modelNums:     return "modelNums";
    default:  return "invalid index";
    }
}

// ****************************************************************************
// Method: ModelFitAtts::GetFieldType
//
// Purpose: 
//   This method returns the type of a field given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

AttributeGroup::FieldType
ModelFitAtts::GetFieldType(int index) const
{
    switch (index)
    {
    case ID_Vars:          return FieldType_stringVector;
    case ID_numVars:       return FieldType_intVector;
    case ID_Tuples:        return FieldType_doubleVector;
    case ID_StatTuples:    return FieldType_ucharVector;
    case ID_numTups:       return FieldType_intVector;
    case ID_thold:         return FieldType_doubleVector;
    case ID_selectionType: return FieldType_intVector;
    case ID_distanceType:  return FieldType_intVector;
    case ID_inputSpace:    return FieldType_intVector;
    case ID_modelNames:    return FieldType_stringVector;
    case ID_modelNums:     return FieldType_intVector;
    default:  return FieldType_unknown;
    }
}

// ****************************************************************************
// Method: ModelFitAtts::GetFieldTypeName
//
// Purpose: 
//   This method returns the name of a field type given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

std::string
ModelFitAtts::GetFieldTypeName(int index) const
{
    switch (index)
    {
    case ID_Vars:          return "stringVector";
    case ID_numVars:       return "intVector";
    case ID_Tuples:        return "doubleVector";
    case ID_StatTuples:    return "ucharVector";
    case ID_numTups:       return "intVector";
    case ID_thold:         return "doubleVector";
    case ID_selectionType: return "intVector";
    case ID_distanceType:  return "intVector";
    case ID_inputSpace:    return "intVector";
    case ID_modelNames:    return "stringVector";
    case ID_modelNums:     return "intVector";
    default:  return "invalid index";
    }
}

// ****************************************************************************
// Method: ModelFitAtts::FieldsEqual
//
// Purpose: 
//   This method compares two fields and return true if they are equal.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

bool
ModelFitAtts::FieldsEqual(int index_, const AttributeGroup *rhs) const
{
    const ModelFitAtts &obj = *((const ModelFitAtts*)rhs);
    bool retval = false;
    switch (index_)
    {
    case ID_Vars:
        {  // new scope
        retval = (Vars == obj.Vars);
        }
        break;
    case ID_numVars:
        {  // new scope
        retval = (numVars == obj.numVars);
        }
        break;
    case ID_Tuples:
        {  // new scope
        retval = (Tuples == obj.Tuples);
        }
        break;
    case ID_StatTuples:
        {  // new scope
        retval = (StatTuples == obj.StatTuples);
        }
        break;
    case ID_numTups:
        {  // new scope
        retval = (numTups == obj.numTups);
        }
        break;
    case ID_thold:
        {  // new scope
        retval = (thold == obj.thold);
        }
        break;
    case ID_selectionType:
        {  // new scope
        retval = (selectionType == obj.selectionType);
        }
        break;
    case ID_distanceType:
        {  // new scope
        retval = (distanceType == obj.distanceType);
        }
        break;
    case ID_inputSpace:
        {  // new scope
        retval = (inputSpace == obj.inputSpace);
        }
        break;
    case ID_modelNames:
        {  // new scope
        retval = (modelNames == obj.modelNames);
        }
        break;
    case ID_modelNums:
        {  // new scope
        retval = (modelNums == obj.modelNums);
        }
        break;
    default: retval = false;
    }

    return retval;
}

///////////////////////////////////////////////////////////////////////////////
// User-defined methods.
///////////////////////////////////////////////////////////////////////////////

