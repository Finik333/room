#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

const int H = 17;
const int W = 40;
String TileMap[H] = {
    "                                        ",
    "                                        ",
    "                                        ",
    "                                        ",
    "                                        ",
    "                                        ",
    "                                        ",
    "                                        ",
    "                                        ",
    "                                        ",
    "                                        ",
    "                                        ",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "Q      0                               Q",
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
};

int main() {
    RenderWindow window(VideoMode(1920, 1080), "Комната", Style::Default);
    Texture blocktr, bg,home;
    blocktr.loadFromFile("block.jpg");
    bg.loadFromFile("bg.png");
    home.loadFromFile("home.png");
    Sprite bt(blocktr);
    Sprite menuBg(bg);
    Sprite Home(home);
    menuBg.setPosition(0, 0);
    Home.setPosition(320, 718);

    sf::View view = window.getDefaultView();

    while (window.isOpen()) {
        window.draw(menuBg);
        window.draw(Home);
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            view.move(0.5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            view.move(-0.5, 0);
        }
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                switch (TileMap[i][j]) {
                case 'B':
                    bt.setPosition(j * 64, i * 64);
                    bt.setTextureRect(IntRect(256, 64, 64, 64));
                    window.draw(bt);
                    break;
                case 'A':
                    bt.setPosition(j * 64, i * 64);
                    bt.setTextureRect(IntRect(0, 710, 64, 64));
                    window.draw(bt);
                    break;
                case '0':
                    bt.setPosition(j * 64, i * 64);
                    bt.setTextureRect(IntRect(0, 0, 64, 64));
                    window.draw(bt);
                    break;
                case 'Q':
                    bt.setPosition(j * 64, i * 64);
                    bt.setTextureRect(IntRect(0, 824, 64, 64));
                    window.draw(bt);
                    break;
                case 'W':
                    bt.setPosition(j * 64, i * 64);
                    bt.setTextureRect(IntRect(384, 254, 64, 64));
                    window.draw(bt);
                    break;
                default:
                    continue;
                }
            }
        }
        window.setView(view);
        window.display();
    }

    return 0;
}