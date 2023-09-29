#pragma once
#include "Engine/Physics/Points.h"

struct GS { // Game Settings
  static bool drawHitbox;

  static float x;
  static float y;
  static float d;

  static float penalty;

  struct Win { // Window
    static int width;
    static int height;
    static float color3f[];
  };

  struct GO { // Game Objects
    struct Room {
      static PointF center;
      static float width;
      static float height;
      static float color3f[];
    };

    struct Ball {
      static float radius;
      static float baseSpeed;
      static float maxSpeed;
      static float color3f[];
      static int damage;
    };

    struct Carriage {
      static PointF center;
      static float baseWidth;
      static float minWidth;
      static float maxWidth;
      static float height;
      static float speed;
      static int balls;
    };

    struct Board {
      static PointF start;
      static int width;
      static int height;
      static char * const brickMp[];
      static char * const bonusMp[];
    };

    struct Bricks {
      static float width;
      static float height;
      
      struct Brick {
        static int points;
        static float color3f[];
      };

      struct Accel {
        static int points;
        static float color3f[];
      };

      struct Indestruct {
        static int points;
        static float color3f[];
      };

      struct Moving {
        static int points;
        static float color3f[];
      };

      struct Save {
        static int points;
        static float color3f[];
        static PointF center;
        static float width;
        static float height;
      };
    };

    struct Bonus {
      static float width;
      static float height;
      static float speed;
      static float time;
    
      struct Accel {
        static float color3f[];
        static float accel;
      };

      struct Slow {
        static float color3f[];
        static float accel;
      };
    };
  };
};