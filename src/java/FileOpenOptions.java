// ***************************************************************************
//
// Copyright (c) 2000 - 2015, Lawrence Livermore National Security, LLC
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
import java.lang.Integer;

// ****************************************************************************
// Class: FileOpenOptions
//
// Purpose:
//    This class contains the file opening options for all the database plugins.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class FileOpenOptions extends AttributeSubject
{
    private static int FileOpenOptions_numAdditionalAtts = 5;

    public FileOpenOptions()
    {
        super(FileOpenOptions_numAdditionalAtts);

        typeNames = new Vector();
        typeIDs = new Vector();
        openOptions = new Vector();
        Enabled = new Vector();
        preferredIDs = new Vector();
        preferredIDs.addElement(new String("Silo_1.0"));
    }

    public FileOpenOptions(int nMoreFields)
    {
        super(FileOpenOptions_numAdditionalAtts + nMoreFields);

        typeNames = new Vector();
        typeIDs = new Vector();
        openOptions = new Vector();
        Enabled = new Vector();
        preferredIDs = new Vector();
        preferredIDs.addElement(new String("Silo_1.0"));
    }

    public FileOpenOptions(FileOpenOptions obj)
    {
        super(FileOpenOptions_numAdditionalAtts);

        int i;

        typeNames = new Vector(obj.typeNames.size());
        for(i = 0; i < obj.typeNames.size(); ++i)
            typeNames.addElement(new String((String)obj.typeNames.elementAt(i)));

        typeIDs = new Vector(obj.typeIDs.size());
        for(i = 0; i < obj.typeIDs.size(); ++i)
            typeIDs.addElement(new String((String)obj.typeIDs.elementAt(i)));

        // *** Copy the openOptions field ***
        openOptions = new Vector(obj.openOptions.size());
        for(i = 0; i < obj.openOptions.size(); ++i)
        {
            DBOptionsAttributes oldObj = (DBOptionsAttributes)obj.openOptions.elementAt(i);
            openOptions.addElement(new DBOptionsAttributes(oldObj));
        }

        Enabled = new Vector();
        for(i = 0; i < obj.Enabled.size(); ++i)
        {
            Integer iv = (Integer)obj.Enabled.elementAt(i);
            Enabled.addElement(new Integer(iv.intValue()));
        }
        preferredIDs = new Vector(obj.preferredIDs.size());
        for(i = 0; i < obj.preferredIDs.size(); ++i)
            preferredIDs.addElement(new String((String)obj.preferredIDs.elementAt(i)));


        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return FileOpenOptions_numAdditionalAtts;
    }

    public boolean equals(FileOpenOptions obj)
    {
        int i;

        // Compare the elements in the typeNames vector.
        boolean typeNames_equal = (obj.typeNames.size() == typeNames.size());
        for(i = 0; (i < typeNames.size()) && typeNames_equal; ++i)
        {
            // Make references to String from Object.
            String typeNames1 = (String)typeNames.elementAt(i);
            String typeNames2 = (String)obj.typeNames.elementAt(i);
            typeNames_equal = typeNames1.equals(typeNames2);
        }
        // Compare the elements in the typeIDs vector.
        boolean typeIDs_equal = (obj.typeIDs.size() == typeIDs.size());
        for(i = 0; (i < typeIDs.size()) && typeIDs_equal; ++i)
        {
            // Make references to String from Object.
            String typeIDs1 = (String)typeIDs.elementAt(i);
            String typeIDs2 = (String)obj.typeIDs.elementAt(i);
            typeIDs_equal = typeIDs1.equals(typeIDs2);
        }
        // Compare the elements in the openOptions vector.
        boolean openOptions_equal = (obj.openOptions.size() == openOptions.size());
        for(i = 0; (i < openOptions.size()) && openOptions_equal; ++i)
        {
            // Make references to DBOptionsAttributes from Object.
            DBOptionsAttributes openOptions1 = (DBOptionsAttributes)openOptions.elementAt(i);
            DBOptionsAttributes openOptions2 = (DBOptionsAttributes)obj.openOptions.elementAt(i);
            openOptions_equal = openOptions1.equals(openOptions2);
        }
        // Compare the elements in the Enabled vector.
        boolean Enabled_equal = (obj.Enabled.size() == Enabled.size());
        for(i = 0; (i < Enabled.size()) && Enabled_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer Enabled1 = (Integer)Enabled.elementAt(i);
            Integer Enabled2 = (Integer)obj.Enabled.elementAt(i);
            Enabled_equal = Enabled1.equals(Enabled2);
        }
        // Compare the elements in the preferredIDs vector.
        boolean preferredIDs_equal = (obj.preferredIDs.size() == preferredIDs.size());
        for(i = 0; (i < preferredIDs.size()) && preferredIDs_equal; ++i)
        {
            // Make references to String from Object.
            String preferredIDs1 = (String)preferredIDs.elementAt(i);
            String preferredIDs2 = (String)obj.preferredIDs.elementAt(i);
            preferredIDs_equal = preferredIDs1.equals(preferredIDs2);
        }
        // Create the return value
        return (typeNames_equal &&
                typeIDs_equal &&
                openOptions_equal &&
                Enabled_equal &&
                preferredIDs_equal);
    }

    // Property setting methods
    public void SetTypeNames(Vector typeNames_)
    {
        typeNames = typeNames_;
        Select(0);
    }

    public void SetTypeIDs(Vector typeIDs_)
    {
        typeIDs = typeIDs_;
        Select(1);
    }

    public void SetEnabled(Vector Enabled_)
    {
        Enabled = Enabled_;
        Select(3);
    }

    public void SetPreferredIDs(Vector preferredIDs_)
    {
        preferredIDs = preferredIDs_;
        Select(4);
    }

    // Property getting methods
    public Vector GetTypeNames() { return typeNames; }
    public Vector GetTypeIDs() { return typeIDs; }
    public Vector GetOpenOptions() { return openOptions; }
    public Vector GetEnabled() { return Enabled; }
    public Vector GetPreferredIDs() { return preferredIDs; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteStringVector(typeNames);
        if(WriteSelect(1, buf))
            buf.WriteStringVector(typeIDs);
        if(WriteSelect(2, buf))
        {
            buf.WriteInt(openOptions.size());
            for(int i = 0; i < openOptions.size(); ++i)
            {
                DBOptionsAttributes tmp = (DBOptionsAttributes)openOptions.elementAt(i);
                tmp.Write(buf);
            }
        }
        if(WriteSelect(3, buf))
            buf.WriteIntVector(Enabled);
        if(WriteSelect(4, buf))
            buf.WriteStringVector(preferredIDs);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetTypeNames(buf.ReadStringVector());
            break;
        case 1:
            SetTypeIDs(buf.ReadStringVector());
            break;
        case 2:
            {
                int len = buf.ReadInt();
                openOptions.clear();
                for(int j = 0; j < len; ++j)
                {
                    DBOptionsAttributes tmp = new DBOptionsAttributes();
                    tmp.Read(buf);
                    openOptions.addElement(tmp);
                }
            }
            Select(2);
            break;
        case 3:
            SetEnabled(buf.ReadIntVector());
            break;
        case 4:
            SetPreferredIDs(buf.ReadStringVector());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + stringVectorToString("typeNames", typeNames, indent) + "\n";
        str = str + stringVectorToString("typeIDs", typeIDs, indent) + "\n";
        str = str + indent + "openOptions = {\n";
        for(int i = 0; i < openOptions.size(); ++i)
        {
            AttributeSubject s = (AttributeSubject)openOptions.elementAt(i);
            str = str + s.toString(indent + "    ");
            if(i < openOptions.size()-1)
                str = str + ", ";
            str = str + "\n";
        }
        str = str + "}\n";
        str = str + intVectorToString("Enabled", Enabled, indent) + "\n";
        str = str + stringVectorToString("preferredIDs", preferredIDs, indent) + "\n";
        return str;
    }

    // Attributegroup convenience methods
    public void AddOpenOptions(DBOptionsAttributes obj)
    {
        openOptions.addElement(new DBOptionsAttributes(obj));
        Select(2);
    }

    public void ClearOpenOptions()
    {
        openOptions.clear();
        Select(2);
    }

    public void RemoveOpenOptions(int index)
    {
        if(index >= 0 && index < openOptions.size())
        {
            openOptions.remove(index);
            Select(2);
        }
    }

    public int GetNumOpenOptions()
    {
        return openOptions.size();
    }

    public DBOptionsAttributes GetOpenOptions(int i)
    {
        DBOptionsAttributes tmp = (DBOptionsAttributes)openOptions.elementAt(i);
        return tmp;
    }


    // Attributes
    private Vector typeNames; // vector of String objects
    private Vector typeIDs; // vector of String objects
    private Vector openOptions; // vector of DBOptionsAttributes objects
    private Vector Enabled; // vector of Integer objects
    private Vector preferredIDs; // vector of String objects
}

