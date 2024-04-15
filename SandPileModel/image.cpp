#include "image.h"


void MakingImage(Matrix& matriks, Arguments& parameters,int number_of_bmp) {

  const int padding = (4 - (matriks.max_width / 2 + matriks.max_width % 2) % 4) % 4;
  const int HeaderSize = 14;
  const int InformationSize = 40;
  const int PaletteSize = 20;
  uint64_t bmp_size = HeaderSize + InformationSize + PaletteSize;
  uint64_t file_size = HeaderSize + InformationSize + PaletteSize + matriks.max_width * matriks.max_heigh / 2 + matriks.max_width * matriks.max_heigh % 2;
  std::ofstream file;
  const char *a = parameters.output_file_name;
  std::string filename = static_cast<std::string>(a) + "/bmpshka" + std::to_string(number_of_bmp) + ".bmp";
  file.open(filename, std::ios::binary);

  if (!file.is_open()) {
    std::cerr << "FILE NOT CREATED";
    return;
  }
  unsigned char BmpFileHeader[HeaderSize]{};
  BmpFileHeader[0] = 'B';
  BmpFileHeader[1] = 'M';
  BmpFileHeader[2] = file_size;
  BmpFileHeader[3] = file_size >> 8;
  BmpFileHeader[4] = file_size >> 16;
  BmpFileHeader[4] = file_size >> 24;
  BmpFileHeader[10] = (unsigned char) (bmp_size);
  unsigned char BmpInfoHeader[InformationSize]{};

  BmpInfoHeader[0] = (unsigned char) (InformationSize);
  BmpInfoHeader[4] = (unsigned char) (matriks.max_width);
  BmpInfoHeader[5] = (unsigned char) (matriks.max_width >> 8);
  BmpInfoHeader[6] = (unsigned char) (matriks.max_width >> 16);
  BmpInfoHeader[7] = (unsigned char) (matriks.max_width >> 24);
  BmpInfoHeader[8] = (unsigned char) (matriks.max_heigh);
  BmpInfoHeader[9] = (unsigned char) (matriks.max_heigh >> 8);
  BmpInfoHeader[10] = (unsigned char) (matriks.max_heigh >> 16);
  BmpInfoHeader[11] = (unsigned char) (matriks.max_heigh >> 24);
  BmpInfoHeader[12] = (unsigned char) (1);
  BmpInfoHeader[14] = (unsigned char) (4);
  BmpInfoHeader[32] = (unsigned char) (5);
  file.write(reinterpret_cast<char *>(BmpFileHeader), HeaderSize);
  file.write(reinterpret_cast<char *>(BmpInfoHeader), InformationSize);
  //white purple green yellow black
  unsigned char palette[PaletteSize] = {0xff, 0xff, 0xff, 0, 0, 0xff, 0, 0, 0, 0xff, 0xff, 0, 0xff, 0, 0xff, 0, 0, 0, 0, 0};
  file.write(reinterpret_cast<char *>(palette), PaletteSize);

  uint8_t pix1;
  uint8_t pix2;
  uint8_t pixel;

  for (int i = matriks.max_width - 1; i >= 0; i--) {
    for (int j = 0; j < matriks.max_heigh; j += 2) {
      if ((j + 1 >= matriks.max_heigh)) {
        if (matriks.matrix[i][j] > 4) {
          pix1 = 4;
        } else {
          pix1 = matriks.matrix[i][j];
        }
        pix2 = 0;
      } else {
        if (matriks.matrix[i][j] >= 4) {
          pix1 = 4;
        } else {
          pix1 = matriks.matrix[i][j];
        }
        if (matriks.matrix[i][j + 1] >= 4) {
          pix2 = 4;
        } else {
          pix2 = matriks.matrix[i][j + 1];
        }
      }
      pixel = (pix1 << 4) + pix2;
      file << pixel;
    }
    for (int t = 0; t < padding; t++) {
      file << static_cast<char>(0);
    }
  }

  file.close();
}
