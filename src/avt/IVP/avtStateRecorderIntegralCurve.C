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
//                      avtStateRecorderIntegralCurve.C                      //
// ************************************************************************* //

#include <avtStateRecorderIntegralCurve.h>

#include <list>
#include <cmath>
#include <cassert>
#include <iostream>
#include <limits>
#include <ImproperUseException.h>
#include <DebugStream.h>
#include <avtVector.h>
#include <algorithm>

#include <avtParallel.h>

// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve constructor
//
//  Programmer: Hank Childs
//  Creation:   June 4, 2010
//
// ****************************************************************************

avtStateRecorderIntegralCurve::avtStateRecorderIntegralCurve(
    unsigned int mask,
    const avtIVPSolver* model, 
    Direction dir,
    const double& t_start,
    const avtVector &p_start,
    const avtVector &v_start,
    int ID) :
    avtIntegralCurve(model, dir, t_start, p_start, v_start, ID), historyMask(mask)
{
    time = 0.0;
    distance = 0.0;
    sequenceCnt = 0;
    _serializeFlags = SERIALIZE_NO_OPT;

    // The data variable will always be the after the secondary variables.
    if( historyMask & SAMPLE_VARIABLE )
    {
      if( historyMask & SAMPLE_SECONDARY5 )
        variableIndex = 6;
      else if( historyMask & SAMPLE_SECONDARY4 )
        variableIndex = 5;
      else if( historyMask & SAMPLE_SECONDARY3 )
        variableIndex = 4;
      else if( historyMask & SAMPLE_SECONDARY2 )
        variableIndex = 3;
      else if( historyMask & SAMPLE_SECONDARY1 )
        variableIndex = 2;
      else if( historyMask & SAMPLE_SECONDARY0 )
        variableIndex = 1;
      else
        variableIndex = 0;
    }
    else
        variableIndex = 0;
}


// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve constructor
//
//  Programmer: Hank Childs
//  Creation:   June 4, 2010
//
// ****************************************************************************

avtStateRecorderIntegralCurve::avtStateRecorderIntegralCurve()
{
    time = 0.0;
    distance = 0.0;
    sequenceCnt = 0;
    _serializeFlags = SERIALIZE_NO_OPT;
    historyMask = 0;
}


// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve destructor
//
//  Programmer: Hank Childs
//  Creation:   June 4, 2010
//
// ****************************************************************************

avtStateRecorderIntegralCurve::~avtStateRecorderIntegralCurve()
{
}

// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::RecordStep
//
//  Purpose:
//      Records a sample from the current step at the specified time.
//
//  Programmer: Christoph Garth
//  Creation:   July 22, 2010
//
//  Modifications:
//
//   Dave Pugmire, Tue Sep 28 10:39:11 EDT 2010
//   If step is with tolerance of previous step, just overwrite the previous step.
//
//   Dave Pugmire, Fri Jan 28 14:49:50 EST 2011
//   Add scalar2
//
// ****************************************************************************

void avtStateRecorderIntegralCurve::RecordStep(const avtIVPField* field,
                                               const avtIVPStep& step,
                                               bool firstStep)
{
    avtVector p = step.GetP(time);

    if( historyMask & SAMPLE_TIME )
        history.push_back( time );

    if( historyMask & SAMPLE_POSITION )
    {
        history.push_back( p.x );
        history.push_back( p.y );
        history.push_back( p.z );
    }
        
    if( historyMask & SAMPLE_VELOCITY )
    {
        // Do not call as it can give inaccurate results. Use the
        // field directly.
        // avtVector v = step.GetV( time );

        avtVector v;
        (*field)( time, p, v );
        history.push_back( v.x );
        history.push_back( v.y );
        history.push_back( v.z );
    }
    
    if( historyMask & SAMPLE_VORTICITY )
        history.push_back( field->ComputeVorticity( time, p ) );
        
    if( historyMask & SAMPLE_ARCLENGTH )
        history.push_back( distance );
    
    if (historyMask & SAMPLE_DOM_VISIT)
    {
        double val = 0.0;
        
        //First step gets recorded with two samples. Seed point, and first step.
        //Set the number of visits to 1.
        
        size_t nSamp = GetNumberOfSamples();
        if (nSamp == 0 || nSamp == 1)
            val = 1.0;
        else
        {
            Sample prevSamp = GetSample(nSamp-1);
            val = prevSamp.numDomainsVisited;
            
            //First step in a domain, increment the val.
            if (firstStep)
                val = val + 1;
        }
        history.push_back(val);
    }
        
    if( historyMask & SAMPLE_VARIABLE )
        history.push_back( field->ComputeScalarVariable( variableIndex, time, p ) );

    if( historyMask & SAMPLE_SECONDARY0 )
        history.push_back( field->ComputeScalarVariable( 0, time, p ) );
        
    if( historyMask & SAMPLE_SECONDARY1 )
        history.push_back( field->ComputeScalarVariable( 1, time, p ) );

    if( historyMask & SAMPLE_SECONDARY2 )
        history.push_back( field->ComputeScalarVariable( 2, time, p ) );

    if( historyMask & SAMPLE_SECONDARY3 )
        history.push_back( field->ComputeScalarVariable( 3, time, p ) );
        
    if( historyMask & SAMPLE_SECONDARY4 )
        history.push_back( field->ComputeScalarVariable( 4, time, p ) );

    if( historyMask & SAMPLE_SECONDARY5 )
        history.push_back( field->ComputeScalarVariable( 5, time, p ) );
}

// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::AnalyzeStep
//
//  Purpose:
//      Analyzes the current step.
//
//  Programmer: Hank Childs
//  Creation:   June 4, 2010
//
//  Modifications:
//
//    Hank Childs, Fri Oct  8 23:30:27 PDT 2010
//    Move termination criteria into derived types.
//
//    Hank Childs, Sun Dec  5 10:18:13 PST 2010
//    Pass the avtIVPField to CheckForTermination.
//
//    Hank Childs, Mon Mar 12 16:28:33 PDT 2012
//    Make sure last step is always recorded.  Previous logic would lead to a
//    missing step if termination occurred somewhere outside this loop.
//    Props to Christoph Garth for eyeballing this.
//
//    Hank Childs, Sun Apr  1 10:35:48 PDT 2012
//    Change status to use new TERMINATED designation.
//
// ****************************************************************************

void
avtStateRecorderIntegralCurve::AnalyzeStep( avtIVPStep& step, 
                                            avtIVPField* field,
                                            bool firstStep)
{
    if (history.empty())
    {
        // Record the first position of the step.
        time = step.GetT0();
        RecordStep( field, step, false );
    }

    if (CheckForTermination(step, field))
        status.SetTerminationMet();

    // These must be called after CheckForTermination, because
    // CheckForTermination will modify the step if it goes beyond the
    // termination criteria.  (Example: integral curve will split a
    // step if it is terminating by distance.)

    time = step.GetT1();
    distance += step.GetLength();

    RecordStep( field, step, firstStep );
}

// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::GetSampleStride()
//
//  Purpose:
//      Returns the stride between consecutive samples.
//
//  Programmer: Christoph Garth
//  Creation:   July 14, 2010
//
//  Modifications:
//
//   Dave Pugmire, Fri Jan 28 14:49:50 EST 2011
//   Add scalar2
//
// ****************************************************************************

size_t avtStateRecorderIntegralCurve::GetSampleStride() const
{
    size_t stride = 0;

#define TEST_AND_INCREMENT( f, n ) \
    if( historyMask & f )          \
        { stride += n; }

    TEST_AND_INCREMENT( SAMPLE_TIME, 1 );
    TEST_AND_INCREMENT( SAMPLE_POSITION, 3 );
    TEST_AND_INCREMENT( SAMPLE_VELOCITY, 3 );
    TEST_AND_INCREMENT( SAMPLE_VORTICITY, 1 );
    TEST_AND_INCREMENT( SAMPLE_ARCLENGTH, 1 );
    TEST_AND_INCREMENT( SAMPLE_DOM_VISIT, 1 );
    TEST_AND_INCREMENT( SAMPLE_VARIABLE, 1 );
    TEST_AND_INCREMENT( SAMPLE_SECONDARY0, 1 );
    TEST_AND_INCREMENT( SAMPLE_SECONDARY1, 1 );
    TEST_AND_INCREMENT( SAMPLE_SECONDARY2, 1 );
    TEST_AND_INCREMENT( SAMPLE_SECONDARY3, 1 );
    TEST_AND_INCREMENT( SAMPLE_SECONDARY4, 1 );
    TEST_AND_INCREMENT( SAMPLE_SECONDARY5, 1 );

#undef TEST_AND_INCREMENT

    return stride;
};

size_t
avtStateRecorderIntegralCurve::GetSampleIndex(const Attribute &attr) const
{
    size_t idx = 0;

#define TEST_AND_INCREMENT(f, n)   \
    if (historyMask & f)           \
    {                              \
        if (f == attr)             \
            { return idx; }        \
        else                       \
            { idx += n; }          \
    }

    TEST_AND_INCREMENT(SAMPLE_TIME, 1);
    TEST_AND_INCREMENT(SAMPLE_POSITION, 3);
    TEST_AND_INCREMENT(SAMPLE_VELOCITY, 3);
    TEST_AND_INCREMENT(SAMPLE_VORTICITY, 1);
    TEST_AND_INCREMENT(SAMPLE_ARCLENGTH, 1);
    TEST_AND_INCREMENT(SAMPLE_DOM_VISIT, 1);
    TEST_AND_INCREMENT(SAMPLE_VARIABLE, 1);
    TEST_AND_INCREMENT(SAMPLE_SECONDARY0, 1);
    TEST_AND_INCREMENT(SAMPLE_SECONDARY1, 1);
    TEST_AND_INCREMENT(SAMPLE_SECONDARY2, 1);
    TEST_AND_INCREMENT(SAMPLE_SECONDARY3, 1);
    TEST_AND_INCREMENT(SAMPLE_SECONDARY4, 1);
    TEST_AND_INCREMENT(SAMPLE_SECONDARY5, 1);
#undef TEST_AND_INCREMENT
    
    EXCEPTION1(ImproperUseException, 
        "Invalid attribute to avtStateRecorderIntegralCurve::GetSampleIndex");
}


// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::GetSample()
//
//  Purpose:
//      Returns a sample from the integral curve.
//
//  Programmer: Christoph Garth
//  Creation:   July 14, 2010
//
//  Modifications:
//
//   Dave Pugmire, Fri Jan 28 14:49:50 EST 2011
//   Add scalar2
//
// ****************************************************************************

avtStateRecorderIntegralCurve::Sample
avtStateRecorderIntegralCurve::GetSample( size_t n ) const
{
    std::vector<double>::const_iterator m =
      history.begin() + n*GetSampleStride();

    Sample s;

    if( historyMask & SAMPLE_TIME )
        s.time = *(m++);
    else
        s.time = 0;

    if( historyMask & SAMPLE_POSITION )
    {
        s.position.x = *(m++);
        s.position.y = *(m++);
        s.position.z = *(m++);
    }
    else
        s.position = avtVector(0,0,0);

    if( historyMask & SAMPLE_VELOCITY )
    {
        s.velocity.x = *(m++);
        s.velocity.y = *(m++);
        s.velocity.z = *(m++);
    }
    else
        s.velocity = avtVector(0,0,0);

    if( historyMask & SAMPLE_VORTICITY )
        s.vorticity = *(m++);
    else
        s.vorticity = 0;

    if( historyMask & SAMPLE_ARCLENGTH )
        s.arclength = *(m++);
    else
        s.arclength = 0;

    if (historyMask & SAMPLE_DOM_VISIT)
        s.numDomainsVisited = *(m++);
    else
        s.numDomainsVisited = 0.0;

    if( historyMask & SAMPLE_VARIABLE )
        s.variable = *(m++);
    else
        s.variable = 0;

    if( historyMask & SAMPLE_SECONDARY0 ) 
        s.secondarys[0] = *(m++);
    else
        s.secondarys[0] = 0;

    if( historyMask & SAMPLE_SECONDARY1 )
        s.secondarys[1] = *(m++);
    else
        s.secondarys[1] = 0;

    if( historyMask & SAMPLE_SECONDARY2 )
        s.secondarys[2] = *(m++);
    else
        s.secondarys[2] = 0;

    if( historyMask & SAMPLE_SECONDARY3 ) 
        s.secondarys[3] = *(m++);
    else
        s.secondarys[3] = 0;

    if( historyMask & SAMPLE_SECONDARY4 )
        s.secondarys[4] = *(m++);
    else
        s.secondarys[4] = 0;

    if( historyMask & SAMPLE_SECONDARY5 )
        s.secondarys[5] = *(m++);
    else
        s.secondarys[5] = 0;

    return s;
}

// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::GetNumberOfSamples()
//
//  Purpose:
//      Returns the number of history samples.
//
//  Programmer: Christoph Garth
//  Creation:   July 14, 2010
//
// ****************************************************************************

size_t avtStateRecorderIntegralCurve::GetNumberOfSamples() const
{
    return history.size() / GetSampleStride();
}


// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::Finalize
//
//  Purpose:
//      Finalize a curve after being sent to another processor.
//
//  Programmer: Hank Childs
//  Creation:   June 4, 2010
//
// ****************************************************************************
void
avtStateRecorderIntegralCurve::Finalize()
{
    if (historyMask & SAMPLE_DOM_VISIT)
    {
        size_t nSamp = GetNumberOfSamples();
        if (nSamp > 0)
        {
            double val = GetSample(nSamp-1).numDomainsVisited;
            for (size_t i = 0; i < nSamp; i++)
                history[i*GetSampleStride() + GetSampleIndex(SAMPLE_DOM_VISIT)] = val;
        }
    }
}

// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::Serialize
//
//  Purpose:
//      Serializes a curve so it can be sent to another processor.
//
//  Programmer: Hank Childs
//  Creation:   June 4, 2010
//
//  Modifications:
//
//    Hank Childs, Tue Jun  8 09:30:45 CDT 2010
//    Add portions for sequence tracking, which were previously in the base
//    class.
//
//   Dave Pugmire, Mon Sep 20 14:51:50 EDT 2010
//   Serialize the distance field.
//
//   David Camp, Wed Mar  7 10:43:07 PST 2012
//   Added a Serialize flag to the arguments. This is to support the restore
//   ICs code.
//
// ****************************************************************************

void
avtStateRecorderIntegralCurve::Serialize(MemStream::Mode mode, MemStream &buff, 
                                         avtIVPSolver *solver, SerializeFlags serializeFlags)
{
    // Have the base class serialize its part
    avtIntegralCurve::Serialize(mode, buff, solver, serializeFlags);

    buff.io(mode, time);
    buff.io(mode, distance);

    buff.io(mode, historyMask);
    unsigned long saveSerializeFlags = serializeFlags | _serializeFlags;
    buff.io(mode, saveSerializeFlags);

    if (DebugStream::Level5())
    {
        debug5<<"  avtStateRecorderIntegralCurve::Serialize "<<(mode==MemStream::READ?"READ":"WRITE")<<" saveSerializeFlags= "<<saveSerializeFlags<<endl;
    }
    // R/W the steps.
    if (saveSerializeFlags & SERIALIZE_STEPS)
        buff.io(mode, history);

    if (saveSerializeFlags & SERIALIZE_INC_SEQ)
    {
        if (mode == MemStream::WRITE)
        {
            long seqCnt = sequenceCnt+1;
            buff.io(mode, seqCnt);
        }
        else
            buff.io(mode, sequenceCnt);
    }
    else
        buff.io(mode, sequenceCnt);

    if (DebugStream::Level5())
    {
        debug5 << "DONE: avtStateRecorderIntegralCurve::Serialize. sz= "<<buff.len() << endl;
    }
}


// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::MergeIntegralCurveSequence
//
//  Purpose:
//      Merge a vector of curve sequences into a single curve.
//      This is destructive, extra curves are deleted.
//
//  Programmer: Dave Pugmire
//  Creation:   September 24, 2009
//
//  Modifications:
//
//   Dave Pugmire, Tue Feb 23 09:42:25 EST 2010
//   Sorting can be done independant of curve direction. Changed curve
//   step from list to vector.
//
//   David Camp, Fri Jul 29 06:55:39 PDT 2011
//   Added code to send the ending setting, IC status, domain, ivp.
//   The pathlines need this information.
//
// ****************************************************************************

avtIntegralCurve *
avtStateRecorderIntegralCurve::MergeIntegralCurveSequence(std::vector<avtIntegralCurve *> &v2)
{
    if( v2.empty() )
        return NULL;
    size_t vSize = v2.size();
    if( vSize == 1 )
        return v2[0];

    std::vector<avtStateRecorderIntegralCurve *> v( vSize );
    
    for( size_t i=0 ; i<vSize; ++i )
    {
        v[i] = dynamic_cast<avtStateRecorderIntegralCurve*>( v2[i] );
        assert( v[i] != NULL );
    }

    // sort the curves by id and sequence number, in ascending order
    std::sort( v.begin(), v.end(), 
               avtStateRecorderIntegralCurve::IdSeqCompare );

    // find the combined history size
    size_t combinedHistorySize = 0;

    vSize = v.size(); // This should be the same size as v2
    for( size_t i=0; i < vSize; ++i )
    {
        combinedHistorySize += v[i]->history.size();

        // sanity check: make sure all ids are the same
        assert( v[i]->id == v[0]->id );
    }

    //If use color by 'domains visited' we need to increment the pieces.
    if (historyMask & SAMPLE_DOM_VISIT)
    {
        double lastVal = 0.0;

        for (size_t i = 0; i < vSize; i++)
            lastVal += v[i]->GetSample(v[i]->GetNumberOfSamples()-1).numDomainsVisited;
        
        for (size_t i = 0; i < vSize; i++)
        {
            size_t nSamp = v[i]->GetNumberOfSamples();
            for (size_t j = 0; j < nSamp; j++)
                v[i]->history[j*GetSampleStride() + GetSampleIndex(SAMPLE_DOM_VISIT)] = lastVal;
        }
    }

    // Get the values from the last curve in the sequence and store
    // them with the first curve.
    
    // Get the values from the child class
    v[0]->MergeIntegralCurve( v[vSize-1] );

    // Get the values from the base class
    v[0]->time      = v[vSize-1]->time;
    v[0]->distance  = v[vSize-1]->distance;
    v[0]->status    = v[vSize-1]->status;
    v[0]->blockList = v[vSize-1]->blockList;
    avtIVPSolver *tmpSolver = v[0]->ivp;
    v[0]->ivp       = v[vSize-1]->ivp;
    v[vSize-1]->ivp = tmpSolver;

    // The curve pieces are now in sorted order. Merge the histories
    // from each curve in the sequence; merge by appending to the
    // first curve's history. Finally delete the curve. 
    v[0]->history.reserve( combinedHistorySize );

    for( size_t i=1; i < vSize; i++ )
    {
        v[0]->history.insert( v[0]->history.end(), 
                              v[i]->history.begin(), v[i]->history.end() );

        delete v[i];
    }

    v2.clear();
    return v[0];
}

// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::LessThan
//
//  Purpose:
//      Performs a LessThan operation, used when doing parallel communication
//      and needing to sort curves.
//
//  Programmer: Hank Childs
//  Creation:   December 6, 2011
//
// ****************************************************************************

bool
avtStateRecorderIntegralCurve::LessThan(const avtIntegralCurve *ic) const
{
    return IdSeqCompare(this, ic);
}

// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::IdSeqCompare
//
//  Purpose:
//      Sort curves by id, then sequence number.
//
//  Programmer: Dave Pugmire
//  Creation:   September 24, 2009
//
//  Modifications:
//
// ****************************************************************************

bool
avtStateRecorderIntegralCurve::IdSeqCompare(const avtIntegralCurve *icA,
                                            const avtIntegralCurve *icB)
{
    avtStateRecorderIntegralCurve *sicA = (avtStateRecorderIntegralCurve *) icA;
    avtStateRecorderIntegralCurve *sicB = (avtStateRecorderIntegralCurve *) icB;

    if (sicA->id == sicB->id)
        return sicA->sequenceCnt < sicB->sequenceCnt;

    return sicA->id < sicB->id;
}

// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::IdRevSeqCompare
//
//  Purpose:
//      Sort curves by id, then reverse sequence number.
//
//  Programmer: Dave Pugmire
//  Creation:   September 24, 2009
//
//  Modifications:
//
// ****************************************************************************

bool
avtStateRecorderIntegralCurve::IdRevSeqCompare(const avtIntegralCurve *icA,
                                               const avtIntegralCurve *icB)
{
    avtStateRecorderIntegralCurve *sicA = (avtStateRecorderIntegralCurve *) icA;
    avtStateRecorderIntegralCurve *sicB = (avtStateRecorderIntegralCurve *) icB;

    if (sicA->id == sicB->id)
        return sicA->sequenceCnt > sicB->sequenceCnt;

    return sicA->id < sicB->id;
}

// ****************************************************************************
//  Method: avtStateRecorderIntegralCurve::SameCurve
//
//  Purpose:
//      Checks to see if two curves are the same.
//
//  Programmer: Hank Childs
//  Creation:   June 8, 2010
//
// ****************************************************************************

bool
avtStateRecorderIntegralCurve::SameCurve(avtIntegralCurve *ic)
{
    avtStateRecorderIntegralCurve *sic = (avtStateRecorderIntegralCurve *) ic;
    return (id == sic->id) && (sequenceCnt == sic->sequenceCnt);
}
