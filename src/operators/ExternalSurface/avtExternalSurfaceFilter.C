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

// ************************************************************************* //
//  File: avtExternalSurfaceFilter.C
// ************************************************************************* //

#include <avtExternalSurfaceFilter.h>

#include <avtFacelistFilter.h>
#include <avtGhostZoneAndFacelistFilter.h>

// ****************************************************************************
//  Method: avtExternalSurfaceFilter constructor
//
//  Programmer: meredith -- generated by xml2info
//  Creation:   Sat Aug 3 11:48:17 PDT 2002
//
//  Modifications:
//
//    Hank Childs, Tue Aug 23 09:49:57 PDT 2005
//    Add support for ghost zone removal.
//
// ****************************************************************************

avtExternalSurfaceFilter::avtExternalSurfaceFilter()
{
    ff = NULL;
    gz_and_ff = NULL;
}


// ****************************************************************************
//  Method: avtExternalSurfaceFilter destructor
//
//  Programmer: meredith -- generated by xml2info
//  Creation:   Sat Aug 3 11:48:17 PDT 2002
//
//  Modifications:
//
//    Hank Childs, Tue Aug 23 09:49:57 PDT 2005
//    Add support for ghost zone removal.
//
// ****************************************************************************

avtExternalSurfaceFilter::~avtExternalSurfaceFilter()
{
    if (ff != NULL)
    {
        delete ff;
        ff = NULL;
    }
    if (gz_and_ff != NULL)
    {
        delete gz_and_ff;
        gz_and_ff = NULL;
    }
}


// ****************************************************************************
//  Method:  avtExternalSurfaceFilter::Create
//
//  Programmer: meredith -- generated by xml2info
//  Creation:   Sat Aug 3 11:48:17 PDT 2002
//
// ****************************************************************************

avtFilter *
avtExternalSurfaceFilter::Create()
{
    return new avtExternalSurfaceFilter();
}


// ****************************************************************************
//  Method:      avtExternalSurfaceFilter::SetAtts
//
//  Purpose:
//      Sets the state of the filter based on the attribute object.
//
//  Arguments:
//      a        The attributes to use.
//
//  Programmer: meredith -- generated by xml2info
//  Creation:   Sat Aug 3 11:48:17 PDT 2002
//
//  Modifications:
//
//    Hank Childs, Tue Aug 23 09:49:57 PDT 2005
//    Add support for ghost zone removal.
//
//    Hank Childs, Mon Sep 26 09:34:35 PDT 2005
//    Add support for edge generation.
//
//    Brad Whitlock, Wed Mar 19 14:14:53 PDT 2014
//    Add callbacks to the facade filters.
//
// ****************************************************************************

void
avtExternalSurfaceFilter::SetAtts(const AttributeGroup *a)
{
    atts = *(const ExternalSurfaceAttributes*)a;
    if (atts.GetRemoveGhosts())
    {
        gz_and_ff = new avtGhostZoneAndFacelistFilter();
        gz_and_ff->SetUseFaceFilter(true);
        gz_and_ff->SetCreateEdgeListFor2DDatasets(atts.GetEdgesIn2D());
        gz_and_ff->SetUpdateDataObjectInfoCallback(UpdateDataObjectInfoCB, (void*)this);
    }
    else
    {
        ff = new avtFacelistFilter();
        ff->SetCreateEdgeListFor2DDatasets(atts.GetEdgesIn2D());
        ff->SetUpdateDataObjectInfoCallback(UpdateDataObjectInfoCB, (void*)this);
    }
}


// ****************************************************************************
//  Method: avtExternalSurfaceFilter::Equivalent
//
//  Purpose:
//      Returns true if creating a new avtExternalSurfaceFilter with the given
//      parameters would result in an equivalent avtExternalSurfaceFilter.
//
//  Programmer: meredith -- generated by xml2info
//  Creation:   Sat Aug 3 11:48:17 PDT 2002
//
// ****************************************************************************

bool
avtExternalSurfaceFilter::Equivalent(const AttributeGroup *a)
{
    return (atts == *(ExternalSurfaceAttributes*)a);
}


// ****************************************************************************
//  Method: avtExternalSurfaceFilter::GetFacadedFilter
//
//  Purpose:
//      Gets the filter that we are a facade of.
//
//  Returns:       The output dataset.
//
//  Programmer: meredith -- generated by xml2info
//  Creation:   Sat Aug 3 11:48:17 PDT 2002
//
//  Modifications:
//
//    Hank Childs, Tue Aug 23 09:49:57 PDT 2005
//    Add support for ghost zone removal.
//
// ****************************************************************************

avtFilter *
avtExternalSurfaceFilter::GetFacadedFilter(void)
{
    if (atts.GetRemoveGhosts())
        return gz_and_ff;
    return ff;

    // Stupid compilers dislike this one...
    // return (atts.GetRemoveGhosts() ? gz_and_ff : ff);
}

// ****************************************************************************
//  Method: avtExternalSurfaceFilter::GetFacadedFilter
//
//  Purpose:
//      Gets the filter that we are a facade of.
//
//  Returns:       The output dataset.
//
//  Programmer: Tom Fogal
//  Creation:   June 23, 2009
//
// ****************************************************************************

const avtFilter *
avtExternalSurfaceFilter::GetFacadedFilter(void) const
{
    if (atts.GetRemoveGhosts())
        return gz_and_ff;
    return ff;
}

// ****************************************************************************
// Method: avtExternalSurfaceFilter::UpdateDataObjectInfoCB
//
// Purpose:
//   Update the data object information.
//
// Note:       Work partially supported by DOE Grant SC0007548.
//
// Programmer: Brad Whitlock
// Creation:   Tue Mar 18 10:53:05 PDT 2014
//
// Modifications:
//
// ****************************************************************************

void
avtExternalSurfaceFilter::UpdateDataObjectInfoCB(avtDataObject_p &input,
    avtDataObject_p &output, void *This)
{
    avtDataAttributes &outAtts = output->GetInfo().GetAttributes();
    outAtts.AddFilterMetaData("ExternalSurface");
}
