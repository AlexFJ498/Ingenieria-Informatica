/*********************************************************************
* File  : MultilayerPerceptron.cpp
* Date  : 2020
*********************************************************************/

#include "MultilayerPerceptron.h"

#include "util.h"


#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <math.h>


using namespace imc;
using namespace std;
using namespace util;

// ------------------------------
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron() {
	this->nOfLayers = 3;
	this->eta = 0.7;
	this->mu = 1.0;
	this->online = false;
	this->validationRatio = 0.0;
	this->decrementFactor = 1.0;
	this->outputFunction = 0;
	this->nOfTrainingPatterns = 1.0;
}

// ------------------------------
// Allocate memory for the data structures
// nl is the number of layers and npl is a vetor containing the number of neurons in every layer
// Give values to Layer* layers
void MultilayerPerceptron::initialize(int nl, int npl[]) {
	this->nOfLayers = nl;
	int nOfNeuronsPrev = 0;

	for(int i=0; i<this->nOfLayers;i++){
		Layer l;
		l.nOfNeurons = npl[i];

		//Layer 0
		if(i == 0){
			for(int j=0; j<l.nOfNeurons; j++){
				Neuron n;
				n.w = NULL;
				n.deltaW = NULL;
				n.lastDeltaW = NULL;
				n.wCopy = NULL;

				l.neurons.push_back(n);
			}

			this->layers.push_back(l);
			nOfNeuronsPrev = l.nOfNeurons;

			continue;
		}

		//Layers 1 - H
		for(int j=0; j<l.nOfNeurons; j++){
			Neuron n;
			n.w = new double[nOfNeuronsPrev + 1];
			n.deltaW = new double[nOfNeuronsPrev + 1];
			n.lastDeltaW = new double[nOfNeuronsPrev + 1];
			n.wCopy = new double[nOfNeuronsPrev + 1];		

			for(int k=0; k<(nOfNeuronsPrev + 1); k++){
				n.w[k] = 0.0;
				n.deltaW[k] = 0.0;
				n.lastDeltaW[k] = 0.0;
				n.wCopy[k] = 0.0;
			}

			l.neurons.push_back(n);
		}

		this->layers.push_back(l);
		nOfNeuronsPrev = l.nOfNeurons;
	}
}


// ------------------------------
// DESTRUCTOR: free memory
MultilayerPerceptron::~MultilayerPerceptron() {
	freeMemory();
}


// ------------------------------
// Free memory for the data structures
void MultilayerPerceptron::freeMemory() {
	layers.clear();
	std::vector<Layer>().swap(layers);
}

// ------------------------------
// Fill all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {
	for(int i=1; i<this->nOfLayers; i++){
		for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
			for(int k=0; k<this->layers.at(i-1).nOfNeurons + 1; k++){
				this->layers.at(i).neurons.at(j).w[k] = (rand()/(double)RAND_MAX)*(1-(-1)) + (-1);
			}
		}
	}
}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputs(double* input) {
	for(int i=0; i<this->layers.at(0).nOfNeurons; i++){
		this->layers.at(0).neurons.at(i).out = input[i];
	}
}

// ------------------------------
// Get the outputs predicted by the network (out vector of the output layer) and save them in the vector passed as an argument
void MultilayerPerceptron::getOutputs(double* output) {
	for(int i=0; i<this->layers.at(this->nOfLayers - 1).nOfNeurons; i++){
		output[i] = this->layers.at(this->nOfLayers - 1).neurons.at(i).out;
	}
}

// ------------------------------
// Make a copy of all the weights (copy w in wCopy)
void MultilayerPerceptron::copyWeights() {
	for(int i=1; i<this->nOfLayers; i++){
		for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
			for(int k=0; k<this->layers.at(i-1).nOfNeurons + 1; k++){
				this->layers.at(i).neurons.at(j).wCopy[k] = this->layers.at(i).neurons.at(j).w[k];
			}
		}
	}
}

// ------------------------------
// Restore a copy of all the weights (copy wCopy in w)
void MultilayerPerceptron::restoreWeights() {
	for(int i=1; i<this->nOfLayers; i++){
		for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
			for(int k=0; k<this->layers.at(i-1).nOfNeurons + 1; k++){
				this->layers.at(i).neurons.at(j).w[k] = this->layers.at(i).neurons.at(j).wCopy[k];
			}
		}
	}
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {
	double net;
	double *sumNet = new double[this->nOfLayers-1];

	for(int i=1; i<this->nOfLayers; i++){
		sumNet[i-1] = 0.0;
		for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
			net = 0.0;
			for(int k=1; k<this->layers.at(i-1).nOfNeurons +1; k++){
				net += this->layers[i].neurons[j].w[k] * this->layers[i-1].neurons[k-1].out;
			}

			net += this->layers[i].neurons[j].w[0];

			if((i == (this->nOfLayers - 1)) && (this->outputFunction == 1)){
				this->layers.at(i).neurons.at(j).out = exp(net);
				sumNet[i-1] += exp(net);
			}
			else{
				this->layers.at(i).neurons.at(j).out = 1.0 / (1 + exp(-net));
			}
		}

		if((i == (this->nOfLayers - 1)) && (this->outputFunction == 1)){
			for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
				this->layers[i].neurons[j].out /= sumNet[i-1];
			}
		}
	}

	delete sumNet;
/*
	
	double net, sumSoftmax = 0.0;

	//Array used in softmax to save neurons net in the last layer
	double* netArray = new double(this->layers.at(this->nOfLayers - 1).nOfNeurons);

	for(int i=1; i<this->nOfLayers; i++){
		for(int j=0;j<this->layers.at(i).nOfNeurons; j++){
			net = 0.0;
			for(int k=1; k<this->layers.at(i-1).nOfNeurons + 1; k++){
				net += this->layers.at(i).neurons.at(j).w[k] * this->layers.at(i-1).neurons.at(k-1).out;
			}
			net += this->layers.at(i).neurons.at(j).w[0];

			if(i == (this->nOfLayers - 1) && this->outputFunction == 1){
				sumSoftmax += exp(net);
				netArray[j] = net;
			}
			else{
				this->layers.at(i).neurons.at(j).out = 1.0 / (1 + exp(-net));
			}
		}
	}

	//SoftMax
	if(this->outputFunction == 1){
		for(int i=0; i<this->layers.at(this->nOfLayers - 1).nOfNeurons; i++){
			this->layers.at(this->nOfLayers - 1).neurons.at(i).out = exp(netArray[i]) / sumSoftmax;
		}
	}		

	delete netArray;
	*/
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::obtainError(double* target, int errorFunction) {
	//MSE
	if(errorFunction == 0){
		double mse = 0.0;

		for(int i=0; i<this->layers.at(this->nOfLayers-1).nOfNeurons; i++){
			mse += pow(target[i] - this->layers.at(this->nOfLayers - 1).neurons.at(i).out, 2);
		}

		return mse / (double)this->layers.at(this->nOfLayers - 1).nOfNeurons;
	}

	//Cross Entropy
	double ce = 0.0;

	for(int i=0; i<this->layers.at(this->nOfLayers-1).nOfNeurons;i++){
		ce += target[i] * log(this->layers.at(this->nOfLayers - 1).neurons.at(i).out);
	}

	return ce / (double)this->layers.at(this->nOfLayers - 1).nOfNeurons;
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::backpropagateError(double* target, int errorFunction) {
	double out, aux;

	for(int i=0; i<this->layers.at(this->nOfLayers-1).nOfNeurons; i++){
		out = this->layers.at(nOfLayers-1).neurons.at(i).out;
		this->layers.at(this->nOfLayers-1).neurons.at(i).delta = 0.0;
		//Softmax
		if(this->outputFunction == 1){
			int conditionSoftmax = 0;

			for(int j=0; j<this->layers.at(this->nOfLayers-1).nOfNeurons; j++){
				if(j == i){
					conditionSoftmax = 1;
				}
				else{
					conditionSoftmax = 0;
				}

				if(errorFunction == 0){
					this->layers.at(this->nOfLayers - 1).neurons.at(i).delta += -(target[j] - this->layers.at(this->nOfLayers-1).neurons.at(j).out) * out * (conditionSoftmax - this->layers.at(this->nOfLayers-1).neurons.at(j).out);
				}
				else{
					this->layers.at(this->nOfLayers - 1).neurons.at(i).delta += -(target[j] / this->layers.at(this->nOfLayers-1).neurons.at(j).out) * out * (conditionSoftmax - this->layers.at(this->nOfLayers-1).neurons.at(j).out);
				}
			}
		}
		//Sigmoid
		else{
			if(errorFunction == 0){
				this->layers.at(this->nOfLayers - 1).neurons.at(i).delta = -(target[i] - out) * out * (1 - out);
			}
			else{
				this->layers.at(this->nOfLayers - 1).neurons.at(i).delta = -(target[i] / out) * out * (1 - out);
			}
		}
	}

	for(int i=this->nOfLayers-2; i>=1; i--){
		for( int j=0; j<this->layers.at(i).nOfNeurons; j++){
			out = this->layers.at(i).neurons.at(j).out;
			aux = 0.0;
			for(int k=0; k<this->layers.at(i+1).nOfNeurons; k++){
				aux += this->layers.at(i+1).neurons.at(k).w[j+1] * this->layers.at(i+1).neurons.at(k).delta;
			}

			this->layers.at(i).neurons.at(j).delta = aux * out * (1 - out);
		}
	}
}

// ------------------------------
// Accumulate the changes produced by one pattern and save them in deltaW
void MultilayerPerceptron::accumulateChange() {
	for(int i=1; i<this->nOfLayers; i++){
		for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
			for(int k=1; k<this->layers.at(i-1).nOfNeurons + 1; k++){
				this->layers.at(i).neurons.at(j).deltaW[k] += this->layers.at(i).neurons.at(j).delta * this->layers.at(i-1).neurons.at(k-1).out;
			}
			this->layers.at(i).neurons.at(j).deltaW[0] += this->layers.at(i).neurons.at(j).delta;
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {
	double newEta = 0.0;
	for(int i=1; i<this->nOfLayers; i++){
		newEta =  pow(this->decrementFactor, -(this->nOfLayers - 1 - i)) * this->eta;
		for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
			for(int k=1; k<this->layers.at(i-1).nOfNeurons + 1; k++){
				this->layers.at(i).neurons.at(j).w[k] += - (newEta * this->layers.at(i).neurons.at(j).deltaW[k]) / this->nOfTrainingPatterns 
														  - (this->mu * (newEta*this->layers.at(i).neurons.at(j).lastDeltaW[k])) / this->nOfTrainingPatterns;
				this->layers.at(i).neurons.at(j).lastDeltaW[k] = this->layers.at(i).neurons.at(j).deltaW[k];
			}
			this->layers.at(i).neurons.at(j).w[0] += - (newEta * this->layers.at(i).neurons.at(j).deltaW[0]) / this->nOfTrainingPatterns
													  - (this->mu * (newEta*this->layers.at(i).neurons.at(j).lastDeltaW[0])) / this->nOfTrainingPatterns;
			this->layers.at(i).neurons.at(j).lastDeltaW[0] = this->layers.at(i).neurons.at(j).deltaW[0];			
		}
	}
}

// ------------------------------
// Print the network, i.e. all the weight matrices
void MultilayerPerceptron::printNetwork() {
	for(int i=1; i<this->nOfLayers; i++){
		std::cout<<"\nLayer "<<i<<":"<<std::endl;
		std::cout<<"-------"<<std::endl;
		for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
			for(int k=0; k<this->layers.at(i-1).nOfNeurons + 1; k++){
				std::cout<<this->layers.at(i).neurons.at(j).w[k]<<" ";
			}
			std::cout<<std::endl;
		}
	}
}

// ------------------------------
// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights
// input is the input vector of the pattern and target is the desired output vector of the pattern
// The step of adjusting the weights must be performed only in the online case
// If the algorithm is offline, the weightAdjustment must be performed in the "train" function
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::performEpoch(double* input, double* target, int errorFunction) {
	if(this->online){
		for(int i=1; i<this->nOfLayers; i++){
			for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
				for(int k=0; k<this->layers.at(i-1).nOfNeurons + 1; k++){
					this->layers.at(i).neurons.at(j).deltaW[k] = 0.0;
				}
			}
		}
	}

	this->feedInputs(input);
	this->forwardPropagate();
	this->backpropagateError(target, errorFunction);
	this->accumulateChange();

	if(this->online){
		this->weightAdjustment();
	}
}

// ------------------------------
// Read a dataset from a file name and return it
Dataset* MultilayerPerceptron::readData(const char *fileName) {
	ifstream file(fileName);
	if(!file.is_open()){
		std::cout<<"Error"<<std::endl;;
		exit(-1);
	}
	Dataset *dataset;

	int inputs, outputs, patterns;
	if(file >> inputs >> outputs >> patterns){
		dataset = new Dataset[1];
		dataset->nOfInputs = inputs;
		dataset->nOfOutputs = outputs;
		dataset->nOfPatterns = patterns;

		dataset->inputs = new double*[patterns];
		dataset->outputs = new double*[patterns];

		for(int i=0; i<patterns; i++){
			dataset->inputs[i] = new double[inputs];
			dataset->outputs[i] = new double[outputs];
		}

		for(int i=0; i<patterns; i++){
			for(int j=0; j<inputs; j++){
				file >> dataset->inputs[i][j];
			}

			for(int k=0; k<outputs; k++){
				file >> dataset->outputs[i][k];
			}
		}
	}
	else{
		std::cout<<"Incorrect file"<<std::endl;
		file.close();
		return NULL;
	}

	file.close();
	return dataset;
}


// ------------------------------
// Train the network for a dataset (one iteration of the external loop)
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::train(Dataset* trainDataset, int errorFunction) {
	if(!this->online){
		for(int i=1; i<this->nOfLayers; i++){
			for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
				for(int k=0; k<this->layers.at(i-1).nOfNeurons + 1; k++){
					this->layers.at(i).neurons.at(j).deltaW[k] = 0.0;
				}
			}
		}
	}

	for(int i=0; i<trainDataset->nOfPatterns; i++){
		performEpoch(trainDataset->inputs[i], trainDataset->outputs[i],errorFunction);
	}
	

	if(!this->online){
		this->weightAdjustment();
	}
}

// ------------------------------
// Test the network with a dataset and return the error
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::test(Dataset* dataset, int errorFunction) {
	double sum = 0.0;

	for(int i=0; i<dataset->nOfPatterns; i++){
		this->feedInputs(dataset->inputs[i]);
		this->forwardPropagate();

		sum += this->obtainError(dataset->outputs[i], errorFunction);
	}

	if(errorFunction == 0)
		return sum / dataset->nOfPatterns; //MSE

	return -1 * (sum / dataset->nOfPatterns); //Cross Entropy
}


// ------------------------------
// Test the network with a dataset and return the CCR
double MultilayerPerceptron::testClassification(Dataset* dataset) {
	int ccr = 0.0;
	int expectedClass = 0, obtainedClass = 0;
	double *outArray = new double[this->layers.at(this->nOfLayers - 1).nOfNeurons];

	for(int i=0; i<dataset->nOfPatterns; i++){
		this->feedInputs(dataset->inputs[i]);
		this->forwardPropagate();
		this->getOutputs(outArray);

		expectedClass = std::distance(dataset->outputs[i], std::max_element(dataset->outputs[i], dataset->outputs[i] + dataset->nOfOutputs));
		obtainedClass = std::distance(outArray, std::max_element(outArray, outArray + dataset->nOfOutputs));

		if(expectedClass == obtainedClass){
			ccr++;
		}
	}

	return ((double)ccr / dataset->nOfPatterns) * 100;
}


// ------------------------------
// Optional Kaggle: Obtain the predicted outputs for a dataset
void MultilayerPerceptron::predict(Dataset* dataset) {
	ofstream f("prediction_kaggle.csv");
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * salidas = new double[numSalidas];
	
	std::cout << "Id,Category" << endl;
	f << "Id,Predicted" << std::endl;
	
	for (int i=0; i<dataset->nOfPatterns; i++){

		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		getOutputs(salidas);

		int maxIndex = 0;
		for (int j = 0; j < numSalidas; j++)
			if (salidas[j] >= salidas[maxIndex])
				maxIndex = j;
		
		std::cout << i << "," << maxIndex << endl;
		f << i << "," << maxIndex;
	}
	f.close();
}



// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
// Both training and test CCRs should be obtained and stored in ccrTrain and ccrTest
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::runBackPropagation(Dataset * trainDataset, Dataset * testDataset, int maxiter, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, int errorFunction, int* index, double nPatterns, std::string nameProblem) {
	int countTrain = 0;

	// Random assignment of weights (starting point)
	this->randomWeights();

	double minTrainError = 0;
	int iterWithoutImproving = 0;
	this->nOfTrainingPatterns = 1.0;
	double testError = 0;
	double trainError = 0;

	Dataset * validationDataset = new Dataset[1];
	Dataset * copyTrainDataset = new Dataset[1];
	double validationError = 0, previousValidationError = 0;
	int iterWithoutImprovingValidation = 0;

	std::ofstream f(nameProblem);

	// Generate validation data
	if(validationRatio > 0 && validationRatio < 1){
		//validationDataset = new Dataset[1];
		//copyTrainDataset = new Dataset[1];

		validationDataset->nOfInputs = trainDataset->nOfInputs;
		validationDataset->nOfOutputs = trainDataset->nOfOutputs;
		validationDataset->nOfPatterns = (int)nPatterns;		
		validationDataset->inputs = new double*[validationDataset->nOfPatterns];
		validationDataset->outputs = new double*[validationDataset->nOfPatterns];

		for(int i=0; i<validationDataset->nOfPatterns; i++){
			validationDataset->inputs[i] = new double[trainDataset->nOfInputs];
			validationDataset->outputs[i] = new double[trainDataset->nOfOutputs];
		}

		copyTrainDataset->nOfPatterns = trainDataset->nOfPatterns - (int)nPatterns;
		copyTrainDataset->nOfInputs = trainDataset->nOfInputs;
		copyTrainDataset->nOfOutputs = trainDataset->nOfOutputs;
		copyTrainDataset->inputs = new double*[copyTrainDataset->nOfPatterns];
		copyTrainDataset->outputs = new double*[copyTrainDataset->nOfPatterns];

		for(int i=0; i<copyTrainDataset->nOfPatterns; i++){
			copyTrainDataset->inputs[i] = new double[trainDataset->nOfInputs];
			copyTrainDataset->outputs[i] = new double[trainDataset->nOfOutputs];
		}

		for(int i=0; i<validationDataset->nOfPatterns; i++){
			for(int j=0; j<validationDataset->nOfInputs; j++){
				validationDataset->inputs[i][j] = trainDataset->inputs[index[i]][j];
			}

			for(int k=0; k<validationDataset->nOfOutputs; k++){
				validationDataset->outputs[i][k] = trainDataset->outputs[index[i]][k];
			}
		}

		int newIndex = 0;
		for(int i=0; i<trainDataset->nOfPatterns; i++){
			if(!searchIndex(i, index, (int)nPatterns)){
				for(int j=0; j<copyTrainDataset->nOfInputs; j++){
					copyTrainDataset->inputs[newIndex][j] = trainDataset->inputs[i][j];
				}

				for(int k=0; k<copyTrainDataset->nOfOutputs; k++){
					copyTrainDataset->outputs[newIndex][k] = trainDataset->outputs[i][k];
				}
				newIndex++;
			}
		}
	}

	if(!this->online){
		if(validationRatio > 0 && validationRatio < 1){
			this->nOfTrainingPatterns = copyTrainDataset->nOfPatterns;
		}
		else{
			this->nOfTrainingPatterns = trainDataset->nOfPatterns;
		}
	}

	// Learning
	do {
		if(!(validationRatio > 0 && validationRatio < 1)){
			train(trainDataset,errorFunction);
			testError = test(testDataset,errorFunction);
			trainError = test(trainDataset,errorFunction);
			if(countTrain==0 || trainError < minTrainError){
				minTrainError = trainError;
				copyWeights();
				iterWithoutImproving = 0;
			}
			else if( (trainError-minTrainError) < 0.00001)
				iterWithoutImproving = 0;
			else
				iterWithoutImproving++;

			if(iterWithoutImproving==50){
				std::cout << "We exit because the training is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
		}

		if(validationRatio > 0 && validationRatio < 1){
			train(copyTrainDataset,errorFunction);
			testError = test(testDataset,errorFunction);
			trainError = test(copyTrainDataset,errorFunction);
			if(countTrain==0 || trainError < minTrainError){
				minTrainError = trainError;
				copyWeights();
				iterWithoutImproving = 0;
			}
			else if( (trainError-minTrainError) < 0.00001)
				iterWithoutImproving = 0;
			else
				iterWithoutImproving++;

			if(iterWithoutImproving==50){
				std::cout << "We exit because the training is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}

			if(previousValidationError==0)
				previousValidationError = 999999999.9999999999;
			else
				previousValidationError = validationError;
			validationError = test(validationDataset,errorFunction);
			if(validationError < previousValidationError)
				iterWithoutImprovingValidation = 0;
			else if((validationError-previousValidationError) < 0.00001)
				iterWithoutImprovingValidation = 0;
			else
				iterWithoutImprovingValidation++;
			if(iterWithoutImprovingValidation==50){
				std::cout << "We exit because validation is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
		}

		countTrain++;

		std::cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;
		f << countTrain << "\t" << trainError << "\t" << testError << "\t" << validationError << std::endl;

	} while ( countTrain<maxiter );

	if ( (iterWithoutImprovingValidation!=50) && (iterWithoutImproving!=50))
		restoreWeights();

	std::cout << "\nNETWORK WEIGHTS" << endl;
	std::cout << "===============" << endl;
	printNetwork();

	std::cout << "\nDesired output Vs Obtained output (test)" << endl;
	std::cout << "=========================================" << endl;
	for(int i=0; i<testDataset->nOfPatterns; i++){
		double* prediction = new double[testDataset->nOfOutputs];

		// Feed the inputs and propagate the values
		feedInputs(testDataset->inputs[i]);
		forwardPropagate();
		getOutputs(prediction);
		for(int j=0; j<testDataset->nOfOutputs; j++)
			std::cout << testDataset->outputs[i][j] << " -- " << prediction[j] << " ";
		std::cout << endl;
		delete[] prediction;

	}
	*errorTest=test(testDataset,errorFunction);;
	*errorTrain=minTrainError;

	*ccrTest = testClassification(testDataset);
	if(!(validationRatio > 0 && validationRatio < 1)){
		*ccrTrain = testClassification(trainDataset);
	}
	else{
		*ccrTrain = testClassification(copyTrainDataset);
		//*ccrTrain = testClassification(trainDataset);
	}
	
	f.close();
}

// -------------------------
// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * fileName) {
	// Object for writing the file
	ofstream f(fileName);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
	{
		f << " " << layers[i].nOfNeurons;
	}
	f << " " << outputFunction;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				if(layers[i].neurons[j].w!=NULL)
				    f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// -----------------------
// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * fileName) {
	// Object for reading a file
	ifstream f(fileName);

	if(!f.is_open())
		return false;

	// Number of layers and number of neurons in every layer
	int nl;
	int *npl;

	// Read number of layers
	f >> nl;

	npl = new int[nl];

	// Read number of neurons in every layer
	for(int i = 0; i < nl; i++)
	{
		f >> npl[i];
	}
	f >> outputFunction;

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				if(!(outputFunction==1 && (i==(nOfLayers-1)) && (k==(layers[i].nOfNeurons-1))))
					f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}
