#include "User.h"
#include "RecommendationSystem.h"


User::User(const std::string &name, const rank_map &ranks,
           const sys_ptr &recommendations) : _name(name), _ranks(ranks),
                                             _recommendations(
                                                     recommendations) {};

std::string User::get_name() const{
    return _name;
}

void User::add_movie_to_rs(const std::string &name, int year,
                           const std::vector<double> &features,
                           double rate) {
    sp_movie new_movie = std::make_shared<Movie>(name, year);
    _ranks[new_movie] = rate;
    _recommendations->add_movie(name, year, features);
}

rank_map User::get_ranks() const {
    return _ranks;
}

sp_movie User::get_recommendation_by_content() const {
    return _recommendations->recommend_by_content(*this);
}

sp_movie User::get_recommendation_by_cf(int k) const {
    return _recommendations->recommend_by_cf(*this, k);
}

double User::get_prediction_score_for_movie(const std::string &name, int year,
                                            int k) const {
    sp_movie new_movie = std::make_shared<Movie>(name, year);
    return _recommendations->predict_movie_score
            (*this, new_movie, k);
}

std::ostream &operator<<(std::ostream &s, User &user) {
    s << "name: " << user.get_name() << std::endl;
    s << *(user._recommendations) << std::endl;
    return s;
}