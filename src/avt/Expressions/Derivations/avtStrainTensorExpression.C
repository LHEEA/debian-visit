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
//                       avtStrainTensorExpression.C                         //
// ************************************************************************* //

#include <avtStrainTensorExpression.h>

#include <vtkDataArray.h>

#include <ExpressionException.h>

// ****************************************************************************
//  Method: avtStrainTensorExpression constructor
//
//  Programmer: Thomas R. Treadway
//  Creation:   Tue Nov 14 12:59:38 PST 2006
//
// ****************************************************************************

avtStrainTensorExpression::avtStrainTensorExpression()
{
    ;
}

// ****************************************************************************
//  Method: avtStrainTensorExpression destructor
//
//  Programmer: Thomas R. Treadway
//  Creation:   Tue Nov 14 12:59:38 PST 2006
//
// ****************************************************************************

avtStrainTensorExpression::~avtStrainTensorExpression()
{
    ;
}

// ****************************************************************************
//  Method: avtStrainTensorExpression::HexPartialDerivative
//
//  Purpose:
//      Computes the the partial derivative of the 8 brick shape
//      functions with respect to each coordinate axis.  The
//      coordinates of the brick are passed in "coorX,Y,Z", and
//      the partial derivatives are returned in "dNx,y,z".
//
//  Programmer: Thomas R. Treadway
//  Creation:   Tue Nov 14 12:59:38 PST 2006
//
// ****************************************************************************

void
avtStrainTensorExpression::HexPartialDerivative
    (double dNx[8], double dNy[8], double dNz[8],
    double coorX[8], double coorY[8], double coorZ[8])
{   // copied from Griz
//  Local shape function derivatives evaluated at node points.
    static double dN1[8] = { -.125, -.125, .125, .125,
                            -.125, -.125, .125, .125 };
    static double dN2[8] = { -.125, -.125, -.125, -.125,
                            .125, .125, .125, .125 };
    static double dN3[8] = { -.125, .125, .125, -.125,
                            -.125, .125, .125, -.125};
    double jacob[9], invJacob[9], detJacob;

    for (int k = 0; k < 9; k++)
       jacob[k] = 0.;
    for (int k = 0; k < 8; k++ )
    {   
        jacob[0] += dN1[k]*coorX[k];
        jacob[1] += dN1[k]*coorY[k];
        jacob[2] += dN1[k]*coorZ[k];
        jacob[3] += dN2[k]*coorX[k];
        jacob[4] += dN2[k]*coorY[k];
        jacob[5] += dN2[k]*coorZ[k];
        jacob[6] += dN3[k]*coorX[k];
        jacob[7] += dN3[k]*coorY[k];
        jacob[8] += dN3[k]*coorZ[k];
    }  
    detJacob =   jacob[0]*jacob[4]*jacob[8] + jacob[1]*jacob[5]*jacob[6]
               + jacob[2]*jacob[3]*jacob[7] - jacob[2]*jacob[4]*jacob[6] 
               - jacob[1]*jacob[3]*jacob[8] - jacob[0]*jacob[5]*jacob[7];
    
    if ( fabs( detJacob ) < 1.0e-20 )
    {   
        EXCEPTION2(ExpressionException, outputVariableName,
                "HexPartialDerivative, Element is degenerate! Result is invalid!");
    }
    
    /* Develop inverse of mapping. */                         
    detJacob = 1.0 / detJacob;                                
                                                              
    /* Cofactors of the jacobian matrix. */                   
    invJacob[0] = detJacob * (  jacob[4]*jacob[8] - jacob[5]*jacob[7] );    
    invJacob[1] = detJacob * ( -jacob[1]*jacob[8] + jacob[2]*jacob[7] );    
    invJacob[2] = detJacob * (  jacob[1]*jacob[5] - jacob[2]*jacob[4] );    
    invJacob[3] = detJacob * ( -jacob[3]*jacob[8] + jacob[5]*jacob[6] );    
    invJacob[4] = detJacob * (  jacob[0]*jacob[8] - jacob[2]*jacob[6] );    
    invJacob[5] = detJacob * ( -jacob[0]*jacob[5] + jacob[2]*jacob[3] );    
    invJacob[6] = detJacob * (  jacob[3]*jacob[7] - jacob[4]*jacob[6] );    
    invJacob[7] = detJacob * ( -jacob[0]*jacob[7] + jacob[1]*jacob[6] );    
    invJacob[8] = detJacob * (  jacob[0]*jacob[4] - jacob[1]*jacob[3] );    
                                                              
    /* Partials dN(k)/dx, dN(k)/dy, dN(k)/dz. */              
    for (int k = 0; k < 8; k++ )                                 
    {                                                         
        dNx[k] = invJacob[0]*dN1[k] + invJacob[1]*dN2[k] + invJacob[2]*dN3[k];
        dNy[k] = invJacob[3]*dN1[k] + invJacob[4]*dN2[k] + invJacob[5]*dN3[k];
        dNz[k] = invJacob[6]*dN1[k] + invJacob[7]*dN2[k] + invJacob[8]*dN3[k];
    }
}
