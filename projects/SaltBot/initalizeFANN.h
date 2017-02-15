#pragma once
class initalizeFANN
{
public:
	initalizeFANN();
	~initalizeFANN();

	void GetTrainingData();
	void TrainFromFile(unsigned int max_neurons, const char* training_file, const char* testing_file, const char* output_file);
	void SetupTraining();

};

