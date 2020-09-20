#include <bangtal.h>
using namespace bangtal;

int main()
{
	
	auto scene1 = Scene::create("시작", "image/원본.jpg");
	auto scene2 = Scene::create("게임", "image/10.jpg");
	auto button = Object::create("image/start.png", scene1,600,500);
	int x0 = 274, x1 = 514, x2 = 754;
	int y0 = 480, y1 = 240, y2 = 0;
	int x[3] = { x0,x1,x2 };
	int y[3] = { y0,y1,y2 };
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	 ObjectPtr puzzle[9] = {
	 Object::create("image/1.jpg", scene2, x[0], y[0]),
	 Object::create("image/2.jpg", scene2, x[1], y[0]),
	 Object::create("image/3.jpg", scene2, x[2], y[0]),
	 Object::create("image/4.jpg", scene2, x[0], y[1]),
	 Object::create("image/5.jpg", scene2, x[1], y[1]),
	 Object::create("image/6.jpg", scene2,x[2], y[1]),
	 Object::create("image/7.jpg", scene2, x[0], y[2]),
	 Object::create("image/8.jpg", scene2, x[1], y[2]),

	};

	
	


	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();

		return true;
		});
	
	
	puzzle[0]->locate(scene2, x[2], y[0]);
	puzzle[1]->locate(scene2, x[1], y[0]);
	puzzle[2]->locate(scene2, x[0], y[0]);
	puzzle[3]->locate(scene2, x[2], y[1]);
	puzzle[4]->locate(scene2, x[1], y[1]);
	puzzle[5]->locate(scene2, x[0], y[1]);
	puzzle[6]->locate(scene2, x[2], y[2]);
	puzzle[7]->locate(scene2, x[1], y[2]);
	

	for (int i = 0;i < 8;i++)
	{
		puzzle[i]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			
			if (action == MouseAction::MOUSE_DRAG_RIGHT)
				puzzle[7]->locate(scene2, x1 + 240, y2);
			
			
			return true;
			});

	}








	startGame(scene1);
	return 0;

}