# Multithreaded Pac-Man

A multithreaded Pac-Man clone implemented in C++ using SFML for graphics and audio. The game features a classic Pac-Man maze, pellet and power-pellet mechanics, ghosts with basic AI, and a menu system. Multithreading is used for ghost movement, pellet production/consumption, and UI updates.

## Features

- Classic Pac-Man gameplay with a custom maze
- Multithreaded ghost movement and pellet logic using POSIX threads and semaphores
- SFML-based graphics and sound
- Menu system with keyboard navigation
- Score and lives display
- Power-pellet (boost) mechanic

## Requirements

- C++ compiler (tested with g++)
- [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)
- POSIX threads (pthreads)
- Linux (paths and makefile are set up for Linux)

## Project Structure

```
img/
    menu1.png
    menu2.png
    menu3.png
    menu4.png
new/
    alexandriaflf.ttf
    app
    border.png
    border1.png
    eat_fruit.wav
    lives.png
    main.cpp
    main.o
    makefile
    things.png
    vaca.ttf
    build/
        Debug/
            main.o
```

## How to Build

1. Make sure SFML is installed on your system.
2. Navigate to the `new/` directory.
3. Run:

    ```sh
    make -f makefile
    ```

   Or, if you want to build manually:

    ```sh
    g++ -c ./main.cpp
    g++ main.o -o app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread
    ```

4. Run the game:

    ```sh
    ./app
    ```

## Controls

- Arrow keys: Move Pac-Man
- P: Pause and show menu
- Enter: Select menu option

## Notes

- All assets (images, fonts, sounds) must be present in the correct directories as referenced in the code.
- The game uses multithreading for various tasks; ensure your system supports POSIX threads.
- The game window is sized for a 23x23 grid with additional space for UI.

## Credits

- SFML (https://www.sfml-dev.org/)
- Pac-Man is a trademark of Bandai Namco Entertainment Inc. This project is for educational purposes only.

