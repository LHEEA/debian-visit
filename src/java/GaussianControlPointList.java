// ***************************************************************************
//
// Copyright (c) 2000 - 2017, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-442911
// All rights reserved.
//
// This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
// LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
// DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ***************************************************************************

package llnl.visit;

import java.util.Vector;

// ****************************************************************************
// Class: GaussianControlPointList
//
// Purpose:
//    This class contains a list of GaussianControlPoint objects.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class GaussianControlPointList extends AttributeSubject
{
    private static int GaussianControlPointList_numAdditionalAtts = 1;

    public GaussianControlPointList()
    {
        super(GaussianControlPointList_numAdditionalAtts);

        controlPoints = new Vector();
    }

    public GaussianControlPointList(int nMoreFields)
    {
        super(GaussianControlPointList_numAdditionalAtts + nMoreFields);

        controlPoints = new Vector();
    }

    public GaussianControlPointList(GaussianControlPointList obj)
    {
        super(obj);

        int i;

        // *** Copy the controlPoints field ***
        controlPoints = new Vector(obj.controlPoints.size());
        for(i = 0; i < obj.controlPoints.size(); ++i)
        {
            GaussianControlPoint oldObj = (GaussianControlPoint)obj.controlPoints.elementAt(i);
            controlPoints.addElement(new GaussianControlPoint(oldObj));
        }


        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return GaussianControlPointList_numAdditionalAtts;
    }

    public boolean equals(GaussianControlPointList obj)
    {
        int i;

        // Compare the elements in the controlPoints vector.
        boolean controlPoints_equal = (obj.controlPoints.size() == controlPoints.size());
        for(i = 0; (i < controlPoints.size()) && controlPoints_equal; ++i)
        {
            // Make references to GaussianControlPoint from Object.
            GaussianControlPoint controlPoints1 = (GaussianControlPoint)controlPoints.elementAt(i);
            GaussianControlPoint controlPoints2 = (GaussianControlPoint)obj.controlPoints.elementAt(i);
            controlPoints_equal = controlPoints1.equals(controlPoints2);
        }
        // Create the return value
        return (controlPoints_equal);
    }

    // Property setting methods
    // Property getting methods
    public Vector GetControlPoints() { return controlPoints; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
        {
            buf.WriteInt(controlPoints.size());
            for(int i = 0; i < controlPoints.size(); ++i)
            {
                GaussianControlPoint tmp = (GaussianControlPoint)controlPoints.elementAt(i);
                tmp.Write(buf);
            }
        }
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        {
            int len = buf.ReadInt();
            controlPoints.clear();
            for(int j = 0; j < len; ++j)
            {
                GaussianControlPoint tmp = new GaussianControlPoint();
                tmp.Read(buf);
                controlPoints.addElement(tmp);
            }
        }
        Select(0);
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "controlPoints = {\n";
        for(int i = 0; i < controlPoints.size(); ++i)
        {
            AttributeSubject s = (AttributeSubject)controlPoints.elementAt(i);
            str = str + s.toString(indent + "    ");
            if(i < controlPoints.size()-1)
                str = str + ", ";
            str = str + "\n";
        }
        str = str + "}\n";
        return str;
    }

    // Attributegroup convenience methods
    public void AddControlPoints(GaussianControlPoint obj)
    {
        controlPoints.addElement(new GaussianControlPoint(obj));
        Select(0);
    }

    public void ClearControlPoints()
    {
        controlPoints.clear();
        Select(0);
    }

    public void RemoveControlPoints(int index)
    {
        if(index >= 0 && index < controlPoints.size())
        {
            controlPoints.remove(index);
            Select(0);
        }
    }

    public int GetNumControlPoints()
    {
        return controlPoints.size();
    }

    public GaussianControlPoint GetControlPoints(int i)
    {
        GaussianControlPoint tmp = (GaussianControlPoint)controlPoints.elementAt(i);
        return tmp;
    }


    // Attributes
    private Vector controlPoints; // vector of GaussianControlPoint objects
}

