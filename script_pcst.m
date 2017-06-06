% Test script for pcst mex function.
% by Dong Gong.
% G(E, V): E={i}_{i=1}^n, V={(i,j)}_{i,j\in E}
%% testing case 1
% for each row in edges: [i, j, cost]
edges = ...
[1 2 3.0;
 2 3 4.0];
% [i, prize]
prizes = ...
[2 5.0;
 3 6.0];
% % testing case 2
% edges = ...
% [1 2 3.0;
%  2 3 4.0];
% % [i, prize]
% prizes = ...
% [1 2;
%  2 5.0;
%  3 6.0];

%%
num_node = max(edges(:)); % n
num_edge = size(edges,1); % |E|
num_nonzero_prize = size(prizes,1); % supp(prize_vector)
%%
% set the root index, 0 means no preferred root setting.
root_idx = 0;
% set for the number of subgraph
target_num_active_clusters= 1; 
%% note:
% All indices for the mex function will be shifted to 0-based numberint, 
% which is also same for the output. 
[out_node_idx, out_edge_idx] = pcst_entry_mex((num_node), (num_edge),...
    int32(edges(:,1)-1), int32(edges(:,2)-1), edges(:,3), num_nonzero_prize, ...
    int32(prizes(:, 1)-1), prizes(:,2), root_idx-1, target_num_active_clusters);
% out_edge_idx+1: shifting index for edges for 1-baesd numbering.
out_node_list = out_node_idx +1;
out_edge_idx = out_edge_idx+1;
%% display results
out_edge_list = edges(out_edge_idx, 1:2);
fprintf('output:\n')
fprintf('node indices:\n')
disp(out_node_list);
fprintf('edge indices:\n')
disp(out_edge_list);

