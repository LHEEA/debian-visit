// ***************************************************************************
//
// Copyright (c) 2000 - 2013, Lawrence Livermore National Security, LLC
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
// Class: TubeAttributes
//
// Purpose:
//    This class contains attributes for the tube operator.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class TubeAttributes extends AttributeSubject implements Plugin
{
    private static int TubeAttributes_numAdditionalAtts = 7;

    // Enum values
    public final static int TUBERADIUSTYPE_FRACTIONOFBBOX = 0;
    public final static int TUBERADIUSTYPE_ABSOLUTE = 1;


    public TubeAttributes()
    {
        super(TubeAttributes_numAdditionalAtts);

        scaleByVarFlag = false;
        tubeRadiusType = TUBERADIUSTYPE_FRACTIONOFBBOX;
        radiusFractionBBox = 0.01;
        radiusAbsolute = 1;
        scaleVariable = new String("");
        fineness = 5;
        capping = false;
    }

    public TubeAttributes(int nMoreFields)
    {
        super(TubeAttributes_numAdditionalAtts + nMoreFields);

        scaleByVarFlag = false;
        tubeRadiusType = TUBERADIUSTYPE_FRACTIONOFBBOX;
        radiusFractionBBox = 0.01;
        radiusAbsolute = 1;
        scaleVariable = new String("");
        fineness = 5;
        capping = false;
    }

    public TubeAttributes(TubeAttributes obj)
    {
        super(TubeAttributes_numAdditionalAtts);

        scaleByVarFlag = obj.scaleByVarFlag;
        tubeRadiusType = obj.tubeRadiusType;
        radiusFractionBBox = obj.radiusFractionBBox;
        radiusAbsolute = obj.radiusAbsolute;
        scaleVariable = new String(obj.scaleVariable);
        fineness = obj.fineness;
        capping = obj.capping;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return TubeAttributes_numAdditionalAtts;
    }

    public boolean equals(TubeAttributes obj)
    {
        // Create the return value
        return ((scaleByVarFlag == obj.scaleByVarFlag) &&
                (tubeRadiusType == obj.tubeRadiusType) &&
                (radiusFractionBBox == obj.radiusFractionBBox) &&
                (radiusAbsolute == obj.radiusAbsolute) &&
                (scaleVariable.equals(obj.scaleVariable)) &&
                (fineness == obj.fineness) &&
                (capping == obj.capping));
    }

    public String GetName() { return "Tube"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetScaleByVarFlag(boolean scaleByVarFlag_)
    {
        scaleByVarFlag = scaleByVarFlag_;
        Select(0);
    }

    public void SetTubeRadiusType(int tubeRadiusType_)
    {
        tubeRadiusType = tubeRadiusType_;
        Select(1);
    }

    public void SetRadiusFractionBBox(double radiusFractionBBox_)
    {
        radiusFractionBBox = radiusFractionBBox_;
        Select(2);
    }

    public void SetRadiusAbsolute(double radiusAbsolute_)
    {
        radiusAbsolute = radiusAbsolute_;
        Select(3);
    }

    public void SetScaleVariable(String scaleVariable_)
    {
        scaleVariable = scaleVariable_;
        Select(4);
    }

    public void SetFineness(int fineness_)
    {
        fineness = fineness_;
        Select(5);
    }

    public void SetCapping(boolean capping_)
    {
        capping = capping_;
        Select(6);
    }

    // Property getting methods
    public boolean GetScaleByVarFlag() { return scaleByVarFlag; }
    public int     GetTubeRadiusType() { return tubeRadiusType; }
    public double  GetRadiusFractionBBox() { return radiusFractionBBox; }
    public double  GetRadiusAbsolute() { return radiusAbsolute; }
    public String  GetScaleVariable() { return scaleVariable; }
    public int     GetFineness() { return fineness; }
    public boolean GetCapping() { return capping; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(scaleByVarFlag);
        if(WriteSelect(1, buf))
            buf.WriteInt(tubeRadiusType);
        if(WriteSelect(2, buf))
            buf.WriteDouble(radiusFractionBBox);
        if(WriteSelect(3, buf))
            buf.WriteDouble(radiusAbsolute);
        if(WriteSelect(4, buf))
            buf.WriteString(scaleVariable);
        if(WriteSelect(5, buf))
            buf.WriteInt(fineness);
        if(WriteSelect(6, buf))
            buf.WriteBool(capping);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetScaleByVarFlag(buf.ReadBool());
            break;
        case 1:
            SetTubeRadiusType(buf.ReadInt());
            break;
        case 2:
            SetRadiusFractionBBox(buf.ReadDouble());
            break;
        case 3:
            SetRadiusAbsolute(buf.ReadDouble());
            break;
        case 4:
            SetScaleVariable(buf.ReadString());
            break;
        case 5:
            SetFineness(buf.ReadInt());
            break;
        case 6:
            SetCapping(buf.ReadBool());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + boolToString("scaleByVarFlag", scaleByVarFlag, indent) + "\n";
        str = str + indent + "tubeRadiusType = ";
        if(tubeRadiusType == TUBERADIUSTYPE_FRACTIONOFBBOX)
            str = str + "TUBERADIUSTYPE_FRACTIONOFBBOX";
        if(tubeRadiusType == TUBERADIUSTYPE_ABSOLUTE)
            str = str + "TUBERADIUSTYPE_ABSOLUTE";
        str = str + "\n";
        str = str + doubleToString("radiusFractionBBox", radiusFractionBBox, indent) + "\n";
        str = str + doubleToString("radiusAbsolute", radiusAbsolute, indent) + "\n";
        str = str + stringToString("scaleVariable", scaleVariable, indent) + "\n";
        str = str + intToString("fineness", fineness, indent) + "\n";
        str = str + boolToString("capping", capping, indent) + "\n";
        return str;
    }


    // Attributes
    private boolean scaleByVarFlag;
    private int     tubeRadiusType;
    private double  radiusFractionBBox;
    private double  radiusAbsolute;
    private String  scaleVariable;
    private int     fineness;
    private boolean capping;
}

