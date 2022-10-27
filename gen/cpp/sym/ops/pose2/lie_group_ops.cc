// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     ops/CLASS/lie_group_ops.cc.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./lie_group_ops.h"

#include <cmath>

#include <sym/pose2.h>

namespace sym {

template <typename Scalar>
sym::Pose2<Scalar> LieGroupOps<Pose2<Scalar>>::FromTangent(const TangentVec& vec,
                                                           const Scalar epsilon) {
  // Total ops: 2

  // Unused inputs
  (void)epsilon;

  // Input arrays

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 4, 1> _res;

  _res[0] = std::cos(vec(0, 0));
  _res[1] = std::sin(vec(0, 0));
  _res[2] = vec(1, 0);
  _res[3] = vec(2, 0);

  return sym::Pose2<Scalar>(_res);
}

template <typename Scalar>
typename LieGroupOps<Pose2<Scalar>>::TangentVec LieGroupOps<Pose2<Scalar>>::ToTangent(
    const sym::Pose2<Scalar>& a, const Scalar epsilon) {
  // Total ops: 5

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 3, 1> _res;

  _res(0, 0) = std::atan2(_a[1], _a[0] + epsilon * ((((_a[0]) > 0) - ((_a[0]) < 0)) + Scalar(0.5)));
  _res(1, 0) = _a[2];
  _res(2, 0) = _a[3];

  return _res;
}

template <typename Scalar>
sym::Pose2<Scalar> LieGroupOps<Pose2<Scalar>>::Retract(const sym::Pose2<Scalar>& a,
                                                       const TangentVec& vec,
                                                       const Scalar epsilon) {
  // Total ops: 10

  // Unused inputs
  (void)epsilon;

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();

  // Intermediate terms (2)
  const Scalar _tmp0 = std::sin(vec(0, 0));
  const Scalar _tmp1 = std::cos(vec(0, 0));

  // Output terms (1)
  Eigen::Matrix<Scalar, 4, 1> _res;

  _res[0] = _a[0] * _tmp1 - _a[1] * _tmp0;
  _res[1] = _a[0] * _tmp0 + _a[1] * _tmp1;
  _res[2] = _a[2] + vec(1, 0);
  _res[3] = _a[3] + vec(2, 0);

  return sym::Pose2<Scalar>(_res);
}

template <typename Scalar>
typename LieGroupOps<Pose2<Scalar>>::TangentVec LieGroupOps<Pose2<Scalar>>::LocalCoordinates(
    const sym::Pose2<Scalar>& a, const sym::Pose2<Scalar>& b, const Scalar epsilon) {
  // Total ops: 13

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 4, 1>& _b = b.Data();

  // Intermediate terms (1)
  const Scalar _tmp0 = _a[0] * _b[0] + _a[1] * _b[1];

  // Output terms (1)
  Eigen::Matrix<Scalar, 3, 1> _res;

  _res(0, 0) = std::atan2(_a[0] * _b[1] - _a[1] * _b[0],
                          _tmp0 + epsilon * ((((_tmp0) > 0) - ((_tmp0) < 0)) + Scalar(0.5)));
  _res(1, 0) = -_a[2] + _b[2];
  _res(2, 0) = -_a[3] + _b[3];

  return _res;
}

template <typename Scalar>
sym::Pose2<Scalar> LieGroupOps<Pose2<Scalar>>::Interpolate(const sym::Pose2<Scalar>& a,
                                                           const sym::Pose2<Scalar>& b,
                                                           const Scalar alpha,
                                                           const Scalar epsilon) {
  // Total ops: 26

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 4, 1>& _b = b.Data();

  // Intermediate terms (4)
  const Scalar _tmp0 = _a[0] * _b[0] + _a[1] * _b[1];
  const Scalar _tmp1 =
      alpha * std::atan2(_a[0] * _b[1] - _a[1] * _b[0],
                         _tmp0 + epsilon * ((((_tmp0) > 0) - ((_tmp0) < 0)) + Scalar(0.5)));
  const Scalar _tmp2 = std::sin(_tmp1);
  const Scalar _tmp3 = std::cos(_tmp1);

  // Output terms (1)
  Eigen::Matrix<Scalar, 4, 1> _res;

  _res[0] = _a[0] * _tmp3 - _a[1] * _tmp2;
  _res[1] = _a[0] * _tmp2 + _a[1] * _tmp3;
  _res[2] = _a[2] + alpha * (-_a[2] + _b[2]);
  _res[3] = _a[3] + alpha * (-_a[3] + _b[3]);

  return sym::Pose2<Scalar>(_res);
}

}  // namespace sym

// Explicit instantiation
template struct sym::LieGroupOps<sym::Pose2<double>>;
template struct sym::LieGroupOps<sym::Pose2<float>>;
