#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <string>

using namespace std;

class Grille {
    bool** grille;
    int longueur;

public:
    // Constructor
    Grille(int lon) {
        if (lon <= 0) throw std::invalid_argument("error length must be >= 1");
        this->longueur = lon;
        grille = new bool*[lon];
        for (int i = 0; i < lon; ++i) {
            grille[i] = new bool[lon];
            for (int j = 0; j < lon; ++j) {
                grille[i][j] = false;
            }
        }
    }

    // Copy Constructor
    Grille(const Grille& other) {
        longueur = other.longueur;
        grille = new bool*[longueur];
        for (int i = 0; i < longueur; ++i) {
            grille[i] = new bool[longueur];
            for (int j = 0; j < longueur; ++j) {
                grille[i][j] = other.grille[i][j];
            }
        }
    }

    // Destructor
    ~Grille() {
        for (int i = 0; i < longueur; ++i) {
            delete[] grille[i];
        }
        delete[] grille;
    }

    // Random Grille static method
    static Grille grille_random(int lon) {
        if (lon <= 0) throw invalid_argument("error length must be >= 1");
        Grille g(lon);
        for (int i = 0; i < lon; ++i) {
            for (int j = 0; j < lon; ++j) {
                g.grille[i][j] = rand() % 2;
            }
        }
        return g;
    }

    int get_length() const {
        return longueur;
    }

    pair<vector<pair<int, int>>, vector<pair<int, int>>> get_True_and_False_neighbors(int i, int j) const {
        vector<pair<int, int>> true_neighbors;
        vector<pair<int, int>> false_neighbors;

        int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1},
                                { 0, -1},         { 0, 1},
                                { 1, -1}, { 1, 0}, { 1, 1}};

        for (auto& direction : directions) {
            int ni = i + direction[0];
            int nj = j + direction[1];

            if (ni >= 0 && ni < longueur && nj >= 0 && nj < longueur) {
                if (grille[ni][nj]) {
                    true_neighbors.push_back({ni, nj});
                } else {
                    false_neighbors.push_back({ni, nj});
                }
            }
        }

        return {true_neighbors, false_neighbors};
    }

    int count_true_neighbors(int i, int j) const {
        return this->get_True_and_False_neighbors(i, j).first.size();
    }

    void setCell(int i, int j, bool state) {
        if (i >= 0 && i < longueur && j >= 0 && j < longueur) {
            grille[i][j] = state;
        }
    }

    bool getCell(int i, int j) const {
        if (i >= 0 && i < longueur && j >= 0 && j < longueur) {
            return grille[i][j];
        }
        return false;
    }
};

class Game {
    Grille grille;

public:
    // Random Game Constructor
    Game() : grille(Grille::grille_random(rand() % 50 + 10)) {}

    // Game Constructor with given length
    Game(int len) : grille(Grille::grille_random(len)) {}

    Grille run_one_term() {
        Grille new_grid(grille);
        for (int i = 0; i < grille.get_length(); i++) {
            for (int j = 0; j < grille.get_length(); j++) {
                int true_neighbors = grille.count_true_neighbors(i, j);
                if (true_neighbors < 2 || true_neighbors > 3) new_grid.setCell(i, j, false);
                else if (true_neighbors == 3) new_grid.setCell(i, j, true);
            }
        }
        this->grille = new_grid;
        return new_grid;
    }

    Grille run_n_terms(int n) {
        for (int i = 0; i < n; i++) {
            run_one_term();
        }
        return grille;
    }

    const Grille& getGrille() const {
        return grille;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "started" << endl;
    Game game(20);
    const int cellSize = 20;
    const int gridSize = game.getGrille().get_length() * cellSize;

    sf::RenderWindow window(sf::VideoMode(gridSize, gridSize), "Game of Life for n = " + std::to_string(gridSize / cellSize));
    cout << "opened window" << endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                cout << "closing game" << endl;
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < game.getGrille().get_length(); i++) {
            for (int j = 0; j < game.getGrille().get_length(); j++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(i * cellSize, j * cellSize);
                if (game.getGrille().getCell(i, j)) {
                    cell.setFillColor(sf::Color::Black);
                } else {
                    cell.setFillColor(sf::Color::White);
                }
                window.draw(cell);
            }
        }
        window.display();
        game.run_one_term();
        sf::sleep(sf::milliseconds(1000)); // Delay to slow down the simulation
    }
    cout << "window closed" << endl;
    return 0;
}

