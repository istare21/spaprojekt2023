#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>

#define MAXG 1000

int buffer_space = 50; //koliki razmak izmedu tocaka
int width; // sirina prozora
int height; // visina prozora
int columns, rows; // koliko stupaca i redaka
int sqgrid[MAXG][MAXG];


int get_representation(int a, int b, int c, int d) {
    return a * 8 + b * 4 + c * 2 + d * 1;
}

void grid(int col, int row, sf::RenderTexture& texture) {

    std::default_random_engine generator;
    std::uniform_int_distribution<int> result(0, 1);

    //basic grid
    sf::CircleShape dot(2.f);
    for (int i = 0; i <= col; i++) {
        for (int j = 0; j <= row; j++) {
            sqgrid[i][j] = result(generator);
            dot.setPosition(i * buffer_space, 
                            j * buffer_space);
            if (sqgrid[i][j] == 1) texture.draw(dot);
        }
    }

    // racunanje tocaka a, b, c, d izmedu tocaka grida
    // odnosno, gdje se spajaju linije

    sf::VertexArray linije(sf::Lines, 4);
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            float x = i * buffer_space;
            float y = j * buffer_space;
            sf::Vector2f a(x + buffer_space*0.5, y);
            sf::Vector2f b(x + buffer_space, y + buffer_space*0.5);
            sf::Vector2f c(x + buffer_space*0.5, y + buffer_space);
            sf::Vector2f d(x, y + buffer_space*0.5);

            int slucaj = get_representation(sqgrid[i][j], sqgrid[i + 1][j],
                                            sqgrid[i + 1][j + 1], sqgrid[i][j + 1]);

            switch (slucaj) {
            case 0: 
                // nista se ne crta
                break;
            case 1: 
                linije[0].position = c;
                linije[1].position = d;
                break; 
            case 2: 
                linije[0].position = b;
                linije[1].position = c;
                break;
            case 3:
                linije[0].position = b;
                linije[1].position = d;
                break;
            case 4: 
                linije[0].position = a;
                linije[1].position = b;
                break;
            case 5: 
                linije[0].position = a;
                linije[1].position = d;
                linije[2].position = b;
                linije[3].position = c;
                break;
            case 6: 
                linije[0].position = a;
                linije[1].position = c;
                break;
            case 7: 
                linije[0].position = a;
                linije[1].position = d;
                break;
            case 8: 
                linije[0].position = d;
                linije[1].position = a;
                break;
            case 9: 
                linije[0].position = c;
                linije[1].position = a;
                break;
            case 10: 
                linije[0].position = a;
                linije[1].position = c;
                linije[2].position = d;
                linije[3].position = b;
                break;
            case 11: 
                linije[0].position = b;
                linije[1].position = a;
                break;
            case 12: 
                linije[0].position = b;
                linije[1].position = d;
                break;
            case 13: 
                linije[0].position = c;
                linije[1].position = b;
                break;
            case 14:
                linije[0].position = c;
                linije[1].position = d;
                break;
            case 15:
                //nista
                break;
            }
            texture.draw(linije);
   
        }
    }


    texture.display();

}

int main()
{
    srand(time(NULL));
    std::cout << "width: ";
    std::cin >> width;
    std::cout << "height: ";
    std::cin >> height;


    columns = width / buffer_space;
    rows = height / buffer_space;

    sf::RenderTexture slika_grid;
    slika_grid.create(width, height);

    grid(columns, rows, slika_grid);

    sf::Sprite final_slika(slika_grid.getTexture());

    sf::RenderWindow window(sf::VideoMode(width, height), "IT LIVEEEES!");

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) window.close();
        }


        //renderiranje
        

        window.clear();

        window.draw(final_slika);

        //grid(columns, rows, window);
        
        window.display();
    }

    return 0;
}