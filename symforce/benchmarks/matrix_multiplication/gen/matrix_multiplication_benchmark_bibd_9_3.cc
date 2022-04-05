// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     matrix_multiplication_benchmark.cc.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

///
/// Experiment to show timing for the matrix multiplication example in the SymForce paper.
///
/// Run with:
///
///     build/bin/benchmarks/matrix_multiplication_benchmark_bibd_9_3
///
/// See run_matmul_benchmarks.py for more information
///

#include <chrono>
#include <thread>

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <spdlog/spdlog.h>

#include <symforce/opt/tic_toc.h>
#include <symforce/opt/util.h>

#include "catch.hpp"

using namespace sym;

#include "./compute_a_bibd_9_3.h"
#include "./compute_a_dense_bibd_9_3.h"
#include "./compute_a_dense_dynamic_bibd_9_3.h"
#include "./compute_at_b_bibd_9_3.h"
#include "./compute_b_bibd_9_3.h"
#include "./compute_b_dense_bibd_9_3.h"
#include "./compute_b_dense_dynamic_bibd_9_3.h"

template <typename Scalar>
__attribute__((noinline)) Eigen::Matrix<Scalar, 84, 84> ComputeDenseFixedBibd93(const Scalar x0,
                                                                                const Scalar x1) {
  Eigen::Matrix<Scalar, 36, 84> A = ComputeADenseBibd93<Scalar>(x0, x1);
  Eigen::Matrix<Scalar, 36, 84> B = ComputeBDenseBibd93<Scalar>(x0, x1);
  return A.transpose() * B;
}

template <typename Scalar>
__attribute__((noinline)) Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>
ComputeDenseDynamicBibd93(const Scalar x0, const Scalar x1) {
  const auto A = ComputeADenseDynamicBibd93<Scalar>(x0, x1);
  const auto B = ComputeBDenseDynamicBibd93<Scalar>(x0, x1);
  return A.transpose() * B;
}

template <typename Scalar>
__attribute__((noinline)) Eigen::SparseMatrix<Scalar> ComputeSparseBibd93(const Scalar x0,
                                                                          const Scalar x1) {
  Eigen::SparseMatrix<Scalar> A = ComputeABibd93<Scalar>(x0, x1);
  Eigen::SparseMatrix<Scalar> B = ComputeBBibd93<Scalar>(x0, x1);
  return A.transpose() * B;
}

// ----------------------------------------------------------------------------
// Test Cases
// ----------------------------------------------------------------------------

TEMPLATE_TEST_CASE("sparse_bibd_9_3", "", double, float) {
  using Scalar = TestType;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("sparse_bibd_9_3_{}", typeid(Scalar).name());

    for (Scalar x0 = 0.1; x0 < 100.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 100.0; x1 += 0.1) {
        auto mat = ComputeSparseBibd93(x0, x1);
        sum += mat.valuePtr()[0];
      }
    }
  }
}

TEMPLATE_TEST_CASE("dense_dynamic_bibd_9_3", "", double, float) {
  using Scalar = TestType;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("dense_dynamic_bibd_9_3_{}", typeid(Scalar).name());
    for (Scalar x0 = 0.1; x0 < 100.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 100.0; x1 += 0.1) {
        auto mat = ComputeDenseDynamicBibd93<Scalar>(x0, x1);
        sum += mat(0, 0);
      }
    }
  }
}

TEMPLATE_TEST_CASE("dense_fixed_bibd_9_3", "", double, float) {
  using Scalar = TestType;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("dense_fixed_bibd_9_3_{}", typeid(Scalar).name());
    for (Scalar x0 = 0.1; x0 < 100.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 100.0; x1 += 0.1) {
        auto mat = ComputeDenseFixedBibd93<Scalar>(x0, x1);
        sum += mat(0, 0);
      }
    }
  }
}

TEMPLATE_TEST_CASE("flattened_bibd_9_3", "", double, float) {
  using Scalar = TestType;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("flattened_bibd_9_3_{}", typeid(Scalar).name());
    for (Scalar x0 = 0.1; x0 < 100.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 100.0; x1 += 0.1) {
        auto mat = ComputeAtBBibd93(x0, x1);
        sum += mat.valuePtr()[0];
      }
    }
  }
}