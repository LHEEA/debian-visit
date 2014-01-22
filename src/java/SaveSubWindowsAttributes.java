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

package llnl.visit;


// ****************************************************************************
// Class: SaveSubWindowsAttributes
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

public class SaveSubWindowsAttributes extends AttributeSubject
{
    private static int SaveSubWindowsAttributes_numAdditionalAtts = 16;

    public SaveSubWindowsAttributes()
    {
        super(SaveSubWindowsAttributes_numAdditionalAtts);

        win1 = new SaveSubWindowAttributes();
        win2 = new SaveSubWindowAttributes();
        win3 = new SaveSubWindowAttributes();
        win4 = new SaveSubWindowAttributes();
        win5 = new SaveSubWindowAttributes();
        win6 = new SaveSubWindowAttributes();
        win7 = new SaveSubWindowAttributes();
        win8 = new SaveSubWindowAttributes();
        win9 = new SaveSubWindowAttributes();
        win10 = new SaveSubWindowAttributes();
        win11 = new SaveSubWindowAttributes();
        win12 = new SaveSubWindowAttributes();
        win13 = new SaveSubWindowAttributes();
        win14 = new SaveSubWindowAttributes();
        win15 = new SaveSubWindowAttributes();
        win16 = new SaveSubWindowAttributes();
    }

    public SaveSubWindowsAttributes(int nMoreFields)
    {
        super(SaveSubWindowsAttributes_numAdditionalAtts + nMoreFields);

        win1 = new SaveSubWindowAttributes();
        win2 = new SaveSubWindowAttributes();
        win3 = new SaveSubWindowAttributes();
        win4 = new SaveSubWindowAttributes();
        win5 = new SaveSubWindowAttributes();
        win6 = new SaveSubWindowAttributes();
        win7 = new SaveSubWindowAttributes();
        win8 = new SaveSubWindowAttributes();
        win9 = new SaveSubWindowAttributes();
        win10 = new SaveSubWindowAttributes();
        win11 = new SaveSubWindowAttributes();
        win12 = new SaveSubWindowAttributes();
        win13 = new SaveSubWindowAttributes();
        win14 = new SaveSubWindowAttributes();
        win15 = new SaveSubWindowAttributes();
        win16 = new SaveSubWindowAttributes();
    }

    public SaveSubWindowsAttributes(SaveSubWindowsAttributes obj)
    {
        super(SaveSubWindowsAttributes_numAdditionalAtts);

        win1 = new SaveSubWindowAttributes(obj.win1);
        win2 = new SaveSubWindowAttributes(obj.win2);
        win3 = new SaveSubWindowAttributes(obj.win3);
        win4 = new SaveSubWindowAttributes(obj.win4);
        win5 = new SaveSubWindowAttributes(obj.win5);
        win6 = new SaveSubWindowAttributes(obj.win6);
        win7 = new SaveSubWindowAttributes(obj.win7);
        win8 = new SaveSubWindowAttributes(obj.win8);
        win9 = new SaveSubWindowAttributes(obj.win9);
        win10 = new SaveSubWindowAttributes(obj.win10);
        win11 = new SaveSubWindowAttributes(obj.win11);
        win12 = new SaveSubWindowAttributes(obj.win12);
        win13 = new SaveSubWindowAttributes(obj.win13);
        win14 = new SaveSubWindowAttributes(obj.win14);
        win15 = new SaveSubWindowAttributes(obj.win15);
        win16 = new SaveSubWindowAttributes(obj.win16);

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return SaveSubWindowsAttributes_numAdditionalAtts;
    }

    public boolean equals(SaveSubWindowsAttributes obj)
    {
        // Create the return value
        return ((win1.equals(obj.win1)) &&
                (win2.equals(obj.win2)) &&
                (win3.equals(obj.win3)) &&
                (win4.equals(obj.win4)) &&
                (win5.equals(obj.win5)) &&
                (win6.equals(obj.win6)) &&
                (win7.equals(obj.win7)) &&
                (win8.equals(obj.win8)) &&
                (win9.equals(obj.win9)) &&
                (win10.equals(obj.win10)) &&
                (win11.equals(obj.win11)) &&
                (win12.equals(obj.win12)) &&
                (win13.equals(obj.win13)) &&
                (win14.equals(obj.win14)) &&
                (win15.equals(obj.win15)) &&
                (win16.equals(obj.win16)));
    }

    // Property setting methods
    public void SetWin1(SaveSubWindowAttributes win1_)
    {
        win1 = win1_;
        Select(0);
    }

    public void SetWin2(SaveSubWindowAttributes win2_)
    {
        win2 = win2_;
        Select(1);
    }

    public void SetWin3(SaveSubWindowAttributes win3_)
    {
        win3 = win3_;
        Select(2);
    }

    public void SetWin4(SaveSubWindowAttributes win4_)
    {
        win4 = win4_;
        Select(3);
    }

    public void SetWin5(SaveSubWindowAttributes win5_)
    {
        win5 = win5_;
        Select(4);
    }

    public void SetWin6(SaveSubWindowAttributes win6_)
    {
        win6 = win6_;
        Select(5);
    }

    public void SetWin7(SaveSubWindowAttributes win7_)
    {
        win7 = win7_;
        Select(6);
    }

    public void SetWin8(SaveSubWindowAttributes win8_)
    {
        win8 = win8_;
        Select(7);
    }

    public void SetWin9(SaveSubWindowAttributes win9_)
    {
        win9 = win9_;
        Select(8);
    }

    public void SetWin10(SaveSubWindowAttributes win10_)
    {
        win10 = win10_;
        Select(9);
    }

    public void SetWin11(SaveSubWindowAttributes win11_)
    {
        win11 = win11_;
        Select(10);
    }

    public void SetWin12(SaveSubWindowAttributes win12_)
    {
        win12 = win12_;
        Select(11);
    }

    public void SetWin13(SaveSubWindowAttributes win13_)
    {
        win13 = win13_;
        Select(12);
    }

    public void SetWin14(SaveSubWindowAttributes win14_)
    {
        win14 = win14_;
        Select(13);
    }

    public void SetWin15(SaveSubWindowAttributes win15_)
    {
        win15 = win15_;
        Select(14);
    }

    public void SetWin16(SaveSubWindowAttributes win16_)
    {
        win16 = win16_;
        Select(15);
    }

    // Property getting methods
    public SaveSubWindowAttributes GetWin1() { return win1; }
    public SaveSubWindowAttributes GetWin2() { return win2; }
    public SaveSubWindowAttributes GetWin3() { return win3; }
    public SaveSubWindowAttributes GetWin4() { return win4; }
    public SaveSubWindowAttributes GetWin5() { return win5; }
    public SaveSubWindowAttributes GetWin6() { return win6; }
    public SaveSubWindowAttributes GetWin7() { return win7; }
    public SaveSubWindowAttributes GetWin8() { return win8; }
    public SaveSubWindowAttributes GetWin9() { return win9; }
    public SaveSubWindowAttributes GetWin10() { return win10; }
    public SaveSubWindowAttributes GetWin11() { return win11; }
    public SaveSubWindowAttributes GetWin12() { return win12; }
    public SaveSubWindowAttributes GetWin13() { return win13; }
    public SaveSubWindowAttributes GetWin14() { return win14; }
    public SaveSubWindowAttributes GetWin15() { return win15; }
    public SaveSubWindowAttributes GetWin16() { return win16; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            win1.Write(buf);
        if(WriteSelect(1, buf))
            win2.Write(buf);
        if(WriteSelect(2, buf))
            win3.Write(buf);
        if(WriteSelect(3, buf))
            win4.Write(buf);
        if(WriteSelect(4, buf))
            win5.Write(buf);
        if(WriteSelect(5, buf))
            win6.Write(buf);
        if(WriteSelect(6, buf))
            win7.Write(buf);
        if(WriteSelect(7, buf))
            win8.Write(buf);
        if(WriteSelect(8, buf))
            win9.Write(buf);
        if(WriteSelect(9, buf))
            win10.Write(buf);
        if(WriteSelect(10, buf))
            win11.Write(buf);
        if(WriteSelect(11, buf))
            win12.Write(buf);
        if(WriteSelect(12, buf))
            win13.Write(buf);
        if(WriteSelect(13, buf))
            win14.Write(buf);
        if(WriteSelect(14, buf))
            win15.Write(buf);
        if(WriteSelect(15, buf))
            win16.Write(buf);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            win1.Read(buf);
            Select(0);
            break;
        case 1:
            win2.Read(buf);
            Select(1);
            break;
        case 2:
            win3.Read(buf);
            Select(2);
            break;
        case 3:
            win4.Read(buf);
            Select(3);
            break;
        case 4:
            win5.Read(buf);
            Select(4);
            break;
        case 5:
            win6.Read(buf);
            Select(5);
            break;
        case 6:
            win7.Read(buf);
            Select(6);
            break;
        case 7:
            win8.Read(buf);
            Select(7);
            break;
        case 8:
            win9.Read(buf);
            Select(8);
            break;
        case 9:
            win10.Read(buf);
            Select(9);
            break;
        case 10:
            win11.Read(buf);
            Select(10);
            break;
        case 11:
            win12.Read(buf);
            Select(11);
            break;
        case 12:
            win13.Read(buf);
            Select(12);
            break;
        case 13:
            win14.Read(buf);
            Select(13);
            break;
        case 14:
            win15.Read(buf);
            Select(14);
            break;
        case 15:
            win16.Read(buf);
            Select(15);
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "win1 = {\n" + win1.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win2 = {\n" + win2.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win3 = {\n" + win3.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win4 = {\n" + win4.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win5 = {\n" + win5.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win6 = {\n" + win6.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win7 = {\n" + win7.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win8 = {\n" + win8.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win9 = {\n" + win9.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win10 = {\n" + win10.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win11 = {\n" + win11.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win12 = {\n" + win12.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win13 = {\n" + win13.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win14 = {\n" + win14.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win15 = {\n" + win15.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "win16 = {\n" + win16.toString(indent + "    ") + indent + "}\n";
        return str;
    }


    // Attributes
    private SaveSubWindowAttributes win1;
    private SaveSubWindowAttributes win2;
    private SaveSubWindowAttributes win3;
    private SaveSubWindowAttributes win4;
    private SaveSubWindowAttributes win5;
    private SaveSubWindowAttributes win6;
    private SaveSubWindowAttributes win7;
    private SaveSubWindowAttributes win8;
    private SaveSubWindowAttributes win9;
    private SaveSubWindowAttributes win10;
    private SaveSubWindowAttributes win11;
    private SaveSubWindowAttributes win12;
    private SaveSubWindowAttributes win13;
    private SaveSubWindowAttributes win14;
    private SaveSubWindowAttributes win15;
    private SaveSubWindowAttributes win16;
}

