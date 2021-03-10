//  ----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./storage_ops.h"

namespace sym {
namespace pose3 {

template <typename ScalarType>
void StorageOps<ScalarType>::ToStorage(const sym::Pose3<ScalarType>& a, ScalarType* out) {
  assert(out != nullptr);
  std::copy_n(a.Data().data(), a.StorageDim(), out);
}

template <typename ScalarType>
sym::Pose3<ScalarType> StorageOps<ScalarType>::FromStorage(const ScalarType* data) {
  assert(data != nullptr);
  return sym::Pose3<ScalarType>(Eigen::Map<const typename sym::Pose3<ScalarType>::DataVec>(data));
}

}  // namespace pose3
}  // namespace sym

// Explicit instantiation
template struct sym::pose3::StorageOps<double>;
template struct sym::pose3::StorageOps<float>;