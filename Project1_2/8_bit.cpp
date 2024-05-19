#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;

// ä�κ� ��Ʈ ��� �Լ�
int reduce_channel_bits(int value, int original_bits, int new_bits) {
    // ���� ��Ʈ ���� ���� ��Ʈ ����ũ ����
    int max_val = (1 << original_bits) - 1;  // ���� ��Ʈ ����ũ
    int new_max_val = (1 << new_bits) - 1;    // ��ҵ� ��Ʈ ����ũ

    // ��Ʈ�� ����ϰ� Ȯ���Ͽ� ��� ��Ʈ ����
    int reduced = (value * new_max_val) / max_val;
    int expanded = (reduced * max_val) / new_max_val;
    return expanded;
}

int main(int argc, char** argv) {
    // RGBA �̹��� �ε�
    Mat image = imread("C:\\Users\\parks\\Downloads\\2024S_MA_image_rgba.png", IMREAD_UNCHANGED);
    if (image.empty()) {
        printf("�̹����� ���� �� �����ϴ�.\n");
        return -1;
    }

    // ���ο� �̹����� ������ �迭 ����
    Mat reduced_image(image.rows, image.cols, CV_8UC3);

    // ��Ʈ ���
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            Vec4b pixel = image.at<Vec4b>(y, x);
            int r = pixel[0];
            int g = pixel[1];
            int b = pixel[2];
            // R, G, B ä���� ��� �� Ȯ��
            int r_reduced = reduce_channel_bits(r, 8, 3);  // 3��Ʈ�� ���
            int g_reduced = reduce_channel_bits(g, 8, 3);  // 3��Ʈ�� ���
            int b_reduced = reduce_channel_bits(b, 8, 2);  // 2��Ʈ�� ���

            reduced_image.at<Vec3b>(y, x) = Vec3b(r_reduced, g_reduced, b_reduced);
        }
    }

    // ��� �̹��� ����
    imwrite("C:\\Users\\parks\\Downloads\\2024S_MA_image_rgba_8bit.png", reduced_image);

    printf("�̹��� ��ȯ�� �Ϸ�Ǿ����ϴ�.\n");

    return 0;
}
