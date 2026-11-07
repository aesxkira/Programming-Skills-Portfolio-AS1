#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct Joke {
    std::string setup;
    std::string punchline;
};

// AI assistance: OpenAI ChatGPT helped plan and draft this solution.
// Prompt: "so do everything that needed and make sure evrything is workinh and uploaded to github, work should be excellent and the best"

std::string toLower(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return text;
}

bool loadJokes(std::vector<Joke>& jokes) {
    std::ifstream file("randomJokes.txt");
    if (!file) {
        file.open("Programming Skills Portfolio/Challenge 2 - Joke Program/randomJokes.txt");
    }
    if (!file) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        const std::size_t separator = line.find('?');
        if (separator == std::string::npos) {
            continue;
        }
        std::string punchline = line.substr(separator + 1);
        const std::size_t firstText = punchline.find_first_not_of(" \t");
        if (firstText != std::string::npos) {
            punchline.erase(0, firstText);
        }
        jokes.push_back({line.substr(0, separator + 1), punchline});
    }
    return !jokes.empty();
}

int main() {
    std::vector<Joke> jokes;
    if (!loadJokes(jokes)) {
        std::cout << "Could not load randomJokes.txt or the file contains no valid jokes.\n";
        return 1;
    }

    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<std::size_t> chooseJoke(0, jokes.size() - 1);
    const std::string request = "alexa, tell me a joke";
    std::string input;

    std::cout << "Type 'Alexa, tell me a joke' for a joke, or 'quit' to exit.\n";
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) {
            break;
        }

        const std::string command = toLower(input);
        if (command == "quit") {
            std::cout << "Goodbye!\n";
            break;
        }
        if (command != request) {
            std::cout << "Please use the requested phrase or type 'quit'.\n";
            continue;
        }

        const Joke& joke = jokes[chooseJoke(generator)];
        std::cout << joke.setup << "\nPress Enter to hear the punchline...";
        std::getline(std::cin, input);
        std::cout << joke.punchline << "\n\n";
    }

    return 0;
}
