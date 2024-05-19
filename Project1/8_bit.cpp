#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// RGBA �ȼ� ����ü ����
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} PixelRGBA;

// ��Ʈ ��� �Լ� ����
uint8_t reduce_channel_bits(uint8_t value, int original_bits, int new_bits) {
    // ���� ��Ʈ ���� ���� ��Ʈ ����ũ ����
    uint8_t max_val = (1 << original_bits) - 1;  // ���� ��Ʈ ����ũ
    uint8_t new_max_val = (1 << new_bits) - 1;   // ��ҵ� ��Ʈ ����ũ

    // ��Ʈ�� ����ϰ� Ȯ���Ͽ� ��� ��Ʈ ����
    uint16_t reduced = (uint16_t)value * new_max_val / max_val;
    uint16_t expanded = (uint16_t)reduced * max_val / new_max_val;
    return (uint8_t)expanded;
}

// �̹��� ũ��
#define IMAGE_WIDTH  100
#define IMAGE_HEIGHT 100

int main() {
    // RGBA �̹��� ������
    PixelRGBA rgba_image[IMAGE_WIDTH][IMAGE_HEIGHT] = { 0 };

    // PNG ���� ���
    const char* image_path = "C:\\Users\\parks\\Downloads\\2024S_MA_image_rgba.png";

    // �̹��� ���� �б� �� RGBA �̹����� ��ȯ (�� �κ��� ���� �б� �� RGBA�� ��ȯ�ϴ� �ڵ�� ��ü�Ǿ�� �մϴ�)

    // ��Ʈ ��� �� �̹��� ��ȯ
    for (int x = 0; x < IMAGE_WIDTH; x++) {
        for (int y = 0; y < IMAGE_HEIGHT; y++) {
            // �̹��� �ȼ� RGBA �� �б�
            uint8_t r = rgba_image[x][y].r;
            uint8_t g = rgba_image[x][y].g;
            uint8_t b = rgba_image[x][y].b;
            uint8_t a = rgba_image[x][y].a;

            // R, G, B ä���� ��� �� Ȯ��
            uint8_t r_reduced = reduce_channel_bits(r, 8, 3);  // 3��Ʈ�� ���
            uint8_t g_reduced = reduce_channel_bits(g, 8, 3);  // 3��Ʈ�� ���
            uint8_t b_reduced = reduce_channel_bits(b, 8, 2);  // 2��Ʈ�� ���

            // ���ο� RGB ���� ���
            uint8_t rgb_reduced = (r_reduced << 5) | (g_reduced << 2) | b_reduced;  // �� ��Ʈ�� ������ ��ġ�� �̵�

            // �̹����� ���ο� �� �Ҵ�
            rgba_image[x][y].r = r_reduced;
            rgba_image[x][y].g = g_reduced;
            rgba_image[x][y].b = b_reduced;
        }
    }

    // ��ȯ�� �̹��� ����
    FILE* output_file;
    if (fopen_s(&output_file, "converted_image.bin", "wb") != 0) {
        printf("Error: Could not open output file.\n");
        return 1;
    }


    // �̹��� �����͸� ���Ͽ� ����
    for (int x = 0; x < IMAGE_WIDTH; x++) {
        for (int y = 0; y < IMAGE_HEIGHT; y++) {
            fwrite(&rgba_image[x][y], sizeof(PixelRGBA), 1, output_file);
        }
    }

    // ���� �ݱ�
    fclose(output_file);

    // ��ȯ�� �̹��� ���
    // ���⿡ �̹����� ����ϴ� �ڵ� �߰�
    // ���� ���, �ȼ� ���� ȭ�鿡 ����ϴ� ����� ������ �����ϴ�.
    for (int y = 0; y < IMAGE_HEIGHT; y++) {
        for (int x = 0; x < IMAGE_WIDTH; x++) {
            printf("(%d, %d, %d, %d) ", rgba_image[x][y].r, rgba_image[x][y].g, rgba_image[x][y].b, rgba_image[x][y].a);
        }
        printf("\n");
    }

    return 0;
}
