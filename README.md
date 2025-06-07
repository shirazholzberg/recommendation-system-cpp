# Recommendation System in C++
This project was implemented as part of a programming course (C & C++) in The Hebrew University.
It implements a movie recommendation system in C++ for media streaming companies.  
It manages users and movies and provides personalized recommendations based on two algorithms:
- Content-based filtering
- Collaborative filtering

# Project Structure
The library is composed of five main classes:
- Movie – Represents a movie in the system.
- User – Represents a user and their movie ratings.
- RecommendationSystem – Provides movie recommendations.
- RecommendationSystemLoader – Loads the recommendation system from file.
- UsersLoader – Loads user data from file.

# Example Files
- print_main.cpp: A sample main program that demonstrates the use of the recommendation system.
- print_main_out.txt: The expected output from running `print_main.cpp`.
- RecommendationSystemLoader_input.txt: Input file used to load movies and their feature vectors.

# How to Complie
Use the provided Makefile (or compile manually if needed). To build both programs:
