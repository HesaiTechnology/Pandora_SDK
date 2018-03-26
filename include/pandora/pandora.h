/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef INCLUDE_PANDORA_PANDORA_H_
#define INCLUDE_PANDORA_PANDORA_H_

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pthread.h>
#include <semaphore.h>
#include <opencv2/highgui/highgui_c.h>

#include <vector>
#include <string>


#include <boost/function.hpp>
#include <opencv2/opencv.hpp>

#include "pandar40p/pandar40p.h"
#include "pandar40p/point_types.h"
#include "src/pandora_camera.h"

namespace apollo {
namespace drivers {
namespace hesai {

class Pandora_Internal;

class Pandora {
 public:
  /**
   * @brief Constructor
   * @param device_ip  				The ip of the device
   *        lidar_port 				The port number of lidar data
   *        gps_port   				The port number of gps data
   *        pcl_callback      The callback of PCL data structure
   *        gps_callback      The callback of GPS structure
   *        type       				The device type
   */
  Pandora(std::string device_ip, const uint16_t lidar_port,
          const uint16_t gps_port,
          boost::function<void(boost::shared_ptr<PPointCloud>, double)>
              pcl_callback,
          boost::function<void(double)> gps_callback, uint16_t start_angle,
          const uint16_t pandoraCameraPort,
          boost::function<void(boost::shared_ptr<cv::Mat> matp,
                               double timestamp, int picid, bool distortion)>
              cameraCallback);
  ~Pandora();

  /**
   * @brief load the correction file
   * @param file The path of correction file
   */
  int LoadLidarCorrectionFile(std::string file);

  /**
   * @brief load the correction file
   * @param angle The start angle
   */
  void ResetLidarStartAngle(uint16_t start_angle);

  int UploadCameraCalibration(const std::vector<cv::Mat> cameras_k,
                              const std::vector<cv::Mat> cameras_d,
                              double extrinsic[6]);
  int GetCameraCalibration(std::vector<cv::Mat> *cameras_k,
                           std::vector<cv::Mat> *cameras_d,
                           double extrinsic[6]);
  int ResetCameraClibration();

  int Start();
  void Stop();

 private:
  Pandora_Internal *internal_;
};

}  // namespace hesai
}  // namespace drivers
}  // namespace apollo

#endif  // INCLUDE_PANDORA_PANDORA_H_
