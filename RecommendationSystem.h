#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H

#include "User.h"
#include <map>
#include <vector>

struct compare_func {
    bool operator()(const sp_movie &movie1, const sp_movie &movie2) const {
        return (*movie1) < (*movie2);
    }
};

typedef std::map<sp_movie, std::vector<double>, compare_func>
        recommendation_map;

class RecommendationSystem {
private:
    recommendation_map _system;
    std::map<std::pair<std::string, int>, sp_movie> movie_map;

    /**
     * @param vec1 first vector
     * @param vec2 second vector
     * @return the first vector multi with the second vector,
     * and the sum by cords
     */
    static double
    multi_vector(std::vector<double> &vec1, std::vector<double> &vec2);

    /**
     * @param vec a vector
     * @return the given vector norm
     */
    static double norm(std::vector<double> &vec);

    /**
     * @param vec1 first vector
     * @param vec2 second vector
     * @return the result of the calculation of the angle
     */
    static double angle_calculation(std::vector<double> &vec1,
                                    std::vector<double> &vec2);

public:

    RecommendationSystem();

    /**
     * adds a new movie to the system
     * @param name name of movie
     * @param year year it was made
     * @param features features for movie
     * @return shared pointer for movie in system
     */
    sp_movie add_movie(const std::string &name, int year,
                       const std::vector<double> &features);


    /**
     * a function that calculates the movie with highest score
     * based on movie features
     * @param ranks user ranking to use for algorithm
     * @return shared pointer to movie in system
     */
    sp_movie recommend_by_content(const User &user);

    /**
     * a function that calculates the movie with highest predicted score
     * based on ranking of other movies
     * @param ranks user ranking to use for algorithm
     * @param k
     * @return shared pointer to movie in system
     */
    sp_movie recommend_by_cf(const User &user, int k);


    /**
     * Predict a user rating for a movie given argument using item cf
     * procedure with k most similar movies.
     * @param user_rankings: ranking to use
     * @param movie: movie to predict
     * @param k:
     * @return score based on algorithm as described in pdf
     */
    double predict_movie_score(const User &user, const sp_movie &movie, int k);

    /**
     * gets a shared pointer to movie in system
     * @param name name of movie
     * @param year year movie was made
     * @return shared pointer to movie in system
     */
    sp_movie get_movie(const std::string &name, int year) const;

    /**
     * output stream operator
     * @param s the output stream
     * @param sys the recommendation system
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &s,
                                    RecommendationSystem &sys);

};


#endif //RECOMMENDATIONSYSTEM_H
