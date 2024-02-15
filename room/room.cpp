#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class world {
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

int main()
{
    RenderWindow window(VideoMode(1920, 1080), L"Комната", Style::Default);
    Texture bg,home,blocktr;
    blocktr.loadFromFile("block.jpg");
    bg.loadFromFile("bg.png");
    home.loadFromFile("home.png");
    Sprite bt(blocktr);
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
                else if (TileMap[i][j] == 'A') {
                    for (int num = 0; num < 40; num++) {
                        bt.setPosition(0, 1016);
                        bt.setPosition(j*64, 1016);
                        bt.setTextureRect(IntRect(256, 64, 64, 64));
                        window.draw(bt);
                    }
                }
                else if (TileMap[i][j] == '0') {
                    rectangle.setFillColor(Color::Blue);
                }
                else if (TileMap[i][j] == 'Q') {
                        bt.setPosition(j * 0, i * 64);
                        bt.setTextureRect(IntRect(256, 64, 64, 64));
                        window.draw(bt);  
                }
                else if (TileMap[i][j] == 'W') {
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