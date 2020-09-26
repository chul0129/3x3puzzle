#include<windows.h>
#include <iostream>
#include <bangtal.h>
#include <ctime>

using namespace bangtal;
using namespace std;
int main()
{
	srand(time(NULL));

	auto scene = Scene::create("게임", "images/배경.jpg");
	auto scene_start = Scene::create("시작", "images/원본.jpg");
	auto button = Object::create("images/start.png", scene_start, 600, 300);
	button->setScale(2);
	ObjectPtr board[9];
	ObjectPtr init_board[9];
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		scene->enter();
		return true;
		});
	int blank = 8;
	for (int i = 0; i < 9; i++)
	{

		string filename = "images/" + to_string(i + 1) + ".jpg";

		board[i] = Object::create(filename, scene, 274 + (i % 3) * 240, 481 - (i / 3) * 240);

		init_board[i] = board[i];

		board[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)->bool {
			int j;
			for (j = 0; j < 9; j++)
			{
				if (board[j] == object)
					break;
			}
			if ((j % 3 > 0 && j - 1 == blank) || //왼쪽 조건
				(j % 3 < 2 && j + 1 == blank) ||//오른쪽 조건
				(j > 2 && j - 3 == blank) ||//위 조건
				(j < 6 && j + 3 == blank))//아래 조건
			{
				board[j]->locate(scene, 274 + (blank % 3) * 240, 481 - (blank / 3) * 240);
				board[blank]->locate(scene, 274 + (j % 3) * 240, 481 - (j / 3) * 240);

				board[j] = board[blank];
				board[blank] = object;
				blank = j;
				int k;
				int p = 0;
				for (k = 0; k < 9; k++) {

					if (board[k] != init_board[k]) break;
				}
				if (k == 9)
				{
					showMessage("끝!");
					scene_start->enter();
				}

			}
			return true;
			});
	}
	board[blank]->hide();

	auto count = 0;
	auto timer = Timer::create(0.1f);

	timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		int j = 0;
		int n = rand() % 4;
		switch (n) {
		case 0://좌
			j = blank - 1; break;
		case 1://우
			j = blank + 1; break;
		case 2: //위
			j = blank - 3; break;
		case 3://아래
			j = blank + 3; break;

		}
		count++;
		if (j > 0 && j < 9 && ((j % 4 > 0 && j - 1 == blank) || //왼쪽 조건
			(j % 4 < 3 && j + 1 == blank) ||//오른쪽 조건
			(j > 3 && j - 3 == blank) ||//위 조건
			(j < 12 && j + 3 == blank)))
		{
			auto object = board[j];
			board[j]->locate(scene, 271 + (blank % 3) * 240, 481 - (blank / 3) * 240);
			board[blank]->locate(scene, 271 + (j % 3) * 240, 481 - (j / 3) * 240);

			board[j] = board[blank];
			board[blank] = object;
			blank = j;
		}
		if (count < 100) {
			timer->set(0.1f);
			timer->start();
		}

		return true;
		});

	timer->start();




	startGame(scene_start);
	return 0;
}