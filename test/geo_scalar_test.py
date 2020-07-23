from symforce import sympy as sm
from symforce import types as T
from symforce.test_util import TestCase
from symforce.test_util.lie_group_ops_test_mixin import LieGroupOpsTestMixin


class GeoScalarTest(LieGroupOpsTestMixin, TestCase):
    """
    Test a scalar as a geometric class.
    Note the mixin that tests all storage, group and lie group ops.
    """

    @classmethod
    def element(cls):
        # type: () -> T.Scalar
        return float(3.2)


if __name__ == "__main__":
    TestCase.main()