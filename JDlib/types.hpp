#ifndef TYPES_HPP
#define TYPES_HPP

#include <dlib/matrix.h>
#include <dlib/svm.h>
#include <vector>

using sample_type = dlib::matrix<double>;
using normalizer_type = dlib::vector_normalizer<sample_type>;
using kernel_type = dlib::radial_basis_kernel<sample_type>;
using decision_funct_type = dlib::decision_function<kernel_type>;
using svm_nu_trainer_type = dlib::svm_nu_trainer<kernel_type>;
using normalized_function_type = dlib::normalized_function<decision_funct_type>;
using probabilistic_funct_type =
  dlib::probabilistic_decision_function<kernel_type>;
using normalized_probabilistic_function_type =
  dlib::normalized_function<probabilistic_funct_type>;
using samples_type = std::vector<sample_type>;
using labels_type = std::vector<double>;

#endif // TYPES_HPP
