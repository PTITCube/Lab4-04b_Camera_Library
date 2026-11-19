/**
 * VÍ DỤ 4-4b: CHỤP ẢNH & LƯU THẺ NHỚ BẰNG THƯ VIỆN PTITCUBE
 */
#include <Arduino.h>
#include <PTITCube.h>

PTIT_CDH cdh;
PTIT_Camera camera;
int imageCount = 0;

void setup() {
    cdh.begin(115200);

    if (!camera.init(255, 255)) {
        cdh.println("Camera: Loi: Khong the khoi tao the nho!");
        return;
    }

    cdh.println("Camera: Ready. Nhap 'p' tren Serial de chup anh.");
}

void loop() {
    if (cdh.available() > 0) {
        char command = cdh.read();

        if (command == 'p' || command == 'P') {
            String path = "/photos/image_" + String(imageCount) + ".jpg";
            cdh.println("Camera: Dang chup: " + path);

            if (camera.captureToFile(path.c_str())) {
                cdh.println("Camera: Da luu anh: " + path);
                imageCount++;
            } else {
                cdh.println("Camera: Chup anh that bai.");
            }
        }

        while (cdh.available() > 0) {
            char trailing = cdh.peek();
            if (trailing != '\r' && trailing != '\n') break;
            cdh.read();
        }
    }
}
