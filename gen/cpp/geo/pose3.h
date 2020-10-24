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
#include "./rot3.h"

namespace geo {

/**
 * Autogenerated C++ implementation of <class 'symforce.geo.pose3.Pose3'>.
 *
 * Group of three-dimensional rigid body transformations - SE(3).
 *
 * The storage is a quaternion (x, y, z, w) for rotation followed by position (x, y, z).
 *
 * The tangent space is 3 elements for rotation followed by 3 elements for translation in
 * the rotated frame, meaning we interpolate the translation in the tangent of the rotating
 * frame for lie operations. This can be useful but is more expensive than SO3 x R3 for often
 * no benefit.
 */
template <typename ScalarType>
class Pose3 {
 public:
  // Typedefs
  using Scalar = ScalarType;
  using Self = Pose3<Scalar>;
  using DataVec = Eigen::Matrix<Scalar, 7, 1>;
  using TangentVec = Eigen::Matrix<Scalar, 6, 1>;
  using SelfJacobian = Eigen::Matrix<Scalar, 6, 6>;

  // Construct from data vec
  explicit Pose3(const DataVec& data) : data_(data) {}

  // Default construct to identity
  Pose3() : Pose3(GroupOps<Self>::Identity()) {}

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

  static Pose3 FromStorage(const Scalar* const vec) {
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
  Pose3<ToScalar> Cast() const {
    return Pose3<ToScalar>(Data().template cast<ToScalar>());
  }

  bool operator==(const Pose3& rhs) const {
    return data_ == rhs.Data();
  }

  // Included from "custom_methods/pose3.h.jinja":
  // --------------------------------------------------------------------------
  // Handwritten methods for Pose3
  // --------------------------------------------------------------------------

  using Vector3 = Eigen::Matrix<Scalar, 3, 1>;

  Pose3(const Rot3<Scalar>& rotation, const Vector3& position) {
    data_.template head<4>() = rotation.Data();
    data_.template tail<3>() = position;
  }

  Rot3<Scalar> Rotation() const {
    return Rot3<Scalar>(data_.template head<4>());
  }

  Vector3 Position() const {
    return data_.template tail<3>();
  }

  // TODO(hayk): Could codegen this.
  Vector3 Compose(const Vector3& point) const {
    return Rotation() * point + Position();
  }

  Vector3 operator*(const Vector3& point) {
    return Compose(point);
  }

 protected:
  DataVec data_;
};

// Shorthand for scalar types
using Pose3d = Pose3<double>;
using Pose3f = Pose3<float>;

}  // namespace geo

// Externs to reduce duplicate instantiation
extern template class geo::Pose3<double>;
extern template class geo::Pose3<float>;

// Print definitions
std::ostream& operator<<(std::ostream& os, const geo::Pose3<double>& a);
std::ostream& operator<<(std::ostream& os, const geo::Pose3<float>& a);

// Concept implementations for this class (include order matters here)
// clang-format off
#include "./ops/pose3/storage_ops.h"
#include "./ops/pose3/lie_group_ops.h"
#include "./ops/pose3/group_ops.h"
// clang-format on
