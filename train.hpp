#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <dlib/matrix.h>
#include <dlib/memory_manager.h>
#include <dlib/svm.h>

namespace jdlib {

template<class T0>
class Vector : public std::vector<T0>
{

public:
  Vector() = default;

  void Add(const T0& value) { push_back(value); }

  int64_t Size() { return this->size(); }

  const T0& Get(int64_t index) const { return this->at(index); }
};

class Vectord : public Vector<double>
{};

class Matrix : public dlib::matrix<double>
{

public:
  Matrix() = default;

  Matrix(const Matrix& other) = default;

  Matrix(const dlib::matrix<double>& other)
    : dlib::matrix<double>(other)
  {}

  Matrix(int row, int col)
    : dlib::matrix<double>(row, col)
  {}

  Matrix& operator=(const dlib::matrix<double>& other)
  {
    this->dlib::matrix<double>::operator=(other);
    return *this;
  }

  Matrix& operator=(const double& other)
  {
    this->dlib::matrix<double>::operator=(other);
    return *this;
  }

  Matrix& operator-=(const double& other)
  {
    this->dlib::matrix<double>::operator-=(other);
    return *this;
  }

  //  Matrix& operator/=(const double& other)
  //  {
  //    this->dlib::matrix<double>::operator/=(other);
  //    return *this;
  //  }

  //  Matrix operator/(const double& other) const
  //  {
  //    return Matrix(
  //      dlib::operator/(static_cast<const dlib::matrix<double>&>(*this),
  //      other));
  //  }

  //  Matrix operator/(const int& other) const
  //  {
  //    return Matrix(
  //      dlib::operator/(static_cast<const dlib::matrix<double>&>(*this),
  //      other));
  //  }

  void set(int row, int col, double val) { (*this)(row, col) = val; }

  double get(int row, int col) { return (*this)(row, col); }
};

Matrix
operator/(const Matrix& A, const double& scalar)
{
  dlib::matrix<double> div = static_cast<dlib::matrix<double>>(A) / scalar;
  return Matrix(div);
}

Matrix
operator/(const Matrix& A, const int& scalar)
{
  dlib::matrix<double> div = static_cast<dlib::matrix<double>>(A) / scalar;
  return Matrix(div);
}

class VectorM : public Vector<Matrix>
{};

// using sample_type = dlib::matrix<double>;
// using kernel_type = dlib::radial_basis_kernel<sample_type>;
// using dec_funct_type = dlib::decision_function<kernel_type>;
// using funct_type = dlib::normalized_function<dec_funct_type>;

class VectorNormalizer : dlib::vector_normalizer<Matrix>
{

public:
  void Train(const VectorM& samples) { train(samples); }

  Matrix Normalize(const Matrix& sample) const { return (*this)(sample); }
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

class RBF : public dlib::radial_basis_kernel<Matrix>
{

public:
  RBF() = default;

  RBF(double gamma)
    : dlib::radial_basis_kernel<Matrix>(gamma)
  {}
};

class SVMNuTrainer : public dlib::svm_nu_trainer<RBF>
{

public:
  void SetKernel(RBF Kernel) { set_kernel(Kernel); }

  void SetNu(double nu) { set_nu(nu); }

  void Train(const std::vector<Matrix>& samples,
             const std::vector<double>& labels)
  {
    train(samples, labels);
  }
};

class Matrix12 : public dlib::matrix<double, 1, 2>
{
public:
  Matrix12() = default;
  Matrix12(const dlib::matrix<double, 1, 2>& other)
    : dlib::matrix<double, 1, 2>(other)
  {}
};

Matrix12
CrossValidateTrainer(const SVMNuTrainer& trainer,
                     const VectorM& samples,
                     const Vectord& labels,
                     long fold)
{
  return dlib::cross_validate_trainer(trainer, samples, labels, fold);
}

class LearnedFunction
{

public:
  double Evaluate(Matrix sample) const { throw std::runtime_error("CHECK!"); }
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
