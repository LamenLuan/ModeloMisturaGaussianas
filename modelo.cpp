#include <iostream>
#include <list>
#include "Pixel.hpp"
#include "opencv2/opencv.hpp"

int main()
{
    int teste;
    bool temFrame = true;

    std::list<Pixel*> pixels;

    cv::VideoCapture video("../Videos/00005.mp4");
    cv::Mat frame, cinza;

    if (!video.isOpened())
    {
        std::cout << "Erro ao tentar abrir o arquivo"
                  << "\n";
        return -1;
    }

    video >> frame;
    if (frame.empty())
    {
        std::cout << "Erro ao tentar ler o primeiro frame"
                  << "\n";
        return -1;
    }

    cv::cvtColor(frame, cinza, cv::COLOR_BGR2GRAY);
    //Repeticao para a criacao de todos os pixels a partir da leitura do
    //primeiro frame.
    for (int i = 0; i < cinza.rows; i++)
    {
        for (int j = 0; j < cinza.cols; j++)
        {
            //ERRO NA CHAMADA DO DESTRUTOR DA CLASSE PIXEL AO TENTAR CRIAR UMA 
            //LISTA DE OBJETOS ESTÁTICOS.
            pixels.push_back(new Pixel((int) cinza.at<unsigned char>(i, j)));
        }
    }

    video.release();
    cv::destroyAllWindows();

    return 0;
}
