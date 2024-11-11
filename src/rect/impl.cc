#include <opencv2/opencv.hpp>
#include <vector>

std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    cv::Mat binary;
    cv::threshold(gray, binary, 50, 255, cv::THRESH_BINARY);

    cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Rect bounding_rect;
    cv::RotatedRect min_area_rect;
    if (!contours.empty()) {
        size_t largest_contour_index = 0;
        double max_area = 0;
        for (size_t i = 0; i < contours.size(); ++i) {
            double area = cv::contourArea(contours[i]);
            if (area > max_area) {
                max_area = area;
                largest_contour_index = i;
            }
        }
        
        bounding_rect = cv::boundingRect(contours[largest_contour_index]);
        min_area_rect = cv::minAreaRect(contours[largest_contour_index]);
    }

    return {bounding_rect, min_area_rect};
}
