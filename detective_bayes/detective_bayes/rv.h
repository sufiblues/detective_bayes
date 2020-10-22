//
//  rv.c
//  detective_bayes
//
//  Created by Ali Hamdani on 10/17/20.
//

#include <stdio.h>
#include <stdbool.h>

enum Relation{LESS_NEQ = 0, LESS_EQ = 1, GREATER_NEQ = 2, GREATER_EQ = 3};

typedef struct RandomVariable{
    float X[10];
    float P[10];
    int storage;
}RandomVariable;

void initRandomVariable(RandomVariable* rv_pointer){
    rv_pointer->X[0] = 0.0f;
    rv_pointer->P[0] = 1.0f;
    for (int i = 1; i < 10; i++){
        rv_pointer->X[i] = 0.0f;
        rv_pointer->P[i] = 0.0f;
    }
    rv_pointer->storage = 1;
}
void addRandomVariable(RandomVariable* rv_pointer, float value, float probability){
    int index = rv_pointer->storage;
    
    if (index >= 10){
        printf("Can't add more values! RandomVariable is full\n");
    }
    //first check to see if there is any probability left to give
    else if(rv_pointer->P[0] < probability){
        printf("Could not add (Value:%f, Probability:%f), max probability left:%f\n", value,probability,rv_pointer->P[0]);
    }
    else{
        rv_pointer->P[0] -=probability;
        rv_pointer->P[index] = probability;
        rv_pointer->X[index] = value;
        rv_pointer->storage += 1;
        printf("Successfully added (Value:%f ,Probability:%f ) at Index %d\n",rv_pointer->X[index] , rv_pointer->P[index], index);
    }
}

void printRandomVariable(RandomVariable rv){
    for (int i = 0; i < rv.storage; i++){
        printf("(Value:%f, Probability:%f)\n",rv.X[i] , rv.P[i]);
    }
}

//TODO: Decide if i still need this, add variable and initrv should make it so that its never not a valid rv.
bool isValidRV(RandomVariable rv){
    double total_probability = 0;
    for (int i = 0; i < rv.storage; i++){
        total_probability+=rv.P[i];
    }
    if (total_probability <= 1){
        return true;
    }
    return false;
}

float probabilityCondition(RandomVariable rv, float condition, int relation){
    float probability = 0.0f;
    for (int i = 0; i < rv.storage; i++){
        if (relation == LESS_NEQ){
            if(rv.X[i] < condition){
                probability += rv.P[i];
            }
        }
        else if(relation == LESS_EQ){
            if(rv.X[i] <= condition){
                probability += rv.P[i];
            }
        }
        else if(relation == GREATER_NEQ){
            if(rv.X[i] > condition){
                probability += rv.P[i];
            }
        }
        else if(relation == GREATER_EQ){
            if(rv.X[i] >= condition){
                probability += rv.P[i];
            }
        }
        else{
            printf("Relation not recognized.\n");
        }
    }
    return probability;
}

//This solves the E[X|X ~ condition] the '~' is the relation enum, ex. >,>=,<,<=
float conditionalExpectation(RandomVariable rv, float condition, int relation){
    //0 for equality, 1 for greater than, 2 for less than
    float expectation = 0;
    //TODO: double count here, can i do better?
    //b is P(X ~ condition)
    float b = probabilityCondition(rv,condition,relation);
    //TODO: Change to cases instead of if else since it looks nicer
    for (int i = 0; i < rv.storage; i++){
        if (relation == LESS_NEQ){
            if(rv.X[i] < condition){
                expectation += rv.X[i]*(rv.P[i]/b);
            }
        }
        else if(relation == LESS_EQ){
            if(rv.X[i] <= condition){
                expectation += rv.X[i]*(rv.P[i]/b);
            }
        }
        else if(relation == GREATER_NEQ){
            if(rv.X[i] > condition){
                expectation += rv.X[i]*(rv.P[i]/b);
            }
        }
        else if(relation == GREATER_EQ){
            if(rv.X[i] >= condition){
                expectation += rv.X[i]*(rv.P[i]/b);
            }
        }
        else{
            printf("Relation not recognized.\n");
        }
    }
    return expectation;
    
}


float expectation(RandomVariable rv){
    float total = 0.0f;
    for(int i = 0; i < 10; i++){
        total+=rv.X[i]*rv.P[i];
    }
    return total;
}

