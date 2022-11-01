#include <stdlib.h>

#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Color {
    unsigned char r, g, b;
    Color() {
        r = 0;
        g = 0;
        b = 0;
    }
    Color(unsigned char red, unsigned char green, unsigned char blue) {
        r = red;
        g = green;
        b = blue;
    }
    void mix(Color c) {
        r -= c.r;
        g -= c.g;
        b -= c.b;
    }
};

struct Image {
    int w, h;
    vector<vector<Color>> colors;
    Image(int width, int height, Color default_color) {
        w = width;
        h = height;
        colors.resize(w, vector<Color>(height, default_color));
    }
    void addSquare(int sx, int sy, int ex, int ey, Color c) {
        for (size_t x = sx; x < ex; x++) {
            for (size_t y = sy; y < ey; y++) {
                colors[x][y].mix(c);
            }
        }
    }
    void out(string path) {
        ofstream img(path);
        img << "P3" << endl;
        img << w << " " << h << endl;
        img << "255" << endl;

        for (auto &&asd : colors) {
            for (auto &&c : asd) {
                img << (int)c.r << " " << (int)c.g << " " << (int)c.b << endl;
            }
        }
        img.close();
    }
};

int main() {
    srand(time(0));

    int width = 255, height = 255;
    Color default_color = Color(255, 255, 255);

    for (int i = 0; i < 10; i++) {
        Image image = Image(width, height, default_color);
        for (int j = 0; j < 10; j++) {
        gen_x:
            int sx = rand() % width;
            int ex = rand() % width;
            if (sx >= ex) goto gen_x;
        gen_y:
            int sy = rand() % height;
            int ey = rand() % height;
            if (sy >= ey) goto gen_y;
            Color c = Color(rand() % 100, rand() % 100, rand() % 100);
            image.addSquare(sx, sy, ex, ey, c);
        }
        image.out("out/" + to_string(i) + ".ppm");
    }
}
