#include "./include/app/app.h"

int main(int argc, char** argv) {
    Logic::Game game;
    int status = game.Start();
    return (status == EXIT_REQUEST) ? 0 : status;
}
