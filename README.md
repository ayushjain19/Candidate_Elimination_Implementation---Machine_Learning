# Candidate_Elimination_Implementation---Machine_Learning

This includes implementation of Candidate Elimination Algorithm. The training data is taken from the file provided above, named "data.txt". The source of this dataset can be found [here](http://archive.ics.uci.edu/ml/machine-learning-databases/zoo/).

The Algorithm is described below:

- Initialize G, the set of maximally general hypotheses, to contain one element: the null description (all features are variables).
- Initialize S, the set of maximally specific hypotheses, to contain one element: the first positive example.
- Accept a new training example.
  - If the example is positive:
    1. Generalize all the specific models to match the positive example, but ensure the following:
        - The new specific models involve minimal changes.
        - Each new specific model is a specialization of some general model.
        - No new specific model is a generalization of some other specific model.
    2. Prune away all the general models that fail to match the positive example.
  - If the example is negative:
    1. Specialize all general models to prevent match with the negative example, but ensure the following:
        - The new general models involve minimal changes.
        - Each new general model is a generalization of some specific model.
        - No new general model is a specialization of some other general model.
    2. Prune away all the specific models that match the negative example.
  - If S and G are both singleton sets, then:
    - if they are identical, output their value and halt.
    - if they are different, the training cases were inconsistent. Output this result and halt.
    - else continue accepting new training examples.
