#include"Convert.h"
//using namespace std;
using namespace cimg_library;
pixel** Init(double* img, int length, int width)
{
    int j = 0;
    pixel** mas = new pixel * [width];
    for (int i = 0; i < width; i++)
    {
        mas[i] = new pixel[length];
    }
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < length; j++) {
            mas[i][j].black = img[i * length + j];
            if (mas[i][j].black > 0)
            {
                mas[i][j].letter = 1;
            }
            else
            {
                mas[i][j].letter = 0;
            }
            mas[i][j].id = 0;
        }
    }
    return mas;
}
void _paint(int i, int j, int width, int height, pixel** mas, int ID, int* Xmax, int* Xmin, int* Ymax, int* Ymin, int *PixelCounter) {
    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(i, j));
    int PixelsCounter = 0;
    while (!stack.empty()) {
        std::pair<int, int> current = stack.top();
        stack.pop();
        i = current.first;
        j = current.second;
        if (mas[i][j].id == 0 && mas[i][j].black > 0) {
            (* PixelCounter)++;
            mas[i][j].id = ID;
            mas[i][j].letter = 1;
            if ((*Xmax) < j) (*Xmax) = j;
            if ((*Ymax) < i) (*Ymax) = i;
            if ((*Xmin) > j) (*Xmin) = j;
            if ((*Ymin) > i) (*Ymin) = i;
            if (i < height - 1) stack.push(std::make_pair(i + 1, j));
            if (i > 0) stack.push(std::make_pair(i - 1, j));
            if (j < width - 1) stack.push(std::make_pair(i, j + 1));
            if (j > 0) stack.push(std::make_pair(i, j - 1));
        }
    }
}

CImg<unsigned char> createBMPFromData(double* data, int width, int height) {
    CImg<unsigned char> image(width, height, 1, 3);

    int i = 0;
    cimg_forXY(image, x, y) {
        double normalized_value = data[i];
        unsigned char pixel_value = static_cast<unsigned char>((1.0 - normalized_value) * 255.0);

        image(x, y, 0) = pixel_value; // ������� �����
        image(x, y, 1) = pixel_value; // ������� �����
        image(x, y, 2) = pixel_value; // ����� �����4

        i++;
    }

    return image;
}
double* Centered(pixel** mas, int Xmax, int Xmin, int Ymax, int Ymin)
{
    double* mas2 = new double[784];
    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            mas2[i * 28 + j] = 0;
        }

    }
    double* letter = new double[(Ymax - Ymin) * (Xmax - Xmin)];
    for (int i = 0; i < Ymax - Ymin; i++)
    {
        for (int j = 0; j < Xmax - Xmin; j++)
        {
            letter[i * (Xmax - Xmin) + j] = mas[Ymin + i][Xmin + j].black;
        }
    }
    //printf("\n%d %d %d %d\n", Xmax ,Xmin, Ymax , Ymin);
    CImg<unsigned char> bmpImage = createBMPFromData(letter, Xmax - Xmin, Ymax - Ymin);
    bmpImage.save("clipped_letter.bmp");

    CImg<unsigned char> image("clipped_letter.bmp");
    int maxWidth = 20, maxLength = 20;
    if (image.width() > maxWidth || image.height() > maxLength)
    {

        const int kernel_size = 3; // ������ ���� ����������
        const int iterations = 1; // ���������� �������� ���������� (���������� �����)
        const unsigned char foreground_color = 0; // ���� ��������� ����� (������)

        for (int iter = 0; iter < iterations; iter++) {
            image.erode(kernel_size, kernel_size, foreground_color);
        }

        // ���������� ��������� �����
        image.blur(1.5);
        image.save("clipped_bold_letter_image.bmp");

        CImg<unsigned char> image("clipped_bold_letter_image.bmp");


        //printf("\n%d %d\n", image.width(), image.height());

        CImg<unsigned char> resized_image = image.resize(20, 20);
        resized_image.save("resized_image.bmp");




        letter = Convert("resized_image.bmp", &maxLength, &maxWidth);
        Xmax = 20;
        Xmin = 0;
        Ymax = 20;
        Ymin = 0;

    }

    int xborder = (28 - (Xmax - Xmin)) / 2.;
    int yborder = (28 - (Ymax - Ymin)) / 2.;

    for (int i = 0; i < Ymax - Ymin; i++)
    {
        for (int j = 0; j < Xmax - Xmin; j++)
        {
            mas2[(i + yborder) * 28 + j + xborder] = letter[i * (Xmax - Xmin) + j];
        }
    }

    CImg<unsigned char> Result = createBMPFromData(mas2, 28, 28);
    Result.save("Result.bmp");
    return mas2;
}

double* Convert(const char* file, int* length, int* width)
{
    const char* input_file = file; // �������� �� ��� ������ �������� ����� BMP
    const char* output_file = "output.txt"; // ������� ��� ��� ��������� ���������� �����
    double* mas;
    CImg<unsigned char> image(input_file);




    (*length) = image.width();
    (*width) = image.height();
    mas = new double[(*width) * (*length)];
    int i = 0;
    double x0 = GetBackground(file,0,0 );
    double x1 = GetBackground(file, (*length)-1, 0);
    double y0 = GetBackground(file, 0, (*width)-1);
    double y1 = GetBackground(file, (*length) - 1, (*width) - 1);

    double background = (x0 + x1 + y0 + y1) / 4.;


    cimg_forXY(image, x, y) {
        unsigned char red = image(x, y, 0);
        unsigned char green = image(x, y, 1);
        unsigned char blue = image(x, y, 2);
        unsigned char inverted_pixel_value = 255 - (red + green + blue) / 3;
        double normalized_value = static_cast<double>(inverted_pixel_value) / 255.0;

        if (normalized_value <= (background+0.3))
            mas[i] = 0;
        else
            mas[i] = normalized_value;


        i++;
    }


    return mas;
}
double GetBackground(const char* filename, int x, int y)
{
    CImg<unsigned char> image(filename);

    unsigned char red = image(x, y, 0);
    unsigned char green = image(x, y, 1);
    unsigned char blue = image(x, y, 2);
    unsigned char inverted_pixel_value = 255 - (red + green + blue) / 3;
    double value = static_cast<double>(inverted_pixel_value) / 255.0;
    return value;
}



