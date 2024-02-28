#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
int side;
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

class PLAYER {
public:
    float dx;
    float dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float f;

    PLAYER(Texture& image) {
        sprite.setTexture(image);
        rect = FloatRect(3 * 32, 9 * 32, 40, 74);
        dx = 0.1;
        dy = 0.1;
        f = 3;
    }
    void update(float time) {
        rect.left += dx * time;
        Collision(0);
        if (!onGround) dy = dy + 0.0005 * time;
        rect.top += dy * time;
        onGround = false;
        Collision(1);
        f += 0.005 * time;

        if (f > 6) f -= 3;

        if (side == 0) sprite.setTextureRect(IntRect(160, 0, 60, 75));
        if (side == 1) sprite.setTextureRect(IntRect(240, 0, -60, 75));

        if (dx > 0) sprite.setTextureRect(IntRect(80 * int(f), 0, -60, 75));
        if (dx < 0) sprite.setTextureRect(IntRect(80 * int(f), 0, 60, 75));
        sprite.setPosition(rect.left, rect.top);
        dx = 0;
    }

    void Collision(int dir) {
        for (int i = rect.top / 64; i < (rect.top + rect.height) / 64; i++) {
            for (int j = rect.left / 64; j < (rect.left + rect.width) / 64; j++) {
                if (i >= 0 && i < H && j >= 0 && j < W) {
                    if (TileMap[i][j] == 'A') {
                        if ((dx > 0) && (dir == 0)) rect.left = j * 64 - rect.width;
                        if ((dx < 0) && (dir == 0)) rect.left = j * 64 + 64;
                        if ((dy > 0) && (dir == 1)) {
                            rect.top = i * 64 - rect.height;
                            dy = 0;
                            onGround = true;
                        }
                        if ((dy < 0) && (dir == 1)) {
                            rect.top = i * 64 + 64;
                            dy = 0;
                        }
                    }
                    if (TileMap[i][j] == 'W') {
                        if ((dx > 0) && (dir == 0)) rect.left = j * 64 - rect.width;
                        if ((dx < 0) && (dir == 0)) rect.left = j * 64 + 64;
                        if ((dy > 0) && (dir == 1)) {
                            rect.top = i * 64 - rect.height;
                            dy = 0;
                            onGround = true;
                        }
                        if ((dy < 0) && (dir == 1)) {
                            rect.top = i * 64 + 64;
                            dy = 0;
                        }
                    }
                }
            }
        }
    }
};

int main() {
    RenderWindow window(VideoMode(1920, 1080), "Room", Style::None);

    SoundBuffer buffer;
    if (!buffer.loadFromFile("sound.wav")) {
        return -1;
    }

    Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    Texture blocktr, bg, home, player;

    blocktr.loadFromFile("block.jpg");
    bg.loadFromFile("bg.png");
    home.loadFromFile("home.png");
    player.loadFromFile("player.png");

    PLAYER p(player);

    Sprite bt(blocktr);
    Sprite menuBg(bg);
    Sprite Home(home);

    menuBg.setPosition(0, -200);
    Home.setPosition(320, 718);

    View view = window.getDefaultView();
    Clock clock;
    while (window.isOpen()) {
        window.draw(menuBg);
        window.draw(Home);
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            if (view.getCenter().x - view.getSize().x / 2 > 0) {
                view.move(-1.3, 0);
                side = 0;
            }
            p.sprite.move(-3.3, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            if (view.getCenter().x + view.getSize().x / 2 < W * 64) {
                view.move(1.3, 0);
                side = 1;

            }
            p.sprite.move(3.3, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (p.onGround) { p.dy = -0.30; p.onGround = false; }
        }
        p.update(time);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                switch (TileMap[i][j]) {
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
        window.draw(p.sprite);
        window.setView(view);
        window.display();
    }
    return 0;
}