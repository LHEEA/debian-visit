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
// Class: EngineList
//
// Purpose:
//    This class contains a list of host names on which engines are running.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class EngineList extends AttributeSubject
{
    private static int EngineList_numAdditionalAtts = 3;

    public EngineList()
    {
        super(EngineList_numAdditionalAtts);

        engineName = new Vector();
        simulationName = new Vector();
        properties = new Vector();
    }

    public EngineList(int nMoreFields)
    {
        super(EngineList_numAdditionalAtts + nMoreFields);

        engineName = new Vector();
        simulationName = new Vector();
        properties = new Vector();
    }

    public EngineList(EngineList obj)
    {
        super(EngineList_numAdditionalAtts);

        int i;

        engineName = new Vector(obj.engineName.size());
        for(i = 0; i < obj.engineName.size(); ++i)
            engineName.addElement(new String((String)obj.engineName.elementAt(i)));

        simulationName = new Vector(obj.simulationName.size());
        for(i = 0; i < obj.simulationName.size(); ++i)
            simulationName.addElement(new String((String)obj.simulationName.elementAt(i)));

        // *** Copy the properties field ***
        properties = new Vector(obj.properties.size());
        for(i = 0; i < obj.properties.size(); ++i)
        {
            EngineProperties oldObj = (EngineProperties)obj.properties.elementAt(i);
            properties.addElement(new EngineProperties(oldObj));
        }


        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return EngineList_numAdditionalAtts;
    }

    public boolean equals(EngineList obj)
    {
        int i;

        // Compare the elements in the engineName vector.
        boolean engineName_equal = (obj.engineName.size() == engineName.size());
        for(i = 0; (i < engineName.size()) && engineName_equal; ++i)
        {
            // Make references to String from Object.
            String engineName1 = (String)engineName.elementAt(i);
            String engineName2 = (String)obj.engineName.elementAt(i);
            engineName_equal = engineName1.equals(engineName2);
        }
        // Compare the elements in the simulationName vector.
        boolean simulationName_equal = (obj.simulationName.size() == simulationName.size());
        for(i = 0; (i < simulationName.size()) && simulationName_equal; ++i)
        {
            // Make references to String from Object.
            String simulationName1 = (String)simulationName.elementAt(i);
            String simulationName2 = (String)obj.simulationName.elementAt(i);
            simulationName_equal = simulationName1.equals(simulationName2);
        }
        // Compare the elements in the properties vector.
        boolean properties_equal = (obj.properties.size() == properties.size());
        for(i = 0; (i < properties.size()) && properties_equal; ++i)
        {
            // Make references to EngineProperties from Object.
            EngineProperties properties1 = (EngineProperties)properties.elementAt(i);
            EngineProperties properties2 = (EngineProperties)obj.properties.elementAt(i);
            properties_equal = properties1.equals(properties2);
        }
        // Create the return value
        return (engineName_equal &&
                simulationName_equal &&
                properties_equal);
    }

    // Property setting methods
    public void SetEngineName(Vector engineName_)
    {
        engineName = engineName_;
        Select(0);
    }

    public void SetSimulationName(Vector simulationName_)
    {
        simulationName = simulationName_;
        Select(1);
    }

    // Property getting methods
    public Vector GetEngineName() { return engineName; }
    public Vector GetSimulationName() { return simulationName; }
    public Vector GetProperties() { return properties; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteStringVector(engineName);
        if(WriteSelect(1, buf))
            buf.WriteStringVector(simulationName);
        if(WriteSelect(2, buf))
        {
            buf.WriteInt(properties.size());
            for(int i = 0; i < properties.size(); ++i)
            {
                EngineProperties tmp = (EngineProperties)properties.elementAt(i);
                tmp.Write(buf);
            }
        }
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetEngineName(buf.ReadStringVector());
            break;
        case 1:
            SetSimulationName(buf.ReadStringVector());
            break;
        case 2:
            {
                int len = buf.ReadInt();
                properties.clear();
                for(int j = 0; j < len; ++j)
                {
                    EngineProperties tmp = new EngineProperties();
                    tmp.Read(buf);
                    properties.addElement(tmp);
                }
            }
            Select(2);
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + stringVectorToString("engineName", engineName, indent) + "\n";
        str = str + stringVectorToString("simulationName", simulationName, indent) + "\n";
        str = str + indent + "properties = {\n";
        for(int i = 0; i < properties.size(); ++i)
        {
            AttributeSubject s = (AttributeSubject)properties.elementAt(i);
            str = str + s.toString(indent + "    ");
            if(i < properties.size()-1)
                str = str + ", ";
            str = str + "\n";
        }
        str = str + "}\n";
        return str;
    }

    // Attributegroup convenience methods
    public void AddProperties(EngineProperties obj)
    {
        properties.addElement(new EngineProperties(obj));
        Select(2);
    }

    public void ClearProperties()
    {
        properties.clear();
        Select(2);
    }

    public void RemoveProperties(int index)
    {
        if(index >= 0 && index < properties.size())
        {
            properties.remove(index);
            Select(2);
        }
    }

    public int GetNumProperties()
    {
        return properties.size();
    }

    public EngineProperties GetProperties(int i)
    {
        EngineProperties tmp = (EngineProperties)properties.elementAt(i);
        return tmp;
    }


    // Attributes
    private Vector engineName; // vector of String objects
    private Vector simulationName; // vector of String objects
    private Vector properties; // vector of EngineProperties objects
}

