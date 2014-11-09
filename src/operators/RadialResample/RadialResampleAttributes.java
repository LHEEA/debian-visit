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

package llnl.visit.operators;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;

// ****************************************************************************
// Class: RadialResampleAttributes
//
// Purpose:
//    
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class RadialResampleAttributes extends AttributeSubject implements Plugin
{
    private static int RadialResampleAttributes_numAdditionalAtts = 11;

    public RadialResampleAttributes()
    {
        super(RadialResampleAttributes_numAdditionalAtts);

        isFast = false;
        minTheta = 0f;
        maxTheta = 90f;
        deltaTheta = 5f;
        radius = 0.5f;
        deltaRadius = 0.05f;
        center = new float[3];
        center[0] = 0.5f;
        center[1] = 0.5f;
        center[2] = 0.5f;
        is3D = true;
        minAzimuth = 0f;
        maxAzimuth = 180f;
        deltaAzimuth = 5f;
    }

    public RadialResampleAttributes(int nMoreFields)
    {
        super(RadialResampleAttributes_numAdditionalAtts + nMoreFields);

        isFast = false;
        minTheta = 0f;
        maxTheta = 90f;
        deltaTheta = 5f;
        radius = 0.5f;
        deltaRadius = 0.05f;
        center = new float[3];
        center[0] = 0.5f;
        center[1] = 0.5f;
        center[2] = 0.5f;
        is3D = true;
        minAzimuth = 0f;
        maxAzimuth = 180f;
        deltaAzimuth = 5f;
    }

    public RadialResampleAttributes(RadialResampleAttributes obj)
    {
        super(RadialResampleAttributes_numAdditionalAtts);

        int i;

        isFast = obj.isFast;
        minTheta = obj.minTheta;
        maxTheta = obj.maxTheta;
        deltaTheta = obj.deltaTheta;
        radius = obj.radius;
        deltaRadius = obj.deltaRadius;
        center = new float[3];
        center[0] = obj.center[0];
        center[1] = obj.center[1];
        center[2] = obj.center[2];

        is3D = obj.is3D;
        minAzimuth = obj.minAzimuth;
        maxAzimuth = obj.maxAzimuth;
        deltaAzimuth = obj.deltaAzimuth;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return RadialResampleAttributes_numAdditionalAtts;
    }

    public boolean equals(RadialResampleAttributes obj)
    {
        int i;

        // Compare the center arrays.
        boolean center_equal = true;
        for(i = 0; i < 3 && center_equal; ++i)
            center_equal = (center[i] == obj.center[i]);

        // Create the return value
        return ((isFast == obj.isFast) &&
                (minTheta == obj.minTheta) &&
                (maxTheta == obj.maxTheta) &&
                (deltaTheta == obj.deltaTheta) &&
                (radius == obj.radius) &&
                (deltaRadius == obj.deltaRadius) &&
                center_equal &&
                (is3D == obj.is3D) &&
                (minAzimuth == obj.minAzimuth) &&
                (maxAzimuth == obj.maxAzimuth) &&
                (deltaAzimuth == obj.deltaAzimuth));
    }

    public String GetName() { return "RadialResample"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetIsFast(boolean isFast_)
    {
        isFast = isFast_;
        Select(0);
    }

    public void SetMinTheta(float minTheta_)
    {
        minTheta = minTheta_;
        Select(1);
    }

    public void SetMaxTheta(float maxTheta_)
    {
        maxTheta = maxTheta_;
        Select(2);
    }

    public void SetDeltaTheta(float deltaTheta_)
    {
        deltaTheta = deltaTheta_;
        Select(3);
    }

    public void SetRadius(float radius_)
    {
        radius = radius_;
        Select(4);
    }

    public void SetDeltaRadius(float deltaRadius_)
    {
        deltaRadius = deltaRadius_;
        Select(5);
    }

    public void SetCenter(float[] center_)
    {
        center[0] = center_[0];
        center[1] = center_[1];
        center[2] = center_[2];
        Select(6);
    }

    public void SetCenter(float e0, float e1, float e2)
    {
        center[0] = e0;
        center[1] = e1;
        center[2] = e2;
        Select(6);
    }

    public void SetIs3D(boolean is3D_)
    {
        is3D = is3D_;
        Select(7);
    }

    public void SetMinAzimuth(float minAzimuth_)
    {
        minAzimuth = minAzimuth_;
        Select(8);
    }

    public void SetMaxAzimuth(float maxAzimuth_)
    {
        maxAzimuth = maxAzimuth_;
        Select(9);
    }

    public void SetDeltaAzimuth(float deltaAzimuth_)
    {
        deltaAzimuth = deltaAzimuth_;
        Select(10);
    }

    // Property getting methods
    public boolean GetIsFast() { return isFast; }
    public float   GetMinTheta() { return minTheta; }
    public float   GetMaxTheta() { return maxTheta; }
    public float   GetDeltaTheta() { return deltaTheta; }
    public float   GetRadius() { return radius; }
    public float   GetDeltaRadius() { return deltaRadius; }
    public float[] GetCenter() { return center; }
    public boolean GetIs3D() { return is3D; }
    public float   GetMinAzimuth() { return minAzimuth; }
    public float   GetMaxAzimuth() { return maxAzimuth; }
    public float   GetDeltaAzimuth() { return deltaAzimuth; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(isFast);
        if(WriteSelect(1, buf))
            buf.WriteFloat(minTheta);
        if(WriteSelect(2, buf))
            buf.WriteFloat(maxTheta);
        if(WriteSelect(3, buf))
            buf.WriteFloat(deltaTheta);
        if(WriteSelect(4, buf))
            buf.WriteFloat(radius);
        if(WriteSelect(5, buf))
            buf.WriteFloat(deltaRadius);
        if(WriteSelect(6, buf))
            buf.WriteFloatArray(center);
        if(WriteSelect(7, buf))
            buf.WriteBool(is3D);
        if(WriteSelect(8, buf))
            buf.WriteFloat(minAzimuth);
        if(WriteSelect(9, buf))
            buf.WriteFloat(maxAzimuth);
        if(WriteSelect(10, buf))
            buf.WriteFloat(deltaAzimuth);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetIsFast(buf.ReadBool());
            break;
        case 1:
            SetMinTheta(buf.ReadFloat());
            break;
        case 2:
            SetMaxTheta(buf.ReadFloat());
            break;
        case 3:
            SetDeltaTheta(buf.ReadFloat());
            break;
        case 4:
            SetRadius(buf.ReadFloat());
            break;
        case 5:
            SetDeltaRadius(buf.ReadFloat());
            break;
        case 6:
            SetCenter(buf.ReadFloatArray());
            break;
        case 7:
            SetIs3D(buf.ReadBool());
            break;
        case 8:
            SetMinAzimuth(buf.ReadFloat());
            break;
        case 9:
            SetMaxAzimuth(buf.ReadFloat());
            break;
        case 10:
            SetDeltaAzimuth(buf.ReadFloat());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + boolToString("isFast", isFast, indent) + "\n";
        str = str + floatToString("minTheta", minTheta, indent) + "\n";
        str = str + floatToString("maxTheta", maxTheta, indent) + "\n";
        str = str + floatToString("deltaTheta", deltaTheta, indent) + "\n";
        str = str + floatToString("radius", radius, indent) + "\n";
        str = str + floatToString("deltaRadius", deltaRadius, indent) + "\n";
        str = str + floatArrayToString("center", center, indent) + "\n";
        str = str + boolToString("is3D", is3D, indent) + "\n";
        str = str + floatToString("minAzimuth", minAzimuth, indent) + "\n";
        str = str + floatToString("maxAzimuth", maxAzimuth, indent) + "\n";
        str = str + floatToString("deltaAzimuth", deltaAzimuth, indent) + "\n";
        return str;
    }


    // Attributes
    private boolean isFast;
    private float   minTheta;
    private float   maxTheta;
    private float   deltaTheta;
    private float   radius;
    private float   deltaRadius;
    private float[] center;
    private boolean is3D;
    private float   minAzimuth;
    private float   maxAzimuth;
    private float   deltaAzimuth;
}
