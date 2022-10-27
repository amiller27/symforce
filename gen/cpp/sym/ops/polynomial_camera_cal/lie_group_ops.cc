// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     ops/CLASS/lie_group_ops.cc.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./lie_group_ops.h"

#include <cmath>

#include <sym/polynomial_camera_cal.h>

namespace sym {

template <typename Scalar>
sym::PolynomialCameraCal<Scalar> LieGroupOps<PolynomialCameraCal<Scalar>>::FromTangent(
    const TangentVec& vec, const Scalar epsilon) {
  // Total ops: 0

  // Unused inputs
  (void)epsilon;

  // Input arrays

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 8, 1> _res;

  _res[0] = vec(0, 0);
  _res[1] = vec(1, 0);
  _res[2] = vec(2, 0);
  _res[3] = vec(3, 0);
  _res[4] = vec(4, 0);
  _res[5] = vec(5, 0);
  _res[6] = vec(6, 0);
  _res[7] = vec(7, 0);

  return sym::PolynomialCameraCal<Scalar>(_res);
}

template <typename Scalar>
typename LieGroupOps<PolynomialCameraCal<Scalar>>::TangentVec
LieGroupOps<PolynomialCameraCal<Scalar>>::ToTangent(const sym::PolynomialCameraCal<Scalar>& a,
                                                    const Scalar epsilon) {
  // Total ops: 0

  // Unused inputs
  (void)epsilon;

  // Input arrays
  const Eigen::Matrix<Scalar, 8, 1>& _a = a.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 8, 1> _res;

  _res(0, 0) = _a[0];
  _res(1, 0) = _a[1];
  _res(2, 0) = _a[2];
  _res(3, 0) = _a[3];
  _res(4, 0) = _a[4];
  _res(5, 0) = _a[5];
  _res(6, 0) = _a[6];
  _res(7, 0) = _a[7];

  return _res;
}

template <typename Scalar>
sym::PolynomialCameraCal<Scalar> LieGroupOps<PolynomialCameraCal<Scalar>>::Retract(
    const sym::PolynomialCameraCal<Scalar>& a, const TangentVec& vec, const Scalar epsilon) {
  // Total ops: 8

  // Unused inputs
  (void)epsilon;

  // Input arrays
  const Eigen::Matrix<Scalar, 8, 1>& _a = a.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 8, 1> _res;

  _res[0] = _a[0] + vec(0, 0);
  _res[1] = _a[1] + vec(1, 0);
  _res[2] = _a[2] + vec(2, 0);
  _res[3] = _a[3] + vec(3, 0);
  _res[4] = _a[4] + vec(4, 0);
  _res[5] = _a[5] + vec(5, 0);
  _res[6] = _a[6] + vec(6, 0);
  _res[7] = _a[7] + vec(7, 0);

  return sym::PolynomialCameraCal<Scalar>(_res);
}

template <typename Scalar>
typename LieGroupOps<PolynomialCameraCal<Scalar>>::TangentVec
LieGroupOps<PolynomialCameraCal<Scalar>>::LocalCoordinates(
    const sym::PolynomialCameraCal<Scalar>& a, const sym::PolynomialCameraCal<Scalar>& b,
    const Scalar epsilon) {
  // Total ops: 8

  // Unused inputs
  (void)epsilon;

  // Input arrays
  const Eigen::Matrix<Scalar, 8, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 8, 1>& _b = b.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 8, 1> _res;

  _res(0, 0) = -_a[0] + _b[0];
  _res(1, 0) = -_a[1] + _b[1];
  _res(2, 0) = -_a[2] + _b[2];
  _res(3, 0) = -_a[3] + _b[3];
  _res(4, 0) = -_a[4] + _b[4];
  _res(5, 0) = -_a[5] + _b[5];
  _res(6, 0) = -_a[6] + _b[6];
  _res(7, 0) = -_a[7] + _b[7];

  return _res;
}

template <typename Scalar>
sym::PolynomialCameraCal<Scalar> LieGroupOps<PolynomialCameraCal<Scalar>>::Interpolate(
    const sym::PolynomialCameraCal<Scalar>& a, const sym::PolynomialCameraCal<Scalar>& b,
    const Scalar alpha, const Scalar epsilon) {
  // Total ops: 24

  // Unused inputs
  (void)epsilon;

  // Input arrays
  const Eigen::Matrix<Scalar, 8, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 8, 1>& _b = b.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 8, 1> _res;

  _res[0] = _a[0] + alpha * (-_a[0] + _b[0]);
  _res[1] = _a[1] + alpha * (-_a[1] + _b[1]);
  _res[2] = _a[2] + alpha * (-_a[2] + _b[2]);
  _res[3] = _a[3] + alpha * (-_a[3] + _b[3]);
  _res[4] = _a[4] + alpha * (-_a[4] + _b[4]);
  _res[5] = _a[5] + alpha * (-_a[5] + _b[5]);
  _res[6] = _a[6] + alpha * (-_a[6] + _b[6]);
  _res[7] = _a[7] + alpha * (-_a[7] + _b[7]);

  return sym::PolynomialCameraCal<Scalar>(_res);
}

}  // namespace sym

// Explicit instantiation
template struct sym::LieGroupOps<sym::PolynomialCameraCal<double>>;
template struct sym::LieGroupOps<sym::PolynomialCameraCal<float>>;
