#include "pch.h"
#include "ProcessTransform.h"
#include "TransformationTables.h"
#include <iostream>
#include <sstream> 
#include <vector>


ProcessTransform::ProcessTransform()
{
}

ProcessTransform::~ProcessTransform()
{
}

// This function evalute CommandType based on command request
CommandType ProcessTransform::EvaluteCommand(const std::string& command)
{
	CommandType cmdType = CommandType::NONE;

	if (command[0] == 'H')
	{
		cmdType = CommandType::TRANSFORM_HORIZONTAL;
	}
	else if (command[0] == 'V')
	{
		cmdType = CommandType::TRANSFORM_VERTICAL;
	}
	else if (command[0] == '-')
	{
		cmdType = CommandType::TRANSFORM_NEGATIVE_SHIFT;
	}
	else if (command[0] == '+')
	{
		cmdType = CommandType::TRANSFORM_POSITIVE_SHIFT;
	}

	return cmdType;
}

// Convert string to int
int ProcessTransform::ConvertStringInt(std::string cmd)
{
	int strInt = 0;

	std::stringstream result;

	result << cmd;
	result >> strInt;

	return strInt;
}

// Main process to do the transformation
std::string ProcessTransform::Execute(const std::string& input, const std::vector<std::string>& commands)
{
	// input data
	std::string result = input;

	for (const auto command : commands)
	{
		CommandType commandType = EvaluteCommand(command);

		switch (commandType)
		{
		case CommandType::TRANSFORM_HORIZONTAL:
		{
			TransformHorizontal(result);
			break;
		}
		case CommandType::TRANSFORM_VERTICAL:
		{
			TransformVertical(result);
			break;
		}
		case CommandType::TRANSFORM_NEGATIVE_SHIFT:
		{
			TransformNegativeShift(result, command);
			break;
		}
		case CommandType::TRANSFORM_POSITIVE_SHIFT:
		{
			TransformPositiveShift(result, command);
			break;
		}
		default:
		{
			std::cout << "Invalid Command Request: " << command << '\n';
			break;
		}
		}
	}

	std::cout << "Transform with input value = " << input << " with commands: ";
	for (auto cmd : commands)
	{
		std::cout << cmd << " ";
	}

	std::cout << " ... Output is " << result << "\n";

	return result;
}

std::string ProcessTransform::Execute(int argc, char* argv[])
{
	std::vector<std::string> commands;

	for (int count = 0; count < argc; ++count)
	{
		if (count > 1)
		{
			commands.emplace_back(std::string(argv[count]));
		}
	}

	// input data
	std::string result = this->Execute(std::string(argv[1]), commands);

	/*
	for (const auto command : commands)
	{
		CommandType commandType = EvaluteCommand(command);

		switch (commandType)
		{
		case CommandType::TRANSFORM_HORIZONTAL:
			{
				TransformHorizontal(result);
				break;
			}
		case CommandType::TRANSFORM_VERTICAL:
			{
				TransformVertical(result);
				break;
			}
		case CommandType::TRANSFORM_NEGATIVE_SHIFT:
			{
				TransformNegativeShift(result, command);
				break;
			}
		case CommandType::TRANSFORM_POSITIVE_SHIFT:
			{
				TransformPositiveShift(result, command);
				break;
			}
			default:
			{
				std::cout << "Invalid Command Request: " << command << '\n';
				break;
			}
		}
	}

	std::cout << "Transform with input value = " << argv[1] << " with commands: ";
	for (auto cmd : commands)
	{
		std::cout << cmd << " ";
	}

	std::cout << " ... Output is " << result << "\n";
	*/
	return result;
}

void ProcessTransform::TransformHorizontal(std::string& data)
{
	for (size_t idx=0; idx < data.length(); ++idx)
	{
		//int intVal = static_cast<int>(data[idx]);
		auto fndData = transform_keys_h.find(static_cast<int>(data[idx]));
		if (fndData != transform_keys_h.end())
		{
			data[idx] = static_cast<char>(fndData->second);
		}
	}
}

void ProcessTransform::TransformVertical(std::string& data)
{
	for (size_t idx = 0; idx < data.length(); ++idx)
	{
		//int intVal = static_cast<int>(data[idx]);
		auto fndData = transform_keys_v.find(static_cast<int>(data[idx]));
		if (fndData != transform_keys_v.end())
		{
			data[idx] = static_cast<char>(fndData->second);
		}
	}
}

void ProcessTransform::TransformNegativeShift(std::string& data, std::string cmd)
{
	int intCmd = this->ConvertStringInt(cmd);

	for (size_t idx = 0; idx < data.length(); ++idx)
	{
		// find the location Idx value of char
		auto fndIdx = keylocationNum.find(static_cast<int>(data[idx]));
		if (fndIdx != keylocationNum.end())
		{
			int val = intCmd + fndIdx->second;
			if (val <= 0)
			{
				val = val + (int)keylocationNum.size();
			}
			
			// now get the transform value based on val
			if (val <= 41)
			{
				data[idx] = static_cast<char>(IndexOfKeys[val]);
			}
			else
			{
				std::cout << "Error in transforming because of invalid Negative Shift=" << intCmd << "\n";
			}
		}
	}
}

void ProcessTransform::TransformPositiveShift(std::string& data, std::string cmd)
{
	int intCmd = this->ConvertStringInt(cmd);

	for (size_t idx = 0; idx < data.length(); ++idx)
	{
		// find the location Idx value of char
		auto fndIdx = keylocationNum.find(static_cast<int>(data[idx]));
		if (fndIdx != keylocationNum.end())
		{
			int val = intCmd + fndIdx->second;
			if (val > (int)keylocationNum.size())
			{
				int keysCover = (int)keylocationNum.size();

				if (intCmd > keysCover)
				{
					keysCover = intCmd;
				}
				val = val - keysCover;
			}

			// now get the transform value based on val
			if (val <= 41)
			{
				data[idx] = static_cast<char>(IndexOfKeys[val]);
			}
			else
			{
				std::cout << "Error in transforming because of invalid Positive Shift=" << intCmd << "\n";
			}
		}
	}
}