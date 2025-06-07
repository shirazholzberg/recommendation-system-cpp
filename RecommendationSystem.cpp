#include "RecommendationSystem.h"
#include <cmath>

RecommendationSystem::RecommendationSystem() = default;

sp_movie RecommendationSystem::add_movie(const std::string &name, int year,
                                         const std::vector<double> &features) {
    sp_movie new_movie = std::make_shared<Movie>(name, year);
    movie_map[{name, year}] = new_movie;
    _system[new_movie] = features;
    return new_movie;
}

double
RecommendationSystem::multi_vector(std::vector<double> &vec1,
                                   std::vector<double> &vec2) {
    double result = 0;
    for (size_t i = 0; i < vec1.size(); i++) {
        result += (vec1[i] * vec2[i]);
    }
    return result;
}

double RecommendationSystem::norm(std::vector<double> &vec) {
    double n = 0;
    for (auto &num: vec) {
        n += num * num;
    }
    double result = sqrt(n);
    return result;
}

double RecommendationSystem::angle_calculation(std::vector<double> &vec1,
                                               std::vector<double> &vec2) {
    double multi = multi_vector(vec1, vec2);
    double norm_multi = norm(vec1) *
                        norm(vec2);
    double result = multi / norm_multi;
    return result;
}

sp_movie RecommendationSystem::recommend_by_content(const User &user) {
    rank_map user_ranks = user.get_ranks();
    double avg = 0;
    size_t movies_amount = user_ranks.size();
    for (auto &movie_rank: user_ranks) {
        avg += movie_rank.second;
    }
    avg = avg / movies_amount;
    for (auto &movie_rank: user_ranks) {
        movie_rank.second -= avg;
    }
    size_t size = (_system.begin())->second.size();
    std::vector<double> user_fav(size);
    for (auto &movie: user_ranks) {
        for (size_t i = 0; i < size; ++i) {
            user_fav[i] += _system[movie.first][i] * movie.second;
        }
    }
    double max = -1;
    sp_movie max_ptr = nullptr;
    for (auto &movie: _system) {
        if (user_ranks.find(movie.first) == user_ranks.end()) {
            double result = angle_calculation(user_fav,
                                              _system[movie.first]);
            if (result > max) {
                max = result;
                max_ptr = movie.first;
            }
        }
    }
    return max_ptr;
}

sp_movie RecommendationSystem::recommend_by_cf(const User &user, int k) {
    //taking the first out
    double max = predict_movie_score
            (user, user.get_ranks().begin()->first, k);
    sp_movie recommended_movie = nullptr;
    for (auto &movie: _system) {
        if (user.get_ranks().find(movie.first) == user.get_ranks().end()) {
            double result = predict_movie_score(user, movie.first, k);
            if (result > max) {
                max = result;
                recommended_movie = movie.first;
            }
        }
    }
    return recommended_movie;
}

double RecommendationSystem::predict_movie_score(const User &user,
                                                 const sp_movie &movie,
                                                 int k) {
    double result;
    std::multimap<double, sp_movie> k_movies;
    for (auto &watched_movie: user.get_ranks()) {
        result = angle_calculation(_system[movie],
                                   _system[watched_movie.first]);
        k_movies.insert({result, watched_movie.first});
    }
    double up = 0, down = 0;
    auto map_it = k_movies.rbegin();
    for (int i = 0; i < k && map_it != k_movies.rend(); ++i) {
        up += map_it->first * user.get_ranks()[map_it->second];
        down += map_it->first;
        map_it++;
    }
    return up / down;
}

sp_movie
RecommendationSystem::get_movie(const std::string &name, int year) const {
    auto it = movie_map.find({name, year});
    if (it != movie_map.end()) {
        return it->second;
    }
    return nullptr;
}


std::ostream &operator<<(std::ostream &s, RecommendationSystem &sys) {
    for (auto &movie: sys._system) {
        s << *(movie.first);
    }
    return s;
}