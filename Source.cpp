#include "Source.h"
#include <QString>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
data_picture* ReadPicture()
{
    data_picture* mas;
    char c;
    mas = new data_picture[372000];
    for (int i = 0; i < 372000; i++)
    {
        mas[i].picture = new double[784];
    }
    int load = 0;
    int num;

    QString fileName = "A_ZHandwrittenData.csv";
    QString currentDir = QDir::currentPath();
    QString filePath = currentDir + "/" + fileName;
    std::ifstream out(filePath.toStdString());
    std::ofstream check("mama.txt");
//    out.open(filePath.toStdString());
//    FILE* in = fopen("A_ZHandwrittenData.csv", "r+");
    if (out.is_open())
    {
        printf("Loading examples...\n");
        for (int k = 0; k < 372000; k++)
        {
//            fscanf(out, "%d,", &num);
            out >> num >> c;
            check << num << c;
            mas[k].letter = num;
            for (int i = 0; i < 783; i++)
            {
//                fscanf(out, "%d,", &num);
                out >> num >> c;
                mas[k].picture[i] = num / 255.;
            }
            out >> num;
            mas[k].picture[783] = num / 255.;
        }
        printf("Loading accept\n");

    }
    else
    {
        std::cout << "We cant open file" << std::endl;
        exit(1);
    }
    /*std::cout << mas[1].letter << std::endl*/

    return mas;
}
int Mama()
{
    data_picture* mas = NULL;
    Network T800;
    data_picture* our;
    T800.NetworkInit(3);
    int choise;
    while (1)
    {
        std::cout << "\nWelcome to Neural Network T-800\nConfiguration: 4 layers: 784-128-64-26\nMenu:\n1.Study\n2.Test\n3.Load Weight\n4.Recognite word\n5.Clear console" << std::endl;
        std::cin >> choise;
        switch (choise)
        {
        case 1:
//            Study(T800);
            T800.SaveWeight();
            break;
        case 2:
            mas = DataTest();
            Test(T800, mas);
        case 3:
            //T800.ReadWeight();
            break;
        case 4:
            /*our = OurData();
            Recognition(T800, our, 1);*/
//            ReadWord(T800);
            break;
        case 5:
            system("cls");
            break;
        default:
            exit(1);
        }
    }
}
string ReadWord(Network T800, string path)
{

//    MyMessageBox myMessageBox;
    string finalstr;
    pixel** mas;
    double* letterIMG = new double[784];
    double* img;
    int length;
    int common_interval=0;
    double average_interval = 0;
    int width;
    bool space = false;
    int PixelCounter = 0;
     const char* cstr = path.c_str();
    img = Convert(cstr, &length, &width);
    int all;
    int letter = 0;
    mas = Init(img, length, width);
    int k = 0;
    int fl = 1;
    int Xmax_pre=0, Xmin_pre, Ymax_pre, Ymin_pre;
    for (int j = 0; j < length; j++)
    {
        PixelCounter = 0;
        for (int i = 0; i < width; i++)
        {
            if (mas[i][j].letter == 1 && mas[i][j].id == 0)
            {
                k++;
                int Xmin = j;
                int Ymin = i;
                int Ymax = i;
                int Xmax = j;
                _paint(i, j, length, width, mas, k, &Xmax, &Xmin, &Ymax, &Ymin,&PixelCounter);
                if (PixelCounter > 90)
                {
                    letter++;
                    if (Xmax < length - 1)
                        Xmax += 2;
                    if (Ymax < width - 1)
                        Ymax += 2;
                    if (Xmin > 1)
                        Xmin -= 1;
                    if (Ymin > 1)
                        Ymin -= 1;
                    if (letter >= 2)
                    {
                        common_interval += -1*(Xmax_pre - Xmin);
                        //cout << "\nCommon:" << common_interval;
                        if (fl)
                            average_interval = common_interval / double(letter-1);
                        fl = 0;
                        if (abs(Xmax_pre - Xmin)*0.4 > average_interval)
                        {
                            //cout << "Space" << endl;
                            space = true;
                        }
                        else
                        {
                            average_interval = common_interval / double(letter-1);
                            space = false;
                            //cout << "Average interval: " << average_interval;
                        }
                        //cout <<"average:"<< average_interval;
                    }
                    //printf(" %d %d %d %d", Xmax, Xmin, Ymax, Ymin);
                    Xmin_pre = Xmin;
                    Ymin_pre = Ymin;
                    Ymax_pre = Ymax;
                    Xmax_pre = Xmax;
                    letterIMG = Centered(mas, Xmax, Xmin, Ymax, Ymin);
                    Recognition(T800, letterIMG, 1,space, finalstr);
                }
            }
        }
    }
    return finalstr;
}

void Test(Network object, data_picture* base)
{
    double lett;
    int rigth_coeff = 0, j = 0;
    double accuracy = 0;
    rigth_coeff = 0;
    for (int i = 0; i < 10000; i++)
    {
        object.DataInput(base[i].picture, 0);
        lett = object.ForwardFeed() - 1;
        if (lett == base[i].letter)
        {
            rigth_coeff++;
        }
    }
    accuracy = (rigth_coeff / 10000.) * 100.;
    std::cout << " Recognition accuracy : " << accuracy << " % " << std::endl;


}
//QString Study(Network object)
//{
//    double lett;
//    QString messageText ;
//    int rigth_coeff = 0, k = 0;
//    double accuracy = 0;
//    int right_answer = 0;
//    double lr = 0.15;
//    int size;
//    data_picture *mas;
//    mas = new data_picture[10000];
//    for (int i = 0; i < 10000; i++)
//    {
//        mas[i].picture = new double[16384];
//    }
//    std::vector<int> indexes(10000);
//    for (int i = 0; i < 10000; ++i) {
//        indexes[i] = i;
//    }
//    int count = 0;
//    while (accuracy < 10)
//    {
//        rigth_coeff = 0;
//        for (int j = 0; j < 1; j++)
//        {
//            std::random_device rd;
//            std::mt19937 rng(rd());
//            std::shuffle(indexes.begin(), indexes.end(), rng);
//            ReadPicture(0, mas, 0, 10000);
//            j += 1;
//            clock_t start, end;
//            start = clock();
//            for (int i : indexes)
//            {
//                object.DataInput(mas[i].picture, 1);
//                lett = object.ForwardFeed();
//                if (lett != mas[i].letter)
//                {
//                    object.BackPropogation(mas[i].letter);
//                    object.WeightsUpdater(0.15 * pow(0.9, (k / (20.))));
//                }
//                else
//                {
//                    right_answer++;
//                    rigth_coeff++;
//                }
//                count++;
//                if (count % 1000 == 0)
//                {
//                    cout << '\n' << right_answer;
//                    cout << '\n' << count;
//                    end = clock();
//                    cout << "\nTIME:" << end - start;
//                    right_answer = 0;
//                }
//            }
//        }
//        accuracy = (rigth_coeff / 387400.) * 100.;
////        std::cout << "Epoch" << k + 1 << "|| Recognition accuracy:" << accuracy << "%" << std::endl;
//         messageText += "Epoch: " + QString::number(accuracy) + "%" + "\n";

//        k++;
////        object.SaveWeight();
//        count = 0;
//    }
//    return messageText;
//}
QString Study(Network object, data_picture* base)
{
    QString messageText ;
    double lett;
    std::ofstream out;
    out.open("log.txt");
    int rigth_coeff = 0, j = 0;
    double accuracy = 0;
    int cnt = 0;
    double lr = 0.15;
    std::vector<int> indexes(372000);
    for (int i = 0; i < 372000; ++i) {
        indexes[i] = i;
    }
    int count = 0;
    while (accuracy < 5)
    {
//        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

        std::random_device rd;
        std::mt19937 rng(rd());
        std::shuffle(indexes.begin(), indexes.end(), rng);

        rigth_coeff = 0;
        clock_t start, end;
        start = clock();
        for (int i : indexes)
        {
            /*if(i % 10000 == 0)
                printf("%d\n",i);*/
            object.DataInput(base[i].picture, 1);
            lett = object.ForwardFeed();
//            out << "X = " << lett << " " << "0 = "<<base[i].letter;
            if (lett != base[i].letter)
            {
//                out << "cnt = " << cnt;
                //cout << lett << RED << " != " RESET << base[i].letter << " || " << endl;
                object.BackPropogation(base[i].letter);
                object.WeightsUpdater(0.15 * pow(0.9, (j / (20.))));
            }
            else
            {
                //cout << lett << GREEN << " == " RESET << base[i].letter << " || " << endl;
                cnt++;
                rigth_coeff++;
            }
            count++;
            if (count % 1000 == 0)
            {
                //cout << "Right in 1000 " << cnt << endl;
                //fprintf(log, "Right in 1000  -  %d\n", cnt);
                //cout << '\n' << count;
                out << "Right in 1000 " << cnt;
                end = clock();
                cnt = 0;
//                out << "cnt = " << cnt;
                out << " || TIME: " << (end - start) / 60000. << "min" << endl;
//                start = clock();


            }
        }

        accuracy = (rigth_coeff / 372000.) * 100.;

        out << "Epoch" << j + 1 << "|| Recognition accuracy:" << accuracy << "%" << std::endl; //<< "    /*Time: " << hours << ":" << minutes << ":" << seconds << std::endl;*/

        j++;
    }
    messageText += "Accuracy: " + QString::number(accuracy) + "%" + "\n";
    return messageText;
}
data_picture* OurData()
{
    //char* input_file = ".bmp";
    data_picture* mas = new data_picture[15];
    for (int i = 0; i < 1; i++)
    {
        mas[i].picture = new double[784];
    }
    for (int i = 1; i < 2; i++)
    {
        std::string path;
        path = to_string(i) + ".bmp";
        CImg<unsigned char> image(path.c_str());
        int j = 0;
        cimg_forXY(image, x, y) {
            unsigned char red = image(x, y, 0);
            unsigned char green = image(x, y, 1);
            unsigned char blue = image(x, y, 2);
            unsigned char inverted_pixel_value = 255 - (red + green + blue) / 3;
            mas[i - 1].letter = i;
            mas[i - 1].picture[j] = static_cast<double>(inverted_pixel_value) / 255.;
            //cout << mas[i - 1].picture[j]<<",";
            j++;
        }
    }
    return mas;
}
data_picture* DataTest()
{
    data_picture* mas;
    mas = new data_picture[10000];
    for (int i = 0; i < 10000; i++)
    {
        mas[i].picture = new double[784];
    }
    int load = 0;
    int num;
    FILE* in = fopen("Test.csv", "r+");
    if (in != NULL)
    {
        printf("Loading examples...\n");
        for (int k = 0; k < 10000; k++)
        {
            fscanf(in, "%d,", &num);
            mas[k].letter = num;
            for (int i = 0; i < 784; i++)
            {
                fscanf(in, "%d,", &num);
                mas[k].picture[i] = num / 255.;
            }

        }
    }
    else
    {
        std::cout << "We cant open file" << std::endl;
    }
    /*std::cout << mas[1].letter << std::endl*/

    return mas;
}

void Recognition(Network object, double* mas, int size, bool space,string &finalstr)
{
    double predict;
    char symbol = 0;
    int right = 0;
    object.DataInput(mas, 0);
    predict = object.ForwardFeed();
    if (space)
//        currentMessage+=" ";  // Вместо std::cout << " ";
        finalstr += ' ';
    symbol = predict + 65;
    finalstr += symbol;  // Вместо std::cout << symbol;
}


