#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "neuralNetFeedForward.h"

namespace DCL
{
	/// \brief This is used with the CGeneticsTraining class with methods which are used to create an entire new population of networks from an existing one.
	///
	/// We typically create a vector of these, transfer the weights for each neural network, along with it's fitness into each one.
	/// Then we use the vector of objects of this class to create a next generation from the existing population.
	/// For example (psuedo code ahead):
	/// \code
	/// std::vector<CGenome> vecGenomes;
	/// for (each neural network)
	/// {
	///		CGenome genome(someExistingNeuralNetwork, itsFitnessScore);
	///		vecGenomes.push_back(genome);
	/// }
	/// CGeneticsTraining genTrainer;
	/// std::vector<CGenome> vecNewPopulation = genTrainer.someMethodWhichCreatesANewPopulation(vecGenomes);
	/// \endcode
	/// Then we can use the vecNewPopulation to update the existing neural networks and reset their fitness for the next generation.
	/// \todo Check constness. I was concentrating on the code and forgot about it!
	class CGenome
	{
	public:
		/// \brief Default constructor, sets everything to zero
		CGenome();

		/// \brief Constructor which copies the given values into itself
		///
		/// \param vecNeuralNetworkWeights The neural network weights of it's neurons.
		/// \param dNetworkFitness The network's fitness score
		CGenome(std::vector<double>& vecNeuralNetworkWeights, double dNetworkFitness);

		/// \brief Constructor which copies the given values into itself
		///
		/// \param neuralNetwork The neural network to use for it's weights
		/// \param dNetworkFitness The networks fitness score.
		CGenome(const CNeuralNetworkFeedForward& neuralNetwork, double dNetworkFitness);

		/// \brief Sets this genome to the given values.
		/// 
		/// \param vecNeuralNetworkWeights The neural network weights of it's neurons.
		/// \param dNetworkFitness The network's fitness score
		void set(std::vector<double>& vecNeuralNetworkWeights, double dNetworkFitness);

		/// \brief Sets this genome to hold the given fitness and weights stored in the given neural network
		///
		/// \param neuralNetwork The neural network to use for it's weights
		/// \param dNetworkFitness The networks fitness score.
		void set(const CNeuralNetworkFeedForward& neuralNetwork, double dNetworkFitness);

		std::vector<double>	vecWeights;		///< This should be filled with the weights from a neural network by calling it's getNeuronWeights() method.
		double dFitness;					///< This should be set to hold the final fitness score of the entity owning the neural network.

		/// \brief Operator overload '<' for sorting a vector of this class's objects by fitness
		///
		/// \param lhs Left hand side of operator
		/// \param rhs Right hand side of operator
		friend bool operator<(const CGenome& lhs, const CGenome& rhs)
		{
			return (lhs.dFitness < rhs.dFitness);
		}
	};

	/// \brief This is the genetics training class which is used with the neural network class to train the weights of that class.
	/// 
	/// \todo Re-read chapter five (Building a better genetic algorithm) of the "AI techniques for game programming" book to get some better methods 
	/// 
	/// A neural network has weights for each of it's neurons and they need to be set to correct values, or trained, so that
	/// the network produces our desired behaviour.
	/// 
	/// The process goes like this...
	/// Say we wish to create a network which flees and enemy entity in a 2D world.
	/// We create a population of networks, say 100 of them, initially with random weights/genes.
	/// We then run the simulation, passing each network it's inputs, calculating their outputs and applying those
	/// outputs to each entity in the simulation.
	/// Whilst the simulation is running, we compute a fitness score for each network depending upon how it is performing.
	/// Increasing the fitness if it is doing what we want (It is far away from predators), reducing if not (It gets eaten).
	/// After a certain time has passed, this class then creates an entirely new generation of the population of networks
	/// from the existing population to run in the next run. This class uses the fitness of each network to determine how
	/// the new child networks are generated. 
	/// This process repeats until, hopefully, most of the networks are performing well. We then take the best performing
	/// networks, save them out for loading into our program at a later date for use.
	/// 
	/// When creating the new generation of networks, there are a few ways this class can choose how to create the child population.
	/// It takes the networks from the best performing networks and use those as parents, to create children from their weights/genes.
	/// It also takes non-best performing networks too, to help keep the population's networks varies to allow for variation
	/// in behaviour which allows new behaviours to evolve in the population.
	/// 
	/// Typically, after a certain number of runs, the population's differences converge so that they all roughly have the
	/// same weights, but we don't want this to happen before an optimal behaviour has been found, so this class has ways of 
	/// preventing this from happening too quickly.
	/// 
	/// There is mutation, which changes the genes/weights and may produce good behaviour, but may not. This helps diversify the
	/// population and create new behaviours.
	/// There is gene/weight crossover which determines which genes the children networks get from their parents. There are
	/// different types of crossover methods, each with subtly differences.
	/// 
	///
	class CGeneticsTraining
	{
	public:

		/// \brief Given a vector of CGenomes representing a all the neural networks and their fitness of an entire population, performs roulette wheel selection and returns a selected CGenome.
		///
		/// \param[in] vecPopulation a vector of each genome representing an entire population of neuron weights and their fitness scores.
		/// \return The selected genome.
		/// 
		/// If the given vector is empty, an exception occurs.
		/// Roulette wheel selection is a method of choosing a member from the entire population 
		/// in a way that is proportional to their fitness.
		/// Imagine a roulette wheel, or pie chart which is divided into portions, each assigned to a member in the population.
		/// The size of each portion is related to each member's fitness score with higher fitness getting a larger portion of the pie/wheel.
		/// The wheel is then spun until the ball stops at a position and then that member is chosen.
		/// It does not guarantee that a member with a high fitness will be chosen, but it increases the odds that it will be.
		/// Note: This may not return any best performing members, so it's probably best to use elitism if using this when selecting members.
		CGenome rouletteWheelSelection(const std::vector<CGenome>& vecPopulation) const;

		/// \brief Given a vector of doubles representing the fitness of each member within a population, calculates
		/// the best, worst, average and total fitness of the population and stores those results in the given variables.
		/// 
		/// \param[in] vecPopulationFitness Vector holding the fitness score of each genome.
		/// \param[out] dWorstFitness Will hold the worst fitness found in all the fitness scores
		/// \param[out] dAverageFitness Will hold the average fitness computed from all the fitness scores
		/// \param[out] dBestFitness Will hold the best fitness found from all the fitness scores
		/// \param[out] dTotalFitness Will hold the accumulated total of all the fitness scores
		void computeFitness(const std::vector<double>& vecPopulationFitness, double& dWorstFitness, double& dAverageFitness, double& dBestFitness, double& dTotalFitness) const;

		/// \brief Given a vector of CGenome objects, calculates the best, worst, average and total fitness of the population and stores those results in the given variables.
		///
		/// \param[in] vecPopulation Vector holding the genomes of an entire population
		/// \param[out] dWorstFitness Will hold the worst fitness found in all the fitness scores
		/// \param[out] dAverageFitness Will hold the average fitness computed from all the fitness scores
		/// \param[out] dBestFitness Will hold the best fitness found from all the fitness scores
		/// \param[out] dTotalFitness Will hold the accumulated total of all the fitness scores
		void computeFitness(const std::vector<CGenome>& vecPopulation, double& dWorstFitness, double& dAverageFitness, double& dBestFitness, double& dTotalFitness) const;

		/// \brief Given the weights of two networks (the parents), performs a basic crossover of their weights and creates two child network weights from them.
		///
		/// \param vecMumWeights The weights of the first parent (the mum!)
		/// \param vecDadWeights The weights of the second parent (the dad!)
		/// \param vecChildAWeights Will hold the weights of the 1st child.
		/// \param vecChildBWeights Will hold the weights of the 2nd child.
		/// \param dCrossoverRate The crossover rate. A random value between 0 and 1 is generated and if the value is lower than the crossover rate, then the weights are crossed over when creating the children.
		/// 
		/// If any of the given vectors' sizes for the parents are not all the same, an exception occurs.
		/// The child vectors are cleared before doing anything, as they are the outputs.
		/// This is the simplest type of crossover and can mess up each neuron's weight values, similar to mutation.
		/// It's probably best to not use this and instead use crossoverBetweenNeurons() instead.
		/// The crossover rate is simply a value between 0 and 1.
		/// It's used to swap genes between two parents when creating their children.
		/// We compute a random value between 0 and 1 and if this value is lower than the crossover rate,
		/// then the genes are swapped at another random value which represents a position among all the genes.
		/// A value of around 0.7 is pretty good, in certain cases however, a different value may produce better results.
		void crossover(
			std::vector<double>& vecMumWeights,
			std::vector<double>& vecDadWeights,
			std::vector<double>& vecChildAWeights,
			std::vector<double>& vecChildBWeights,
			double dCrossoverRate = 0.7) const;

		/// \brief Given the weights of two networks (the parents), performs a crossover of their weights between each neuron and creates two child network weights from them.
		///
		/// \param vecMumWeights The weights of the first parent (the mum!)
		/// \param vecDadWeights The weights of the second parent (the dad!)
		/// \param vecChildAWeights Will hold the weights of the 1st child.
		/// \param vecChildBWeights Will hold the weights of the 2nd child.
		/// \param vecSplitPoints The split points which need to be obtained from either parent by calling calculateSplitPoints().
		/// \param dCrossoverRate The crossover rate. A random value between 0 and 1 is generated and if the value is lower than the crossover rate, then the weights are crossed over when creating the children.
		///
		/// vecSplitPoints needs to be obtained from one of the parent neural networks with a call to it's calculateSplitPoints() method.
		/// If any of the given vectors' sizes for the parents are not all the same, an exception occurs.
		/// The child vectors are cleared before doing anything, as they are the outputs.
		/// This crossover takes into consideration the number of weights in each neuron and only splits the weight between those.
		/// The crossover rate is simply a value between 0 and 1.
		/// It's used to swap genes between two parents when creating their children.
		/// We compute a random value between 0 and 1 and if this value is lower than the crossover rate,
		/// then the genes are swapped at another random value which represents a position among all the genes.
		/// A value of around 0.7 is pretty good, in certain cases however, a different value may produce better results.
		void crossoverBetweenNeurons(
			std::vector<double>& vecMumWeights,
			std::vector<double>& vecDadWeights,
			std::vector<double>& vecChildAWeights,
			std::vector<double>& vecChildBWeights,
			const std::vector<int>& vecSplitPoints,
			double dCrossoverRate = 0.7) const;

		/// \brief Given the weights of a neural network, mutates them depending upon the given values.
		///
		/// \param[in,out] vecNetworkWeights The network weights which are to be mutated
		/// \param dMutationProbability The mutation rate is the probability that a gene will be changed. This is typically a very small value of around 0.001 or so.
		/// \param dMutationMaxAmount The maximum amount of deviation from the weight's current value if mutation occurs.
		/// 
		/// The mutation rate is the probability that a gene will be changed.
		/// This is typically a very small value of around 0.001 or so.
		/// We generate a random value between 0 and 1 for each weight in the given vector and if this
		/// value is less than dMutationProbability, the weight is mutated by a maximum of dMaxMutationAmount.
		void mutate(std::vector<double>& vecNetworkWeights, double dMutationProbability = 0.001, double dMutationMaxAmount = 0.3) const;

		/// \brief Performs elitism.
		///
		/// \param vecOldPop A vector of CGenome representing the old population
		/// \param vecNewPop A vector of CGenome which will represent the new population with the elite
		/// \param iNumberOfElite The number of elite from the top to copy.
		/// \param iNumCopiesOfEachElite How many copies of each iNumberOfElite to place.
		/// 
		/// Given two vectors of CGenomes representing the old population and the new population.
		/// iNumberOfElite is the number of elite from the top to copy.
		/// iNumCopiesOfEachElite is how many copies of each iNumberOfElite to place.
		/// As long as the new population's size is less than the size of the old population,
		/// will choose a certain number of genomes with the best fitness and inserts them into
		/// the new population.
		/// This is typically called fom inside a createNewGeneration method.
		/// This will sort the old population vector so that the genomes with the greatest fitness
		/// are twoards the end of the vector.
		/// We don't want the number of elites and number of copies to be too high, otherwise the population's
		/// diversity will suffer. These values all depend upon the size of the population.
		void insertElite(std::vector<CGenome>& vecOldPop, std::vector<CGenome>& vecNewPop, int iNumberOfElite = 2, int iNumCopiesOfEachElite = 1) const;

		/// \brief Given a vector of CGenomes holding each neural network and their fitness scores, generates and returns a vector of CGenomes which contain a new generation.
		///
		/// \param genomes A vector of CGenome which represent the current population which is used to generate the new population.
		/// \param vecSplitsPoints The split points which need to be obtained from either parent by calling calculateSplitPoints().
		/// \param dMutationProbability The mutation rate is the probability that a gene will be changed. This is typically a very small value of around 0.001 or so.
		/// \param dMutationMaxAmount The maximum amount of deviation from the weight's current value if mutation occurs.
		/// \param dCrossoverRate The crossover rate. A random value between 0 and 1 is generated and if the value is lower than the crossover rate, then the weights are crossed over when creating the children.
		/// \param iNumberOfElite
		/// \param iNumCopiesOfEachElite
		/// \return A vector of CGenomes holding the new population.
		/// 
		/// This new generation creation method uses crossoverBetweenNeurons(), mutate(), rouletteWheelSelection() and insertElite()
		/// to generate the new population.
		std::vector<CGenome> createNewGeneration(
			const std::vector<CGenome>& genomes,
			const std::vector<int>& vecSplitsPoints,
			double dMutationProbability = 0.001,
			double dMutationMaxAmount = 0.3,
			double dCrossoverRate = 0.7,
			int iNumberOfElite = 2,
			int iNumCopiesOfEachElite = 1) const;

	private:

	};

}   // namespace DCL

#endif // #ifndef FILENAME_H
