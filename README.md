# PageRank-Algorithm
This is a search engine that implements and calculates the PageRank algorithm for any number of websites in a single webgraph.
It creates the matrix of probabilities and calculates the PageRank of each website using matrix-vector multiplication. This program is also capable of dealing with the case of calculating the PageRank even with the existence of dangling nodes in any webgraph.
It sorts the websites according to their scores. These scores are calculated using the formula that involves: CTR(Click Through Rates), the number of clicks, number of impressions and PageRank of each website.

Available functionalities:
- You can search for a single word from the keywords in the keywords.csv file
- You can use "AND" to search for sites that have the same keywords
- You can use "OR" to search for all possible sites that have the entered keywords
- You can enter the desired words between double quotations to search for it as it is

Created this project for the lab of the following course: Analysis & Design of Algorithms in Fall 2021 at AUC.
