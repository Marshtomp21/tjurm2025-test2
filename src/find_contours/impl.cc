#include <opencv2/opencv.hpp>
#include <vector>

std::vector<cv::Mat> erode(const cv::Mat& src_erode, const cv::Mat& src_dilate) {
    cv::Mat gray_erode, gray_dilate;
    cv::Mat bin_erode, bin_dilate;
    cv::Mat dst_erode, dst_dilate;

    cv::cvtColor(src_erode, gray_erode, cv::COLOR_BGR2GRAY);
    cv::cvtColor(src_dilate, gray_dilate, cv::COLOR_BGR2GRAY);

    cv::threshold(gray_erode, bin_erode, 50, 255, cv::THRESH_BINARY);
    cv::threshold(gray_dilate, bin_dilate, 50, 255, cv::THRESH_BINARY);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    cv::erode(bin_erode, dst_erode, kernel, cv::Point(-1, -1), 1);

    cv::dilate(bin_dilate, dst_dilate, kernel, cv::Point(-1, -1), 1);

    return {dst_erode, dst_dilate};
}
