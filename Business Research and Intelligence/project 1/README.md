# Operational Research and Business Intelligence Project

Project 1 header:

You are given a .csv of 7537 transactions that happened over the last 75 days concerning 170 different products.

Use Python to extract useful information about them using the following techniques:

1. **Data Cleaning and Visualization**
    1. You're given a list of the top 13 products that interest the Marketing Department. Transform the data so irrelevant data are discarded.
    2. Discretize the basket values of each transaction into three uniform categories.
    3. One-Hot-Encode all remaining data.
    4. Use the correct visualization techniques to discover information and reach some first conclusions about the products and/or transactions.
2. **Correlation Rules through the Apriori Method**
    1. Run the Apriori method on the products and discretized basket value exclusively, trying different parameters to achieve the minimum Support.
    2. Find the 20 rules with the highest Confidence concerning solely the products. Mention any rules that surprise you or peak your interest.
    3. Find the 20 rules with the highest Confidence concerning both the products and the discretized basket value. Make a prediction about the most expensive product.
    4. Draw conclusions using these rules. Mention where these new conclusions clash with your first ones and where they agree.
3. **Transaction Clustering using the K-Means Method**
    1. Apply 5-Means clustering on the basket value and the recency days (continuous forms). Plot the results.
    2. Provide the mean and the standard deviation of the centroid of each resulting cluster. Through them, give real-life meaning to each cluster.
       Mention any transaction cluster that should worry the Marketing team, perhaps concerning expensive transactions that took place long ago.
    3. Include the clustering into your dataframe as a new discretized value. One-Hot-Encode and visualize the data once more.
4. **Combination of methods**
    1. Find the 20 rules with the highest Confidence concerning the products and the clusters using Apriori.
        * Name product combinations that appear most in each cluster
        * If you noticed any worrying clusters on task 3, identify the most likely culprit and try to explain the phenomenon.
    2. Find the 20 rules with the highest Confidence concerning the products, the clusters and the discretized basket value. Mention any new interesting rules.

Original header in greek can be found in this directory, courtesy of Aristotle University of Thessalonica, CSD.

    
  

  
