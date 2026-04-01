# 图像旋转作业

## 作业要求：
将 24 位真彩色 .bmp 图像文件，顺时针旋转 90 度。

提交可执行程序 rotatebmp.exe 和相应的.cpp 源代码。 

可执行程序名：rotatebmp 

用法：rotatebmp src.bmp dest.bmp (文件名可变) 

生成的 dest.bmp 是从 src.bmp 顺时针旋转 90 度得到的。

通过这次作业，我练习了二进制文件的操作方法，学习了有关bmp文件格式的有关知识

## 我的代码

```cpp
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#pragma pack(1)

struct BITMAPFILEHEADER {
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;
};

struct BITMAPINFOHEADER {
    unsigned int   biSize;
    int            biWidth;
    int            biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
};

#pragma pack()

int main(int argc, char* argv[]) {
    //处理错误输入
    if (argc != 3) {
        cerr << "用法: rotatebmp src.bmp dest.bmp" << endl;
        return 1;
    }
    
    const char* inputFileName = argv[1];
    const char* outputFileName = argv[2];
    
    ifstream input(inputFileName, ios::binary);
    //处理文件无法打开的情况
    if (!input) {
        cerr << "无法打开输入文件: " << inputFileName << endl;
        return 1;
    }
    
    //文件头和信息头
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    
    input.read(reinterpret_cast<char*>(&fileHeader), sizeof(BITMAPFILEHEADER));
    input.read(reinterpret_cast<char*>(&infoHeader), sizeof(BITMAPINFOHEADER));
    
    if (fileHeader.bfType != 0x4D42) {   // "BM"
        std::cerr << "错误: 不是 BMP 文件" << std::endl;
        return 1;
    }
    if (infoHeader.biBitCount != 24) {
        std::cerr << "错误: 仅支持 24 位真彩色 BMP" << std::endl;
        return 1;
    }
    
    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    //每行的字节数
    int bytesPerLine = (width * 3 + 3) / 4 * 4;
    //图像区域总大小
    int dataSize = bytesPerLine * height;
    
    vector<unsigned char> srcData(dataSize);
    input.seekg(fileHeader.bfOffBits, ios::beg);
    input.read(reinterpret_cast<char*>(srcData.data()), dataSize);
    input.close();
    
    //构建新文件
    int newWidth  = height;
    int newHeight = width;
    int newBytesPerLine = (newWidth * 3 + 3) / 4 * 4;
    int newDataSize     = newBytesPerLine * newHeight;
    vector<unsigned char> dstDate(newDataSize, 0);
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            //对于原图中的y列x行像素,变成新的中的
            //注意！由于bmp是上下翻转的，所以这里应该用的是逆时针旋转的代码！！！！！！！
            int locate = y * bytesPerLine + x * 3;
            int newX = y;
            int newY = width - 1 - x;
            int newLocate = newY * newBytesPerLine + newX * 3;
            dstDate[newLocate] = srcData[locate];
            dstDate[newLocate + 1] = srcData[locate + 1];
            dstDate[newLocate + 2] = srcData[locate + 2];
        }
    }
    
    //输出新文件
    BITMAPFILEHEADER newFileHeader = fileHeader;
    BITMAPINFOHEADER newInfoHeader = infoHeader;
    newInfoHeader.biWidth = newWidth;
    newInfoHeader.biHeight = newHeight;
    newInfoHeader.biSizeImage = newDataSize;
    newFileHeader.bfSize = fileHeader.bfOffBits + newDataSize;
    
    ofstream output(outputFileName, ios::binary);
    if (!output){
        cerr << "无法创建输出文件: " << endl;
        return 1;
    }
    
    output.write(reinterpret_cast<char*>(&newFileHeader), sizeof(newFileHeader));
    output.write(reinterpret_cast<char*>(&newInfoHeader), sizeof(newInfoHeader));
    output.write(reinterpret_cast<char*>(dstDate.data()), newDataSize);
    output.close();
    
    std::cout << "旋转成功！输出文件: " << outputFileName << std::endl;
    return 0;
}
```
