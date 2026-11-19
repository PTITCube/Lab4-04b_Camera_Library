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
        cdh.println("Camera: Loi the nho!");
        return;
    }

    cdh.println("Camera: San sang. Go 'capture' de chup anh.");
}

void loop() {
    if (cdh.available()) {
        String cmd = cdh.readStringUntil('\n');
        cmd.trim();
        if (cmd.length() == 0) return;

        if (cmd.equalsIgnoreCase("capture") || cmd.equalsIgnoreCase("photo")) {
            String path = "/photos/image_" + String(imageCount) + ".jpg";
            cdh.println("Camera: Dang chup " + path);

            if (camera.captureToFile(path.c_str())) {
                cdh.println("Camera: Da luu " + path);
                imageCount++;
            } else {
                cdh.println("Camera: Chup that bai.");
            }
        } else {
            cdh.printf("Camera: Lenh '%s' khong hop le. Go 'capture' de chup anh.\n", cmd.c_str());
        }
    }
}
