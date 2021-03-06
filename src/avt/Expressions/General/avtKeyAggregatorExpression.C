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
//                       avtKeyAggregatorExpression.C                        //
// ************************************************************************* //
#include <avtKeyAggregatorExpression.h>

#include <math.h>

#include <avtParallel.h>

#include <vtkCellData.h>
#include <vtkDataSet.h>
#include <vtkDoubleArray.h>

#include <DebugStream.h>
#include <ExpressionException.h>
#include <Utility.h>

#ifdef PARALLEL
  #include <mpi.h>
#endif

#include <string>
#include <vector>

using std::string;
using std::vector;

// ****************************************************************************
//  Method: avtKeyAggregatorExpression constructor
//
//  Purpose:
//      Defines the constructor.  Note: this should not be inlined in the
//      header because it causes problems for certain compilers.
//
//  Programmer: Cyrus Harrison
//  Creation:   March 26, 2009
//
//
// ****************************************************************************

avtKeyAggregatorExpression::avtKeyAggregatorExpression()
{
    ;
}


// ****************************************************************************
//  Method: avtKeyAggregatorExpression destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Cyrus Harrison
//  Creation:   March 26, 2009
//
// ****************************************************************************

avtKeyAggregatorExpression::~avtKeyAggregatorExpression()
{
    ;
}


// ****************************************************************************
//  Method: avtKeyAggregatorExpression::AddInputVariableName
//
//  Purpose:
//      Override base to support mulitple variables.
//
//  Programmer: Cyrus Harrison
//  Creation:   March 26, 2009
//
// ****************************************************************************

void
avtKeyAggregatorExpression::AddInputVariableName(const char *var)
{
    if (inputVarNames.size() == 0)
        SetActiveVariable(var);
    else
        AddSecondaryVariable(var);
    inputVarNames.push_back(string(var));
}


// ****************************************************************************
//  Method: avtKeyAggregatorExpression::GetVariableDimension
//
//  Purpose:
//      Returns the dimension of the result.
//
//  Programmer: Cyrus Harrison
//  Creation:   March 30, 2009
//
// ****************************************************************************

int
avtKeyAggregatorExpression::GetVariableDimension()
{
    avtDataAttributes &atts = GetInput()->GetInfo().GetAttributes();

    // check for invalid cases 
    if(inputVarNames.size() != 2 || !atts.ValidVariable(inputVarNames[1])) 
        return 1;

    return atts.GetVariableDimension(inputVarNames[1].c_str());
}


// ****************************************************************************
//  Method: avtKeyAggregatorExpression::Execute
//
//  Purpose:
//      Implements aggregation of values based on key variable.
//
//  Programmer: Cyrus Harrison
//  Creation:   March 26, 2009
//
//  Modifications:
//   Cyrus Harrison, Thu Oct 29 10:26:42 PDT 2009
//   Switch to generic use of vtkDataArray to support non integer key types.
//
//   Hank Childs, Sat Sep  4 18:26:29 PDT 2010
//   Fix parallel hang ... if a processor doesn't data, then it didn't finding
//   out the number of components.  This led to an all reduce with array 
//   length 0 ... which MPI automatically bails out on (for those processors)
//   ... and ultimately a hang.
//
// ****************************************************************************
void
avtKeyAggregatorExpression::Execute()
{
    // get input data tree to obtain datasets
    avtDataTree_p tree = GetInputDataTree();
    // holds number of datasets
    int nsets;

    int current_progress = 0;
    int total_steps = 0;

    // get input datasets
    vtkDataSet **data_sets_ptr = tree->GetAllLeaves(nsets);

    vector<vtkDataSet*> data_sets;
    for(int i = 0; i < nsets ; i++)
        data_sets.push_back(data_sets_ptr[i]);

    // set up suitable # of total steps based on the # of input data sets.
    total_steps = nsets * 5;

    // get dataset domain ids
    vector<int> domain_ids;
    tree->GetAllDomainIds(domain_ids);

    // get the variable names of the inputs (there should only be two)
    if(inputVarNames.size() != 2)
    {
        EXCEPTION2(ExpressionException, outputVariableName,
                "The key_aggregate expression requires two arguments:\n"
                " An key array.\n"
                " A floating point values array.\n");
    }

    string key_vname = inputVarNames[0];
    string val_vname = inputVarNames[1];
    debug2 << "avtKeyAggregatorExpression:: "
           << "key name = " << key_vname 
           << " variable name = " << val_vname << endl; 

    // obtain key and value arrays.
    vector<vtkDataArray*> key_arrays(nsets);
    vector<vtkDataArray*> val_arrays(nsets);

    // holds the # of components for each tuple the values arrays.
    int num_val_comps = 0;

    for(int i = 0; i < nsets ; i++)
    {
        vtkDataArray *keys = data_sets[i]->GetCellData()->GetArray(key_vname.c_str());
        vtkDataArray *vals = data_sets[i]->GetCellData()->GetArray(val_vname.c_str());

        if(!keys)
        {
            EXCEPTION2(ExpressionException, outputVariableName,
                "key_aggregate() Invalid key array " + key_vname + ".");
        }

        key_arrays[i] = keys;

        if(!vals)
        {
            EXCEPTION2(ExpressionException, outputVariableName,
                "key_aggregate() Invalid values array " + key_vname +"\n"
                "A float data array is required.");
        }

        if(i == 0)
        {
            num_val_comps = vals->GetNumberOfComponents();
            if(num_val_comps == 0)
            {
                EXCEPTION2(ExpressionException, outputVariableName,
                    "key_aggregate() Invalid values array " + key_vname +"\n"
                    "# of tuple components == 0.");
            }
        }

        if(vals->GetNumberOfComponents() != num_val_comps)
        {
            EXCEPTION2(ExpressionException, outputVariableName,
                "key_aggregate() Invalid values array " + key_vname +"\n"
                    "# of tuple components does not match between datasets.");
        }
        val_arrays[i] = vals;

        // update progress
        current_progress+=nsets;
        UpdateProgress(current_progress,total_steps);
    }

    // find the max keys
    // NOTE: With this implementation we assume the key values are contigious,
    // so we can use the max key value +1 to setup bins to aggregate by key.
    int num_keys = FindMaxKey(key_arrays);
    // update progress
    current_progress+=nsets;
    UpdateProgress(current_progress,total_steps);

#ifdef PARALLEL
    num_keys = UnifyMaximumValue(num_keys);
    num_val_comps = UnifyMaximumValue(num_val_comps);
#endif
    // number of keys is one more than the max key value.
    num_keys++;

    debug2 << "avtKeyAggregatorExpression:: # of keys = " << num_keys << endl;

    vector<double> key_results;
    Aggregate(key_arrays,val_arrays,num_keys,num_val_comps,key_results);

    // update progress
    current_progress+=nsets;
    UpdateProgress(current_progress,total_steps);

#ifdef PARALLEL
    // Sum key'd results across all processors
    // NOTE: even though this code would compile & work fine for the serial 
    // case, it contains an extra copy we don't want to execute.
    int result_len = num_keys*num_val_comps;
    vector<double> sum_results(result_len);
    SumDoubleArrayAcrossAllProcessors(&key_results[0],&sum_results[0],result_len);
    // copy s
    memcpy(&key_results[0],&sum_results[0],result_len * sizeof(double));
#endif 

    // array to hold output sets
    avtDataTree_p *leaves = new avtDataTree_p[nsets];

    // vectors to hold result sets and aggregate value
    vector<vtkDataSet*>  result_sets(nsets);
    vector<vtkDataArray*> result_arrays(nsets);

    // prepare output arrays
    for(int i = 0; i < nsets ; i++)
    {
        // create result array for this data set.
        vtkDoubleArray *res_array = CreateResultArray(key_arrays[i],
                                                     key_results,
                                                     num_val_comps);
        // create a shallow copy of the current data set to add to output
        vtkDataSet *res_set = (vtkDataSet *) data_sets[i]->NewInstance();
        res_set->ShallowCopy(data_sets[i]);

        // add array to dataset
        res_set->GetCellData()->AddArray(res_array);

        // keep pointers to the result set and labels
        result_arrays[i] = res_array;
        result_sets[i]   = res_set;

        if(res_array->GetNumberOfTuples() > 0) // add result as new leaf
            leaves[i] = new avtDataTree(res_set,domain_ids[i]);
        else // if the dataset only contained ghost zones we could end up here
            leaves[i] = NULL;

        // update progress
        UpdateProgress(current_progress++,total_steps);
    }

    if(nsets > 0 )
    {
        // create output data tree
        avtDataTree_p result_tree = new avtDataTree(nsets,leaves);
        // set output data tree
        SetOutputDataTree(result_tree);
    }

    // cleanup leaves array
    delete [] leaves;
    // cleanup data_sets array
    delete [] data_sets_ptr;

    // cleanup result sets
    for(int i = 0; i< nsets; i++)
    {
       // dec ref pointer for each set
       result_sets[i]->Delete();
       // dec ref pointer for each set's label array
       result_arrays[i]->Delete();
    }

    // Set progress to complete
    UpdateProgress(total_steps,total_steps);
}

// ****************************************************************************
//  Method: avtKeyAggregatorExpression::FindMaxKey
//
//  Purpose:
//      Scans input data arrays and finds the maximum integer key value.
//
//  Arguments:
//      key_arrays  Key cell data arrays for the input datasets.
//
//  Returns: Max key id.
//
//  Programmer: Cyrus Harrison
//  Creation:   March 26, 2009
//
//  Modifications:
//   Cyrus Harrison, Thu Oct 29 10:26:42 PDT 2009
//   Switch to generic use of vtkDataArray to support non integer key types.
//
// ****************************************************************************

int
avtKeyAggregatorExpression::FindMaxKey(vector<vtkDataArray*> &key_arrays)
{
    // get the # of data sets we need to scan.
    size_t nsets = key_arrays.size();

    // init our result
    int result = 0;

    // over all data sets
    for(size_t i=0; i < nsets; i++)
    {
        // get the current key array
        vtkDataArray *keys = key_arrays[i];
        // get the number of cells in the current key array
        vtkIdType ncells = keys->GetNumberOfTuples();
        for(vtkIdType j=0; j < ncells; j++)
        {
           // compare current cell's key with max
           int key = (int)keys->GetTuple1(j);
           if(key > result) result = key;
        }
    }
    // return max
    return result;
}


// ****************************************************************************
//  Method: avtKeyAggregatorExpression::Aggregate
//
//  Purpose:
//      Scans input data arrays sums up values per key.
//
//  Programmer: Cyrus Harrison
//  Creation:   March 26, 2009
//
//  Arguments:
//      key_arrays  Key cell data arrays for the input datasets.
//      val_arrays  Value cell data arrays for the input datasets.
//      num_keys    Total number of keys
//      key_results Output array to hold per key aggregate values.
//
//  Modifications:
//   Cyrus Harrison, Thu Oct 29 10:26:42 PDT 2009
//   Switch to generic use of vtkDataArray to support non integer key types.
//
// ****************************************************************************

void
avtKeyAggregatorExpression::Aggregate(vector<vtkDataArray*> &key_arrays,
                                      vector<vtkDataArray*> &val_arrays,
                                      int num_keys,
                                      int num_val_comps,
                                      vector<double> &key_results)
{
    // get the # of data sets we are dealing with.
    size_t nsets = key_arrays.size();

    // prepare key results array
    key_results = vector<double>(num_keys * num_val_comps,0.0);

    // loop over input data sets.
    for(size_t i=0; i < nsets; i++)
    {
        // get the keys & values arrays for the 
        // current data set.
        vtkDataArray *keys = key_arrays[i];
        vtkDataArray *vals = val_arrays[i];

        // get the # of cells to scan
        vtkIdType ncells = keys->GetNumberOfTuples();

        for(vtkIdType j=0; j < ncells; j++)
        {
            // get this cell's key
            int   key = (int)keys->GetTuple1(j);

            // get this cell's values
            double *val_tuple = vals->GetTuple(j);
            double  *res_tuple = &key_results[key * num_val_comps];
            for(int k=0;k < num_val_comps; k++)
                res_tuple[k] += val_tuple[k];
        }
    }
}


// ****************************************************************************
//  Method: avtKeyAggregatorExpression::CreateResultArray
//
//  Purpose:
//      Sets result cell values using aggregate value for the cell's key.
//
//  Programmer: Cyrus Harrison
//  Creation:   March 26, 2009
//
//  Arguments:
//      key_arrays  Key cell data arrays for the input datasets.
//      key_results Per key aggregate values.
//      vals_ncomps Number of components per tuple in the result array.
//
//  Returns: Result data set with values set from key aggregates.
//
//  Modifications:
//   Cyrus Harrison, Thu Oct 29 10:26:42 PDT 2009
//   Switch to generic use of vtkDataArray to support non integer key types.
//
// ****************************************************************************

vtkDoubleArray *
avtKeyAggregatorExpression::CreateResultArray(vtkDataArray  *key_array,
                                              vector<double> &key_results,
                                              int num_val_comps)
{
    // get the # of cells
    vtkIdType ncells = key_array->GetNumberOfTuples();
    // create the result array
    vtkDoubleArray *res_array = vtkDoubleArray::New();
    // set name of the result variable
    res_array->SetName(outputVariableName);
    // set the proper # of components
    res_array->SetNumberOfComponents(num_val_comps);
    // cell data has a tuple for each cell
    res_array->SetNumberOfTuples(ncells);

    // loop over cells.
    for(vtkIdType i=0;i<ncells;i++)
    {
        // get the key for this cell
        int key = (int)key_array->GetTuple1(i);
        // get pointer to tuple data for this key
        double *key_tuple_ptr = &key_results[key * num_val_comps];
        // set its result to the key's aggregate value.
        res_array->SetTupleValue(i,key_tuple_ptr);
    }

    // return result array.
    return res_array;
}


