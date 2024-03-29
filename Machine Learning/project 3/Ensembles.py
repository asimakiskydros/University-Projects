# -*- coding: utf-8 -*-
"""3881_Ασημάκης_Κύδρος_asimakis@csd.auth.gr_Ensembles2023.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1IG1wwP_Lyu3WTnRDsLAIpHWVIf55KoId

## About iPython Notebooks ##

iPython Notebooks are interactive coding environments embedded in a webpage. You will be using iPython notebooks in this class. Make sure you fill in any place that says `# BEGIN CODE HERE #END CODE HERE`. After writing your code, you can run the cell by either pressing "SHIFT"+"ENTER" or by clicking on "Run" (denoted by a play symbol). Before you turn this problem in, make sure everything runs as expected. First, **restart the kernel** (in the menubar, select Kernel$\rightarrow$Restart) and then **run all cells** (in the menubar, select Cell$\rightarrow$Run All).

 **What you need to remember:**

- Run your cells using SHIFT+ENTER (or "Run cell")
- Write code in the designated areas using Python 3 only
- Do not modify the code outside of the designated areas
- In some cases you will also need to explain the results. There will also be designated areas for that.

Fill in your **NAME** and **AEM** below:
"""

NAME = "Ασημάκης Κύδρος"
AEM = "3881"

"""---

# Assignment 3 - Ensemble Methods #

Welcome to your third assignment. This exercise will test your understanding on Ensemble Methods.
"""

# Always run this cell
import numpy as np
import pandas as pd

# USE THE FOLLOWING RANDOM STATE FOR YOUR CODE
RANDOM_STATE = 42

"""## Download the Dataset ##
Download the dataset using the following cell or from this [link](https://github.com/sakrifor/public/tree/master/machine_learning_course/EnsembleDataset) and put the files in the same folder as the .ipynb file.
In this assignment you are going to work with a dataset originated from the [ImageCLEFmed: The Medical Task 2016](https://www.imageclef.org/2016/medical) and the **Compound figure detection** subtask. The goal of this subtask is to identify whether a figure is a compound figure (one image consists of more than one figure) or not. The train dataset consits of 4197 examples/figures and each figure has 4096 features which were extracted using a deep neural network. The *CLASS* column represents the class of each example where 1 is a compoung figure and 0 is not.

"""

import urllib.request
url_train = 'https://github.com/sakrifor/public/raw/master/machine_learning_course/EnsembleDataset/train_set.csv'
filename_train = 'train_set.csv'
urllib.request.urlretrieve(url_train, filename_train)
url_test = 'https://github.com/sakrifor/public/raw/master/machine_learning_course/EnsembleDataset/test_set_noclass.csv'
filename_test = 'test_set_noclass.csv'
urllib.request.urlretrieve(url_test, filename_test)

# Run this cell to load the data
train_set = pd.read_csv("train_set.csv").sample(frac=1).reset_index(drop=True)
train_set.head()
X = train_set.drop(columns=['CLASS'])
y = train_set['CLASS'].values

!pip install -U imbalanced-learn

"""The following code will reduce the number of instances, dealing with the small imbalance of the dataset, as well as reducing the size of the dataset!"""

from collections import Counter
from imblearn.under_sampling import NeighbourhoodCleaningRule, RandomUnderSampler

ncr = NeighbourhoodCleaningRule()
X_res, y_res = ncr.fit_resample(X, y)
rus = RandomUnderSampler(random_state=42)
X_res, y_res = rus.fit_resample(X_res, y_res)
print('Resampled dataset shape %s' % Counter(y_res))
X = X_res
y = y_res

"""## 1.0 Testing different ensemble methods ##
In this part of the assignment you are asked to create and test different ensemble methods using the train_set.csv dataset. You should use **5-fold cross validation** for your tests and report the average f-measure weighted and balanced accuracy of your models. You can use [cross_validate](https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.cross_validate.html#sklearn.model_selection.cross_validate) and select both metrics to be measured during the evaluation.

### !!! Use n_jobs=-1 where is posibble to use all the cores of a machine for running your tests ###

### 1.1 Voting ###
Create a voting classifier which uses two **simple** estimators/classifiers. Test both soft and hard voting and report the results. Consider as simple estimators the following:


*   Decision Trees
*   Linear Models
*   KNN Models
"""

### BEGIN SOLUTION

from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import VotingClassifier
from sklearn.model_selection import train_test_split, cross_validate
from sklearn.metrics import get_scorer_names

# USE RANDOM STATE!

cls1 = LogisticRegression(max_iter=1000, random_state=RANDOM_STATE)
cls2 = DecisionTreeClassifier(max_depth=5, random_state=RANDOM_STATE)
soft_vcls = VotingClassifier([('lr', cls1), ('dt', cls2)], voting='soft', n_jobs=-1)
hard_vcls = VotingClassifier([('lr', cls1), ('dt', cls2)], voting='hard', n_jobs=-1)

svlcs_scores = cross_validate(soft_vcls, X, y, scoring=('f1_weighted', 'balanced_accuracy'), n_jobs=-1)
s_avg_fmeasure = svlcs_scores['test_f1_weighted'].mean()
s_avg_accuracy = svlcs_scores['test_balanced_accuracy'].mean()

hvlcs_scores = cross_validate(hard_vcls, X, y, scoring=('f1_weighted', 'balanced_accuracy'), n_jobs=-1)
h_avg_fmeasure = hvlcs_scores['test_f1_weighted'].mean()
h_avg_accuracy = hvlcs_scores['test_balanced_accuracy'].mean()

### END SOLUTION

print("Classifier:")
print(soft_vcls)
print("F1 Weighted-Score: {} & Balanced Accuracy: {}".format(round(s_avg_fmeasure,4), round(s_avg_accuracy,4)))

print("Classifier:")
print(hard_vcls)
print("F1 Weighted-Score: {} & Balanced Accuracy: {}".format(round(h_avg_fmeasure,4), round(h_avg_accuracy,4)))

"""For both soft/hard voting classifiers the F1 weighted score should be above 0.74 and 0.79, respectively, and for balanced accuracy 0.74 and 0.80. Remember! This should be the average performance of each fold, as measured through cross-validation with 5 folds!

### 1.2 Randomization

You are asked to create three ensembles of decision trees where each one uses a different method for producing homogeneous ensembles. Compare them with a simple decision tree classifier and report your results in the dictionaries (dict) below using as key the given name of your classifier and as value the f1_weighted/balanced_accuracy score. The dictionaries should contain four different elements. Use the same cross-validation approach as before!
"""

### BEGIN SOLUTION
from sklearn.ensemble import BaggingClassifier, RandomForestClassifier, AdaBoostClassifier

ens1 = BaggingClassifier(DecisionTreeClassifier(max_depth=5), random_state=RANDOM_STATE, n_jobs=-1)
ens2 = RandomForestClassifier(random_state=RANDOM_STATE, n_jobs=-1)
ens3 = AdaBoostClassifier(DecisionTreeClassifier(max_depth=5), random_state=RANDOM_STATE)
tree = DecisionTreeClassifier(max_depth=5, random_state=RANDOM_STATE)

scores_ens1 = cross_validate(ens1, X, y, scoring=('f1_weighted', 'balanced_accuracy'), n_jobs=-1)
scores_ens2 = cross_validate(ens1, X, y, scoring=('f1_weighted', 'balanced_accuracy'), n_jobs=-1)
scores_ens3 = cross_validate(ens3, X, y, scoring=('f1_weighted', 'balanced_accuracy'), n_jobs=-1)
scores_tree = cross_validate(tree, X, y, scoring=('f1_weighted', 'balanced_accuracy'), n_jobs=-1)

f_measures = {
    'Bagging': scores_ens1['test_f1_weighted'].mean(),
    'Random Forest': scores_ens2['test_f1_weighted'].mean(),
    'Ada Boost': scores_ens3['test_f1_weighted'].mean(),
    'Simple Decision': scores_tree['test_f1_weighted'].mean()
}
accuracies = {
    'Bagging': scores_ens1['test_balanced_accuracy'].mean(),
    'Random Forest': scores_ens2['test_balanced_accuracy'].mean(),
    'Ada Boost': scores_ens3['test_balanced_accuracy'].mean(),
    'Simple Decision': scores_tree['test_balanced_accuracy'].mean()
}
# Example f_measures = {'Simple Decision':0.8551, 'Ensemble with random ...': 0.92, ...}


### END SOLUTION

print(ens1)
print(ens2)
print(ens3)
print(tree)
for name,score in f_measures.items():
    print("Classifier: {} -  F1 Weighted: {}".format(name,round(score,4)))
for name,score in accuracies.items():
    print("Classifier: {} -  BalancedAccuracy: {}".format(name,round(score,4)))

"""### 1.3 Question

Increasing the number of estimators in a bagging classifier can drastically increase the training time of a classifier. Is there any solution to this problem? Can the same solution be applied to boosting classifiers?

Parallelizing the cross validation of the bagging classifier with as many cores as possible will give a noticable performance improvement. This is also true for other classifiers, such as Random Forests.

This tactic unfortunately cannot be applied to boosting classifiers, such as AdaBoost used above, as their estimators have to learn from each other. Thus parallelization is unfeasible.

## 2.0 Creating the best classifier ##
In the second part of this assignment, we will try to train the best classifier, as well as to evaluate it using stratified cross valdiation.

### 2.1 Good Performing Ensemble

In this part of the assignment you are asked to train a good performing ensemble, that is able to be used in a production environment! Describe the process you followed to achieve this result. How did you choose your classifier and your parameters and why. Report the f-measure (weighted) & balanced accuracy, using 10-fold stratified cross validation, of your final classifier. Can you achieve a balanced accuracy over 88%, while keeping the training time low? (Tip 1: You can even use a model from the previous parts, but you are advised to test additional configurations, and ensemble architectures, Tip 2: If you try a lot of models/ensembles/configurations or even grid searches, in your answer leave only the classifier you selected as the best!)
"""

### BEGIN SOLUTION
from xgboost import XGBClassifier

best_cls = XGBClassifier(n_estimators=100, tree_method='gpu_hist')
scores_bcls = cross_validate(best_cls, X, y, cv=10, scoring=('f1_weighted', 'balanced_accuracy'), n_jobs=-1)
best_fmeasure = scores_bcls['test_f1_weighted'].mean()
best_accuracy = scores_bcls['test_balanced_accuracy'].mean()
### END SOLUTION

print("Classifier:")
#print(best_cls)
print("F1 Weighted-Score: {} & Balanced Accuracy: {}".format(best_fmeasure, best_accuracy))

"""LEAVE HERE ANY COMMENTS ABOUT YOUR CLASSIFIER

### 2.2 Question
 What other ensemble architectures you tried, and why you did not choose them as your final classifier?

I didn't use any other architectures, as I already knew Microsoft's XGBooster to be one of the best choices that juggles good time performance and high accuracy.

### 2.3 Setup the Final Classifier
Finally, in this last cell, set the cls variable to either the best model as occured by the stratified cross_validation, or choose to retrain your classifier in the whole dataset (X, y). There is no correct answer, but try to explain your choice. Then, save your model using pickle and upload it with your submission to e-learning!
"""

import pickle

### BEGIN SOLUTION

# I chose to retrain the model in the whole dataset because
# either way it scores very well and also, it wouldn't let me
# pass it without invoking 'fit' in this code box again.
cls = XGBClassifier(n_estimators=100, tree_method='gpu_hist')
cls.fit(X, y)
# save with pickle
file_name = "xgbcls.pkl"
pickle.dump(cls, open(file_name, 'wb'))
### END SOLUTION


# load
cls = pickle.load(open(file_name, "rb"))

test_set = pd.read_csv("test_set_noclass.csv")
predictions = cls.predict(test_set)

# We are going to run the following code
if False:
  from sklearn.metrics import f1_score, balanced_accuracy_score
  final_test_set = pd.read_csv('test_set.csv')
  ground_truth = final_test_set['CLASS']
  print("Balanced Accuracy: {}".format(balanced_accuracy_score(predictions, ground_truth)))
  print("F1 Weighted-Score: {}".format(f1_score(predictions, ground_truth, average='weighted')))

"""Both metrics should aim above 82%! This is going to be tested by us! Make sure your cross validation or your retrained model achieves high balanced accuracy and f1_score (based on 2.1) (more than 88%) as it should achieve at least 82% in our unknown test set!

Please provide your feedback regarding this project! Did you enjoy it?
"""

# Pretty solid and enjoyable test.
# As per the last one, I liked having a lot of freedom in how I will solve each task.
# I have no real complaints.

# (why a code box? xd)

pass