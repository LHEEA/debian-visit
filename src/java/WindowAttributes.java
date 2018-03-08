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


// ****************************************************************************
// Class: WindowAttributes
//
// Purpose:
//    This class contains the attributes for a visualization window.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class WindowAttributes extends AttributeSubject
{
    private static int WindowAttributes_numAdditionalAtts = 17;

    public WindowAttributes()
    {
        super(WindowAttributes_numAdditionalAtts);

        viewCurve = new ViewCurveAttributes();
        view2D = new View2DAttributes();
        view3D = new View3DAttributes();
        viewAxisArray = new ViewAxisArrayAttributes();
        lights = new LightList();
        renderAtts = new RenderingAttributes();
        colorTables = new ColorTableAttributes();
        size = new int[2];
        size[0] = 300;
        size[1] = 300;
        background = new byte[3];
        background[0] = (byte)255;
        background[1] = (byte)255;
        background[2] = (byte)255;
        foreground = new byte[3];
        foreground[0] = (byte)0;
        foreground[1] = (byte)0;
        foreground[2] = (byte)0;
        backgroundMode = 0;
        gradBG1 = new double[3];
        gradBG1[0] = 0;
        gradBG1[1] = 0;
        gradBG1[2] = 1;
        gradBG2 = new double[3];
        gradBG2[0] = 0;
        gradBG2[1] = 0;
        gradBG2[2] = 0;
        gradientBackgroundStyle = 0;
        backgroundImage = new String("");
        imageRepeatX = 1;
        imageRepeatY = 1;
    }

    public WindowAttributes(int nMoreFields)
    {
        super(WindowAttributes_numAdditionalAtts + nMoreFields);

        viewCurve = new ViewCurveAttributes();
        view2D = new View2DAttributes();
        view3D = new View3DAttributes();
        viewAxisArray = new ViewAxisArrayAttributes();
        lights = new LightList();
        renderAtts = new RenderingAttributes();
        colorTables = new ColorTableAttributes();
        size = new int[2];
        size[0] = 300;
        size[1] = 300;
        background = new byte[3];
        background[0] = (byte)255;
        background[1] = (byte)255;
        background[2] = (byte)255;
        foreground = new byte[3];
        foreground[0] = (byte)0;
        foreground[1] = (byte)0;
        foreground[2] = (byte)0;
        backgroundMode = 0;
        gradBG1 = new double[3];
        gradBG1[0] = 0;
        gradBG1[1] = 0;
        gradBG1[2] = 1;
        gradBG2 = new double[3];
        gradBG2[0] = 0;
        gradBG2[1] = 0;
        gradBG2[2] = 0;
        gradientBackgroundStyle = 0;
        backgroundImage = new String("");
        imageRepeatX = 1;
        imageRepeatY = 1;
    }

    public WindowAttributes(WindowAttributes obj)
    {
        super(obj);

        int i;

        viewCurve = new ViewCurveAttributes(obj.viewCurve);
        view2D = new View2DAttributes(obj.view2D);
        view3D = new View3DAttributes(obj.view3D);
        viewAxisArray = new ViewAxisArrayAttributes(obj.viewAxisArray);
        lights = new LightList(obj.lights);
        renderAtts = new RenderingAttributes(obj.renderAtts);
        colorTables = new ColorTableAttributes(obj.colorTables);
        size = new int[2];
        size[0] = obj.size[0];
        size[1] = obj.size[1];

        background = new byte[3];
        background[0] = obj.background[0];
        background[1] = obj.background[1];
        background[2] = obj.background[2];

        foreground = new byte[3];
        foreground[0] = obj.foreground[0];
        foreground[1] = obj.foreground[1];
        foreground[2] = obj.foreground[2];

        backgroundMode = obj.backgroundMode;
        gradBG1 = new double[3];
        gradBG1[0] = obj.gradBG1[0];
        gradBG1[1] = obj.gradBG1[1];
        gradBG1[2] = obj.gradBG1[2];

        gradBG2 = new double[3];
        gradBG2[0] = obj.gradBG2[0];
        gradBG2[1] = obj.gradBG2[1];
        gradBG2[2] = obj.gradBG2[2];

        gradientBackgroundStyle = obj.gradientBackgroundStyle;
        backgroundImage = new String(obj.backgroundImage);
        imageRepeatX = obj.imageRepeatX;
        imageRepeatY = obj.imageRepeatY;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return WindowAttributes_numAdditionalAtts;
    }

    public boolean equals(WindowAttributes obj)
    {
        int i;

        // Compare the size arrays.
        boolean size_equal = true;
        for(i = 0; i < 2 && size_equal; ++i)
            size_equal = (size[i] == obj.size[i]);

        // Compare the background arrays.
        boolean background_equal = true;
        for(i = 0; i < 3 && background_equal; ++i)
            background_equal = (background[i] == obj.background[i]);

        // Compare the foreground arrays.
        boolean foreground_equal = true;
        for(i = 0; i < 3 && foreground_equal; ++i)
            foreground_equal = (foreground[i] == obj.foreground[i]);

        // Compare the gradBG1 arrays.
        boolean gradBG1_equal = true;
        for(i = 0; i < 3 && gradBG1_equal; ++i)
            gradBG1_equal = (gradBG1[i] == obj.gradBG1[i]);

        // Compare the gradBG2 arrays.
        boolean gradBG2_equal = true;
        for(i = 0; i < 3 && gradBG2_equal; ++i)
            gradBG2_equal = (gradBG2[i] == obj.gradBG2[i]);

        // Create the return value
        return ((viewCurve.equals(obj.viewCurve)) &&
                (view2D.equals(obj.view2D)) &&
                (view3D.equals(obj.view3D)) &&
                (viewAxisArray.equals(obj.viewAxisArray)) &&
                (lights.equals(obj.lights)) &&
                (renderAtts.equals(obj.renderAtts)) &&
                (colorTables.equals(obj.colorTables)) &&
                size_equal &&
                background_equal &&
                foreground_equal &&
                (backgroundMode == obj.backgroundMode) &&
                gradBG1_equal &&
                gradBG2_equal &&
                (gradientBackgroundStyle == obj.gradientBackgroundStyle) &&
                (backgroundImage.equals(obj.backgroundImage)) &&
                (imageRepeatX == obj.imageRepeatX) &&
                (imageRepeatY == obj.imageRepeatY));
    }

    // Property setting methods
    public void SetViewCurve(ViewCurveAttributes viewCurve_)
    {
        viewCurve = viewCurve_;
        Select(0);
    }

    public void SetView2D(View2DAttributes view2D_)
    {
        view2D = view2D_;
        Select(1);
    }

    public void SetView3D(View3DAttributes view3D_)
    {
        view3D = view3D_;
        Select(2);
    }

    public void SetViewAxisArray(ViewAxisArrayAttributes viewAxisArray_)
    {
        viewAxisArray = viewAxisArray_;
        Select(3);
    }

    public void SetLights(LightList lights_)
    {
        lights = lights_;
        Select(4);
    }

    public void SetRenderAtts(RenderingAttributes renderAtts_)
    {
        renderAtts = renderAtts_;
        Select(5);
    }

    public void SetColorTables(ColorTableAttributes colorTables_)
    {
        colorTables = colorTables_;
        Select(6);
    }

    public void SetSize(int[] size_)
    {
        size[0] = size_[0];
        size[1] = size_[1];
        Select(7);
    }

    public void SetSize(int e0, int e1)
    {
        size[0] = e0;
        size[1] = e1;
        Select(7);
    }

    public void SetBackground(byte[] background_)
    {
        background[0] = background_[0];
        background[1] = background_[1];
        background[2] = background_[2];
        Select(8);
    }

    public void SetBackground(byte e0, byte e1, byte e2)
    {
        background[0] = e0;
        background[1] = e1;
        background[2] = e2;
        Select(8);
    }

    public void SetForeground(byte[] foreground_)
    {
        foreground[0] = foreground_[0];
        foreground[1] = foreground_[1];
        foreground[2] = foreground_[2];
        Select(9);
    }

    public void SetForeground(byte e0, byte e1, byte e2)
    {
        foreground[0] = e0;
        foreground[1] = e1;
        foreground[2] = e2;
        Select(9);
    }

    public void SetBackgroundMode(int backgroundMode_)
    {
        backgroundMode = backgroundMode_;
        Select(10);
    }

    public void SetGradBG1(double[] gradBG1_)
    {
        gradBG1[0] = gradBG1_[0];
        gradBG1[1] = gradBG1_[1];
        gradBG1[2] = gradBG1_[2];
        Select(11);
    }

    public void SetGradBG1(double e0, double e1, double e2)
    {
        gradBG1[0] = e0;
        gradBG1[1] = e1;
        gradBG1[2] = e2;
        Select(11);
    }

    public void SetGradBG2(double[] gradBG2_)
    {
        gradBG2[0] = gradBG2_[0];
        gradBG2[1] = gradBG2_[1];
        gradBG2[2] = gradBG2_[2];
        Select(12);
    }

    public void SetGradBG2(double e0, double e1, double e2)
    {
        gradBG2[0] = e0;
        gradBG2[1] = e1;
        gradBG2[2] = e2;
        Select(12);
    }

    public void SetGradientBackgroundStyle(int gradientBackgroundStyle_)
    {
        gradientBackgroundStyle = gradientBackgroundStyle_;
        Select(13);
    }

    public void SetBackgroundImage(String backgroundImage_)
    {
        backgroundImage = backgroundImage_;
        Select(14);
    }

    public void SetImageRepeatX(int imageRepeatX_)
    {
        imageRepeatX = imageRepeatX_;
        Select(15);
    }

    public void SetImageRepeatY(int imageRepeatY_)
    {
        imageRepeatY = imageRepeatY_;
        Select(16);
    }

    // Property getting methods
    public ViewCurveAttributes     GetViewCurve() { return viewCurve; }
    public View2DAttributes        GetView2D() { return view2D; }
    public View3DAttributes        GetView3D() { return view3D; }
    public ViewAxisArrayAttributes GetViewAxisArray() { return viewAxisArray; }
    public LightList               GetLights() { return lights; }
    public RenderingAttributes     GetRenderAtts() { return renderAtts; }
    public ColorTableAttributes    GetColorTables() { return colorTables; }
    public int[]                   GetSize() { return size; }
    public byte[]                  GetBackground() { return background; }
    public byte[]                  GetForeground() { return foreground; }
    public int                     GetBackgroundMode() { return backgroundMode; }
    public double[]                GetGradBG1() { return gradBG1; }
    public double[]                GetGradBG2() { return gradBG2; }
    public int                     GetGradientBackgroundStyle() { return gradientBackgroundStyle; }
    public String                  GetBackgroundImage() { return backgroundImage; }
    public int                     GetImageRepeatX() { return imageRepeatX; }
    public int                     GetImageRepeatY() { return imageRepeatY; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            viewCurve.Write(buf);
        if(WriteSelect(1, buf))
            view2D.Write(buf);
        if(WriteSelect(2, buf))
            view3D.Write(buf);
        if(WriteSelect(3, buf))
            viewAxisArray.Write(buf);
        if(WriteSelect(4, buf))
            lights.Write(buf);
        if(WriteSelect(5, buf))
            renderAtts.Write(buf);
        if(WriteSelect(6, buf))
            colorTables.Write(buf);
        if(WriteSelect(7, buf))
            buf.WriteIntArray(size);
        if(WriteSelect(8, buf))
            buf.WriteByteArray(background, true);
        if(WriteSelect(9, buf))
            buf.WriteByteArray(foreground, true);
        if(WriteSelect(10, buf))
            buf.WriteInt(backgroundMode);
        if(WriteSelect(11, buf))
            buf.WriteDoubleArray(gradBG1);
        if(WriteSelect(12, buf))
            buf.WriteDoubleArray(gradBG2);
        if(WriteSelect(13, buf))
            buf.WriteInt(gradientBackgroundStyle);
        if(WriteSelect(14, buf))
            buf.WriteString(backgroundImage);
        if(WriteSelect(15, buf))
            buf.WriteInt(imageRepeatX);
        if(WriteSelect(16, buf))
            buf.WriteInt(imageRepeatY);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            viewCurve.Read(buf);
            Select(0);
            break;
        case 1:
            view2D.Read(buf);
            Select(1);
            break;
        case 2:
            view3D.Read(buf);
            Select(2);
            break;
        case 3:
            viewAxisArray.Read(buf);
            Select(3);
            break;
        case 4:
            lights.Read(buf);
            Select(4);
            break;
        case 5:
            renderAtts.Read(buf);
            Select(5);
            break;
        case 6:
            colorTables.Read(buf);
            Select(6);
            break;
        case 7:
            SetSize(buf.ReadIntArray());
            break;
        case 8:
            SetBackground(buf.ReadByteArray());
            break;
        case 9:
            SetForeground(buf.ReadByteArray());
            break;
        case 10:
            SetBackgroundMode(buf.ReadInt());
            break;
        case 11:
            SetGradBG1(buf.ReadDoubleArray());
            break;
        case 12:
            SetGradBG2(buf.ReadDoubleArray());
            break;
        case 13:
            SetGradientBackgroundStyle(buf.ReadInt());
            break;
        case 14:
            SetBackgroundImage(buf.ReadString());
            break;
        case 15:
            SetImageRepeatX(buf.ReadInt());
            break;
        case 16:
            SetImageRepeatY(buf.ReadInt());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "viewCurve = {\n" + viewCurve.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "view2D = {\n" + view2D.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "view3D = {\n" + view3D.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "viewAxisArray = {\n" + viewAxisArray.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "lights = {\n" + lights.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "renderAtts = {\n" + renderAtts.toString(indent + "    ") + indent + "}\n";
        str = str + indent + "colorTables = {\n" + colorTables.toString(indent + "    ") + indent + "}\n";
        str = str + intArrayToString("size", size, indent) + "\n";
        str = str + ucharArrayToString("background", background, indent) + "\n";
        str = str + ucharArrayToString("foreground", foreground, indent) + "\n";
        str = str + intToString("backgroundMode", backgroundMode, indent) + "\n";
        str = str + doubleArrayToString("gradBG1", gradBG1, indent) + "\n";
        str = str + doubleArrayToString("gradBG2", gradBG2, indent) + "\n";
        str = str + intToString("gradientBackgroundStyle", gradientBackgroundStyle, indent) + "\n";
        str = str + stringToString("backgroundImage", backgroundImage, indent) + "\n";
        str = str + intToString("imageRepeatX", imageRepeatX, indent) + "\n";
        str = str + intToString("imageRepeatY", imageRepeatY, indent) + "\n";
        return str;
    }


    // Attributes
    private ViewCurveAttributes     viewCurve;
    private View2DAttributes        view2D;
    private View3DAttributes        view3D;
    private ViewAxisArrayAttributes viewAxisArray;
    private LightList               lights;
    private RenderingAttributes     renderAtts;
    private ColorTableAttributes    colorTables;
    private int[]                   size;
    private byte[]                  background;
    private byte[]                  foreground;
    private int                     backgroundMode;
    private double[]                gradBG1;
    private double[]                gradBG2;
    private int                     gradientBackgroundStyle;
    private String                  backgroundImage;
    private int                     imageRepeatX;
    private int                     imageRepeatY;
}

