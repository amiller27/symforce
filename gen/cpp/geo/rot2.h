//  -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <ostream>
#include <random>
#include <vector>

#include <Eigen/Dense>

#include "./ops/group_ops.h"
#include "./ops/lie_group_ops.h"
#include "./ops/storage_ops.h"

namespace geo {

/**
 * Autogenerated C++ implementation of <class 'symforce.geo.rot2.Rot2'>.
 *
 * Group of two-dimensional orthogonal matrices with determinant +1, representing rotations
 * in 2D space. Backed by a complex number.
 */
template <typename ScalarType>
class Rot2 {
 public:
  // Typedefs
  using Scalar = ScalarType;
  using Self = Rot2<Scalar>;
  using DataVec = Eigen::Matrix<Scalar, 2, 1>;
  using TangentVec = Eigen::Matrix<Scalar, 1, 1>;
  using SelfJacobian = Eigen::Matrix<Scalar, 1, 1>;

  // Construct from data vec
  // For rotation types the storage is normalized on construction.
  // This ensures numerical stability as this constructor is called after each codegen operation.
  explicit Rot2(const DataVec& data) : data_(data.normalized()) {}

  // Default construct to identity
  Rot2() : Rot2(GroupOps<Self>::Identity()) {}

  // Access underlying storage as const
  inline const DataVec& Data() const {
    return data_;
  }

  // --------------------------------------------------------------------------
  // StorageOps concept
  // --------------------------------------------------------------------------

  static constexpr int32_t StorageDim() {
    return StorageOps<Self>::StorageDim();
  }

  void ToStorage(Scalar* const vec) const {
    return StorageOps<Self>::ToStorage(*this, vec);
  }

  static Rot2 FromStorage(const Scalar* const vec) {
    return StorageOps<Self>::FromStorage(vec);
  }

  // --------------------------------------------------------------------------
  // GroupOps concept
  // --------------------------------------------------------------------------

  static Self Identity() {
    return GroupOps<Self>::Identity();
  }

  Self Inverse() const {
    return GroupOps<Self>::Inverse(*this);
  }

  Self Compose(const Self& b) const {
    return GroupOps<Self>::Compose(*this, b);
  }

  Self Between(const Self& b) const {
    return GroupOps<Self>::Between(*this, b);
  }

  Self InverseWithJacobian(SelfJacobian* const res_D_a = nullptr) const {
    return GroupOps<Self>::InverseWithJacobian(*this, res_D_a);
  }

  Self ComposeWithJacobians(const Self& b, SelfJacobian* const res_D_a = nullptr,
                            SelfJacobian* const res_D_b = nullptr) const {
    return GroupOps<Self>::ComposeWithJacobians(*this, b, res_D_a, res_D_b);
  }

  Self BetweenWithJacobians(const Self& b, SelfJacobian* const res_D_a = nullptr,
                            SelfJacobian* const res_D_b = nullptr) const {
    return GroupOps<Self>::BetweenWithJacobians(*this, b, res_D_a, res_D_b);
  }

  // Compose shorthand
  template <typename Other>
  Other operator*(const Other& b) const {
    return Compose(b);
  }

  // --------------------------------------------------------------------------
  // LieGroupOps concept
  // --------------------------------------------------------------------------

  static constexpr int32_t TangentDim() {
    return LieGroupOps<Self>::TangentDim();
  }

  static Self FromTangent(const TangentVec& vec, const Scalar epsilon = 1e-8f) {
    return LieGroupOps<Self>::FromTangent(vec, epsilon);
  }

  TangentVec ToTangent(const Scalar epsilon = 1e-8f) const {
    return LieGroupOps<Self>::ToTangent(*this, epsilon);
  }

  Self Retract(const TangentVec& vec, const Scalar epsilon = 1e-8f) const {
    return LieGroupOps<Self>::Retract(*this, vec, epsilon);
  }

  TangentVec LocalCoordinates(const Self& b, const Scalar epsilon = 1e-8f) const {
    return LieGroupOps<Self>::LocalCoordinates(*this, b, epsilon);
  }

  // --------------------------------------------------------------------------
  // General Helpers
  // --------------------------------------------------------------------------

  bool IsApprox(const Self& b, const Scalar tol) const {
    // isApprox is multiplicative so we check the norm for the exact zero case
    // https://eigen.tuxfamily.org/dox/classEigen_1_1DenseBase.html#ae8443357b808cd393be1b51974213f9c
    if (b.Data() == DataVec::Zero()) {
      return Data().norm() < tol;
    }

    return Data().isApprox(b.Data(), tol);
  }

  template <typename ToScalar>
  Rot2<ToScalar> Cast() const {
    return Rot2<ToScalar>(Data().template cast<ToScalar>());
  }

  bool operator==(const Rot2& rhs) const {
    return data_ == rhs.Data();
  }

  // Included from "custom_methods/rot2.h.jinja":
  // --------------------------------------------------------------------------
  // Handwritten methods for Rot2
  // --------------------------------------------------------------------------

  // Generate a random element of SO2 from a number u1 in [0, 1]
  static Rot2 RandomFromUniformSamples(const Scalar u1) {
    const Scalar theta = 2 * M_PI * u1;
    return Rot2(Eigen::Matrix<Scalar, 2, 1>(std::cos(theta), std::sin(theta)));
  }

  // Generate a random element in SO3
  static Rot2 Random(std::mt19937& gen) {
    std::uniform_real_distribution<Scalar> dist(0.0, 1.0);
    return RandomFromUniformSamples(dist(gen));
  }

 protected:
  DataVec data_;
};

// Shorthand for scalar types
using Rot2d = Rot2<double>;
using Rot2f = Rot2<float>;

}  // namespace geo

// Externs to reduce duplicate instantiation
extern template class geo::Rot2<double>;
extern template class geo::Rot2<float>;

// Print definitions
std::ostream& operator<<(std::ostream& os, const geo::Rot2<double>& a);
std::ostream& operator<<(std::ostream& os, const geo::Rot2<float>& a);

// Concept implementations for this class (include order matters here)
// clang-format off
#include "./ops/rot2/storage_ops.h"
#include "./ops/rot2/lie_group_ops.h"
#include "./ops/rot2/group_ops.h"
// clang-format on
