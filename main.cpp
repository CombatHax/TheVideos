#include <iostream>
#include <fstream>
#include <cmath>

void writeByte(char byte, std::fstream* file) {
    (*file) << byte;
}
void writeInt(int num, std::fstream* file) {
    (*file) << (char)((num >> 24) & 0xff) << (char)((num >> 16) & 0xff) << (char)((num >> 8) & 0xff) << (char)(num & 0xff);
}
void writeShort(short num, std::fstream* file) {
    writeByte((char)(num >> 8), file);
    writeByte((char)(num & 0xff), file);
}
void writePixel(unsigned short x, unsigned short y, unsigned short color, std::fstream* file) {
    writeShort(0, file);
    writeShort(x, file);
    writeShort(y, file);
    writeShort(color, file);
}
void writeDisplay(std::fstream* file) {
    writeInt(0x10000, file);
    writeInt(0, file);
}

int main() {
    std::fstream file("testing.bin", std::ios::out | std::ios::binary);
    unsigned short width = 400;
    unsigned short height = 400;
    unsigned short fps = 60;
    unsigned short testColor = 0x0f0;
    writeShort(width, &file);
    writeShort(height, &file);
    writeShort(fps, &file);
    for(short x = -20; x < 40; x++) {
        for(short y = -20; y < 40; y++) {
            if(sqrt(x * x + y * y) <= 20) {
                writePixel(x + 20, y + 20, 0x00f, &file);
            }
        }
    }
    writeDisplay(&file);
    return 0;
}