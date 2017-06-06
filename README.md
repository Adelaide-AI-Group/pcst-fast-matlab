# pcst-fast-matlab

+ *pcst-fast-matlab* contains a MATLAB mex interface to [pcs-fast](https://github.com/ludwigschmidt/pcst-fast).

+ *pcst-fast* is a fast approximation algorithm for the PCST/F (prize collecting Steiner tree/forest) problem, which can be used in the problem inducing structured sparsity. The original project is implemented in C++. I write a MATLAB MEX file based interface for using it in my MATLAB based academic project (which will be released later). 

# Usage

Run `make_mexfiles;` in MATLAB console to produce *.mex** files.

You can solve PCST/F problem by calling `[~,~] = pcst_entry_mex(...);` in your MATLAB code.

Several testing cases in *test_script.m* will help to learn how to use `pcst_entry_mex()`.

In *pcst_entry_mex.cc* and *script_pcst.m*, you can find detailed comments about the function interface and meaning of the variables.

# Note

+ The main contribution of this project is on the MATLAB MEX interface, including *pcst_entry_mex.cc* and *script_pcst.m*

+ Please check the original [project page](https://github.com/ludwigschmidt/pcst-fast) for more information, including the algorithm details, related academic papers and the license info.

# Related Papers and Projects

To be updated...
