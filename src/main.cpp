#include <iostream>
#include "GameManager.h"

int main() {
    try {
        GameManager gameManager;
        gameManager.startGame();
        return 0;
    } catch (std::exception &e) {
        std::cout << e.what();
        return -999;
    }

}
