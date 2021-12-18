// This file was autogenerated
// DO NOT MODIFY BY HAND!
#pragma once
#include <utility>

#include <Eigen/Dense>
#include <lcm/lcm_coretypes.h>

namespace eigen_lcm {

class Matrix2f : public Eigen::Matrix<float, 2, 2, Eigen::DontAlign> {
 public:
  // Pass through constructor
  template <typename... Args>
  Matrix2f(Args&&... args) : Eigen::Matrix<float, 2, 2, Eigen::DontAlign>(args...) {}

  // This method allows you to assign Eigen expressions to eigen_lcm::Matrix2f
  template <typename OtherDerived>
  eigen_lcm::Matrix2f& operator=(const Eigen::MatrixBase<OtherDerived>& other) {
    Eigen::Matrix<float, 2, 2, Eigen::DontAlign>::operator=(other);
    return *this;
  }

 private:
  // Disable comma initialization magic for eigen_lcm types
  template <typename T>
  Eigen::Matrix<float, 2, 2, Eigen::DontAlign>& operator<<(T other);

 public:
  /**
   * Encode a message into binary form.
   *
   * @param buf The output buffer.
   * @param offset Encoding starts at thie byte offset into @p buf.
   * @param maxlen Maximum number of bytes to write.  This should generally be
   *  equal to getEncodedSize().
   * @return The number of bytes encoded, or <0 on error.
   */
  inline int encode(void* buf, int offset, int maxlen) const;

  /**
   * Check how many bytes are required to encode this message.
   */
  inline int getEncodedSize() const;

  /**
   * Decode a message from binary form into this instance.
   *
   * @param buf The buffer containing the encoded message.
   * @param offset The byte offset into @p buf where the encoded message starts.
   * @param maxlen The maximum number of bytes to reqad while decoding.
   * @return The number of bytes decoded, or <0 if an error occured.
   */
  inline int decode(const void* buf, int offset, int maxlen);

  /**
   * Retrieve the 64-bit fingerprint identifying the structure of the message.
   * Note that the fingerprint is the same for all instances of the same
   * message type, and is a fingerprint on the message type definition, not on
   * the message contents.
   */
  constexpr static int64_t getHash();

  /**
   * Returns "Matrix2f"
   */
  inline static const char* getTypeName();

  /**
   * Returns "eigen_lcm"
   */
  inline static const char* getPackageName();

  // LCM support functions. Users should not call these
  inline int _encodeNoHash(void* buf, int offset, int maxlen) const;
  inline int _getEncodedSizeNoHash() const;
  inline int _decodeNoHash(const void* buf, int offset, int maxlen);
  constexpr static uint64_t _computeHash(const __lcm_hash_ptr* p);
};

int Matrix2f::encode(void* buf, int offset, int maxlen) const {
  int pos = 0, tlen;
  int64_t hash = (int64_t)getHash();

  tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
  if (tlen < 0)
    return tlen;
  else
    pos += tlen;

  tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
  if (tlen < 0)
    return tlen;
  else
    pos += tlen;

  return pos;
}

int Matrix2f::decode(const void* buf, int offset, int maxlen) {
  int pos = 0, thislen;

  int64_t msg_hash;
  thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
  if (thislen < 0)
    return thislen;
  else
    pos += thislen;
  if (msg_hash != getHash())
    return -1;

  thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
  if (thislen < 0)
    return thislen;
  else
    pos += thislen;

  return pos;
}

int Matrix2f::getEncodedSize() const {
  return 8 + _getEncodedSizeNoHash();
}

constexpr int64_t Matrix2f::getHash() {
  return _computeHash(NULL);
}

const char* Matrix2f::getTypeName() {
  return "Matrix2f";
}

const char* Matrix2f::getPackageName() {
  return "eigen_lcm";
}

int Matrix2f::_encodeNoHash(void* buf, int offset, int maxlen) const {
  int pos = 0, tlen;

  tlen = __float_encode_array(buf, offset + pos, maxlen - pos, this->data(), 4);
  if (tlen < 0)
    return tlen;
  else
    pos += tlen;

  return pos;
}

int Matrix2f::_decodeNoHash(const void* buf, int offset, int maxlen) {
  int pos = 0, tlen;

  tlen = __float_decode_array(buf, offset + pos, maxlen - pos, this->data(), 4);
  if (tlen < 0)
    return tlen;
  else
    pos += tlen;

  return pos;
}

int Matrix2f::_getEncodedSizeNoHash() const {
  int enc_size = 0;
  enc_size += __float_encoded_array_size(NULL, 4);
  return enc_size;
}

constexpr uint64_t Matrix2f::_computeHash(const __lcm_hash_ptr*) {
  uint64_t hash = 0x5c782a36eaf5245aLL;
  return (hash << 1) + ((hash >> 63) & 1);
}

}  // namespace eigen_lcm
