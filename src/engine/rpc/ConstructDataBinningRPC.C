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

#include "ConstructDataBinningRPC.h"
#include <DebugStream.h>


// ****************************************************************************
//  Constructor: ConstructDataBinningRPC::ConstructDataBinningRPC
//
//  Purpose: 
//    This is the constructor.
//
//  Arguments:
//
//  Programmer: Hank Childs
//  Creation:   February 13, 2006
//
// ****************************************************************************

ConstructDataBinningRPC::ConstructDataBinningRPC() : BlockingRPC("ia")
{
}

// ****************************************************************************
//  Destructor: ConstructDataBinningRPC::~ConstructDataBinningRPC
//
//  Purpose: 
//    This is the destructor.
//
//  Arguments:
//
//  Programmer: Hank Childs
//  Creation:   February 13, 2006
//
// ****************************************************************************

ConstructDataBinningRPC::~ConstructDataBinningRPC()
{
}

// ****************************************************************************
//  Method: ConstructDataBinningRPC::operator()
//
//  Purpose: 
//    This is the RPC's invocation method.
//
//  Arguments:
//    id        the network id
//    origData  the type of input 
//
//  Programmer: Hank Childs
//  Creation:   February 13, 2006
//
//  Modifications:
// ****************************************************************************

void
ConstructDataBinningRPC::operator()(const int id_, const ConstructDataBinningAttributes *atts)
{
    SetID(id_);
    SetConstructDataBinningAtts(atts);

    Execute();
}

// ****************************************************************************
//  Method: ConstructDataBinningRPC::SelectAll
//
//  Purpose: 
//    This selects all variables for sending.
//
//  Arguments:
//
//  Programmer: Hank Childs
//  Creation:   February 13, 2006
//
// ****************************************************************************

void
ConstructDataBinningRPC::SelectAll()
{
    Select(0, (void*)&id);
    Select(1, (void*)&constructDataBinningAtts);
}


// ****************************************************************************
//  Method: ConstructDataBinningRPC::SetID
//
//  Purpose: 
//    This sets the id parameter.
//
//  Arguments:
//    id_         the id
//
//  Programmer: Hank Childs
//  Creation:   February 13, 2006
//
// ****************************************************************************

void
ConstructDataBinningRPC::SetID(const int id_)
{
    id = id_;
    Select(0, (void*)&id);
}


// ****************************************************************************
//  Method: ConstructDataBinningRPC::GetID
//
//  Purpose: 
//    This returns network id.
//
//  Arguments:
//
//  Programmer: Hank Childs
//  Creation:   February 13, 2006
//
// ****************************************************************************

int
ConstructDataBinningRPC::GetID() const
{
    return id;
}

// ****************************************************************************
//  Method: ConstructDataBinningRPC::SetConstructDataBinningAtts 
//
//  Purpose:
//    This sets the constructDataBinning atts.
//
//  Arguments:
//    atts      the constructDataBinning atts
//
//  Programmer: Hank Childs
//  Creation:   February 13, 2006 
//
// ****************************************************************************
 
void
ConstructDataBinningRPC::SetConstructDataBinningAtts(const ConstructDataBinningAttributes *atts)
{
    constructDataBinningAtts = *atts;
    Select(1, (void*)&constructDataBinningAtts);
}


// ****************************************************************************
//  Method: ConstructDataBinningRPC::GetConstructDataBinningAtts 
//
//  Purpose:
//    This returns the constructDataBinning atts.
//
//  Programmer: Hank Childs
//  Creation:   February 13, 2006 
//
// ****************************************************************************
 
ConstructDataBinningAttributes *
ConstructDataBinningRPC::GetConstructDataBinningAtts()
{
    return &constructDataBinningAtts;
}
