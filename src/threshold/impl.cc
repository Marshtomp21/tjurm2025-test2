#include "impls.h"

std::vector<cv::Mat> threshold(const cv::Mat& src, int threshold_value) {
    cv::Mat gray, dst;

    // 1. 将彩色图像转换为灰度图像
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);  // 转换为灰度图像

    // 2. 使用给定的阈值进行二值化处理
    cv::threshold(gray, dst, threshold_value, 255, cv::THRESH_BINARY);  // 二值化，阈值为threshold_value

    // 3. 返回灰度图像和二值化图像
    return {gray, dst};
}
