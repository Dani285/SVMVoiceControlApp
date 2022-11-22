
// dlib SWIG interface
%include "typemaps.i" 
// %include "std_vector.i"

%module jdlib 
%{
  #include "train.hpp"
%}

// Parse the original header file
%include "train.hpp"
// Instantiate some templates

// %template(Vectord) std::vector<double>;
// %template(VectorM) std::vector<jdlib::Matrix>;