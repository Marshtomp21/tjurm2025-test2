#include "impls.h"
#include <unordered_map>
#include <opencv2/opencv.hpp>

std::unordered_map<int, cv::Rect> roi_color(const cv::Mat& input) {
    /**
     * INPUT: 一张彩色图片
     * OUTPUT: 一个 unordered_map, key 为颜色(Blue: 0, Green: 1, Red: 2), value 为对应颜色的矩形区域(cv::Rect)
     */

    std::unordered_map<int, cv::Rect> res;

    // 1. 将 input 转换为灰度图像
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    // 2. 对灰度图像进行二值化
    cv::Mat binarized;
    cv::threshold(gray, binarized, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

    // 3. 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binarized, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 4. 对每个轮廓，计算其外接矩形
    for (size_t i = 0; i < contours.size(); ++i) {
        // 获取当前轮廓的外接矩形
        cv::Rect rect = cv::boundingRect(contours[i]);

        // 5. 提取 ROI 区域并计算颜色
        cv::Mat roi = input(rect);  // 获取矩形区域

        // 计算该区域的颜色平均值
        cv::Scalar meanColor = cv::mean(roi);

        // 6. 根据颜色计算其对应的颜色类别
        if (meanColor[0] > meanColor[1] && meanColor[0] > meanColor[2]) {
            // 蓝色区域
            res[0] = rect;
        } else if (meanColor[1] > meanColor[0] && meanColor[1] > meanColor[2]) {
            // 绿色区域
            res[1] = rect;
        } else if (meanColor[2] > meanColor[0] && meanColor[2] > meanColor[1]) {
            // 红色区域
            res[2] = rect;
        }
    }

    return res;
}
