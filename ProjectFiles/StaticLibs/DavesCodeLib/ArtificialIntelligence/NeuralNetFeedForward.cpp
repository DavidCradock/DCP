#include "neuralNetFeedForward.h"
#include "../Core/Utilities.h"
#include "../Core/Exceptions.h"

namespace DCL
{
	CNeuron::CNeuron(int iNumInputs)
	{
		// We need an additional weight for the bias of this neuron
		miNumInputs = iNumInputs + 1;
		for (int i = 0; i < iNumInputs + 1; i++)
		{
			// Set weights to random values between -1 and +1
			mvecInputWeights.push_back(randomClamped());
		}
	}

	CNeuronLayer::CNeuronLayer(int iNumNeurons, int iNumInputsPerNeuron)
	{
		miNumNeurons = iNumNeurons;
		for (int i = 0; i < iNumNeurons; i++)
		{
			mvecNeurons.push_back(CNeuron(iNumInputsPerNeuron));
		}
	}

	CNeuralNetworkFeedForward::CNeuralNetworkFeedForward()
	{
		create(1, 1, 0, 0);
	}

	CNeuralNetworkFeedForward::CNeuralNetworkFeedForward(int iNumInputs, int iNumOutputs, int iNumLayers, int iNumNeuronsPerLayer)
	{
		create(iNumInputs, iNumOutputs, iNumLayers, iNumNeuronsPerLayer);
	}

	void CNeuralNetworkFeedForward::create(int iNumInputs, int iNumOutputs, int iNumLayers, int iNumNeuronsPerLayer)
	{
		// Check for valid parameters
		ThrowIfTrue(iNumInputs < 1, "CNeuralNetworkFeedForward::create() given invalid number of inputs. Must be at least 1");
		ThrowIfTrue(iNumOutputs < 1, "CNeuralNetworkFeedForward::create() given invalid number of outputs. Must be at least 1");
		ThrowIfTrue(iNumLayers < 0, "CNeuralNetworkFeedForward::create() given invalid number of layers. Must be at least 0");
		ThrowIfTrue(iNumNeuronsPerLayer < 1 && iNumLayers > 0, "CNeuralNetworkFeedForward::create() given invalid number of neurons per layer. Must be at least 1 if iNumLayers is > 0");

		// Clear everything
		_mvecLayers.clear();

		// Set given parameters
		_miNumInputs = iNumInputs;
		_miNumOutputs = iNumOutputs;
		_miNumLayers = iNumLayers;
		_miNumNeuronsPerLayer = iNumNeuronsPerLayer;

		// Set default bias
		_mdBias = -1;

		// Set default sigmoid response
		_mdSigmoidResponse = 1;

		if (_miNumLayers)
		{
			// Create the first layer of neurons which have the number of inputs set to the number of inputs of the network.
			_mvecLayers.push_back(CNeuronLayer(_miNumNeuronsPerLayer, _miNumInputs));

			// Create the other layers
			// iNumLayers -1 because we've already created a layer above
			for (int i = 0; i < _miNumLayers - 1; i++)
			{
				// Create the layer, using the number of inputs set to the number of neurons per layer
				_mvecLayers.push_back(CNeuronLayer(_miNumNeuronsPerLayer, _miNumNeuronsPerLayer));
			}

			// Create the output layer
			_mvecLayers.push_back(CNeuronLayer(_miNumOutputs, _miNumNeuronsPerLayer));
		}
		else
		{
			// Create the output layer
			_mvecLayers.push_back(CNeuronLayer(_miNumOutputs, _miNumInputs));
		}
	}

	std::vector<double> CNeuralNetworkFeedForward::getNeuronWeights(void) const
	{
		std::vector<double> vecWeights;

		// For each layer (+1 as we are also returning the output layer)
		for (int iLayer = 0; iLayer < _miNumLayers + 1; iLayer++)
		{
			// For each neuron in each layer
			for (int iNeuron = 0; iNeuron < _mvecLayers[iLayer].miNumNeurons; iNeuron++)
			{
				// For each weight in each neuron, not including the bias of the neuron
				for (int iWeight = 0; iWeight < _mvecLayers[iLayer].mvecNeurons[iNeuron].miNumInputs; iWeight++)
				{
					vecWeights.push_back(_mvecLayers[iLayer].mvecNeurons[iNeuron].mvecInputWeights[iWeight]);
				}
			}
		}
		return vecWeights;
	}

	int CNeuralNetworkFeedForward::getNumberOfWeights(void) const
	{
		int iNumberOfWeights = 0;
		// For each layer (+1 as we are also returning the output layer)
		for (int iLayer = 0; iLayer < _miNumLayers + 1; iLayer++)
		{
			// For each neuron in each layer
			for (int iNeuron = 0; iNeuron < _mvecLayers[iLayer].miNumNeurons; iNeuron++)
			{
				// For each weight in each neuron, not including the bias of the neuron
				for (int iWeight = 0; iWeight < _mvecLayers[iLayer].mvecNeurons[iNeuron].miNumInputs; iWeight++)
				{
					iNumberOfWeights++;
				}
			}
		}
		return iNumberOfWeights;
	}

	void CNeuralNetworkFeedForward::replaceWeights(const std::vector<double>& newWeights)
	{
		int iIndex = 0;

		// For each layer (+1 as we are also replacing the output layer)
		for (int iLayer = 0; iLayer < _miNumLayers + 1; iLayer++)
		{
			// For each neuron in each layer
			for (int iNeuron = 0; iNeuron < _mvecLayers[iLayer].miNumNeurons; iNeuron++)
			{
				// For each weight in each neuron, not including the bias of the neuron
				for (int iWeight = 0; iWeight < _mvecLayers[iLayer].mvecNeurons[iNeuron].miNumInputs; iWeight++)
				{
					_mvecLayers[iLayer].mvecNeurons[iNeuron].mvecInputWeights[iWeight] = newWeights[iIndex++];
				}
			}
		}
	}

	std::vector<double> CNeuralNetworkFeedForward::update(std::vector<double>& vecInputs)
	{
		ThrowIfTrue(vecInputs.size() != _miNumInputs, "CNeuralNetworkFeedForward::update() failed. Was given a vector of inputs which are not equal to in size of the network's number of inputs");
		std::vector<double> vecOutputs;

		int cWeight = 0;

		// For each layer (+1 as we are also updating the output layer)
		for (int iLayer = 0; iLayer < _miNumLayers + 1; iLayer++)
		{
			// If we've used the inputs, we need to set the inputs to be the outputs of the previous layer
			if (iLayer > 0)
				vecInputs = vecOutputs;

			// Clear the outputs, as we're going to calculate them below
			vecOutputs.clear();

			// Used to count through each weight in the inputs below.
			cWeight = 0;

			int iNumInputs = 0;

			// For each neuron in each layer
			// multiply the input by the weight for that input, then use the sigmoid
			// function to smooth it out to get the final output.
			for (int iNeuron = 0; iNeuron < _mvecLayers[iLayer].miNumNeurons; iNeuron++)
			{
				double dAccumulatedInput = 0;
				iNumInputs = _mvecLayers[iLayer].mvecNeurons[iNeuron].miNumInputs;

				// For each weight, not including the bias (the -1)
				for (int iWeight = 0; iWeight < iNumInputs - 1; iWeight++)
				{
					dAccumulatedInput += _mvecLayers[iLayer].mvecNeurons[iNeuron].mvecInputWeights[iWeight] * vecInputs[cWeight++];
				}

				// Multiply by the bias
				dAccumulatedInput += _mvecLayers[iLayer].mvecNeurons[iNeuron].mvecInputWeights[iNumInputs - 1] * _mdBias;

				// Pass the final computed input value, multiplied by the weights, with the bias applied, to the sigmoid function to
				// obtain the final output value and store that in the vector of outputs.
				vecOutputs.push_back(sigmoid(dAccumulatedInput, _mdSigmoidResponse));

				cWeight = 0;
			}
		}
		return vecOutputs;
	}

	void CNeuralNetworkFeedForward::setWeightBias(double dWeightBias)
	{
		_mdBias = dWeightBias;
	}

	void CNeuralNetworkFeedForward::setSigmoidResponse(double dResponse)
	{
		ThrowIfTrue(areDoublesEqual(0, dResponse), "CNeuralNetworkFeedForward::setSigmoidResponse() failed. The given value should not be zero. Otherwise a divide by zero error occurs.");
		_mdSigmoidResponse = dResponse;
	}

	std::vector<int> CNeuralNetworkFeedForward::calculateSplitPoints(void)
	{
		std::vector<int> vecSplitPoints;

		int iWeightCounter = 0;

		// For each layer (+1 as we are also giving the output layer)
		for (int iLayer = 0; iLayer < _miNumLayers + 1; iLayer++)
		{
			// For each neuron in each layer
			for (int iNeuron = 0; iNeuron < _mvecLayers[iLayer].miNumNeurons; iNeuron++)
			{
				// For each weight in each neuron, not including the bias of the neuron
				for (int iWeight = 0; iWeight < _mvecLayers[iLayer].mvecNeurons[iNeuron].miNumInputs; iWeight++)
				{
					iWeightCounter++;
				}
				vecSplitPoints.push_back(iWeightCounter - 1);
			}
		}
		return vecSplitPoints;
	}
}