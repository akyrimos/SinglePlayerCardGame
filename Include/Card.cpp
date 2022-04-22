#include <glad.h>
#include <time.h>
#include <vector>
#include "VecMat.h"
#include "Card.h"
#include "CardEnum.h"
#include "Sprite.h"
#include "Character.h"

using namespace std;
using std::string;


Card::Card(string image) {
	this->Image.Initialize(image, 0.1f);
}