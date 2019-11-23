#include <iostream>
#include <list>
#include "Pixel.hpp"
#include "opencv2/opencv.hpp"

void iniciaModelo(cv::Mat &frameVideo, std::list<Pixel *>& frameModelo);

int main()
{

    int teste;
    bool temFrame = true;

    std::list<Pixel*> frameModelo;
    std::list<Pixel*>::iterator atual;
    
    cv::Mat frame, cinza, resultado;
    cv::VideoCapture video("../Videos/teste.mts");
    cv::VideoWriter videoSaida;

    if (!video.isOpened())
    {
        std::cout << "Erro ao tentar abrir o arquivo" << "\n";
        return -1;
    }
  
    //A matriz "frame" recebe um frame do video aberto.
    video >> frame;

    if (frame.empty() )
    {
        std::cout << "Erro ao tentar ler o primeiro frame" << "\n";
        return -1;
    }

    //A matriz "cinza" recebe o frame convertido para grayscale.
    cv::cvtColor(frame, cinza, cv::COLOR_BGR2GRAY);
    frame.release();

    //Leitura do "cinza" e criacao do modelo de cada pixel correspondente.
    iniciaModelo(cinza, frameModelo);
    
    //Abertura do arquivo onde sera escrito o video de saida.
    videoSaida.open("../Videos/resultado.avi",
        videoSaida.fourcc('M','J','P','G'),
        60,
        cv::Size(video.get(cv::CAP_PROP_FRAME_WIDTH),
        video.get(cv::CAP_PROP_FRAME_HEIGHT)));

    if(!videoSaida.isOpened()) return -1;

    //CV_8UC1 para criar matriz resultado de um canal.
    resultado.create(cinza.rows, cinza.cols, CV_8UC1);
    cinza.release();
    
    //Leitura de novos frames, escrita do video de resultado e atualizacao do
    // modelo ao ler seus valores.
    while(temFrame)
    {
        video >> frame;

        if(frame.empty())
        {
            temFrame = false;
            continue;
        }

        cv::cvtColor(frame, cinza, cv::COLOR_BGR2GRAY);
        frame.release();

        //Escrita do frame resultado que sera inserido no video criado.
        atual = frameModelo.begin();
        for (size_t i = 0; i < cinza.rows; i++)
        {
            for (size_t j = 0; j < cinza.cols ; j++)
            {
                resultado.at<unsigned char>(i, j) = (*atual)->
                    probabilidadeDoPixel(cinza.at<unsigned char>(i, j)) >= 0.05
                ? 0
                : 255;
                
                atual++;
            }
            
        }

        cv::cvtColor(resultado, frame, cv::COLOR_GRAY2BGR);

        videoSaida << frame;

        //Printando cada frame da repeticao na tela
        imshow("Resultado", frame);
        char c = (char)cv::waitKey(1);
        if (c == 27)  break;

        frame.release();
        atual = frameModelo.begin();
/*     
        std::cout << "Frame: " << contador++ << "\n";
*/
        for (int i = 0; i < cinza.rows; i++)
        {
            for (int j = 0; j < cinza.cols; j++)
            {
/*
                if (i == 723 && j == 841)
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
*/
                (*atual)->leNovoPixel(cinza.at<unsigned char>(i, j));
                atual++;
                
            }
        }
        cinza.release();
    }
    
    frame.release();
    cinza.release();
    video.release();
    resultado.release();

    cv::destroyAllWindows();

    return 0;
}

void iniciaModelo(cv::Mat &frameVideo, std::list<Pixel *>& frameModelo)
{
    //Repeticao para a criacao de todos os pixels a partir dos valores lidos do
    // primeiro frame.
    for (int i = 0; i < frameVideo.rows; i++)
    {
        for (int j = 0; j < frameVideo.cols; j++)
            frameModelo.push_back
                (new Pixel((int)frameVideo.at<unsigned char>(i, j)));
    }
}
