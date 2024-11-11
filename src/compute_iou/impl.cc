#include <opencv2/opencv.hpp>
#include <algorithm>

float compute_iou(const cv::Rect& a, const cv::Rect& b) {
    int x_left = std::max(a.x, b.x);
    int y_top = std::max(a.y, b.y);
    int x_right = std::min(a.x + a.width, b.x + b.width);
    int y_bottom = std::min(a.y + a.height, b.y + b.height);

    int intersection_width = x_right - x_left;
    int intersection_height = y_bottom - y_top;
    int intersection_area = (intersection_width > 0 && intersection_height > 0) ? 
                            intersection_width * intersection_height : 0;


    int area_a = a.width * a.height;
    int area_b = b.width * b.height;

    int union_area = area_a + area_b - intersection_area;

    return (union_area > 0) ? static_cast<float>(intersection_area) / union_area : 0.0f;
}
