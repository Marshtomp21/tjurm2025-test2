#include <opencv2/opencv.hpp>
#include <vector>

float compute_area_ratio(const std::vector<cv::Point>& contour) {
    float contourArea = cv::contourArea(contour);

    cv::RotatedRect minRect = cv::minAreaRect(contour);

    float rectArea = minRect.size.width * minRect.size.height;

    return (rectArea > 0) ? (contourArea / rectArea) : 0.0f;
}