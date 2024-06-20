# MnemonicAid CLI

MnemonicAid CLI is a command-line application designed to help users improve their memory skills through various mnemonic games. The application currently includes three games: Card Game, Numbers Game, and Words Game. Users can configure game settings, play the games, and receive feedback on their performance.

## Background

I started working on MnemonicAid CLI due to my disappointment with the official memory leagues' paywall. I wanted a free, accessible tool to practice and improve my memory skills without any barriers. This project is still very rough around the edges and is in active development. However, as a tool that I plan to use frequently, it will receive consistent support and updates.

## CLI Only Application

MnemonicAid CLI is a command-line interface (CLI) only application and must be run from a terminal. It is compatible with Windows, macOS, and Linux. Make sure you have a terminal or command prompt available to run this application. There is currently some personal desire to migrate to a gui application or a web application, but there are currently no plans or roadmaps to make that a reality.

### Windows Compatibility

Ensure that you have a terminal or command prompt available. On Windows, you can use Command Prompt, PowerShell, or Windows Terminal. To compile the program, you may need to install a C++ compiler such as MinGW or use the Windows Subsystem for Linux (WSL).

## Pre-Install Requirements

### Windows

1. **Install MinGW:**
    - Download and install MinGW from [MinGW official site](http://www.mingw.org/).
    - During installation, ensure you select the C++ compiler and `msys-base` package.
    - Add the `bin` directory of MinGW to your system's PATH environment variable.

2. **Install Windows Subsystem for Linux (WSL):**
    - Follow the instructions from [Microsoft's WSL installation guide](https://docs.microsoft.com/en-us/windows/wsl/install).
    - Once WSL is installed, you can use a Linux distribution from the Microsoft Store (e.g., Ubuntu) to run Linux commands and tools.

### macOS

1. **Install Homebrew (if not already installed):**
    ```bash
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```

2. **Install GNU Make and GCC:**
    ```bash
    brew install make gcc
    ```

### Linux

1. **Install Build-Essential:**
    - On Debian-based distributions (e.g., Ubuntu):
        ```bash
        sudo apt update
        sudo apt install build-essential
        ```

    - On Red Hat-based distributions (e.g., Fedora):
        ```bash
        sudo dnf group install "Development Tools"
        ```

    - On Arch-based distributions (e.g., Arch Linux):
        ```bash
        sudo pacman -S base-devel
        ```

## Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/yourusername/MnemonicAid-cli.git
    cd MnemonicAid-cli
    ```

2. **Build the project:**
    ```bash
    make
    ```

3. **Run the application:**
    ```bash
    ./bin/mnemonic_aid
    ```

## Usage

After running the application, you will be presented with a main menu where you can choose which game to play or configure settings.

## Games

### Card Game

In the Card Game, you will memorize a series of cards drawn from a shuffled deck. The game phases include:

1. **Preparation Phase:** A timer during which you can prepare for the game.
2. **Memorization Phase:** You are shown a series of cards to memorize.
3. **Recall Phase:** You input the cards you remember.
4. **Review Phase:** Your recall is compared to the original series, and you receive feedback on your performance.

### Numbers Game

In the Numbers Game, you will memorize a series of randomly generated numbers. The game phases include:

1. **Preparation Phase:** A timer during which you can prepare for the game.
2. **Memorization Phase:** You are shown a series of numbers to memorize.
3. **Recall Phase:** You input the numbers you remember.
4. **Review Phase:** Your recall is compared to the original series, and you receive feedback on your performance.

### Words Game

In the Words Game, you will memorize a series of randomly selected words. The game phases include:

1. **Preparation Phase:** A timer during which you can prepare for the game.
2. **Memorization Phase:** You are shown a series of words to memorize.
3. **Recall Phase:** You input the words you remember.
4. **Review Phase:** Your recall is compared to the original series, and you receive feedback on your performance.

## Configuration

Each game has configurable settings that can be adjusted in the options menu:

- **Card Game:**
  - Number of decks
  - Number of draws

- **Numbers Game:**
  - Number of digits per number
  - Number of rows

- **Words Game:**
  - Number of words per row
  - Number of rows

Additionally, you can configure the preparation, memorization, and recall times for each game.

## Contributing

Contributions are welcome! If you have suggestions for improvements or new features, please submit an issue or pull request.

1. Fork the repository
2. Create a new branch (`git checkout -b feature-branch`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature-branch`)
5. Create a new Pull Request

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

