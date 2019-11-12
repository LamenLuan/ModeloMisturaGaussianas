#include <iostream>
#include <list>
#include "Pixel.hpp"
#include "opencv2/opencv.hpp"

int main()
{
    unsigned int contador = 1;

    int teste;
    bool temFrame = true;

    std::list<Pixel*> pixels;
    std::list<Pixel*>::iterator atual;
    
    cv::VideoCapture video("../Videos/00005.mp4");
    cv::Mat frame, cinza, resultado;

    if (!video.isOpened())
    {
        std::cout << "Erro ao tentar abrir o arquivo"
            << "\n";
        return -1;
    }
    
    //A matriz frame recebe um frame do video.
    video >> frame;
    if (frame.empty())
    {
        std::cout << "Erro ao tentar ler o primeiro frame"
            << "\n";
        return -1;
    }

    //A matriz "cinza" recebe o frame convertido para grayscale.
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

        for (size_t i = 0; i < frame.rows; i++)
        {
            for (size_t j = 0; j < frame.cols ; j++)
            {
                std::cout << (*atual)->probabilidadeDoPixel(cinza.at<unsigned char>(i, j)) << "\n";
                atual++;
            }
            
        }

        for (size_t i = 0; i < frame.rows; i++)
        {
            for (size_t j = 0; j < frame.cols; j++)
            {
                //FAZER if
            }
        }

        // Abertura do video
        cv::VideoWriter video("../Videos/Querido_fruto_do_nosso_esforço.avi",
                              video.fourcc('M', 'J', 'P', 'G'), 10,
                              cv::Size(frame.cols, frame.rows));

        // Escrita de frames em no video 'Querido_fruto_do_nosso_esforço.avi'
        video.write(frame);

        // Print do resultado da escrita do video
        //imshow("Frame", frame);
        //char c = (char)cv::waitKey(1);
        //if (c == 27) // pause para print da imagem
          //  break;

        atual = pixels.begin();
        std::cout << "Frame: " << contador++ << "\n";
        for (int i = 0; i < cinza.rows; i++)
        {
            for (int j = 0; j < cinza.cols; j++)
            {
                if(i == 250 && j == 322)
                {
                    for (int k = 0; k < Pixel::M_QUANTIDADE_DISTRIBUICOES; k++)
                    {
                        std::cout << ((*atual)->m_mistura + k)->
                            getMedia() << " ";
                        std::cout << ((*atual)->m_mistura + k)->
                            getDesvioPadrao() << " ";
                        std::cout << ((*atual)->m_mistura + k)->
                            getPeso() << "\n";
                    }
                
                    std::cout << (unsigned int) cinza.at<unsigned char>(i, j)
                        << "\n";

                    (*atual)->leNovoPixel(cinza.at<unsigned char>(i,j));
                    
                    for(int k = 0; k < Pixel::M_QUANTIDADE_DISTRIBUICOES; k++)
                    {
                        std::cout << ((*atual)->m_mistura + k)->getMedia() 
                            << " ";
                        std::cout << ((*atual)->m_mistura + k)->
                            getDesvioPadrao() << " ";
                        std::cout << ((*atual)->m_mistura + k)->getPeso() 
                            << "\n";
                    }
                    std::cout << "\n";
                }
                else
                {
                    (*atual)->leNovoPixel(cinza.at<unsigned char>(i, j));
                }
                atual++;
            }
        }
                   
    }
    
    video.release();
    cv::destroyAllWindows();

    return 0;
}