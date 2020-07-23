import numpy as np

from symforce import cam
from symforce import geo
from symforce.ops import StorageOps
from symforce.test_util import TestCase
from symforce.test_util.storage_ops_test_mixin import StorageOpsTestMixin
from symforce.test_util.cam_test_mixin import CamTestMixin


class EquidistantEpipolarTest(StorageOpsTestMixin, CamTestMixin, TestCase):
    """
    Test the EquidistantEpipolarCameraCal class.
    Note the mixin that tests all storage ops and camera projection/reprojection ops.
    """

    @classmethod
    def element(cls):
        # type: () -> cam.EquidistantEpipolarCameraCal
        [f_x, f_y, c_x, c_y] = np.random.uniform(low=0.0, high=1000.0, size=(4,))
        return cam.EquidistantEpipolarCameraCal(focal_length=(f_x, f_y), principal_point=(c_x, c_y))

    def test_is_valid(self):
        # type: () -> None
        """
        Tests if random points and pixels are correctly labeled as valid/invalid
        """
        for _ in range(10):
            cam_cal = self.element()
            point = geo.V3(np.random.uniform(low=-1.0, high=1.0, size=(3,)))
            pixel, is_valid_forward_proj = cam_cal.pixel_from_camera_point(point)

            # Points behind the camera should be invalid
            if point[2] > 0:
                self.assertNear(is_valid_forward_proj, 1)
            else:
                self.assertNear(is_valid_forward_proj, 0)

            _, is_valid_back_proj = cam_cal.camera_ray_from_pixel(pixel)

            linear_camera_cal = cam.LinearCameraCal(cam_cal.focal_length, cam_cal.principal_point)
            unit_depth = linear_camera_cal.unit_depth_from_pixel(pixel)
            if (
                abs(StorageOps.evalf(unit_depth[0])) >= np.pi / 2.0
                or abs(StorageOps.evalf(unit_depth[1])) >= np.pi / 2.0
            ):
                self.assertNear(is_valid_back_proj, 0)
            else:
                self.assertNear(is_valid_back_proj, 1)

    def test_invalid_points(self):
        # type: () -> None
        """
        Tests if specific invalid points are correctly labeled as invalid
        """
        invalid_points = [
            geo.V3(0, 0, -1),
            geo.V3(0, 0, -1e-9),
            geo.V3(0, 0, -1000),
            geo.V3(1, 1, -1),
            geo.V3(-1, -1, -1),
            geo.V3(1000, 1000, -1000),
        ]
        for point in invalid_points:
            for _ in range(10):
                cam_cal = self.element()
                _, is_valid_forward_proj = cam_cal.pixel_from_camera_point(point)
                self.assertTrue(is_valid_forward_proj == 0)

    def test_invalid_pixels(self):
        # type: () -> None
        """
        Tests if specific invalid pixels are correctly labeled as invalid
        """
        f_x, f_y = (380, 380)
        c_x, c_y = (320, 240)
        cam_cal = cam.EquidistantEpipolarCameraCal(
            focal_length=(f_x, f_y), principal_point=(c_x, c_y)
        )
        invalid_pixels = [
            geo.V2(f_x * (np.pi / 2.0 + 1e-6) + c_x, 0),
            geo.V2(0, f_y * (np.pi / 2.0 + 1e-6) + c_y),
            geo.V2(f_x * (-np.pi / 2.0 - 1e-6) + c_x, 0),
            geo.V2(0, f_y * (-np.pi / 2.0 - 1e-6) + c_y),
            geo.V2(1000, 1000),
            geo.V2(-1000, -1000),
        ]
        for pixel in invalid_pixels:
            _, is_valid_back_proj = cam_cal.camera_ray_from_pixel(pixel)
            self.assertTrue(StorageOps.evalf(is_valid_back_proj) == 0.0)


if __name__ == "__main__":
    TestCase.main()