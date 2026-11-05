# Lab4-04b_Camera_Library

**Chụp ảnh bằng thư viện PTITCube và lưu vào thẻ MicroSD trên OBC**

Bài thực hành thuộc Lab4 (Sensor) trong hệ thống CubeSat-LMS.

Sử dụng thư viện `PTITCube` để giao tiếp với module ESP32-CAM qua UART2, gửi lệnh chụp ảnh và lưu trực tiếp tệp ảnh JPEG vào thẻ MicroSD trên máy tính nhúng OBC.

### Sơ đồ kết nối:
- **ESP32-CAM GPIO 14 (TX2)** -> **ESP32 GPIO 16 (RX2)**
- **ESP32-CAM GPIO 15 (RX2)** -> **ESP32 GPIO 17 (TX2)**
- **GND** -> **GND**
- **5V** -> **5V**
