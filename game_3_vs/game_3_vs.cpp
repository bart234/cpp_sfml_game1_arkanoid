#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;
class Element {

public:
    float x_left_in{};
    float x_right_in{};
    float y_top_in{};
    float y_bot_in{};
    float x_mid_in{};
    float y_mid_in{};
    float x_length_in{};
    float y_height_in{};
    sf::Sprite sprite{};
    std::string texture_name{};
    sf::Texture texture{};

    //function prototype
    float x_right();
    float x_left();
    float y_top();
    float y_bot();
    float x_mid();
    float y_mid();

    Element(std::string texture_name_in, float start_position_x_in, float start_position_y_in)
        :texture_name{texture_name_in}
        {
        texture.loadFromFile(texture_name); // true gdy wczytalo, false jak blad
        sprite.setTexture(texture);
        sprite.setPosition(start_position_x_in, start_position_y_in);
        x_mid_in = sprite.getOrigin().x;
        y_mid_in = sprite.getOrigin().y;
        x_length_in = sprite.getTexture()->getSize().x * sprite.getScale().x ;
        y_height_in = sprite.getTexture()->getSize().y * sprite.getScale().y ;
        }
 
   
};

float Element::x_right() {
    return sprite.getPosition().x + x_length_in;
}
float Element::x_left() {
    return sprite.getPosition().x;
}
float Element::y_top() {
    return sprite.getPosition().y;
}
float Element::y_bot() {
    return sprite.getPosition().y + y_height_in;
}
float Element::x_mid() {
    return sprite.getPosition().x + (x_length_in/2);
}
float Element::y_mid() {
    return sprite.getPosition().y +(y_height_in/2);
}

class Ball : public Element {
public:
    float move_on_y{ 0.03 };
    float* move_y{ &move_on_y };
    float move_on_x{ 0.0 };
    float* move_x{ &move_on_x };
    float kierunek{ 0.1 };
    float* param_kierunku{ &kierunek };
    
    Ball(std::string texture_name_in, float start_position_x_in, float start_position_y_in) :Element(texture_name_in,start_position_x_in,start_position_y_in)
    {}

};


//function prototype
bool czy_zderzenie(sf::Sprite& spr_ball, sf::Sprite& spr_pad);
bool czy_zderzenie(sf::Sprite& spr_ball, sf::Shape& spr_pad);
char zderzenie_x_czy_y(sf::Sprite& spr_ball, sf::Sprite& spr_pad);

char zderzenie_x_czy_y(sf::Sprite& spr_ball, sf::Shape& spr_pad);
void pod_moves_x_y(sf::Sprite* spr_pod, float pod_move_speed, sf::RenderWindow* oknoAplikacji);

char is_collide(Element& spr_ball, Element& spr_pad);

//--------------------------------------------------------------------------------------
char is_collide(Element& spr_ball, Element& spr_pad) {
  /*  if (
        ((x_ball_right >= x_pad_left && x_ball_right <= x_pad_right) || (x_ball_left < x_pad_right && x_ball_left >= x_pad_left))
        &&
        ((y_ball_top <= y_pad_bot && y_ball_top >= y_pad_top) || (y_ball_bot >= y_pad_top && y_ball_bot <= y_pad_bot))
        )
    {
        return true;
    }
    else
    {*/
        return false;
    //}
}
void odbicie(sf::Sprite* spr_ball, sf::Sprite* spr_pad, float* move_x, float* move_y, float* param_kierunku);
void odbicie(sf::Sprite* spr_ball, sf::Shape* spr_pad, float* move_x, float* move_y, float* param_kierunku);

void odbicie(sf::Sprite* spr_ball, sf::Sprite* spr_pad, float* move_x, float* move_y, float* param_kierunku)
{
   
    sf::Vector2f aktualna_pozycja_pod = spr_pad->getPosition();
    sf::Vector2f aktualna_pozycja_ball = spr_ball->getPosition();
    sf::Vector2f srodek_ball = spr_ball->getOrigin();

    float ball_2r_lenght{ spr_ball->getTexture()->getSize().x * spr_ball->getScale().x };

    float pod_x_lenght{ spr_pad->getTexture()->getSize().x * spr_pad->getScale().x };
    float pod_y_lenght{ spr_pad->getTexture()->getSize().y * spr_pad->getScale().y };
    //float pod_x_lenght{ spr_pad->getPoint(2).x };
    //float pod_y_lenght{ spr_pad->getPoint(2).y };

    float x_ball_left{ aktualna_pozycja_ball.x };
    float x_ball_right{ aktualna_pozycja_ball.x + ball_2r_lenght };
    float y_ball_top{ aktualna_pozycja_ball.y };
    float y_ball_bot{ aktualna_pozycja_ball.y + ball_2r_lenght };
    float x_ball_srodek{ x_ball_left + ball_2r_lenght / 2 };
    float y_ball_srodek{ y_ball_top + ball_2r_lenght / 2 };


    float x_pad_left{ aktualna_pozycja_pod.x }; 
    float x_pad_right{ aktualna_pozycja_pod.x + pod_x_lenght };
    float y_pad_top{ aktualna_pozycja_pod.y }; 
    float y_pad_bot{ aktualna_pozycja_pod.y + pod_y_lenght };

    char out{};
    //x
   
    if (x_ball_right >= x_pad_left && ((abs(x_ball_right - x_pad_left)) < 2) && ((y_ball_srodek >= y_pad_top) && (y_ball_srodek <= y_pad_bot)))
    {
        std::cout << "zderzenie x z lewej .|" << std::endl;
        //wyjmujemy pilke niewazne jak gleboko weszla

        std::cout << "weszla w sciane na:" << (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x) << std::endl;
        spr_ball->move(-1 - (x_ball_right - x_pad_left), 0);
        std::cout << "po wyjeciu" << (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x) << std::endl;

        out = 'x';
    }
    //printf("param Ball 2: %f ,Ball R: %f ,wall L: %f ,Wall R : %f \n", x_ball_left, x_ball_right, x_pad_left, x_pad_right);

    //x
    if (x_ball_left <= x_pad_right && ((abs(x_ball_left - x_pad_right)) < 2) && ((y_ball_srodek >= y_pad_top) && (y_ball_srodek <= y_pad_bot)))
    {
        std::cout << "zderzenie x z prawejb |." << std::endl;
        //wyjmujemy pilke niewazne jak gleboko weszla
        std::cout << "weszla w sciane lewa na:" << x_ball_left - x_pad_right << std::endl;

        spr_ball->move(+1 + abs(x_ball_left - x_pad_right), 0);
        std::cout << "po wyjeciu" << (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x) << std::endl;

        out = 'x';
    }
    printf("param Ball 3: %f ,Ball R: %f ,wall L: %f ,Wall R : %f \n", x_ball_left, x_ball_right, x_pad_left, x_pad_right);

    if ((abs(y_ball_top - y_pad_bot)) < 1 && ((x_ball_srodek >= x_pad_left) && (x_ball_srodek <= x_pad_right)))
    {
        spr_ball->move(0, 1 + abs(y_ball_top - y_pad_bot));
        out = 'y';
    }

    if ((abs(y_ball_bot - y_pad_top)) < 1 && ((x_ball_srodek >= x_pad_left) && (x_ball_srodek <= x_pad_right)))
    {
        spr_ball->move(0, -1 - abs(y_ball_bot - y_pad_top));
        out = 'y';
    }
    // float *move_x, float *move_y, float *param_kierunku
    std::cout << "my out is: " << out << std::endl;
    printf("start: move_y: %f , move_x: %f, param: %f\n", *move_x, *move_y, *param_kierunku);
    if (out == 'x' || out == 'y') {
        if (out == 'x') {
            if (abs(*move_y) > abs(*move_x)) 
            {

                (*param_kierunku) *= -1;
            }
            else 
            {
                (*move_x) *= -1;
            }
        }
        else
        {
            if (abs(*move_y) > abs(*move_x)) 
            {
                (*move_y) *= -1;
            }
            else 
            {
                (*param_kierunku) *= -1;
            }
        }
    }
    else 
    {
        std::cout << "error on zderzenie_x_czy_y" << std::endl;
    }

    printf(" end: move_y: %f , move_x: %f, param: %f \n", *move_x, *move_y, *param_kierunku);
    
}
void odbicie(sf::Sprite* spr_ball, sf::Shape* spr_pad, float* move_x, float* move_y, float* param_kierunku)
{

    sf::Vector2f aktualna_pozycja_pod = spr_pad->getPosition();
    sf::Vector2f aktualna_pozycja_ball = spr_ball->getPosition();
    sf::Vector2f srodek_ball = spr_ball->getOrigin();

    float ball_2r_lenght{ spr_ball->getTexture()->getSize().x * spr_ball->getScale().x };

    float pod_x_lenght{ spr_pad->getPoint(2).x };
    float pod_y_lenght{ spr_pad->getPoint(2).y };

    float x_ball_left{ aktualna_pozycja_ball.x };
    float x_ball_right{ aktualna_pozycja_ball.x + ball_2r_lenght };
    float y_ball_top{ aktualna_pozycja_ball.y };
    float y_ball_bot{ aktualna_pozycja_ball.y + ball_2r_lenght };
    float x_ball_srodek{ x_ball_left + ball_2r_lenght / 2 };
    float y_ball_srodek{ y_ball_top + ball_2r_lenght / 2 };


    float x_pad_left{ aktualna_pozycja_pod.x };
    float x_pad_right{ aktualna_pozycja_pod.x + pod_x_lenght };
    float y_pad_top{ aktualna_pozycja_pod.y };
    float y_pad_bot{ aktualna_pozycja_pod.y + pod_y_lenght };

    char out{};
    //x

    if (x_ball_right >= x_pad_left && ((abs(x_ball_right - x_pad_left)) < 2) && ((y_ball_srodek >= y_pad_top) && (y_ball_srodek <= y_pad_bot)))
    {
        std::cout << "zderzenie x z lewej .|" << std::endl;
        //wyjmujemy pilke niewazne jak gleboko weszla

        std::cout << "weszla w sciane na:" << (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x) << std::endl;
        spr_ball->move(-1 - (x_ball_right - x_pad_left), 0);
        std::cout << "po wyjeciu" << (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x) << std::endl;

        out = 'x';
    }
    //printf("param Ball 2: %f ,Ball R: %f ,wall L: %f ,Wall R : %f \n", x_ball_left, x_ball_right, x_pad_left, x_pad_right);

    //x
    if (x_ball_left <= x_pad_right && ((abs(x_ball_left - x_pad_right)) < 2) && ((y_ball_srodek >= y_pad_top) && (y_ball_srodek <= y_pad_bot)))
    {
        std::cout << "zderzenie x z prawejb |." << std::endl;
        //wyjmujemy pilke niewazne jak gleboko weszla
        std::cout << "weszla w sciane lewa na:" << x_ball_left - x_pad_right << std::endl;

        spr_ball->move(+1 + abs(x_ball_left - x_pad_right), 0);
        std::cout << "po wyjeciu" << (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x) << std::endl;

        out = 'x';
    }
    printf("param Ball 3: %f ,Ball R: %f ,wall L: %f ,Wall R : %f \n", x_ball_left, x_ball_right, x_pad_left, x_pad_right);

    if ((abs(y_ball_top - y_pad_bot)) < 1 && ((x_ball_srodek >= x_pad_left) && (x_ball_srodek <= x_pad_right)))
    {
        spr_ball->move(0, 1 + abs(y_ball_top - y_pad_bot));
        out = 'y';
    }

    if ((abs(y_ball_bot - y_pad_top)) < 1 && ((x_ball_srodek >= x_pad_left) && (x_ball_srodek <= x_pad_right)))
    {
        spr_ball->move(0, -1 - abs(y_ball_bot - y_pad_top));
        out = 'y';
    }
    // float *move_x, float *move_y, float *param_kierunku
    std::cout << "my out is: " << out << std::endl;
    printf("start: move_y: %f , move_x: %f, param: %f\n", *move_x, *move_y, *param_kierunku);
    if (out == 'x' || out == 'y') {
        if (out == 'x') {
            if (abs(*move_y) > abs(*move_x))
            {

                (*param_kierunku) *= -1;
            }
            else
            {
                (*move_x) *= -1;
            }
        }
        else
        {
            if (abs(*move_y) > abs(*move_x))
            {
                (*move_y) *= -1;
            }
            else
            {
                (*param_kierunku) *= -1;
            }
        }
    }
    else
    {
        std::cout << "error on zderzenie_x_czy_y" << std::endl;
    }

    printf(" end: move_y: %f , move_x: %f, param: %f \n", *move_x, *move_y, *param_kierunku);

}

//functions--------------------------------------------------------------

bool czy_zderzenie(sf::Sprite* spr_ball, sf::Shape* spr_pad)
{
    sf::Vector2f aktualna_pozycja_pod = spr_pad->getPosition();
    sf::Vector2f aktualna_pozycja_ball = spr_ball->getPosition();

    float ball_2r_lenght{ spr_ball->getTexture()->getSize().x * spr_ball->getScale().x };
    float pod_x_lenght{ spr_pad->getPoint(2).x };
    float pod_y_lenght{ spr_pad->getPoint(2).y };

    float x_ball_left{ aktualna_pozycja_ball.x };
    float x_ball_right{ aktualna_pozycja_ball.x + ball_2r_lenght };
    float y_ball_top{ aktualna_pozycja_ball.y };
    float y_ball_bot{ aktualna_pozycja_ball.y + ball_2r_lenght };


    float x_pad_left{ aktualna_pozycja_pod.x }; float x_pad_right{ aktualna_pozycja_pod.x + pod_x_lenght };
    float y_pad_top{ aktualna_pozycja_pod.y }; float y_pad_bot{ aktualna_pozycja_pod.y + pod_y_lenght };

    ////printf("ball_right: %f , pad_left: %f , ball_left: %f , pad_right: %f \n",x_ball_right,x_pad_left,x_ball_left,x_pad_right);
    if (
        ((x_ball_right >= x_pad_left && x_ball_right <= x_pad_right) || (x_ball_left < x_pad_right && x_ball_left >= x_pad_left))
        &&
        ((y_ball_top <= y_pad_bot && y_ball_top >= y_pad_top) || (y_ball_bot >= y_pad_top && y_ball_bot <= y_pad_bot))
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool czy_zderzenie(sf::Sprite* spr_ball, sf::Sprite* spr_pad)
{
    sf::Vector2f aktualna_pozycja_pod = spr_pad->getPosition();
    sf::Vector2f aktualna_pozycja_ball = spr_ball->getPosition();

    float ball_2r_lenght{ spr_ball->getTexture()->getSize().x * spr_ball->getScale().x };

    float pod_x_lenght{ spr_pad->getTexture()->getSize().x * spr_pad->getScale().x };
    float pod_y_lenght{ spr_pad->getTexture()->getSize().y * spr_pad->getScale().y };

    float x_ball_left{ aktualna_pozycja_ball.x };
    float x_ball_right{ aktualna_pozycja_ball.x + ball_2r_lenght };
    float y_ball_top{ aktualna_pozycja_ball.y };
    float y_ball_bot{ aktualna_pozycja_ball.y + ball_2r_lenght };


    float x_pad_left{ aktualna_pozycja_pod.x }; float x_pad_right{ aktualna_pozycja_pod.x + pod_x_lenght };
    float y_pad_top{ aktualna_pozycja_pod.y }; float y_pad_bot{ aktualna_pozycja_pod.y + pod_y_lenght };

    //printf("ball_right: %f , pad_left: %f , ball_left: %f , pad_right: %f \n",x_ball_right,x_pad_left,x_ball_left,x_pad_right);
    if (
        ((x_ball_right >= x_pad_left && x_ball_right <= x_pad_right) || (x_ball_left < x_pad_right && x_ball_left >= x_pad_left))
        &&
        ((y_ball_top <= y_pad_bot && y_ball_top >= y_pad_top) || (y_ball_bot >= y_pad_top && y_ball_bot <= y_pad_bot))
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void pod_moves_x_y(sf::Sprite* spr_pad, float pod_move_speed, sf::RenderWindow* oknoAplikacji)
{
    float szerokosc_pada = spr_pad->getTexture()->getSize().x * spr_pad->getScale().x;

    sf::Vector2u wymiary_okna = oknoAplikacji->getSize();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if ((spr_pad->getPosition().x - (pod_move_speed)) < 0)
        {
        }
        else
        {
            spr_pad->move(-pod_move_speed, 0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if ((spr_pad->getPosition().x + (szerokosc_pada)+pod_move_speed) > wymiary_okna.x)
        {
        }
        else
        {
            spr_pad->move(+pod_move_speed, 0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        spr_pad->move(0, +pod_move_speed);
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        spr_pad->move(0, -pod_move_speed);
    }


}

//char zderzenie_x_czy_y(sf::Sprite* spr_ball, sf::Sprite* spr_pad)
//{
//    sf::Vector2f aktualna_pozycja_pod = spr_pad->getPosition();
//    sf::Vector2f aktualna_pozycja_ball = spr_ball->getPosition();
//    sf::Vector2f srodek_ball = spr_ball->getOrigin();
//
//    float ball_2r_lenght{ spr_ball->getTexture()->getSize().x * spr_ball->getScale().x };
//
//    float pod_x_lenght{ spr_pad->getTexture()->getSize().x * spr_pad->getScale().x };
//    float pod_y_lenght{ spr_pad->getTexture()->getSize().y * spr_pad->getScale().y };
//
//    float x_ball_left{ aktualna_pozycja_ball.x };
//    float x_ball_right{ aktualna_pozycja_ball.x + ball_2r_lenght };
//    float y_ball_top{ aktualna_pozycja_ball.y };
//    float y_ball_bot{ aktualna_pozycja_ball.y + ball_2r_lenght };
//    float x_ball_srodek{ x_ball_left + ball_2r_lenght / 2 };
//    float y_ball_srodek{ y_ball_top + ball_2r_lenght / 2 };
//
//
//    float x_pad_left{ aktualna_pozycja_pod.x }; float x_pad_right{ aktualna_pozycja_pod.x + pod_x_lenght };
//    float y_pad_top{ aktualna_pozycja_pod.y }; float y_pad_bot{ aktualna_pozycja_pod.y + pod_y_lenght };
//
//    //x
//   //printf("param Ball L: %f ,Ball R: %f ,wall L: %f ,Wall R : %f \n", x_ball_left, x_ball_right, x_pad_left, x_pad_right);
//    if (x_ball_right >= x_pad_left && ((x_ball_right - x_pad_left) < 2) && ((y_ball_srodek >= y_pad_top) && (y_ball_srodek <= y_pad_bot)))
//    {
//        std::cout << "zderzenie x z lewej .|" << std::endl;
//        //wyjmujemy pilke niewazne jak gleboko weszla
//
//        std::cout << "weszla w sciane na:" <<  (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x)  << std::endl;
//        spr_ball->move(-1 - (x_ball_right - x_pad_left), 0);
//        std::cout << "po wyjeciu" << (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x) << std::endl;
//
//        return 'x';
//    }
//   // printf("param Ball P: %f ,Ball R: %f ,wall L: %f ,Wall R : %f \n", x_ball_left, x_ball_right, x_pad_left, x_pad_right);
//    //x
//    if (x_ball_left <= x_pad_right && ((x_ball_left - x_pad_right) < 2) && ((y_ball_srodek >= y_pad_top) && (y_ball_srodek <= y_pad_bot)))
//    {
//        std::cout << "zderzenie x z prawejb |." << std::endl;
//        //wyjmujemy pilke niewazne jak gleboko weszla
//        std::cout << "weszla w sciane lewa na:" << x_ball_left - x_pad_right << std::endl;
//
//        spr_ball->move(+1 + abs(x_ball_left - x_pad_right), 0);
//        std::cout << "po wyjeciu" << (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x) << std::endl;
//
//
//        return 'x';
//    }
//
//    //printf("y_ball_top: %f | y_pad_bot: %f | x_ball_srodek: %f | x_pad_left: %f | x_ball_srodek: %f | x_pad_right: %f | ",y_ball_top,y_pad_bot,x_ball_srodek,x_pad_left,x_ball_srodek,x_pad_right);
//
//    if (abs(y_ball_top - y_pad_bot) < 1 && ((x_ball_srodek >= x_pad_left) && (x_ball_srodek <= x_pad_right)))
//    {
//        //std::cout<<" .- "<<std::endl;
//        //printf("od dolu %f %f ", y_ball_top, y_pad_bot);
//        spr_ball->move(0, 1 + abs(y_ball_top - y_pad_bot));
//        return 'y';
//    }
//
//    if (abs(y_ball_bot - y_pad_top) < 1 && ((x_ball_srodek >= x_pad_left) && (x_ball_srodek <= x_pad_right)))
//    {
//        //std::cout<<" *_  "<<std::endl;
//       // printf("od gory %f %f ", y_ball_bot, y_pad_top);
//        spr_ball->move(0, -1 - abs(y_ball_bot - y_pad_top));
//        return 'y';
//    }
//    std::cout << "error on zderzenie_x_czy_y" << std::endl;
//    return 'e';
//}

//char zderzenie_x_czy_y(sf::Sprite* spr_ball, sf::Shape* spr_pad)
//{
//    sf::Vector2f aktualna_pozycja_pod = spr_pad->getPosition();
//    sf::Vector2f aktualna_pozycja_ball = spr_ball->getPosition();
//    sf::Vector2f srodek_ball = spr_ball->getOrigin();
//
//    float ball_2r_lenght{ spr_ball->getTexture()->getSize().x * spr_ball->getScale().x };
//
//    float pod_x_lenght{ spr_pad->getPoint(2).x };
//    float pod_y_lenght{ spr_pad->getPoint(2).y };
//
//    float x_ball_left{ aktualna_pozycja_ball.x };
//    float x_ball_right{ aktualna_pozycja_ball.x + ball_2r_lenght };
//    float y_ball_top{ aktualna_pozycja_ball.y };
//    float y_ball_bot{ aktualna_pozycja_ball.y + ball_2r_lenght };
//    float x_ball_srodek{ x_ball_left + ball_2r_lenght / 2 };
//    float y_ball_srodek{ y_ball_top + ball_2r_lenght / 2 };
//
//
//    float x_pad_left{ aktualna_pozycja_pod.x }; float x_pad_right{ aktualna_pozycja_pod.x + pod_x_lenght };
//    float y_pad_top{ aktualna_pozycja_pod.y }; float y_pad_bot{ aktualna_pozycja_pod.y + pod_y_lenght };
//
//    x
//    printf("param Ball L: %f ,Ball R: %f ,wall L: %f ,Wall R : %f \n", x_ball_left, x_ball_right, x_pad_left, x_pad_right);
//    if (x_ball_right >= x_pad_left && ((x_ball_right - x_pad_left) < 2) && ((y_ball_srodek >= y_pad_top) && (y_ball_srodek <= y_pad_bot)))
//    {
//        std::cout << "zderzenie x z lewej .|" << std::endl;
//        wyjmujemy pilke niewazne jak gleboko weszla
//
//        std::cout << "weszla w sciane na:" << x_ball_right - x_pad_left << std::endl;
//        spr_ball->move(-1 - (x_ball_right - x_pad_left), 0);
//        std::cout << "po wyjeciu" << (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x) << std::endl;
//
//        return 'x';
//    }
//
//    x
//    if (x_ball_left <= x_pad_right && ((x_ball_left - x_pad_right) < 2) && ((y_ball_srodek >= y_pad_top) && (y_ball_srodek <= y_pad_bot)))
//    {
//        std::cout << "zderzenie x z prawejb |." << std::endl;
//        wyjmujemy pilke niewazne jak gleboko weszla
//        std::cout << "weszla w sciane lewa na:" << x_ball_left - x_pad_right << std::endl;
//
//        spr_ball->move(+1 + abs(x_ball_left - x_pad_right), 0);
//        std::cout << "po wyjeciu" << (spr_ball->getPosition().x) << " - " << (spr_ball->getPosition().x) << std::endl;
//
//        return 'x';
//    }
//
//    if (abs(y_ball_top - y_pad_bot) < 1 && ((x_ball_srodek >= x_pad_left) && (x_ball_srodek <= x_pad_right)))
//    {
//        spr_ball->move(0, 1 + abs(y_ball_top - y_pad_bot));
//        return 'y';
//    }
//
//    if (abs(y_ball_bot - y_pad_top) < 1 && ((x_ball_srodek >= x_pad_left) && (x_ball_srodek <= x_pad_right)))
//    {
//        spr_ball->move(0, -1 - abs(y_ball_bot - y_pad_top));
//        return 'y';
//    }
//    std::cout << "error on zderzenie_x_czy_y" << std::endl;
//    return 'e';
//}

//--------------------------------------------------------------------------------------


int main()
{
    sf::RenderWindow oknoAplikacji(sf::VideoMode(850, 600, 32), "Kurs SFML 2.0 - http://cpp0x.pl");

    sf::Vector2u wymiary_okna = oknoAplikacji.getSize();    
    
    Ball ball("ball.bmp", wymiary_okna.x / 2, wymiary_okna.y / 2);
    sf::Sprite spr_ball{ ball.sprite };

    sf::Texture text_pad;
    text_pad.loadFromFile("kreska.bmp");
    sf::Sprite spr_pad;
    spr_pad.setTexture(text_pad);
    float pod_x_lenght{ spr_pad.getTexture()->getSize().x * spr_pad.getScale().x };
    float pod_y_lenght{ spr_pad.getTexture()->getSize().y * spr_pad.getScale().y };

    Element prawa_sciana("sciana.bmp", wymiary_okna.x - 5, 0);
    sf::Sprite spr_sciana_right{ prawa_sciana.sprite };

    Element lewa_sciana("sciana.bmp", 0 + 5, 0);
    sf::Sprite spr_sciana_left{ lewa_sciana.sprite };

    Element top_sciana("sciana_top.bmp", 20, 0 + 5);
    sf::Sprite spr_sciana_top{ top_sciana.sprite };

    Element bot_sciana("sciana_top.bmp", 0, wymiary_okna.y - 5);
    sf::Sprite spr_sciana_bot{ bot_sciana.sprite };

    sf::RectangleShape box(sf::Vector2f(350.0f, 130.0f));
    box.setPosition(150, 100);
    box.setFillColor(sf::Color::Blue);


    //float sciana_grubosc {spr_sciana_left->getTexture()->getSize().x * spr_sciana_left->getScale().x}; //5
    //float sciana_dlugosc {spr_sciana_left->getTexture()->getSize().y * spr_sciana_left->getScale().y};  //800 ?

    //parametry gry
    float cienkosc_sciany{ 5 };
    float pod_move_speed{ 15.0 };
    float pod_grubosc{ 20.0 };
    float odl_od_ramki_dolnej{ 10 };
    int temp_x{ 0 };

    float move_on_y{ 0.03 };
    float* ptr_move_y{ &move_on_y };

    float move_on_x{ 0.0 };
    float* ptr_move_x{ &move_on_x };

    float kierunek{ 0.1 };
    float* ptr_param_kierunku{ &kierunek };

    spr_pad.setPosition(wymiary_okna.x / 2 - pod_x_lenght / 2, 400);
    //spr_pad.setPosition(wymiary_okna.x/2 - pod_x_lenght/2,wymiary_okna.y-pod_y_lenght - odl_od_ramki_dolnej);


    while (oknoAplikacji.isOpen()) // petla glowna
    {
        sf::Event zdarzenie;

        //event loop
        while (oknoAplikacji.pollEvent(zdarzenie))
        {
            //exit
            if (zdarzenie.type == sf::Event::Closed)
            {
                oknoAplikacji.close();
            }
            if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
            {
                oknoAplikacji.close();
            }
            //pad moves
            pod_moves_x_y(&spr_pad, pod_move_speed, &oknoAplikacji);
        }
        // event loop  end

        //ruch pod katem
        {
            if (temp_x == 10) {
                if (abs(*ptr_move_y) > abs(*ptr_move_x))
                {
                    spr_ball.move(*ptr_move_x + *ptr_param_kierunku, *ptr_move_y);
                    temp_x = 0;
                }
                else {
                    spr_ball.move(*ptr_move_x, *ptr_move_y + *ptr_param_kierunku);
                    temp_x = 0;
                }
            }
            else {
                spr_ball.move(*ptr_move_x, *ptr_move_y);
            }
            ++temp_x;
        }

        if (czy_zderzenie(&spr_ball, &box)) {
            std::cout << "klocek print" << std::endl;
            {
                odbicie(&spr_ball, &box, ptr_move_x, ptr_move_y, ptr_param_kierunku);
            }
        }

        if (czy_zderzenie(&spr_ball, &spr_pad) == true)
        {
            odbicie(&spr_ball, &spr_pad, ptr_move_x, ptr_move_y, ptr_param_kierunku);


            float pozycja_srodka_pilki{ spr_ball.getPosition().x + (ball.x_length_in / 2) };
            float pozycja_srodka_pad{ spr_pad.getPosition().x + (pod_x_lenght / 2) };
            float pozycja_pilki_od_srodka_pada{ abs(pozycja_srodka_pad - pozycja_srodka_pilki) };
            std::cout << "pozycja pilki na padzie: " << pozycja_pilki_od_srodka_pada << std::endl;

            if (pozycja_srodka_pilki > pozycja_srodka_pad) {
                //z prawej
                *ptr_param_kierunku = *ptr_param_kierunku + (pozycja_pilki_od_srodka_pada * 2) / 100;
                /*if (*param_kierunku > 0){
                        0.1 - 1

                    *param_kierunku += 1;
                }else{
                    *param_kierunku -= 0.8
;
                }*/
            }
            else {
                //z lewej
                *ptr_param_kierunku = -(*ptr_param_kierunku + (pozycja_pilki_od_srodka_pada * 2) / 100);
            }
        }

        if (czy_zderzenie(&spr_ball, &spr_sciana_right) == true)
        {
            odbicie(&spr_ball, &spr_sciana_right, ptr_move_x, ptr_move_y, ptr_param_kierunku);
        }

        if (czy_zderzenie(&spr_ball, &spr_sciana_left) == true)
        {
            odbicie(&spr_ball, &spr_sciana_left, ptr_move_x, ptr_move_y, ptr_param_kierunku);
        }

        if (czy_zderzenie(&spr_ball, &spr_sciana_top) == true)
        {
            odbicie(&spr_ball, &spr_sciana_top, ptr_move_x, ptr_move_y, ptr_param_kierunku);
        }

        if (czy_zderzenie(&spr_ball, &spr_sciana_bot) == true)
        {
            odbicie(&spr_ball, &spr_sciana_bot, ptr_move_x, ptr_move_y, ptr_param_kierunku);
        }

        // ball outside frame

        if (((spr_ball.getPosition().y + ball.x_length_in) >= wymiary_okna.y) || (spr_ball.getPosition().y <= 0)) {
            *ptr_move_y = 0;
            std::cout << "przegrales" << std::endl;
            break;
        }

        //std::cout<<"ball x:"<<spr_ball.getPosition().x<<" y: " <<spr_ball.getPosition().y <<"sciana x:"<<spr_sciana_right.getPosition().x<<" y: " <<spr_sciana_right.getPosition().y <<std::endl;

       //---------------------------

        oknoAplikacji.clear();
        oknoAplikacji.draw(box);
        oknoAplikacji.draw(spr_sciana_left);
        oknoAplikacji.draw(spr_sciana_right);
        oknoAplikacji.draw(spr_sciana_top);
        oknoAplikacji.draw(spr_sciana_bot);
        oknoAplikacji.draw(spr_ball);
        oknoAplikacji.draw(spr_pad);
        oknoAplikacji.display();
    }


    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
