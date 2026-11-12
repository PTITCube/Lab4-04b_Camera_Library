/**
 * @file 1_Capture_To_SD.cpp
 * @brief Ví dụ cơ bản về khởi tạo Camera và chụp ảnh lưu vào thẻ MicroSD.
 * 
 * Mô tả:
 * - Khởi tạo module ESP32-CAM và thẻ nhớ MicroSD.
 * - Sau mỗi 10 giây, camera sẽ chụp một bức ảnh và lưu vào thẻ nhớ với tên 
 *   tuần tự (VD: /photos/image_0.jpg, /photos/image_1.jpg).
 * 
 * Lưu ý: 
 * - Đảm bảo chân CS của thẻ nhớ đã được cấu hình đúng (Mặc định: GPIO 13).
 */

#include <Arduino.h>

#include <PTITCube.h>

PTIT_CDH cdh;

PTIT_Camera camera;
int imageCount = 0;

void setup() {
    cdh.begin(115200);
    delay(2000);
    
    cdh.println("\n--- CAMERA READY ---");

    if (!camera.init(255, 255)) {
        cdh.println("[Loi] Khong the khoi tao the nho!");
        while (1) {
            delay(1000);
        }
    }

    cdh.println("[OK] Nhap 'p' de chup anh.");
}

void loop() {
    if (cdh.available() > 0) {
        char command = cdh.read();

        if (command == 'p' || command == 'P') {
            String path = "/photos/image_" + String(imageCount) + ".jpg";
            cdh.println("[Camera] Dang chup: " + path);

            if (camera.captureToFile(path.c_str())) {
                cdh.println("[OK] Da luu anh: " + path);
                imageCount++;
            } else {
                cdh.println("[Loi] Chup anh that bai.");
            }
        }

        // Consume CR/LF from the same cdh Monitor command.
        while (cdh.available() > 0) {
            char trailing = cdh.peek();
            if (trailing != '\r' && trailing != '\n') {
                break;
            }
            cdh.read();
        }
    }
}
