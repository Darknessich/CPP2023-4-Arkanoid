#include "GameSettings.h"

// General
bool    GS::drawHitbox          = false;
float   GS::x                   = 400.f;
float   GS::y                   = 300.f;
float   GS::d                   = 500.f;

float   GS::penalty             = - .05f * x;

// Window
int     GS::Win::width          = static_cast<int>(2 * x);
int     GS::Win::height         = static_cast<int>(2 * y);
float   GS::Win::color3f[]      = { .235f, .267f, .337f };

// ************
// Game Objects
// ************

// Room
PointF  GS::GO::Room::center    = { 0.f * x, 0.f * y};
float   GS::GO::Room::width     = 1.95f * x;
float   GS::GO::Room::height    = 1.95f * y;
float   GS::GO::Room::color3f[] = { .518f, .565f, .667f };

// Ball
float   GS::GO::Ball::radius    = .01f * d;
float   GS::GO::Ball::baseSpeed = .25f * d;
float   GS::GO::Ball::maxSpeed  = .5f * d;
float   GS::GO::Ball::color3f[] = {1.f, 1.f, 1.f};
int     GS::GO::Ball::damage    = 1;

// Carriage
PointF  GS::GO::Carriage::center    = {0.f * x, -.75f * y};
float   GS::GO::Carriage::baseWidth = .4f * x;
float   GS::GO::Carriage::minWidth  = .1f * x;
float   GS::GO::Carriage::maxWidth  = 1.2f * x;
float   GS::GO::Carriage::height    = .03f * y;
float   GS::GO::Carriage::speed     = 2.f * x;
int     GS::GO::Carriage::balls     = 1;

// Board
PointF  GS::GO::Board::start        = {-.9f * x, .6f * y};
int     GS::GO::Board::width        = 9;
int     GS::GO::Board::height       = 5;

  // 'n': None
  // 'b': Brick
  // 'a': AccelBrick
  // 'i': IndestructibleBrick
  // 'm': MovingBrick
  static char brl1[] = "iabbmbbai";
  static char brl2[] = "ibabnbabi";
  static char brl3[] = "ibbnmnbbi";
  static char brl4[] = "ibabnbabi";
  static char brl5[] = "iabbmbbai";

  char * const GS::GO::Board::brickMp[] = {brl1, brl2, brl3, brl4, brl5};

  // 'n': none
  // 'i': increase
  // 'd': downsizing
  // 't': sticky
  // 'a': accelerate
  // 'l': slowdown
  // 's': save
  // 'b': addball

  static char bsl1[] = "ndalasain";
  static char bsl2[] = "nsdstsisn";
  static char bsl3[] = "ntlisdltn";
  static char bsl4[] = "nsistsdsn";
  static char bsl5[] = "nialasadn";
  char * const GS::GO::Board::bonusMp[] = { bsl1, bsl2, bsl3, bsl4, bsl5 };

// ***************************
//          Bricks
// ***************************

float GS::GO::Bricks::width         = .2f * x;
float GS::GO::Bricks::height        = .06f * x;

int GS::GO::Bricks::Accel::points       = 1;
float GS::GO::Bricks::Accel::color3f[]  = { .167f, .255f, .435f };

int GS::GO::Bricks::Brick::points       = 1;
float GS::GO::Bricks::Brick::color3f[]  = { 0.647f, 0.51f, 0.243f };

int GS::GO::Bricks::Indestruct::points  = 1;
float GS::GO::Bricks::Indestruct::color3f[] = { .235f, .267f, .337f };

int GS::GO::Bricks::Moving::points      = 3;
float GS::GO::Bricks::Moving::color3f[] = { 0.235f, 0.173f, 0.447f };

int GS::GO::Bricks::Save::points        = 0;
float GS::GO::Bricks::Save::color3f[]   = { 0.149f, 0.392f, 0.384f };
float GS::GO::Bricks::Save::width       = GS::GO::Room::width;
float GS::GO::Bricks::Save::height      = GS::GO::Carriage::height;
PointF GS::GO::Bricks::Save::center =
{ 0.0f * x, 0.5f * (GS::GO::Bricks::Save::height - GS::GO::Room::height) };

// ***************************
//            Bonus
// ***************************

float GS::GO::Bonus::width    = .02f * d;
float GS::GO::Bonus::height   = .02f * d;
float GS::GO::Bonus::speed    = -0.2f * y;
float GS::GO::Bonus::time = 30.f;

float GS::GO::Bonus::Accel::color3f[] = { 0.996f, 0.859f, 0.749f };
float GS::GO::Bonus::Accel::accel = 1.25f;

float GS::GO::Bonus::Slow::color3f[] = { 0.416f, 0.443f, 0.502f };
float GS::GO::Bonus::Slow::accel = 0.8f;