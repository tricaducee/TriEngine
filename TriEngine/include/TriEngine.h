#ifndef TRI_ENGINE_H
# define TRI_ENGINE_H
# define TRI_FPS 60
# include <string>
# include <functional>
namespace Tri {
	class Engine {
		private:
			bool	_isInit = false;
			std::function<void()> _userLoop;
			static void	_emscriptenLoop(void *arg);
		public:
			Engine();
			Engine(int width, int height, const char *windowName);
			~Engine();
			int	init(int width, int height, const char *windowName);
			void	loop(std::function<void()> userLoop);
	};
};

#endif