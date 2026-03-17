#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct Image {
    int width;
    int height;
    int max_val;
    vector<Pixel> pixels;
};

void skip(ifstream& file) {
    file >> ws;

    while (file.peek() == '#') {
        string ignore;
        getline(file, ignore);
        file >> ws;
    }
}

Image load_image(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Cannot Open File!");
    }

    string format;
    file >> format;

    if (format != "P6") {
        throw runtime_error("Only PPM P6 format is supported!");
    }

    Image image;
    skip(file);
    file >> image.width >> image.height;
    skip(file);
    file >> image.max_val;
    file.ignore(1);

    image.pixels.resize(image.width * image.height);
    file.read(reinterpret_cast<char*>(image.pixels.data()),image.pixels.size() * sizeof(Pixel));

    return image;
}

void print(const Image& image) {
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            const Pixel& p = image.pixels[i * image.width + j];

            cout << "(" << (int)p.r << ", " << (int)p.g << ", " << (int)p.b << ") ";
        }
        cout << endl;
    }
}

void info(const Image& image) {
    cout << "Width: " << image.width << endl;
    cout << "Height: " << image.height << endl;
    cout << "Max Value: " << image.max_val << endl;
}

void save_image(const string& filename, const Image& image) {
    ofstream file(filename, ios :: binary);

    file << "P6" << endl;
    file << image.width << " " << image.height << endl;
    file << image.max_val << endl;

    file.write(reinterpret_cast<const char*>(image.pixels.data()),image.pixels.size() * sizeof(Pixel));
}

int main() {
    Image image = load_image("test_p6.ppm");

    info(image);
    print(image);

    save_image("output.ppm", image);
    cout << "Processing complete!" << endl;
    return 0;
}