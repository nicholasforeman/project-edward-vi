#pragma once

#include "rendering/graphics_context.hpp"

struct GLFWwindow;

namespace Engine::Renderer {

	class OpenGlContext : public GraphicsContext {

		GLFWwindow* mWindow;

	public:

		OpenGlContext(GLFWwindow* window);
		~OpenGlContext();

		void SwapBuffers() override;

	};

}