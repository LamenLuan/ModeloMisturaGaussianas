#include <iostream>
#include <list>
#include "Pixel.hpp"
#include "opencv2/opencv.hpp"

int main()
{
    int teste;
    bool temFrame = true;

    std::list<Pixel*> pixels;
    std::list<Pixel*>::iterator atual;
    
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

    //Repetição para a leitura de novos frames e atualização do modelo ao ler
    //seus valores.
    while(temFrame)
    {
        video >> frame;

        if(frame.empty())
        {
            temFrame = false;
            continue;
        }
        
        cv::cvtColor(frame, cinza, cv::COLOR_BGR2GRAY);
        
        atual = pixels.begin();
        for (int i = 0; i < cinza.rows; i++)
        {
            for (int j = 0; j < cinza.cols; j++)
            {
                for(int k = 0; k < Pixel::M_QUANTIDADE_DISTRIBUICOES; k++)
                {
                    std::cout << ((*atual)->m_mistura + k)-> getMedia() << " ";
                    std::cout << ((*atual)->m_mistura + k)-> getDesvioPadrao() 
                              << " ";
                    std::cout << ((*atual)->m_mistura + k)-> getPeso() << "\n";
                }
                
                std::cout << (unsigned int) cinza.at<unsigned char>(i, j)
                          << "\n";

                (*atual)->leNovoPixel(cinza.at<unsigned char>(i,j));
                
                for(int k = 0; k < Pixel::M_QUANTIDADE_DISTRIBUICOES; k++)
                {
                    std::cout << ((*atual)->m_mistura + k)-> getMedia() << " ";
                    std::cout << ((*atual)->m_mistura + k)-> getDesvioPadrao() 
                              << " ";
                    std::cout << ((*atual)->m_mistura + k)-> getPeso() << "\n";
                }
                atual++;
            }
        }
                   
    }
    
    video.release();
    cv::destroyAllWindows();

    return 0;
}
