//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica1.cpp
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
#include <float.h> // For DBL_MAX
#include <sstream>

#include "imc/MultilayerPerceptron.h"


using namespace imc;
using namespace std;

int main(int argc, char **argv) {
	// Process the command line
    bool tflag = 0, Tflag = 0, iflag = 0, lflag = 0, hflag = 0, eflag = 0, mflag = 0;
    bool vflag = 0, dflag = 0, oflag = 0, fflag = 0, sflag = 0, wflag = 0, pflag = 0;
    char *tvalue = NULL, *Tvalue = NULL, *wvalue = NULL;
    int c, ivalue = 0, lvalue = 0, hvalue = 0, dvalue = 0, fvalue = 0;
    double evalue = 0.0, mvalue = 0, vvalue = 0;
    bool ovalue = false, svalue = false;

    opterr = 0;

    // a: Option that requires an argument
    // a:: The argument required is optional
    while ((c = getopt(argc, argv, "t:T:i:l:h:e:m:v:d:of:sw:p")) != -1)
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
                hflag = true;
                hvalue = atoi(optarg);
                break;
            case 'e':
                eflag = true;
                evalue = atof(optarg);
                break;
            case 'm':
                mflag = true;
                mvalue = atof(optarg);
                break;
            case 'v':
                vflag = true;
                vvalue = atof(optarg);
                break;
            case 'd':
                dflag = true;
                dvalue = atoi(optarg);
                break;
            case 'o':
                oflag = true;
                ovalue = true;
            case 'f':
                fflag = true;
                fvalue = atoi(optarg);
            case 's':
                sflag = true;
                svalue = true;
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
                    || optopt == 'f' || optopt == 'w' || optopt == 'p')
                    fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Caracter de opción desconocido `\\x%x'.\n",
                             optopt);
                return EXIT_FAILURE;
            default:
                return EXIT_FAILURE;
        }
    }

    if(!tflag && !pflag){
        std::cout<<"Error: Incorrect arguments"<<std::endl;
    }

    if (!pflag) {
        //////////////////////////////////
        // TRAINING AND EVALUATION MODE //
        //////////////////////////////////

        // Multilayer perceptron object
    	MultilayerPerceptron mlp;

        // Parameters of the mlp. For example, mlp.eta = value
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

        if(!dflag){
            dvalue = 1;
        }
        mlp.decrementFactor = dvalue;

        if(!fflag){
            fvalue = 0;
        }

        if(!iflag){
            ivalue = 1000;
        }
        int maxIter = ivalue;

        mlp.online = ovalue;
        mlp.outputFunction = svalue;
    	int error = fvalue; 

        // Read training and test data: call to mlp.readData(...)
        if(!Tflag){
            Tvalue = tvalue;
        }
    	Dataset * trainDataset = mlp.readData(tvalue);
    	Dataset * testDataset = mlp.readData(Tvalue);

        // Initialize topology vector
        int *topology = new int[lvalue+2];
        topology[0] = trainDataset->nOfInputs;
        for(int i=1; i<(lvalue+2-1); i++)
            topology[i] = hvalue;
        topology[lvalue+2-1] = trainDataset->nOfOutputs;
        mlp.initialize(lvalue+2,topology);

		// Seed for random numbers
		int seeds[] = {1,2,3,4,5};
		double *trainErrors = new double[5];
		double *testErrors = new double[5];
		double *trainCCRs = new double[5];
		double *testCCRs = new double[5];
		double bestTestError = DBL_MAX;
        string nameProblem;
		for(int i=0; i<5; i++){
			cout << "\n**********" << endl;
			cout << "SEED " << seeds[i] << endl;
			cout << "**********" << endl;
			srand(seeds[i]);
            std::ostringstream auxnameProblem;
            auxnameProblem << "/pesos/seed_" << i << ".txt";
            nameProblem = auxnameProblem.str();
			mlp.runBackPropagation(trainDataset,testDataset,maxIter,&(trainErrors[i]),&(testErrors[i]),&(trainCCRs[i]),&(testCCRs[i]),error, nameProblem);
			cout << "\nWe end!! => Final test CCR: " << testCCRs[i] << endl;

			// We save the weights every time we find a better model
			if(wflag && testErrors[i] <= bestTestError){
				mlp.saveWeights(wvalue);
				bestTestError = testErrors[i];
			}
		}


		double trainAverageError = 0, trainStdError = 0;
		double testAverageError = 0, testStdError = 0;
		double trainAverageCCR = 0, trainStdCCR = 0;
		double testAverageCCR = 0, testStdCCR = 0;

        // Obtain training and test averages and standard deviations
        
        //Averages
        for(int i=0; i<5; i++){
            trainAverageError += trainErrors[i];
            testAverageError += testErrors[i];
            trainAverageCCR += trainCCRs[i];
            testAverageCCR += testCCRs[i];
        }
        trainAverageError /= 5;
        testAverageError /= 5;
        trainAverageCCR /= 5;
        testAverageCCR /= 5;

        //Standard deviations
        for(int i=0; i<5; i++){
            trainStdError += pow(trainErrors[i] - trainAverageError, 2);
            testStdError += pow(testErrors[i] - testAverageError, 2);
            trainStdCCR += pow(trainCCRs[i] - trainAverageCCR, 2);
            testStdCCR += pow(testCCRs[i] - testAverageCCR, 2);
        }
        trainStdError = sqrt(trainStdError / 5);
        testStdError = sqrt(testStdError / 5);
        trainStdCCR = sqrt(trainStdCCR / 5);
        testStdCCR = sqrt(testStdCCR / 5);

		cout << "\nWE HAVE FINISHED WITH ALL THE SEEDS" << endl;

		cout << "\nFINAL REPORT" << endl;
		cout << "*************" << endl;
	    cout << "Train error (Mean +- SD): " << trainAverageError << " +- " << trainStdError << endl;
	    cout << "Test error (Mean +- SD): " << testAverageError << " +- " << testStdError << endl;
	    cout << "Train CCR (Mean +- SD): " << trainAverageCCR << " +- " << trainStdCCR << endl;
	    cout << "Test CCR (Mean +- SD): " << testAverageCCR << " +- " << testStdCCR << endl;
		return EXIT_SUCCESS;
    } else {
        //////////////////////////////
        // PREDICTION MODE (KAGGLE) //
        //////////////////////////////

        // You do not have to modify anything from here.
        
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

