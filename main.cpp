#include <iostream>
#include <fstream>

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

int main() {
    std::fstream file("testing.bin", std::ios::out | std::ios::binary);
    unsigned short width = 400;
    unsigned short height = 400;
    unsigned short fps = 60;
    unsigned short testColor = 0x0f0;
    writeShort(width, &file);
    writeShort(height, &file);
    writeShort(fps, &file);

    writeShort(0, &file);
    writeShort(10, &file);
    writeShort(10, &file);
    writeShort(0x0f0, &file);
    writeShort(0x1, &file);
    writeShort(0, &file);
    writeInt(0, &file);
    return 0;
}