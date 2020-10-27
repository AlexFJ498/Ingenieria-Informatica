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
#include "imc/util.h"


using namespace imc;
using namespace std;

int main(int argc, char **argv) {
	// Process the command line
    bool tflag = 0, Tflag = 0, iflag = 0, lflag = 0, hflag = 0, eflag = 0;
    bool mflag = 0, vflag = 0, dflag = 0, fflag = 0, wflag = 0, pflag = 0;
    char *tvalue = NULL, *Tvalue = NULL, *wvalue = NULL;
    int c, ivalue = 0, lvalue = 0, hvalue = 0, dvalue = 0, fvalue = 0, svalue = 0;
    double evalue = 0.0, mvalue = 0, vvalue = 0;
    bool ovalue = false;

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
                ovalue = true;
                break;
            case 'f':
                fflag = true;
                fvalue = atoi(optarg);
                break;
            case 's':
                svalue = 1;
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
        if(!lflag){
            lvalue = 1;
        }
        if(!hflag){
            hvalue = 4;
        }
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
        double nPatterns = 0.0;
        int * index = NULL;
        int *** confusionMatrix = NULL;
        confusionMatrix = new int**[5]();
        int ** bestConfusionMatrix = NULL;
        bestConfusionMatrix = new int*[trainDataset->nOfOutputs];
        double bestccr = 0.0;
        int seed = 0;

        for(int i=0; i<5; i++){
            confusionMatrix[i] = new int*[trainDataset->nOfOutputs]();

            for(int j=0; j<trainDataset->nOfOutputs; j++){
                confusionMatrix[i][j] = new int[trainDataset->nOfOutputs]();
            }
        }

        for(int i=0; i<trainDataset->nOfOutputs; i++){
            bestConfusionMatrix[i] = new int[trainDataset->nOfOutputs]();
        }

        if(mlp.validationRatio > 0 && mlp.validationRatio < 1){
            nPatterns = trainDataset->nOfPatterns * mlp.validationRatio;

            if(nPatterns < 1){
                nPatterns = 1.0;
            }

            srand(time(NULL));
            index = util::integerRandomVectorWithoutRepeating(0, trainDataset->nOfPatterns-1, (int)nPatterns);
        }

		for(int i=0; i<5; i++){
			std::cout << "\n**********" << endl;
			std::cout << "SEED " << seeds[i] << endl;
			std::cout << "**********" << endl;
			srand(seeds[i]);
            std::ostringstream auxnameProblem;
            auxnameProblem << "/pesos/seed_" << i << ".txt";
            nameProblem = auxnameProblem.str();
            
			mlp.runBackPropagation(trainDataset,testDataset,maxIter,&(trainErrors[i]),&(testErrors[i]),&(trainCCRs[i]),&(testCCRs[i]),error, index, nPatterns, nameProblem, confusionMatrix[i]);
			std::cout << "\nWe end!! => Final test CCR: " << testCCRs[i] << endl;

			// We save the weights every time we find a better model
			if(wflag && testErrors[i] <= bestTestError){
				mlp.saveWeights(wvalue);
				bestTestError = testErrors[i];
			}

            if(testCCRs[i] > bestccr){
                bestccr = testCCRs[i];
                bestConfusionMatrix = confusionMatrix[i];
                seed = i;
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

		std::cout << "\nWE HAVE FINISHED WITH ALL THE SEEDS" << endl;

        std::cout<<"\nConfusion Matrix (seed "<<seed<<")"<<std::endl;
        for(int i=0; i<trainDataset->nOfOutputs; i++){
            for(int j=0; j<trainDataset->nOfOutputs; j++){
                std::cout<<bestConfusionMatrix[i][j]<<" ";
            }
            std::cout<<std::endl;
        }

        delete confusionMatrix;
        delete bestConfusionMatrix;

		std::cout << "\nFINAL REPORT" << endl;
		std::cout << "*************" << endl;
	    std::cout << "Train error (Mean +- SD): " << trainAverageError << " +- " << trainStdError << endl;
	    std::cout << "Test error (Mean +- SD): " << testAverageError << " +- " << testStdError << endl;
	    std::cout << "Train CCR (Mean +- SD): " << trainAverageCCR << " +- " << trainStdCCR << endl;
	    std::cout << "Test CCR (Mean +- SD): " << testAverageCCR << " +- " << testStdCCR << endl;
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
            std::exit(-1);
        }

        // Reading training and test data: call to mlp.readData(...)
        Dataset *testDataset;
        testDataset = mlp.readData(Tvalue);
        if(testDataset == NULL)
        {
            cerr << "The test file is not valid, we can not continue" << endl;
            std::exit(-1);
        }

        mlp.predict(testDataset);

        return EXIT_SUCCESS;

	}
}

