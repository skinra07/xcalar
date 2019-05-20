#pragma once

#include <string>
#include <vector>

#include "Transform_global.h"

enum class CommandType
{
	NONE,
	TRANSFORM_HORIZONTAL,
	TRANSFORM_VERTICAL,
	TRANSFORM_POSITIVE_SHIFT,
	TRANSFORM_NEGATIVE_SHIFT
};

class TRANSFORM_EXPORT ProcessTransform
{
public:
	ProcessTransform();
	~ProcessTransform();

	std::string Execute(int argc, char* argv[]);
	std::string Execute(const std::string& input, const std::vector<std::string>& commands);

private:
	CommandType EvaluteCommand(const std::string& command);
	void TransformHorizontal(std::string& data);
	void TransformVertical(std::string& data);
	void TransformNegativeShift(std::string& data, std::string cmd);
	void TransformPositiveShift(std::string& data, std::string cmd);
	int ConvertStringInt(std::string cmd);

};