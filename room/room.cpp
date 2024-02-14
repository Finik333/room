#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

const int H = 17;
const int W = 40;

String TileMap[H] = {
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B      0                               B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

int main()
{
    RenderWindow window(VideoMode(1920, 1080), L"Комната", Style::Default);
    Texture bg,home;
    bg.loadFromFile("bg.png");
    home.loadFromFile("home.png");
    Sprite menuBg(bg);
    Sprite Home(home);
    menuBg.setPosition(0, 0);
    Home.setPosition(320, 715);
    RectangleShape rectangle(Vector2f(64, 64));

    while (window.isOpen())
    {
        window.draw(menuBg);
        window.draw(Home);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'B') {
                    rectangle.setFillColor(Color::Yellow);
                }
                else if (TileMap[i][j] == '0') {
                    rectangle.setFillColor(Color::Red);
                }
                else {
                    continue;
                }

                rectangle.setPosition(j * 64, i * 64);
                window.draw(rectangle);
            }
        }

        window.display();
    }

    return 0;
}