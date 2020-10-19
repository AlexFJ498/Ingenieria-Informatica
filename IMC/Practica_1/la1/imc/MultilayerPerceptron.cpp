/*********************************************************************
* File  : MultilayerPerceptron.cpp
* Date  : 2020
*********************************************************************/

#include "MultilayerPerceptron.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <limits>
#include <math.h>


using namespace imc;
using namespace std;

// ------------------------------
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron(){
	this->nOfLayers = 1;
	this->eta = 0.1;
	this->mu = 0.9;
	this->validationRatio = 0.2;
	this->decrementFactor = 1;
}

// ------------------------------
// Allocate memory for the data structures
// nl is the number of layers and npl is a vector containing the number of neurons in every layer
// Give values to Layer* layers
void MultilayerPerceptron::initialize(int nl, int npl[]) {
	this->nOfLayers = nl;
	int nOfNeuronsPrev;

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

			for(int k=0; k<nOfNeuronsPrev + 1; k++){
				n.lastDeltaW[k] = 0.0;
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
	vector<Layer>().swap(layers);
}

// ------------------------------
// Feed all the weights (w) with random numbers between -1 and +1
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
	for(int i=0;i<this->layers.at(0).nOfNeurons; i++){
		this->layers.at(0).neurons.at(i).out = input[i];
	}
}

// ------------------------------
// Get the outputs predicted by the network (out vector the output layer) and save them in the vector passed as an argument
void MultilayerPerceptron::getOutputs(double* output) {
	for(int i=0; i<this->layers.at(this->nOfLayers-1).nOfNeurons; i++){
		output[i] = this->layers[this->nOfLayers-1].neurons.at(i).out;
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
	for(int i=1; i<this->nOfLayers; i++){
		for(int j=0;j<this->layers.at(i).nOfNeurons; j++){
			net = 0.0;
			for(int k=1; k<this->layers.at(i-1).nOfNeurons + 1; k++){
				net += this->layers.at(i).neurons.at(j).w[k] * this->layers.at(i-1).neurons.at(k-1).out;
			}
			net += this->layers.at(i).neurons.at(j).w[0];
			this->layers.at(i).neurons.at(j).out = 1.0 / (1 + exp(-net));
		}
	}
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
double MultilayerPerceptron::obtainError(double* target) {
	double mse = 0.0;

	for(int i=0; i<this->layers.at(this->nOfLayers-1).nOfNeurons; i++){
		mse += pow(target[i] - this->layers.at(this->nOfLayers - 1).neurons.at(i).out, 2);
	}

	return mse / this->layers.at(this->nOfLayers - 1).nOfNeurons;
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
void MultilayerPerceptron::backpropagateError(double* target) {
	double out, aux;

	for(int i=0; i<this->layers.at(this->nOfLayers-1).nOfNeurons; i++){
		out = this->layers.at(nOfLayers-1).neurons.at(i).out;
		this->layers.at(this->nOfLayers - 1).neurons.at(i).delta = -(target[i] - out) * out * (1 - out);
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
	double newEta;
	for(int i=1; i<this->nOfLayers; i++){
		newEta =  pow(this->decrementFactor, -(this->nOfLayers - 1 - i)) * this->eta;
		for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
			for(int k=1; k<this->layers.at(i-1).nOfNeurons + 1; k++){
				this->layers.at(i).neurons.at(j).w[k] += (- newEta * this->layers.at(i).neurons.at(j).deltaW[k]) 
														  - this->mu * this->layers.at(i).neurons.at(j).lastDeltaW[k];
				this->layers.at(i).neurons.at(j).lastDeltaW[k] = this->layers.at(i).neurons.at(j).deltaW[k];
			}
			this->layers.at(i).neurons.at(j).w[0] += (- newEta * this->layers.at(i).neurons.at(j).deltaW[0]) 
													  - this->mu * this->layers.at(i).neurons.at(j).lastDeltaW[0];
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
void MultilayerPerceptron::performEpochOnline(double* input, double* target) {
	for(int i=1; i<this->nOfLayers; i++){
		for(int j=0; j<this->layers.at(i).nOfNeurons; j++){
			for(int k=0; k<this->layers.at(i-1).nOfNeurons + 1; k++){
				this->layers.at(i).neurons.at(j).deltaW[k] = 0.0;
			}
		}
	}

	this->feedInputs(input);
	this->forwardPropagate();
	this->backpropagateError(target);
	this->accumulateChange();
	this->weightAdjustment();
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
// Perform an online training for a specific trainDataset
void MultilayerPerceptron::trainOnline(Dataset* trainDataset) {
	for(int i=0; i<trainDataset->nOfPatterns; i++){
		performEpochOnline(trainDataset->inputs[i], trainDataset->outputs[i]);
	}
}

// ------------------------------
// Test the network with a dataset and return the MSE
double MultilayerPerceptron::test(Dataset* testDataset) {
	double mse = 0.0;

	for(int i=0; i<testDataset->nOfPatterns; i++){
		this->feedInputs(testDataset->inputs[i]);
		this->forwardPropagate();

		mse += this->obtainError(testDataset->outputs[i]);
	}

	return mse / testDataset->nOfPatterns;
}


// Optional - KAGGLE
// Test the network with a dataset and return the MSE
// Your have to use the format from Kaggle: two columns (Id y predictied)
void MultilayerPerceptron::predict(Dataset* pDatosTest) {
	ofstream f("prediccion_kaggle.csv");
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * obtained = new double[numSalidas];
	
	std::cout << "Id,Predicted" << endl;
	f << "Id,Predicted" << std::endl;
	
	for (int i=0; i<pDatosTest->nOfPatterns; i++){

		feedInputs(pDatosTest->inputs[i]);
		forwardPropagate();
		getOutputs(obtained);
		
		std::cout << i;
		f << i;

		for (int j = 0; j < numSalidas; j++){
			std::cout << "," << obtained[j];
			f << "," << obtained[j];
		}

		f << std::endl;
		std::cout << endl;
	}
	f.close();
}

// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
void MultilayerPerceptron::runOnlineBackPropagation(Dataset * trainDataset, Dataset * testDataset, int maxiter, double *errorTrain, double *errorTest, string nameProblem) {
	int countTrain = 0;

	// Random assignment of weights (starting point)
	this->randomWeights();

	int iterWithoutImproving = 0;
	int validationWithoutImproving = 0;
	double minTrainError = 0;
	double lastValidationError = 0;
	double testError = 0;
	double validationError = 0;
	Dataset *validationDataset = new Dataset[1];

	ofstream f(nameProblem);

	// Generate validation data
	if(this->validationRatio > 0 && this->validationRatio < 1){
		validationDataset->nOfInputs = trainDataset->nOfInputs;
		validationDataset->nOfOutputs = trainDataset->nOfOutputs;
		validationDataset->nOfPatterns = trainDataset->nOfPatterns * this->validationRatio;

		if(validationDataset->nOfPatterns < 1){
			validationDataset->nOfPatterns = 1;
		}

		validationDataset->inputs = new double*[validationDataset->nOfPatterns];
		validationDataset->outputs = new double*[validationDataset->nOfPatterns];

		for(int i=0; i<validationDataset->nOfPatterns; i++){
			validationDataset->inputs[i] = new double[validationDataset->nOfInputs];
			validationDataset->outputs[i] = new double[validationDataset->nOfOutputs];
		}

		for(int i=0; i<validationDataset->nOfPatterns; i++){
			validationDataset->inputs[i] = trainDataset->inputs[i];
			validationDataset->outputs[i] = trainDataset->outputs[i];
		}

		trainDataset->nOfPatterns -= validationDataset->nOfPatterns;

		double **tmpInput = new double*[trainDataset->nOfPatterns];
		double **tmpOutput = new double*[trainDataset->nOfPatterns];

		for(int i=0; i<trainDataset->nOfPatterns; i++){
			tmpInput[i] = trainDataset->inputs[i + validationDataset->nOfPatterns];
			tmpOutput[i] = trainDataset->outputs[i + validationDataset->nOfPatterns];
		}

		delete [] trainDataset->inputs;
		delete [] trainDataset->outputs;

		trainDataset->inputs = tmpInput;
		trainDataset->outputs = tmpOutput;
	}

	// Learning
	do {
		trainOnline(trainDataset);
		testError = test(testDataset);
		double trainError = test(trainDataset);
		if(countTrain==0 || trainError < minTrainError){
			minTrainError = trainError;
			copyWeights();
			iterWithoutImproving = 0;
		}
		else if( (trainError-minTrainError) < 0.00001)
			iterWithoutImproving = 0;
		else
			iterWithoutImproving++;

		if(this->validationRatio > 0 && this->validationRatio < 1){
			validationError = test(validationDataset);

			if(countTrain == 0 ){
				lastValidationError = validationError;
				validationWithoutImproving = 0;
			}
			else if ((validationError - lastValidationError) < 0.00001)
				validationWithoutImproving = 0;
			else
				validationWithoutImproving++;
			
			lastValidationError = validationError;
		}

		if(iterWithoutImproving==50){
			std::cout << "We exit because the training is not improving!!"<< endl;
			restoreWeights();
			countTrain = maxiter;
		} else if(this->validationRatio > 0 && this->validationRatio < 1 && validationWithoutImproving == 50){
			std::cout<<"We exit because the validation is not improving!!"<<std::endl;
			countTrain = maxiter;
		}

		countTrain++;

		// Check validation stopping condition and force it
		// BE CAREFUL: in this case, we have to save the last validation error, not the minimum one
		// Apart from this, the way the stopping condition is checked is the same than that
		// applied for the training set

		if(iterWithoutImproving < 50){
			std::cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;
		}

		f << countTrain << "\t" << trainError << "\t" << testError <<std::endl;

	} while ( countTrain<maxiter );

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

	testError = test(testDataset);
	*errorTest=testError;
	*errorTrain=minTrainError;

	f.close();
}

// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * archivo)
{
	// Object for writing the file
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
		f << " " << layers[i].nOfNeurons;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * archivo)
{
	// Object for reading a file
	ifstream f(archivo);

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
		f >> npl[i];

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}
