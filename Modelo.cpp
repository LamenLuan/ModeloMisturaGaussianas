#include "Modelo.hpp"

Modelo::Modelo(std::string caminho_entrada, std::string caminho_saida)
    :
    m_entrada(caminho_entrada), m_caminho_saida(caminho_saida)
{ 
}

Modelo::~Modelo()
{
}

void Modelo::abre_saida(cv::VideoWriter &saida, std::string caminho,
    std::string nome)
{
    // Video de saida criado com 30 fps, formato .avi com com MJPG.
    saida.open(caminho + nome + ".avi", saida.fourcc('M', 'J', 'P', 'G'),
        30, cv::Size(m_entrada.get(cv::CAP_PROP_FRAME_WIDTH),
        m_entrada.get(cv::CAP_PROP_FRAME_HEIGHT)));
}

void Modelo::inicia_gaussianas()
{
    cv::Mat frame, cinza;
    m_entrada >> frame;

    cv::cvtColor(frame, cinza, cv::COLOR_BGR2GRAY);
    frame.release();

    for (size_t i = 0; i < cinza.rows; i++)
    {
        for (size_t j = 0; j < cinza.cols; j++)
            m_frames_modelo.push_back
                (new Pixel( (int) cinza.at<unsigned char>(i, j) ) );
    }

    cinza.release();
}

void Modelo::gera_frames_saida(cv::Mat &frame, cv::VideoWriter &saida1,
cv::VideoWriter &saida2)
{
    std::list<Pixel *>::iterator atual = m_frames_modelo.begin();
    cv::Mat auxiliar, resultado1, resultado2;

    // Criando os frames de resultado com o tamanho do frame tirado da entrada.
    resultado1.create(m_entrada.get(cv::CAP_PROP_FRAME_HEIGHT),
        m_entrada.get(cv::CAP_PROP_FRAME_WIDTH), CV_8UC1);
    resultado2.create(m_entrada.get(cv::CAP_PROP_FRAME_HEIGHT),
        m_entrada.get(cv::CAP_PROP_FRAME_WIDTH), CV_8UC1);

    for (size_t i = 0; i < frame.rows; i++)
    {
        for (size_t j = 0; j < frame.cols; j++)
        {
            resultado1.at<unsigned char>(i, j) = (*atual)->pixelMaisProvavel();

            resultado2.at<unsigned char>(i, j) = 
                (*atual)->probabilidadeDoPixel(frame.at<unsigned char>(i, j))
                >= 0.005
                ? 0
                : 255;

            atual++;
        }
    }

    cv::cvtColor(resultado1, auxiliar, cv::COLOR_GRAY2BGR);
    saida1 << auxiliar;
    resultado1.release();

    cv::cvtColor(resultado2, auxiliar, cv::COLOR_GRAY2BGR);
    saida2 << auxiliar;
    resultado2.release();
    
    auxiliar.release();
}

void Modelo::le_novo_pixel(cv::Mat &frame)
{
    std::list<Pixel *>::iterator atual = m_frames_modelo.begin();

    for (size_t i = 0; i < frame.rows; i++)
    {
        for (size_t j = 0; j < frame.cols; j++)
        {
            (*atual)->leNovoPixel(frame.at<unsigned char>(i, j) );
            atual++;
        }
    }
}

void Modelo::executa(std::string diretorio)
{
    bool temFrame = true;
    cv::Mat frame, cinza;
    cv::VideoWriter saida1, saida2;

    abre_saida(saida1, diretorio, "saida1");
    abre_saida(saida2, diretorio, "saida2");

    inicia_gaussianas();

    while (temFrame)
    {
        // A matriz "frame" recebe um frame do video aberto.
        m_entrada >> frame;

        if (frame.empty())
        {
            temFrame = false;
            continue;
        }

        // A matriz "cinza" recebe o frame convertido para grayscale.
        cv::cvtColor(frame, cinza, cv::COLOR_BGR2GRAY);
        frame.release();


        // Um frame de cada uma das duas saidas sao geradas antes da atualizacao.
        gera_frames_saida(cinza, saida1, saida2);

        // Logo em seguida, atualizo as gaussianas com o frame lido.
        le_novo_pixel(cinza);

        cinza.release();
    }

    saida1.release();
    saida2.release();
}