/*************************
* MATLAB mex file for pcst.
* by Dong Gong, edgong01@gmail.com, 2016.09.18
*************************/
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdio>
#include <functional>
#include <iostream>
#include <locale>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <unistd.h>
#include "pcst_fast.h"

#include "mex.h"
using namespace std;
using cluster_approx::PCSTFast;

void output_function(const char* msg);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) 
{
/*	
	parameters list:
	0: number of nodes; (int)
	1: number of edges; (int)
	2: edge_1 list; (int list)
	3: edge_2 list; (int list)
	4: cost list (for edges); (double list)
  5: number of nonzero prize; (int)
  6: prize indices (for nodes); (int list)
	7: prize list (for nodes); (double list)
  8: root idx; (int)
  9: target_num_active_clusters; 
  -- All indices are in zero-based numbering. 
*/

  	// manage input
  	int num_node, num_edge, *edge_1_list, *edge_2_list, num_nonzero_prize, *prize_idx_list, root_idx;
  	double *cost_list, *prize_list;  	
  	num_node = (int)(*(double*)mxGetPr(prhs[0]));
  	num_edge = (int)(*(double*)mxGetPr(prhs[1]));
  	edge_1_list = (int*)mxGetPr(prhs[2]); 
  	edge_2_list = (int*)mxGetPr(prhs[3]); 
  	cost_list = (double*)mxGetPr(prhs[4]);
    num_nonzero_prize = (int)(*(double*)mxGetPr(prhs[5]));
    prize_idx_list = (int*)mxGetPr(prhs[6]);
  	prize_list= (double*)mxGetPr(prhs[7]);
  	root_idx = (int)(*(double*)mxGetPr(prhs[8]));

  	
  	// input for c++ code
  	vector<pair<int, int>> edges;
  	vector<double> prizes;
  	vector<double> costs;
//  	int root = -1;//PCSTFast::kNoRoot;
    int root;
  	vector<int> result_nodes;
  	vector<int> result_edges;

  	// adapt the inputs
  	edges.resize(num_edge);
  	costs.resize(num_edge);
  	for (int i = 0; i < num_edge; ++i)
  	{
  		edges[i].first = edge_1_list[i];
  		edges[i].second = edge_2_list[i];
  		costs[i] = cost_list[i];
  	}
  	prizes.resize(num_node, 0.0);
  	for (int i = 0; i < num_nonzero_prize; ++i)
  	{
  		prizes[prize_idx_list[i]] = prize_list[i];
  	}
    root = root_idx;

    // set the number of subgraphs.
    int target_num_active_clusters;
    target_num_active_clusters = (int)(*(double*)mxGetPr(prhs[9]));
//    if(root > PCSTFast::kNoRoot)
    if(root != PCSTFast::kNoRoot)
    {
      target_num_active_clusters = 0;
    }
    
//    target_num_active_clusters = (root == PCSTFast::kNoRoot ? 1 : 0); // must be
  	// processing
  	PCSTFast algo(edges,
                  prizes,
                  costs,
                  root,
                  target_num_active_clusters,
                  PCSTFast::kStrongPruning,
                  0,
                  output_function);
	algo.run(&result_nodes, &result_edges);


	// manage out
  double *out_node_list, *out_edge_list;
	int num_result_node, num_result_edge;
	num_result_node = static_cast<int>(result_nodes.size());
	num_result_edge = static_cast<int>(result_edges.size());

//	plhs[0] = mxCreateNumericArray(num_result_node,1,mxINT16_CLASS,mxREAL); 
  plhs[0] = mxCreateDoubleMatrix(num_result_node,1,mxREAL); 
	out_node_list = (double*)mxGetPr(plhs[0]);
	for (int i = 0; i < num_result_node; ++i)
	{
		out_node_list[i] = static_cast<double>(result_nodes[i]);
	}
  plhs[1] = mxCreateDoubleMatrix(num_result_edge,1,mxREAL); 
	out_node_list = (double*)mxGetPr(plhs[1]);
	for (int i = 0; i < num_result_edge; ++i)
	{
		out_node_list[i] = static_cast<double>(result_edges[i]);
	}


}


void output_function(const char* msg) {
  fprintf(stderr, msg);
}