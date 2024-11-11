#include "impls.h"

std::vector<cv::Mat> split(const cv::Mat& rgb_image) {
    /**
     * TODO: 将图像分割为 blue green red 三个通道
     */
    std::vector<cv::Mat> result;

    // 使用cv::split分割图像为三个通道
    cv::Mat channels[3];  // 用于存储三个通道
    cv::split(rgb_image, channels);  // 将图像分割为BGR三个通道

    // 将分割后的通道放入 result 中
    result.push_back(channels[0]);  // Blue 通道
    result.push_back(channels[1]);  // Green 通道
    result.push_back(channels[2]);  // Red 通道

    return result;
}
