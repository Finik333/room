#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class World {
public:
    float dx;
    float dy;
    FloatRect rect;
    Sprite sprite;
    float f;

    void Block(Texture& image) {
        sprite.setTexture(image);
        rect = FloatRect(3 * 64, 9 * 64, 40, 74);
        dx = 0.1;
        dy = 0.1;
        f = 3;
    }
};

const int H = 17;
const int W = 40;
String TileMap[H] = {
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "W                                      W",
    "Q                                      Q",
    "Q                                      Q",
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

    while (window.isOpen()) {
        window.draw(menuBg);
        window.draw(Home);
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                switch (TileMap[i][j]) {
                case 'B':
                    bt.setPosition(j * 64, i * 64);
                    bt.setTextureRect(IntRect(0, 0, 64, 64));
                    window.draw(bt);
                    break;
                case 'A':
                    bt.setPosition(j * 64, i * 64);
                    bt.setTextureRect(IntRect(0, 0, 64, 64));
                    window.draw(bt);
                    break;
                case '0':
                    bt.setPosition(j * 64, i * 64);
                    bt.setTextureRect(IntRect(0, 0, 64, 64));
                    window.draw(bt);
                    break;
                case 'Q':
                    bt.setPosition(j * 64, i * 64);
                    bt.setTextureRect(IntRect(0, 0, 64, 64));
                    window.draw(bt);
                    break;
                case 'W':
                    bt.setPosition(j * 64, i * 64);
                    bt.setTextureRect(IntRect(0, 0, 64, 64));
                    window.draw(bt);
                    break;
                default:
                    continue;
                }
            }
        }

        window.display();
    }

    return 0;
}