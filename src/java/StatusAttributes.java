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

import java.lang.Byte;
import java.util.Vector;

// ****************************************************************************
// Class: StatusAttributes
//
// Purpose:
//    This class contains the status that is displayed in the GUI's status bar.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class StatusAttributes extends AttributeSubject
{
    private static int StatusAttributes_numAdditionalAtts = 11;

    // Constants
    public final static int DEFAULT_DURATION = 5000;


    public StatusAttributes()
    {
        super(StatusAttributes_numAdditionalAtts);

        sender = new String("viewer");
        clearStatus = false;
        statusMessage = new String("");
        unicode = new Vector();
        hasUnicode = false;
        percent = 0;
        currentStage = 1;
        currentStageName = new String("stage1");
        maxStage = 1;
        messageType = 0;
        duration = 5000;
    }

    public StatusAttributes(int nMoreFields)
    {
        super(StatusAttributes_numAdditionalAtts + nMoreFields);

        sender = new String("viewer");
        clearStatus = false;
        statusMessage = new String("");
        unicode = new Vector();
        hasUnicode = false;
        percent = 0;
        currentStage = 1;
        currentStageName = new String("stage1");
        maxStage = 1;
        messageType = 0;
        duration = 5000;
    }

    public StatusAttributes(StatusAttributes obj)
    {
        super(StatusAttributes_numAdditionalAtts);

        int i;

        sender = new String(obj.sender);
        clearStatus = obj.clearStatus;
        statusMessage = new String(obj.statusMessage);
        unicode = new Vector(obj.unicode.size());
        for(i = 0; i < obj.unicode.size(); ++i)
        {
            Byte bv = (Byte)obj.unicode.elementAt(i);
            unicode.addElement(new Byte(bv.byteValue()));
        }

        hasUnicode = obj.hasUnicode;
        percent = obj.percent;
        currentStage = obj.currentStage;
        currentStageName = new String(obj.currentStageName);
        maxStage = obj.maxStage;
        messageType = obj.messageType;
        duration = obj.duration;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return StatusAttributes_numAdditionalAtts;
    }

    public boolean equals(StatusAttributes obj)
    {
        int i;

        // Compare the elements in the unicode vector.
        boolean unicode_equal = (obj.unicode.size() == unicode.size());
        for(i = 0; (i < unicode.size()) && unicode_equal; ++i)
        {
            // Make references to Byte from Object.
            Byte unicode1 = (Byte)unicode.elementAt(i);
            Byte unicode2 = (Byte)obj.unicode.elementAt(i);
            unicode_equal = unicode1.equals(unicode2);
        }
        // Create the return value
        return ((sender.equals(obj.sender)) &&
                (clearStatus == obj.clearStatus) &&
                (statusMessage.equals(obj.statusMessage)) &&
                unicode_equal &&
                (hasUnicode == obj.hasUnicode) &&
                (percent == obj.percent) &&
                (currentStage == obj.currentStage) &&
                (currentStageName.equals(obj.currentStageName)) &&
                (maxStage == obj.maxStage) &&
                (messageType == obj.messageType) &&
                (duration == obj.duration));
    }

    // Property setting methods
    public void SetSender(String sender_)
    {
        sender = sender_;
        Select(0);
    }

    public void SetClearStatus(boolean clearStatus_)
    {
        clearStatus = clearStatus_;
        Select(1);
    }

    public void SetStatusMessage(String statusMessage_)
    {
        statusMessage = statusMessage_;
        Select(2);
    }

    public void SetUnicode(Vector unicode_)
    {
        unicode = unicode_;
        Select(3);
    }

    public void SetHasUnicode(boolean hasUnicode_)
    {
        hasUnicode = hasUnicode_;
        Select(4);
    }

    public void SetPercent(int percent_)
    {
        percent = percent_;
        Select(5);
    }

    public void SetCurrentStage(int currentStage_)
    {
        currentStage = currentStage_;
        Select(6);
    }

    public void SetCurrentStageName(String currentStageName_)
    {
        currentStageName = currentStageName_;
        Select(7);
    }

    public void SetMaxStage(int maxStage_)
    {
        maxStage = maxStage_;
        Select(8);
    }

    public void SetMessageType(int messageType_)
    {
        messageType = messageType_;
        Select(9);
    }

    public void SetDuration(int duration_)
    {
        duration = duration_;
        Select(10);
    }

    // Property getting methods
    public String  GetSender() { return sender; }
    public boolean GetClearStatus() { return clearStatus; }
    public String  GetStatusMessage() { return statusMessage; }
    public Vector  GetUnicode() { return unicode; }
    public boolean GetHasUnicode() { return hasUnicode; }
    public int     GetPercent() { return percent; }
    public int     GetCurrentStage() { return currentStage; }
    public String  GetCurrentStageName() { return currentStageName; }
    public int     GetMaxStage() { return maxStage; }
    public int     GetMessageType() { return messageType; }
    public int     GetDuration() { return duration; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteString(sender);
        if(WriteSelect(1, buf))
            buf.WriteBool(clearStatus);
        if(WriteSelect(2, buf))
            buf.WriteString(statusMessage);
        if(WriteSelect(3, buf))
            buf.WriteByteVector(unicode);
        if(WriteSelect(4, buf))
            buf.WriteBool(hasUnicode);
        if(WriteSelect(5, buf))
            buf.WriteInt(percent);
        if(WriteSelect(6, buf))
            buf.WriteInt(currentStage);
        if(WriteSelect(7, buf))
            buf.WriteString(currentStageName);
        if(WriteSelect(8, buf))
            buf.WriteInt(maxStage);
        if(WriteSelect(9, buf))
            buf.WriteInt(messageType);
        if(WriteSelect(10, buf))
            buf.WriteInt(duration);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetSender(buf.ReadString());
            break;
        case 1:
            SetClearStatus(buf.ReadBool());
            break;
        case 2:
            SetStatusMessage(buf.ReadString());
            break;
        case 3:
            SetUnicode(buf.ReadByteVector());
            break;
        case 4:
            SetHasUnicode(buf.ReadBool());
            break;
        case 5:
            SetPercent(buf.ReadInt());
            break;
        case 6:
            SetCurrentStage(buf.ReadInt());
            break;
        case 7:
            SetCurrentStageName(buf.ReadString());
            break;
        case 8:
            SetMaxStage(buf.ReadInt());
            break;
        case 9:
            SetMessageType(buf.ReadInt());
            break;
        case 10:
            SetDuration(buf.ReadInt());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + stringToString("sender", sender, indent) + "\n";
        str = str + boolToString("clearStatus", clearStatus, indent) + "\n";
        str = str + stringToString("statusMessage", statusMessage, indent) + "\n";
        str = str + ucharVectorToString("unicode", unicode, indent) + "\n";
        str = str + boolToString("hasUnicode", hasUnicode, indent) + "\n";
        str = str + intToString("percent", percent, indent) + "\n";
        str = str + intToString("currentStage", currentStage, indent) + "\n";
        str = str + stringToString("currentStageName", currentStageName, indent) + "\n";
        str = str + intToString("maxStage", maxStage, indent) + "\n";
        str = str + intToString("messageType", messageType, indent) + "\n";
        str = str + intToString("duration", duration, indent) + "\n";
        return str;
    }


    // Attributes
    private String  sender;
    private boolean clearStatus;
    private String  statusMessage;
    private Vector  unicode; // vector of Byte objects
    private boolean hasUnicode;
    private int     percent;
    private int     currentStage;
    private String  currentStageName;
    private int     maxStage;
    private int     messageType;
    private int     duration;
}

