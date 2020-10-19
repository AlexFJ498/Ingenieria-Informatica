/*********************************************************************
 * File  : MultilayerPerceptron.h
 * Date  : 2020
 *********************************************************************/


#ifndef _MULTILAYERPERCEPTRON_H_
#define _MULTILAYERPERCEPTRON_H_

namespace imc{

// Suggested structures
// ---------------------
struct Neuron {
	double  out;            /* Output produced by the neuron (out_j^h)*/
	double  delta;          /* Derivative of the output produced by the neuron (delta_j^h)*/
	double* w;              /* Input weight vector (w_{ji}^h)*/
	double* deltaW;         /* Change to be applied to every weight (\Delta_{ji}^h (t))*/
	double* lastDeltaW;     /* Last change applied to the every weight (\Delta_{ji}^h (t-1))*/
	double* wCopy;          /* Copy of the input weights */
};

struct Layer {
	int     nOfNeurons;   /* Number of neurons of the layer*/
	Neuron* neurons;      /* Vector with the neurons of the layer*/
};

struct Dataset {
	int nOfInputs;     /* Number of inputs */
	int nOfOutputs;    /* Number of outputs */
	int nOfPatterns;   /* Number of patterns */
	double** inputs;   /* Matrix with the inputs of the problem */
	double** outputs;  /* Matrix with the outputs of the problem */
};

class MultilayerPerceptron {
private:
	int    nOfLayers;        /* Total number of layers in the network */
	Layer* layers;           /* Vector containing every layer */
	int nOfTrainingPatterns; /* For the offline derivatives */

	// Free memory for the data structures
	void freeMemory();

	// Fill all the weights (w) with random numbers between -1 and +1
	void randomWeights();

	// Feed the input neurons of the network with a vector passed as an argument
	void feedInputs(double* input);

	// Get the outputs predicted by the network (out vector of the output layer) and save them in the vector passed as an argument
	void getOutputs(double* output);

	// Make a copy of all the weights (copy w in wCopy)
	void copyWeights();

	// Restore a copy of all the weights (copy wCopy in w)
	void restoreWeights();

	// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
	void forwardPropagate();

	// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
	// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
	double obtainError(double* target, int errorFunction);

	// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
	// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
	void backpropagateError(double* target, int errorFunction);

	// Accumulate the changes produced by one pattern and save them in deltaW
	void accumulateChange();

	// Update the network weights, from the first layer to the last one
	void weightAdjustment();

	// Print the network, i.e. all the weight matrices
	void printNetwork();

	// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights
	// input is the input vector of the pattern and target is the desired output vector of the pattern
	// The step of adjusting the weights must be performed only in the online case
	// If the algorithm is offline, the weightAdjustment must be performed in the "train" function
	// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
	void performEpoch(double* input, double* target, int errorFunction);


public:
	// Values of the parameters (they are public and can be updated from outside)
	double eta;             // Learning rate
	double mu;              // Momentum factor
	bool   online;          // Online training? (true->online,false->offline)
	double validationRatio; // Ratio of training patterns used as validation (e.g.
	                        // if validationRatio=0.2, a 20% of the training patterns
	                        // are used for validation; if validationRatio=0, there is no validation)
	double decrementFactor; // Decrement factor used for eta in the different layers
	int outputFunction;      /* Type of activation function in the output layer (outputFunction=0 sigmoid, outputFunction=1 softmax) */

	// Constructor: Default values for all the parameters
	MultilayerPerceptron();

	// DESTRUCTOR: free memory
	~MultilayerPerceptron();

	// Allocate memory for the data structures
    // nl is the number of layers and npl is a vetor containing the number of neurons in every layer
    // Give values to Layer* layers
	int initialize(int nl, int npl[]);

	// Read a dataset from a file name and return it
	Dataset* readData(const char *fileName);

	// Test the network with a dataset and return the error
	// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
	double test(Dataset* dataset, int errorFunction);
	
	// Test the network with a dataset and return the CCR
	double testClassification(Dataset* dataset);

	// Optional Kaggle: Obtain the predicted outputs for a dataset
	void predict(Dataset* testDataset);

	// Train the network for a dataset (one iteration of the external loop)
	// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
	void train(Dataset* trainDataset, int errorFunction);

	// Run the traning algorithm for a given number of epochs, using trainDataset
    // Once finished, check the performance of the network in testDataset
    // Both training and test MSEs should be obtained and stored in errorTrain and errorTest
    // Both training and test CCRs should be obtained and stored in ccrTrain and ccrTest
	// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
	void runBackPropagation(Dataset * trainDataset, Dataset * testDataset, int maxiter, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, int errorFunction);

	// Optional Kaggle: Save the model weights in a textfile
	bool saveWeights(const char * fileName);

	// Optional Kaggle: Load the model weights from a textfile
	bool readWeights(const char * fileName);
};

};

#endif
