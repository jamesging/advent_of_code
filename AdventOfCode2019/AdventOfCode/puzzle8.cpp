#include "puzzle8.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle8::parsePixels(const std::vector<std::string> &fileContents, std::vector<layer> &layers, int width, int height) {
    int layerNumber = 0;
    int x = 0;
    int y = 0;
    std::map<int, std::map<int, int> > layerSums;
    for(auto &line : fileContents) {
        for (auto &ch : line) {
            if (layers.size() <= layerNumber) {
                layers.push_back(layer());
            }
            if (layers[layerNumber].find(y) == layers[layerNumber].end()) {
                layers[layerNumber][y] = std::map<int, int>();
            }
            if (layers[layerNumber][y].find(x) == layers[layerNumber][y].end()) {
                layers[layerNumber][y][x] = ch-'0';
                if (layerSums.find(layerNumber) == layerSums.end()) {
                    layerSums[layerNumber] = std::map<int, int>();
                }
                if (layerSums[layerNumber].find(layers[layerNumber][y][x]) == layerSums[layerNumber].end()) {
                    layerSums[layerNumber][layers[layerNumber][y][x]] = 0;
                }
                layerSums[layerNumber][layers[layerNumber][y][x]] = layerSums[layerNumber][layers[layerNumber][y][x]] + 1;
            } else {
                printf("Duplicate position, weird\n");
            }
            x++;
            if (x >= width) {
                y++;
                x = 0;
            }
            if (y >= height) {
                layerNumber++;
                x = 0;
                y = 0;
            }
        }
    }
    
    int minZeroes = INT_MAX;
    int minZeroesLayer = -1;
    for (int i = 0;i < layerSums.size();i++) {
        for (auto ch : layerSums[i]) {
            if (ch.first == 0 && ch.second < minZeroes) {
                minZeroes = ch.second;
                minZeroesLayer = i;
            }
        }
    }
    printf("Part one answer: %d\n", layerSums[minZeroesLayer][1] * layerSums[minZeroesLayer][2]);
}

void puzzle8::drawImage(std::vector<layer> &layers) {
    layer image;
    for (auto &layer : layers) {
        for (auto &row : layer) {
            if (image.find(row.first) == image.end()) {
                image[row.first] = std::map<int, int>();
            }
            for (auto &pixel : row.second) {
                if (image[row.first].find(pixel.first) == image[row.first].end()) {
                    image[row.first][pixel.first] = pixel.second;
                }
                if (image[row.first][pixel.first] == 2 && pixel.second < 2) {
                    image[row.first][pixel.first] = pixel.second;
                }
            }
        }
    }
    
    printf("\n");
    for (auto &row : image) {
        for (auto &pixel : row.second) {
            if (pixel.second) {
                printf("%d", pixel.second);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void puzzle8::runPuzzle(...) {
    puzzle8 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle8_input.txt", fileContents);
    
    std::vector<layer> layers;
    puzzle.parsePixels(fileContents, layers, 25, 6);
    
    puzzle.drawImage(layers);
}
