// ***************************************************************************
//
// Copyright (c) 2000 - 2014, Lawrence Livermore National Security, LLC
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


// ****************************************************************************
// Class: PointAttributes
//
// Purpose:
//    Attributes for a point
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class PointAttributes extends AttributeSubject
{
    private static int PointAttributes_numAdditionalAtts = 1;

    public PointAttributes()
    {
        super(PointAttributes_numAdditionalAtts);

        point = new double[3];
        point[0] = 0;
        point[1] = 0;
        point[2] = 0;
    }

    public PointAttributes(int nMoreFields)
    {
        super(PointAttributes_numAdditionalAtts + nMoreFields);

        point = new double[3];
        point[0] = 0;
        point[1] = 0;
        point[2] = 0;
    }

    public PointAttributes(PointAttributes obj)
    {
        super(PointAttributes_numAdditionalAtts);

        int i;

        point = new double[3];
        point[0] = obj.point[0];
        point[1] = obj.point[1];
        point[2] = obj.point[2];


        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return PointAttributes_numAdditionalAtts;
    }

    public boolean equals(PointAttributes obj)
    {
        int i;

        // Compare the point arrays.
        boolean point_equal = true;
        for(i = 0; i < 3 && point_equal; ++i)
            point_equal = (point[i] == obj.point[i]);

        // Create the return value
        return (point_equal);
    }

    // Property setting methods
    public void SetPoint(double[] point_)
    {
        point[0] = point_[0];
        point[1] = point_[1];
        point[2] = point_[2];
        Select(0);
    }

    public void SetPoint(double e0, double e1, double e2)
    {
        point[0] = e0;
        point[1] = e1;
        point[2] = e2;
        Select(0);
    }

    // Property getting methods
    public double[] GetPoint() { return point; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteDoubleArray(point);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        SetPoint(buf.ReadDoubleArray());
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + doubleArrayToString("point", point, indent) + "\n";
        return str;
    }


    // Attributes
    private double[] point;
}

