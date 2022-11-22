#include "train.hpp"

double jdlib::MaximumNu(std::vector<double> labels)
{
  return dlib::maximum_nu(labels);
}

void jdlib::RandomizeSamples(std::vector<sample_type> &samples, std::vector<double> &labels)
{
  dlib::randomize_samples(samples, labels);
}
