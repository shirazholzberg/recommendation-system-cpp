#include "UsersLoader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "RecommendationSystem.h"
#define MSG_FILE "problem with reading the file"
#define MSG_SCORE "the score is invalid"
#define LOWER_BOUND 1
#define UPPER_BOUND 10

std::vector<User> UsersLoader::create_users
        (const std::string &users_file_path,
         std::unique_ptr<RecommendationSystem> rs) noexcept(false) {
    std::shared_ptr<RecommendationSystem> sys_ptr= std::move(rs);
    std::ifstream users_file(users_file_path);//opening the file
    if (!users_file.is_open()) {
        throw std::runtime_error(MSG_FILE);
    }
    std::string movie_name, user_name, line;
    int movie_year;
    std::vector<sp_movie> movies;
    if (std::getline(users_file, line)) {//reading movies line:
        std::istringstream my_stream(line);
        std::string name_and_year;
        while (std::getline(my_stream, name_and_year, ' ')) {
            std::istringstream seperated(name_and_year);
            std::getline(seperated, movie_name, YEAR_SEPARATOR);
            seperated >> movie_year;
            sp_movie my_movie = std::make_shared<Movie>(movie_name,
                                                        movie_year);
            movies.push_back(my_movie);
        }
    }
    std::string score_input; //reading a line each time - users:
    double score;
    std::vector<User> users_vec;
    while (std::getline(users_file, line)) {
        std::istringstream my_stream(line);
        my_stream >> user_name; // getting the name of the user
        int index =0;
        rank_map ranks(0,sp_movie_hash, sp_movie_equal);
        while (my_stream >> score_input) { // running on the user's scores
            if (score_input == "NA") {//in case of "NA"
                index++;
                continue;
            }
            score = std::stod(score_input);
            if ((score < LOWER_BOUND) || (score > UPPER_BOUND)) {
                users_file.close();
                throw std::runtime_error(MSG_SCORE);
            }
            ranks[movies[index]] = score;
            index++;
        }
        users_vec.push_back(User(user_name,ranks,sys_ptr));
        my_stream.clear();
    }
    users_file.close();
    return users_vec;
}