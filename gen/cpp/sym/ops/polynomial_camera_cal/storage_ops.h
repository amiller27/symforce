// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/cam_package/ops/CLASS/storage_ops.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <vector>

#include <Eigen/Dense>
#include <sym/polynomial_camera_cal.h>

namespace sym {
namespace polynomial_camera_cal {

/**
 * C++ StorageOps implementation for <class
 * 'symforce.cam.polynomial_camera_cal.PolynomialCameraCal'>.
 */
template <typename Scalar>
struct StorageOps {
  static constexpr int32_t StorageDim() {
    return 8;
  }

  static void ToStorage(const sym::PolynomialCameraCal<Scalar>& a, Scalar* const vec);
  static sym::PolynomialCameraCal<Scalar> FromStorage(const Scalar* const vec);
};

}  // namespace polynomial_camera_cal
}  // namespace sym

// Wrapper to specialize the public concept
namespace sym {

template <>
struct StorageOps<sym::PolynomialCameraCal<double>>
    : public sym::polynomial_camera_cal::StorageOps<double> {};
template <>
struct StorageOps<sym::PolynomialCameraCal<float>>
    : public sym::polynomial_camera_cal::StorageOps<float> {};

}  // namespace sym

// Explicit instantiation
extern template struct sym::polynomial_camera_cal::StorageOps<double>;
extern template struct sym::polynomial_camera_cal::StorageOps<float>;
