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
    "Q     0                                Q",
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
        rect = FloatRect(100, 960, 0, 56);
        dx = 0.1;
        dy = 0.1;
        f = 3;
    }
    void update(float time) {
        rect.left += dx * time;
        Collision(0);
        dy = dy + 0.0005 * time;
        rect.top += dy * time;
        onGround = false;
        Collision(1);
        f += 0.005 * time;

        if (f > 6) f -= 3;

        if (side == 0) sprite.setTextureRect(IntRect(15, 5, 31, 57));
        if (side == 1) sprite.setTextureRect(IntRect(48, 5, -31, 57));

        if (dx > 0) sprite.setTextureRect(IntRect(80 * int(f), 0, -31, 57));
        if (dx < 0) sprite.setTextureRect(IntRect(80 * int(f), 0, 31, 57));
        sprite.setPosition(rect.left, rect.top);
        dx = 0;
    }
    void Collision(int dir) {
        int left = rect.left / 64;
        int right = (rect.left + rect.width) / 64;
        int top = rect.top / 64;
        int bottom = (rect.top + rect.height) / 64;
        for (int i = top; i <= bottom; i++) {
            for (int j = left; j <= right; j++) {
                char tile = TileMap[i][j];
                if (tile == 'A' || tile == 'W' || tile == 'Q') {
                    if (dir == 0 && !onGround) {
                        if (dx > 0) {
                            rect.left = j * 64 - rect.width;
                        }
                        if (dx < 0) {
                            rect.left = j * 64 + 64;
                        }
                    }
                    if (dir == 1) {
                        if (dy > 0) {
                            rect.top = i * 64 - rect.height;
                            dy = 1;
                            onGround = true;
                        }
                        if (dy < 0) {
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
                    view.move(-0.1, 0);
                }
                side = 1;
                p.dx = -0.2;
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                if (view.getCenter().x + view.getSize().x / 2 < W * 64) {
                    view.move(0.1, 0);
                }
                side = 0;
                p.dx = 0.2;
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