//============================================================================
// Introduction to computational models
// Name        : la1.cpp
// Author      : Alejandro Fuerte Jurado
// Version     : 
// Copyright   : Universidad de Córdoba
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // To obtain current time time()
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <string.h>
#include <math.h>

#include "imc/MultilayerPerceptron.h"


using namespace imc;
using namespace std;

int main(int argc, char **argv) {
    // Process arguments of the command line
    bool tflag = 0, Tflag = 0, iflag = 0, lflag = 0, hflag = 0, eflag = 0;
    bool mflag = 0, vflag = 0, dflag = 0, wflag = 0, pflag = 0;
    char *tvalue = NULL, *Tvalue = NULL, *wvalue = NULL;
    int c, ivalue = 0, lvalue = 0, hvalue = 0, dvalue = 0;
    double evalue = 0.0, mvalue = 0.0, vvalue = 0.0;

    opterr = 0;

    // a: Option that requires an argument
    // a:: The argument required is optional
    while ((c = getopt(argc, argv, "t:T:i:l:h:e:m:v:d:w:p")) != -1)
    {
        // The parameters needed for using the optional prediction mode of Kaggle have been included.
        // You should add the rest of parameters needed for the lab assignment.
        switch(c){
            case 't':
                tflag = true;
                tvalue = optarg;
                break;
            case 'T':
                Tflag = true;
                Tvalue = optarg;
                break;
            case 'i':
                iflag = true;
                ivalue = atoi(optarg);
                break;
            case 'l':
                lflag = true;
                lvalue = atoi(optarg);
                break;
            case 'h':
                lflag = true;
                lvalue = atoi(optarg);
                break;
            case 'e':
                lflag = true;
                lvalue = atof(optarg);
                break;
            case 'm':
                lflag = true;
                lvalue = atof(optarg);
                break;
            case 'v':
                lflag = true;
                lvalue = atof(optarg);
                break;
            case 'd':
                lflag = true;
                lvalue = atoi(optarg);
                break;
            case 'w':
                wflag = true;
                wvalue = optarg;
                break;
            case 'p':
                pflag = true;
                break;
            case '?':
                if (optopt == 't' || optopt == 'T' || optopt == 'i' 
                    || optopt == 'l' || optopt == 'h' || optopt == 'e' 
                    || optopt == 'm' || optopt == 'v' || optopt == 'd' 
                    || optopt == 'w' || optopt == 'p')
                    fprintf (stderr, "The option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown character `\\x%x'.\n",
                             optopt);
                return EXIT_FAILURE;
            default:
                return EXIT_FAILURE;
        }
    }

    if (!pflag) {
        //////////////////////////////////
        // TRAINING AND EVALUATION MODE //
        //////////////////////////////////

        // Multilayer perceptron object
    	MultilayerPerceptron mlp;

        // Parameters of the mlp
        if(!eflag){
            evalue = 0.1;
        }
        mlp.eta = evalue;

        if(!mflag){
            mvalue = 0.9;
        }
        mlp.mu = mvalue;

        if(!vflag){
            vvalue = 0.0;
        }
        mlp.validationRatio = vvalue;

        if(!dvalue){
            dvalue = 1;
        }
        mlp.decrementFactor = dvalue;

        if(!iflag){
            ivalue = 1000;
        }
    	int iterations = ivalue;

        // Read training and test data
        if(!Tflag){
            Tvalue = tvalue;
        }
    	Dataset * trainDataset = mlp.readData(tvalue);
    	Dataset * testDataset = mlp.readData(Tvalue);

        // Initialize topology vector
        if(!lflag){
            lvalue = 1;
        }
    	int layers = lvalue;
    	int * topology = new int[lvalue+2];

        if(!hflag){
            hvalue = 5;
        }
        topology[0] = trainDataset->nOfInputs;
        for(int i=0; i<sizeof(topology); i++){
            topology[i] = hvalue;
        }
        topology[lvalue+2] = trainDataset->nOfOutputs;

        // Initialize the network using the topology vector
        mlp.initialize(layers+2,topology);


        // Seed for random numbers
        int seeds[] = {1,2,3,4,5};
        double *testErrors = new double[5];
        double *trainErrors = new double[5];
        double bestTestError = 1;
        for(int i=0; i<5; i++){
            cout << "**********" << endl;
            cout << "SEED " << seeds[i] << endl;
            cout << "**********" << endl;
            srand(seeds[i]);
            mlp.runOnlineBackPropagation(trainDataset,testDataset,iterations,&(trainErrors[i]),&(testErrors[i]));
            cout << "We end!! => Final test error: " << testErrors[i] << endl;

            // We save the weights every time we find a better model
            if(wflag && testErrors[i] <= bestTestError){
                mlp.saveWeights(wvalue);
                bestTestError = testErrors[i];
            }
        }

        cout << "WE HAVE FINISHED WITH ALL THE SEEDS" << endl;

        double averageTestError = 0, stdTestError = 0;
        double averageTrainError = 0, stdTrainError = 0;
        
        // Obtain training and test averages and standard deviations

        //Averages
        for(int i=0; i<5; i++){
            averageTestError += testErrors[i];
            averageTrainError += trainErrors[i];
        }
        averageTestError /= 5;
        averageTrainError /= 5;

        //Standard deviations
        for(int i=0; i<5; i++){
            stdTestError += pow(testErrors[i] - averageTestError, 2);
            stdTrainError += pow(trainErrors[i] - averageTrainError, 2);
        }
        stdTestError = sqrt(stdTestError / 5);
        stdTrainError = sqrt(stdTrainError / 5);
        

        cout << "FINAL REPORT" << endl;
        cout << "************" << endl;
        cout << "Train error (Mean +- SD): " << averageTrainError << " +- " << stdTrainError << endl;
        cout << "Test error (Mean +- SD):          " << averageTestError << " +- " << stdTestError << endl;
        return EXIT_SUCCESS;
    }
    else {
        //////////////////////////////
        // PREDICTION MODE (KAGGLE) //
        //////////////////////////////
        
        // Multilayer perceptron object
        MultilayerPerceptron mlp;

        // Initializing the network with the topology vector
        if(!wflag || !mlp.readWeights(wvalue))
        {
            cerr << "Error while reading weights, we can not continue" << endl;
            exit(-1);
        }

        // Reading training and test data: call to mlp.readData(...)
        Dataset *testDataset;
        testDataset = mlp.readData(Tvalue);
        if(testDataset == NULL)
        {
            cerr << "The test file is not valid, we can not continue" << endl;
            exit(-1);
        }

        mlp.predict(testDataset);

        return EXIT_SUCCESS;
    }

    
}

