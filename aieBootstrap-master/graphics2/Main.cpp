#include "app.h"

int main()
{
	auto app = new App();

	app->run("graphics", 1280, 720, false);

	//deallocation
	delete app;

	return 0;

}