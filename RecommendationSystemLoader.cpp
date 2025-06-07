#include "RecommendationSystemLoader.h"
#include <fstream>
#include <sstream>
#include <vector>

#define MSG_FILE "Problem with reading the file"
#define MSG_SCORE "The score is invalid"
#define LOWER_BOUND 1
#define UPPER_BOUND 10
#define YEAR_SEPARATOR '-'

std::unique_ptr<RecommendationSystem>
RecommendationSystemLoader::create_rs_from_movies
        (const std::string &movies_file_path) noexcept(false) {
    //opening the file
    std::ifstream movies_file(movies_file_path);
    if (!movies_file.is_open()) {
        throw std::runtime_error(MSG_FILE);
    }
    std::unique_ptr<RecommendationSystem> result =
            std::make_unique<RecommendationSystem>();
    std::string line;
    std::string movie_name;
    double score;
    int movie_year;
    //reading a line each time
    while (std::getline(movies_file, line)) {
        std::istringstream my_stream(line);
        std::getline(my_stream, movie_name, YEAR_SEPARATOR);
        my_stream >> movie_year;
        std::vector<double> movie_features;
        while (my_stream >> score) {
            if ((score < LOWER_BOUND) || (score > UPPER_BOUND)) {
                movies_file.close();
                throw std::runtime_error(MSG_SCORE);
            }
            movie_features.push_back(score);
        }
        result->add_movie
                (movie_name, movie_year, movie_features);
        my_stream.clear();
    }
    movies_file.close();
    return result;
}