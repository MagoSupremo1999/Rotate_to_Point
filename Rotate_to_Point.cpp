/* ===============================================================================================
   = Código desenvolvido para um goleiro-robô peerceber um chute e se posicionar para defendê-lo =
   = 19/11/2019                                                                                  =
   = Desenvolvido por Vinícius Alves                                                             =
   =============================================================================================== */

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

#define SEN_1 0.017452406           //Seno de 1º
#define COS_1 0.999847695           //Cosseno de 1º
#define TAN_1 0.017455064           //Tangente de 1º

int main(){
    float tan_line = 0;                                     //Tangente inicial de alpha
    float alpha, beta;                                      //Coeficientes angular e linear, respectivamente, da reta
    float ball_x, ball_y;                                   //Coordenadas da bola
    bool activate_trajectory;                               //Variável que define se a trajetória é mostrada

    sf::RenderWindow window(sf::VideoMode(900, 600), "My window");          //Configura a janela

//======================= Desenvolvimento do layout do estádio de futebol ==========================================
    sf::RectangleShape stadium(sf::Vector2f(900, 600));                     //Configura o estádio
    stadium.setFillColor(sf::Color::Green);

    sf::RectangleShape field(sf::Vector2f(880, 580));                       //Configura a área do campo
    field.setFillColor(sf::Color::Transparent);
    field.setPosition(10, 10);
    field.setOutlineColor(sf::Color::White);
    field.setOutlineThickness(1);

    sf::RectangleShape left_area(sf::Vector2f(100, 150));                   //Configura a pequena área esquerda
    left_area.setFillColor(sf::Color::Transparent);
    left_area.setPosition(10, 225);
    left_area.setOutlineColor(sf::Color::White);
    left_area.setOutlineThickness(1);

    sf::CircleShape center_area(50);                                        //Configura a área central do campo
    center_area.setFillColor(sf::Color::Transparent);
    center_area.setPosition(400, 250);
    center_area.setOutlineColor(sf::Color::White);
    center_area.setOutlineThickness(1);

    sf::Vertex cut_field[] = {sf::Vertex(sf::Vector2f(450, 10)), sf::Vertex(sf::Vector2f(450, 590))};   //Configura a divisória do campo

    sf::RectangleShape right_area(sf::Vector2f(100, 150));                  //Configura a pequena área direita
    right_area.setFillColor(sf::Color::Transparent);
    right_area.setPosition(790, 225);
    right_area.setOutlineColor(sf::Color::White);
    right_area.setOutlineThickness(1);
//==================================================================================================================

//======================================= Adição de objetos ao campo ===============================================
    sf::RectangleShape front(sf::Vector2f(2, 18));                     //Configura a frente do robô
    front.setFillColor(sf::Color::Black);
    front.setPosition(612, 291);

    sf::RectangleShape robot(sf::Vector2f(18, 18));                    //Configura o robô
    robot.setFillColor(sf::Color::Yellow);
    robot.setPosition(612, 291);
//==================================================================================================================

    while (window.isOpen()){                                            //Abre a janela

//========================================= Desenho das criações na janela =========================================
        window.clear();
        window.draw(stadium);                                           //Desenha o estádio
        window.draw(field);                                             //Desenha a região do campo
        window.draw(left_area);                                         //Desenha a pequena área esquerda
        window.draw(right_area);                                        //Desenha a pequena área direita
        window.draw(cut_field, 10, sf::Lines);                          //Desenha a divisória do campo dos times
        window.draw(center_area);                                       //Desenha a área central do campo
        window.draw(robot);                                             //Desenha o robô
        window.draw(front);                                             //Desenha a frente do robô
//====================================================================================================================

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            float r = sqrt((sf::Mouse::getPosition(window).y - 300)*(sf::Mouse::getPosition(window).y - 300) + (sf::Mouse::getPosition(window).x - 621)*(sf::Mouse::getPosition(window).x - 621));
            float sin = (sf::Mouse::getPosition(window).x - 621)/r;
            robot.setRotation(sin + sin*sin*sin/6 + 3*sin*sin*sin*sin*sin/40 + 15*sin*sin*sin*sin*sin*sin*sin/336);
            front.setRotation(sin + sin*sin*sin/6 + 3*sin*sin*sin*sin*sin/40 + 15*sin*sin*sin*sin*sin*sin*sin/336);
        }


        window.display();                                                       //Aplica os desenhos na janela

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();                                                 //Fecha a janela
            }
        }
    }
    return 0;
}