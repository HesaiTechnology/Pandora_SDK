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

#include "pandora/pandora.h"
#include "src/pandora_client.h"

namespace apollo {
namespace drivers {
namespace hesai {

class Pandora_Internal {
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
  Pandora_Internal(
      std::string device_ip, const uint16_t lidar_port, const uint16_t gps_port,
      boost::function<void(boost::shared_ptr<PPointCloud>, double)>
          pcl_callback,
      boost::function<void(double)> gps_callback, uint16_t start_angle,
      const uint16_t pandoraCameraPort,
      boost::function<void(boost::shared_ptr<cv::Mat> matp, double timestamp,
                           int picid, bool distortion)>
          cameraCallback);
  ~Pandora_Internal();

  /**
   * @brief load the correction file
   * @param file The path of correction file
   */
  int LoadLidarCorrectionFile(std::string correction_content);

  /**
   * @brief load the correction file
   * @param angle The start angle
   */
  void ResetLidarStartAngle(uint16_t start_angle);

  int UploadCameraCalibrationFile(const std::vector<cv::Mat> cameras_k,
                                  const std::vector<cv::Mat> cameras_d,
                                  double extrinsic[6]);
  int GetCameraCalibration(std::vector<cv::Mat> *cameras_k,
                           std::vector<cv::Mat> *cameras_d,
                           double extrinsic[6]);
  int ResetCameraClibration();

  int Start();
  void Stop();

 private:
  Pandar40P *pandar40p_;
  PandoraCamera *pandora_camera_;
};

Pandora_Internal::Pandora_Internal(
    std::string device_ip, const uint16_t lidar_port, const uint16_t gps_port,
    boost::function<void(boost::shared_ptr<PPointCloud>, double)> pcl_callback,
    boost::function<void(double)> gps_callback, uint16_t start_angle,
    const uint16_t pandoraCameraPort,
    boost::function<void(boost::shared_ptr<cv::Mat> matp, double timestamp,
                         int picid, bool distortion)>
        cameraCallback) {
  pandar40p_ = new Pandar40P(device_ip, lidar_port, gps_port, pcl_callback,
                             gps_callback, start_angle);
  pandora_camera_ =
      new PandoraCamera(device_ip, pandoraCameraPort, cameraCallback, NULL);
}

Pandora_Internal::~Pandora_Internal() {
  Stop();
  if (pandar40p_) {
    delete pandar40p_;
  }

  if (pandora_camera_) {
    delete pandora_camera_;
  }
}

/**
 * @brief load the correction file
 * @param file The path of correction file
 */
int Pandora_Internal::LoadLidarCorrectionFile(std::string correction_content) {
  std::cout << "LoadCorrectionFile" << std::endl;
}

/**
 * @brief load the correction file
 * @param angle The start angle
 */
void Pandora_Internal::ResetLidarStartAngle(uint16_t start_angle) {
  if (!pandar40p_) return;
  pandar40p_->ResetStartAngle(start_angle);
}

int Pandora_Internal::Start() {
  Stop();
  pandora_camera_->Start();
  pandar40p_->Start();
}

void Pandora_Internal::Stop() {
  pandar40p_->Stop();
  pandora_camera_->Stop();
}

int Pandora_Internal::UploadCameraCalibrationFile(
    const std::vector<cv::Mat> cameras_k, const std::vector<cv::Mat> cameras_d,
    double extrinsic[6]) {
  std::cout << "UploadCameraCalibrationFile" << std::endl;
}

int Pandora_Internal::GetCameraCalibration(std::vector<cv::Mat> *cameras_k,
                                           std::vector<cv::Mat> *cameras_d,
                                           double extrinsic[6]) {
  std::cout << "GetCameraCalibration" << std::endl;
}

int Pandora_Internal::ResetCameraClibration() {
  std::cout << "ResetCameraClibration" << std::endl;
}

/*****************************************************************************************
Pandora Part
*****************************************************************************************/

Pandora::Pandora(
    std::string device_ip, const uint16_t lidar_port, const uint16_t gps_port,
    boost::function<void(boost::shared_ptr<PPointCloud>, double)> pcl_callback,
    boost::function<void(double)> gps_callback, uint16_t start_angle,
    const uint16_t pandoraCameraPort,
    boost::function<void(boost::shared_ptr<cv::Mat> matp, double timestamp,
                         int picid, bool distortion)>
        cameraCallback) {
  internal_ = new Pandora_Internal(device_ip, lidar_port, gps_port,
                                   pcl_callback, gps_callback, start_angle,
                                   pandoraCameraPort, cameraCallback);
}

Pandora::~Pandora() { delete internal_; }

/**
 * @brief load the correction file
 * @param angle The start angle
 */
int Pandora::LoadLidarCorrectionFile(std::string correction_content) {
  internal_->LoadLidarCorrectionFile(correction_content);
}

int Pandora::Start() { internal_->Start(); }

void Pandora::Stop() { internal_->Stop(); }

void Pandora::ResetLidarStartAngle(uint16_t start_angle) {
  internal_->ResetLidarStartAngle(start_angle);
}

int Pandora::UploadCameraCalibration(const std::vector<cv::Mat> cameras_k,
                                     const std::vector<cv::Mat> cameras_d,
                                     double extrinsic[6]) {
  internal_->UploadCameraCalibrationFile(cameras_k, cameras_d, extrinsic);
}
int Pandora::GetCameraCalibration(std::vector<cv::Mat> *cameras_k,
                                  std::vector<cv::Mat> *cameras_d,
                                  double extrinsic[6]) {
  internal_->GetCameraCalibration(cameras_k, cameras_d, extrinsic);
}

int Pandora::ResetCameraClibration() { internal_->ResetCameraClibration(); }

}  // namespace hesai
}  // namespace drivers
}  // namespace apollo
