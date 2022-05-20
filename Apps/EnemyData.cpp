#include "EnemyData.h"
#include "../Include/CardEnum.h"

using namespace std;



string filepath = "../PLACEHOLDER/FILEPATH/";

Enemy enemy1(10, filepath + "placeholder.png");
Enemy enemy2(20, filepath + "placeholder.png");
Enemy enemy3(30, filepath + "placeholder.png");


EnemyData::EnemyData() {
	//Enemy 1
	enemy1.AddAction(CardEnum::Attack, 10);
	enemy1.AddAction(CardEnum::Defend, 5);

	//Enemy 2
	enemy2.AddAction(CardEnum::Attack, 2);
	enemy2.AddAction(CardEnum::Attack, 4);
	enemy2.AddAction(CardEnum::Attack, 20);

	//Enemy 3
	enemy3.AddAction(CardEnum::Attack, 15);
	enemy3.AddAction(CardEnum::Defend, 20);

	//Add to Vector
	Enemies.push_back(&enemy1);
	Enemies.push_back(&enemy2);
	Enemies.push_back(&enemy3);

}