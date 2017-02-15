#include "initalizeFANN.h"

#include <stdio.h>
#include <stdlib.h>  
#include "fann.h"

#include <math.h>
#include <Windows.h>
#include <time.h>

#include <iostream>


//Continue making the Training ANN

initalizeFANN::initalizeFANN()
{
}


initalizeFANN::~initalizeFANN()
{
}

void initalizeFANN::GetTrainingData()
{
	//Tells the neural network what a good or bad outcome is. 


}

void initalizeFANN::TrainFromFile(unsigned int max_neurons, const char* training_file, const char* testing_file, const char* output_file)
{
	//Sets how the neural network is going to be trained.
	struct fann *ann;
	struct fann_train_data *train_data, *test_data;
	const float desired_error = (const float)0.05;
	unsigned int neurons_between_reports = 5;

	//Gets the files
	printf("Trying to read data");

	train_data = fann_read_train_from_file(training_file);
	test_data = fann_read_train_from_file(testing_file);

	fann_scale_train_data(train_data, -1, 1);


	printf("Starting Network");
	printf("input number: %d, output number: %d\n", fann_num_input_train_data(train_data), fann_num_output_train_data(train_data));

	//Creates the neural network. This is a shortcut network. 
	ann = fann_create_shortcut(2, fann_num_input_train_data(train_data), fann_num_output_train_data(train_data));


	//Sets up what type of training is going to be conducted, as well as the paramaters for the network.
	fann_set_training_algorithm(ann, FANN_TRAIN_RPROP);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_LINEAR);
	fann_set_train_error_function(ann, FANN_ERRORFUNC_LINEAR);
	fann_set_bit_fail_limit(ann, (fann_type)0.35);
	fann_set_train_stop_function(ann, FANN_STOPFUNC_BIT);
	fann_print_parameters(ann);

	printf("Starting Training ");
	fann_cascadetrain_on_data(ann, train_data, max_neurons, neurons_between_reports, desired_error);
	fann_print_connections(ann);

	//Print the error difference data from tests 
	float mse_train = fann_test_data(ann, train_data);
	unsigned int bit_fail_train = fann_get_bit_fail(ann);
	float mse_test = fann_test_data(ann, test_data);
	unsigned int bit_fail_test = fann_get_bit_fail(ann);

	printf("Train error: %f, Train bit-fail: %d, Test error: %f, Test bit-fail: %d", mse_train, bit_fail_train, mse_test, bit_fail_test);

	for (unsigned int i = 0; i < train_data->num_data; i++)
	{
		fann_type* output = fann_run(ann, train_data->input[i]);
		if (abs(train_data->output[i][0] - output[0]) > 5 || train_data->output[i][0] >= 0 && output[0] <= 0 || train_data->output[i][0] <= 0 && output[0] >= 0)
		{
			printf("Error: %f does not match %f", train_data->output[i][0], output[0]);
		}
	}
	

	printf("Saving nueral net");
	fann_save(ann, output_file);


	printf("Cleaning up nueral Net");
	fann_destroy_train(train_data);
	fann_destroy(ann);

}

void initalizeFANN::SetupTraining()
{
	//Used to initalize the files.
}