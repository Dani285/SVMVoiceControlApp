#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <dlib/matrix.h>
#include <dlib/memory_manager.h>
#include <dlib/svm.h>

namespace jdlib {

template<class T0>
class Vector
{
public:
  using mem_manager_type = typename dlib::memory_manager<Vector<T0>>::kernel_1d;
  using type = T0;

public:
  Vector() = default;

  std::vector<T0> _data;

  void Add(const T0& value) { _data.push_back(value); }

  int64_t Size() { return _data.size(); }

  const T0& Get(int64_t index) const { return _data.at(index); }
};

class Vectord : public Vector<double>
{};

class Matrix
{
public:
  using mem_manager_type = dlib::memory_manager<Matrix>::kernel_1d;
  using type = double;

  const long NR = dlib::matrix<double>::NR; //< Dynamic Matrices
  const long NC = dlib::matrix<double>::NC; //< Dynamic Matrices

private:
  dlib::matrix<double> _data;

public:
  Matrix() = default;

  Matrix(const dlib::matrix<double>& _data)
    : _data(_data)
  {}

  Matrix(int row, int col)
    : _data(row, col)
  {}

  void set(int row, int col, double val) { _data(row, col) = val; }

  double get(int row, int col) { return _data(row, col); }

  const dlib::matrix<double>& data() const { return _data; }
};

class VectorM : public Vector<Matrix>
{};

// using sample_type = dlib::matrix<double>;
// using kernel_type = dlib::radial_basis_kernel<sample_type>;
// using dec_funct_type = dlib::decision_function<kernel_type>;
// using funct_type = dlib::normalized_function<dec_funct_type>;

class VectorNormalizer
{
private:
  dlib::vector_normalizer<Matrix> _normalizer;

public:
  void Train(const VectorM& samples) { _normalizer.train(samples); }

  Matrix Normalize(const Matrix& sample) const { return _normalizer(sample); }
};

void
RandomizeSamples(VectorM& samples, Vectord& labels)
{
  dlib::randomize_samples(samples, labels);
}

double
MaximumNu(const Vectord& labels)
{
  return dlib::maximum_nu(labels);
}

class RBF
{
public:
  using scalar_type = double;
  using sample_type = Matrix;
  using mem_manager_type = dlib::memory_manager<RBF>::kernel_1d;

private:
  dlib::radial_basis_kernel<Matrix> _kernel;

public:
  RBF() = default;

  RBF(double gamma)
    : _kernel(gamma)
  {}
};

class SVMNuTrainer
{
public:
  using mem_manager_type = dlib::memory_manager<SVMNuTrainer>::kernel_1d;
  using kernel_type = RBF;
  using scalar_type = double;
  using sample_type = Matrix;
  using trained_function_type = dlib::decision_function<kernel_type>;

private:
  dlib::svm_nu_trainer<kernel_type> _trainer;

public:
  void SetKernel(RBF Kernel) { _trainer.set_kernel(Kernel); }

  void SetNu(double nu) { _trainer.set_nu(nu); }

  void Train(const std::vector<Matrix>& samples,
             const std::vector<double>& labels)
  {
    _trainer.train(samples, labels);
  }
};

Matrix
CrossValidateTrainer(SVMNuTrainer trainer,
                     VectorM samples,
                     Vectord labels,
                     long fold)
{
  return Matrix(dlib::cross_validate_trainer(trainer, samples, labels, fold));
}

class LearnedFunction
{
public:
  using dec_funct_type = dlib::decision_function<RBF>;
  using learned_function_type = dlib::normalized_function<dec_funct_type>;

private:
  learned_function_type _data;

public:
  double Evaluate(Matrix sample) const { return _data(sample); }
};

class NormalizedProbabilisticFunction
{
  void SetNormalizer() {}

  void SetFunction() {}
};

dlib::reduced_decision_function_trainer2<SVMNuTrainer>
Reduced2(const SVMNuTrainer& trainer, const long num_bv, double eps = 1e-3)
{
  return dlib::reduced2(trainer, num_bv, eps);
}

NormalizedProbabilisticFunction
TrainProbabilisticDecisionFunction()
{
  throw std::runtime_error("Not Implemented!");
}

} // namespace jdlib

#endif // TRAIN_HPP
