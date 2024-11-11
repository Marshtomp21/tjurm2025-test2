#include "impls.h"

cv::Mat my_resize(const cv::Mat& input, float scale) {
    int new_rows = input.rows * scale, new_cols = input.cols * scale;

    cv::Mat output = cv::Mat::zeros(new_rows, new_cols, input.type());

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            int orig_i = static_cast<int>(i / scale);
            int orig_j = static_cast<int>(j / scale);

            if (input.channels() == 1) {
                output.at<uchar>(i, j) = input.at<uchar>(orig_i, orig_j);
            } else {
                for (int c = 0; c < input.channels(); ++c) {
                    output.at<cv::Vec3b>(i, j)[c] = input.at<cv::Vec3b>(orig_i, orig_j)[c];
                }
            }
        }
    }

    return cv::Mat::zeros(new_rows, new_cols, input.type());
}
