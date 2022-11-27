#include <stdlib.h>

#include <fstream>
#include <iostream>
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
        colors.resize(h, vector<Color>(w, default_color));
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

    int w = 297, h = 421;

    for (int i = 0; i < 10; i++) {
        Color dc = Color(255, 255, 255);
        // Color dc = Color(rand() % 255, rand() % 255, rand() % 255);
        Image image = Image(w, h, dc);
        for (int j = 0; j < 10; j++) {
            int sx = rand() % h;
            int ex = rand() % h;
            if (sx >= ex) swap(sx, ex);
            int sy = rand() % w;
            int ey = rand() % w;
            if (sy >= ey) swap(sy, ey);
            Color c = Color(rand() % 90, rand() % 90, rand() % 90);
            image.addSquare(sx, sy, ex, ey, c);
        }
        // image.out("out/" + to_string(i) + ".ppm");
        image.out("out/" + to_string(rand() % 1000000) + ".ppm");
    }
}
