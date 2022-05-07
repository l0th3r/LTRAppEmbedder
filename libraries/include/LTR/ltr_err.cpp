#include "ltr_err.h"

using namespace ltr;

const std::string ltr::ErrContextToStr(const ErrContext context)
{
	switch (context)
	{
	default:
	case ErrContext::App:
		return "App";
		break;

	case ErrContext::GLFW:
		return "GLFW dependency";
		break;

	case ErrContext::GLEW:
		return "GLEW dependency";
		break;

	case ErrContext::Shader:
		return "Shaders";
		break;
	}
}

const std::string ltr::ErrCodeToStr(const ErrCode code)
{
	switch (code)
	{
	case ErrCode::no_err:
		return "nothing";
		break;

	case ErrCode::init:
		return "initialisation";
		break;

	case ErrCode::terminate:
		return "terminate";
		break;

	// > 100 (GLFW)
	case ErrCode::creating_window:
		return "creating window";
		break;

	// > 300 (Shader)
	case ErrCode::shader_parsing:
		return "parsing";
		break;

	case ErrCode::shader_compilation:
		return "compilation";
		break;

	// default return raw code
	default:
		return "Code " + std::to_string((int)code);
	}
}