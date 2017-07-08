#include<stdio.h>
#include <SDL2/SDL.h>
#include "headers/game.h"
#include "headers/inimigo.h"
#include "headers/gamer.h"
#include "headers/enemy.h"


typedef minions{
	
	RECT life
	RECT assest;
	int life,x,y,damage;

}Minions;

typedef RECT{
	
	int large;high;
	
}rect;