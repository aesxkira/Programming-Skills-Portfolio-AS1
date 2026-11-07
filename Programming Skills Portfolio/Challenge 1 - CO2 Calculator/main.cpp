#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

// AI assistance: OpenAI ChatGPT helped plan and draft this solution.
// Prompt: "check whatyou did on git hub for it and also check all the documents i sent earlier regarrding this assesment and start working on it"

double getDistanceTravelled() {
    double distance = 0.0;

    while (true) {
        std::cout << "Enter the journey distance in miles: ";
        if (std::cin >> distance && distance > 0.0) {
            return distance;
        }

        std::cout << "Please enter a number greater than zero.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string getFuelType() {
    char choice = ' ';

    while (true) {
        std::cout << "Choose fuel type: (D)iesel or (P)etrol: ";
        std::cin >> choice;
        choice = static_cast<char>(std::tolower(static_cast<unsigned char>(choice)));

        if (choice == 'd') {
            return "Diesel";
        }
        if (choice == 'p') {
            return "Petrol";
        }

        std::cout << "Please enter D for diesel or P for petrol.\n";
    }
}

double calculateEmissions(double distance, const std::string& fuelType) {
    const double litresPer100Miles = 9.66;
    const double emissionsPerLitre = (fuelType == "Diesel") ? 2.68 : 2.31;
    const double litresUsed = distance * litresPer100Miles / 100.0;

    return litresUsed * emissionsPerLitre;
}

int main() {
    const double distance = getDistanceTravelled();
    const std::string fuelType = getFuelType();
    const double emissions = calculateEmissions(distance, fuelType);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Estimated CO2 emissions for " << distance << " miles using "
              << fuelType << " are " << emissions << " kg.\n";

    return 0;
}
