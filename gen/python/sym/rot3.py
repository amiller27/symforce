# -----------------------------------------------------------------------------
# This file was autogenerated by symforce from template:
#     geo_package/CLASS.py.jinja
# Do NOT modify by hand.
# -----------------------------------------------------------------------------

import math
import typing as T

import numpy

# isort: split
from .ops import rot3 as ops


class Rot3(object):
    """
    Autogenerated Python implementation of <class 'symforce.geo.rot3.Rot3'>.

    Group of three-dimensional orthogonal matrices with determinant +1, representing
    rotations in 3D space. Backed by a quaternion with (x, y, z, w) storage.
    """

    __slots__ = ["data"]

    def __repr__(self):
        # type: () -> str
        return "<{} {}>".format(self.__class__.__name__, self.data)

    # --------------------------------------------------------------------------
    # Handwritten methods included from "custom_methods/rot3.py.jinja"
    # --------------------------------------------------------------------------

    def __init__(self, q=None):
        # type: (T.Union[T.Sequence[float], numpy.ndarray]) -> None
        if q is None:
            self.data = ops.GroupOps.identity().data  # type: T.List[float]
        else:
            if isinstance(q, numpy.ndarray):
                if q.shape in [(4, 1), (1, 4)]:
                    q = q.flatten()
                elif q.shape != (4,):
                    raise IndexError(
                        "Expected q to be a vector of length 4; instead had shape {}".format(
                            q.shape
                        )
                    )
            elif len(q) != 4:
                raise IndexError(
                    "Expected q to be a sequence of length 4, was instead length {}.".format(len(q))
                )
            self.data = list(q)

    @classmethod
    def from_rotation_matrix(cls, R, epsilon=0.0):
        # type: (numpy.ndarray, float) -> Rot3
        assert R.shape == (3, 3)
        w = numpy.sqrt(max(epsilon ** 2, 1 + R[0, 0] + R[1, 1] + R[2, 2])) / 2
        x = numpy.sqrt(max(epsilon ** 2, 1 + R[0, 0] - R[1, 1] - R[2, 2])) / 2
        y = numpy.sqrt(max(epsilon ** 2, 1 - R[0, 0] + R[1, 1] - R[2, 2])) / 2
        z = numpy.sqrt(max(epsilon ** 2, 1 - R[0, 0] - R[1, 1] + R[2, 2])) / 2

        x = abs(x)
        if (R[2, 1] - R[1, 2]) < 0:
            x = -x

        y = abs(y)
        if (R[0, 2] - R[2, 0]) < 0:
            y = -y

        z = abs(z)
        if (R[1, 0] - R[0, 1]) < 0:
            z = -z

        return Rot3.from_storage([x, y, z, w])

    # --------------------------------------------------------------------------
    # Custom generated methods
    # --------------------------------------------------------------------------

    def compose_with_point(self, right):
        # type: (Rot3, numpy.ndarray) -> numpy.ndarray
        """
        Left-multiplication. Either rotation concatenation or point transform.
        """

        # Total ops: 43

        # Input arrays
        _self = self.data
        if right.shape == (3,):
            right = right.reshape((3, 1))
        elif right.shape != (3, 1):
            raise IndexError(
                "right is expected to have shape (3, 1) or (3,); instead had shape {}".format(
                    right.shape
                )
            )

        # Intermediate terms (11)
        _tmp0 = 2 * _self[0]
        _tmp1 = _self[1] * _tmp0
        _tmp2 = 2 * _self[2]
        _tmp3 = _self[3] * _tmp2
        _tmp4 = 2 * _self[1] * _self[3]
        _tmp5 = _self[2] * _tmp0
        _tmp6 = -2 * _self[1] ** 2
        _tmp7 = 1 - 2 * _self[2] ** 2
        _tmp8 = _self[3] * _tmp0
        _tmp9 = _self[1] * _tmp2
        _tmp10 = -2 * _self[0] ** 2

        # Output terms
        _res = numpy.zeros((3, 1))
        _res[0, 0] = (
            right[0, 0] * (_tmp6 + _tmp7)
            + right[1, 0] * (_tmp1 - _tmp3)
            + right[2, 0] * (_tmp4 + _tmp5)
        )
        _res[1, 0] = (
            right[0, 0] * (_tmp1 + _tmp3)
            + right[1, 0] * (_tmp10 + _tmp7)
            + right[2, 0] * (-_tmp8 + _tmp9)
        )
        _res[2, 0] = (
            right[0, 0] * (-_tmp4 + _tmp5)
            + right[1, 0] * (_tmp8 + _tmp9)
            + right[2, 0] * (_tmp10 + _tmp6 + 1)
        )
        return _res

    def to_rotation_matrix(self):
        # type: (Rot3) -> numpy.ndarray
        """
        Converts to a rotation matrix
        """

        # Total ops: 28

        # Input arrays
        _self = self.data

        # Intermediate terms (11)
        _tmp0 = -2 * _self[1] ** 2
        _tmp1 = 1 - 2 * _self[2] ** 2
        _tmp2 = 2 * _self[0]
        _tmp3 = _self[1] * _tmp2
        _tmp4 = 2 * _self[2]
        _tmp5 = _self[3] * _tmp4
        _tmp6 = 2 * _self[1] * _self[3]
        _tmp7 = _self[2] * _tmp2
        _tmp8 = -2 * _self[0] ** 2
        _tmp9 = _self[3] * _tmp2
        _tmp10 = _self[1] * _tmp4

        # Output terms
        _res = numpy.zeros((3, 3))
        _res[0, 0] = _tmp0 + _tmp1
        _res[1, 0] = _tmp3 + _tmp5
        _res[2, 0] = -_tmp6 + _tmp7
        _res[0, 1] = _tmp3 - _tmp5
        _res[1, 1] = _tmp1 + _tmp8
        _res[2, 1] = _tmp10 + _tmp9
        _res[0, 2] = _tmp6 + _tmp7
        _res[1, 2] = _tmp10 - _tmp9
        _res[2, 2] = _tmp0 + _tmp8 + 1
        return _res

    @staticmethod
    def random_from_uniform_samples(u1, u2, u3):
        # type: (float, float, float) -> Rot3
        """
        Generate a random element of SO3 from three variables uniformly sampled in [0, 1].
        """

        # Total ops: 14

        # Input arrays

        # Intermediate terms (5)
        _tmp0 = math.sqrt(1 - u1)
        _tmp1 = 2 * math.pi
        _tmp2 = _tmp1 * u2
        _tmp3 = math.sqrt(u1)
        _tmp4 = _tmp1 * u3

        # Output terms
        _res = [0.0] * 4
        _res[0] = _tmp0 * math.sin(_tmp2)
        _res[1] = _tmp0 * math.cos(_tmp2)
        _res[2] = _tmp3 * math.sin(_tmp4)
        _res[3] = _tmp3 * math.cos(_tmp4)
        return Rot3.from_storage(_res)

    def to_yaw_pitch_roll(self):
        # type: (Rot3) -> numpy.ndarray
        """
        This function was autogenerated from a symbolic function. Do not modify by hand.

        Symbolic function: <lambda>

        Args:

        Outputs:
            res: Matrix31
        """

        # Total ops: 27

        # Input arrays
        _self = self.data

        # Intermediate terms (5)
        _tmp0 = 2 * _self[0]
        _tmp1 = 2 * _self[2]
        _tmp2 = _self[2] ** 2
        _tmp3 = _self[0] ** 2
        _tmp4 = -_self[1] ** 2 + _self[3] ** 2

        # Output terms
        _res = numpy.zeros((3, 1))
        _res[0, 0] = math.atan2(_self[1] * _tmp0 + _self[3] * _tmp1, -_tmp2 + _tmp3 + _tmp4)
        _res[1, 0] = -math.asin(max(-1, min(1, -2 * _self[1] * _self[3] + _self[2] * _tmp0)))
        _res[2, 0] = math.atan2(_self[1] * _tmp1 + _self[3] * _tmp0, _tmp2 - _tmp3 + _tmp4)
        return _res

    @staticmethod
    def from_yaw_pitch_roll(yaw, pitch, roll):
        # type: (float, float, float) -> Rot3
        """
        Construct from yaw, pitch, and roll Euler angles in radians
        """

        # Total ops: 25

        # Input arrays

        # Intermediate terms (13)
        _tmp0 = (1.0 / 2.0) * pitch
        _tmp1 = math.sin(_tmp0)
        _tmp2 = (1.0 / 2.0) * yaw
        _tmp3 = math.sin(_tmp2)
        _tmp4 = (1.0 / 2.0) * roll
        _tmp5 = math.cos(_tmp4)
        _tmp6 = _tmp3 * _tmp5
        _tmp7 = math.cos(_tmp0)
        _tmp8 = math.sin(_tmp4)
        _tmp9 = math.cos(_tmp2)
        _tmp10 = _tmp8 * _tmp9
        _tmp11 = _tmp3 * _tmp8
        _tmp12 = _tmp5 * _tmp9

        # Output terms
        _res = [0.0] * 4
        _res[0] = -_tmp1 * _tmp6 + _tmp10 * _tmp7
        _res[1] = _tmp1 * _tmp12 + _tmp11 * _tmp7
        _res[2] = -_tmp1 * _tmp10 + _tmp6 * _tmp7
        _res[3] = _tmp1 * _tmp11 + _tmp12 * _tmp7
        return Rot3.from_storage(_res)

    # --------------------------------------------------------------------------
    # StorageOps concept
    # --------------------------------------------------------------------------

    @staticmethod
    def storage_dim():
        # type: () -> int
        return 4

    def to_storage(self):
        # type: () -> T.List[float]
        return list(self.data)

    @classmethod
    def from_storage(cls, vec):
        # type: (T.Sequence[float]) -> Rot3
        instance = cls.__new__(cls)

        if isinstance(vec, list):
            instance.data = vec
        else:
            instance.data = list(vec)

        if len(vec) != cls.storage_dim():
            raise ValueError(
                "{} has storage dim {}, got {}.".format(cls.__name__, cls.storage_dim(), len(vec))
            )

        return instance

    # --------------------------------------------------------------------------
    # GroupOps concept
    # --------------------------------------------------------------------------

    @classmethod
    def identity(cls):
        # type: () -> Rot3
        return ops.GroupOps.identity()

    def inverse(self):
        # type: () -> Rot3
        return ops.GroupOps.inverse(self)

    def compose(self, b):
        # type: (Rot3) -> Rot3
        return ops.GroupOps.compose(self, b)

    def between(self, b):
        # type: (Rot3) -> Rot3
        return ops.GroupOps.between(self, b)

    # --------------------------------------------------------------------------
    # LieGroupOps concept
    # --------------------------------------------------------------------------

    @staticmethod
    def tangent_dim():
        # type: () -> int
        return 3

    @classmethod
    def from_tangent(cls, vec, epsilon=1e-8):
        # type: (numpy.ndarray, float) -> Rot3
        if len(vec) != cls.tangent_dim():
            raise ValueError(
                "Vector dimension ({}) not equal to tangent space dimension ({}).".format(
                    len(vec), cls.tangent_dim()
                )
            )
        return ops.LieGroupOps.from_tangent(vec, epsilon)

    def to_tangent(self, epsilon=1e-8):
        # type: (float) -> numpy.ndarray
        return ops.LieGroupOps.to_tangent(self, epsilon)

    def retract(self, vec, epsilon=1e-8):
        # type: (numpy.ndarray, float) -> Rot3
        if len(vec) != self.tangent_dim():
            raise ValueError(
                "Vector dimension ({}) not equal to tangent space dimension ({}).".format(
                    len(vec), self.tangent_dim()
                )
            )
        return ops.LieGroupOps.retract(self, vec, epsilon)

    def local_coordinates(self, b, epsilon=1e-8):
        # type: (Rot3, float) -> numpy.ndarray
        return ops.LieGroupOps.local_coordinates(self, b, epsilon)

    def interpolate(self, b, alpha, epsilon=1e-8):
        # type: (Rot3, float, float) -> Rot3
        return ops.LieGroupOps.interpolate(self, b, alpha, epsilon)

    # --------------------------------------------------------------------------
    # General Helpers
    # --------------------------------------------------------------------------
    def __eq__(self, other):
        # type: (T.Any) -> bool
        if isinstance(other, Rot3):
            return self.data == other.data
        else:
            return False

    @T.overload
    def __mul__(self, other):  # pragma: no cover
        # type: (Rot3) -> Rot3
        pass

    @T.overload
    def __mul__(self, other):  # pragma: no cover
        # type: (numpy.ndarray) -> numpy.ndarray
        pass

    def __mul__(self, other):
        # type: (T.Union[Rot3, numpy.ndarray]) -> T.Union[Rot3, numpy.ndarray]
        if isinstance(other, Rot3):
            return self.compose(other)
        elif isinstance(other, numpy.ndarray) and hasattr(self, "compose_with_point"):
            return self.compose_with_point(other).reshape(other.shape)
        else:
            raise NotImplementedError("Cannot compose {} with {}.".format(type(self), type(other)))
