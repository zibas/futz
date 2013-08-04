/*
 * InputEventQueue.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: ziba
 */

#include "InputEventQueue.h"
#include <stdio.h>
#include <stdlib.h>
InputEventQueue::InputEventQueue() {
	cursorTail = 0;
	cursorHead = 0;

	mouseState = futzMouseState(); 
	lastMouseState = futzMouseState(); 
	mouseState.pixelX = mouseState.pixelY = 0;
	lastMouseState.pixelX = lastMouseState.pixelY = 0;
	mouseState.relativeX = mouseState.relativeY = 50;
}

InputEventQueue::~InputEventQueue() {
}

void InputEventQueue::PushMouse(int x, int y){
	// Created here, destroyed when removed from queue
	futzInputEvent* ie = new futzInputEvent();

	ie->player = FUTZ_PLAYER_ONE;
	ie->x = x;
	ie->y = y;
	ie->eventType = FUTZ_MOUSE_MOVE;
	lastMouseState.pixelX = mouseState.pixelX;
	lastMouseState.pixelY = mouseState.pixelY;

	mouseState.pixelX = x;
	mouseState.pixelY = y;
	this->Enqueue(ie);
}

void InputEventQueue::Push(unsigned char key){

	// Created here, destroyed when removed from queue

	futzInputEvent* ie = new futzInputEvent();

	ie->player = FUTZ_PLAYER_ONE;
	ie->character = key;
	ie->x = 0;
	ie->y = 0;

	switch(key){
		case 'w':
			ie->eventType = FUTZ_UP;
			break;
		case 's':
			ie->eventType = FUTZ_DOWN;
			break;
		case 'a':
			ie->eventType = FUTZ_LEFT;
			break;
		case 'd':
			ie->eventType = FUTZ_RIGHT;
			break;
		case '+':
			ie->eventType = FUTZ_ASCEND;
			break;
		case '-':
			ie->eventType = FUTZ_DESCEND;
			break;
		case 27:
			ie->eventType = FUTZ_BACK;
			break;
		default:
			ie->eventType = FUTZ_UNMAPPED;
			break;
	}

	if(cursorHead + 1 == cursorTail){
		futzInputEvent* temp = this->Pop();
		delete temp;
	}
	if(cursorHead + 1 == FUTZ_MAX_INPUT_EVENTS){
		if(cursorTail == 0){
			futzInputEvent* temp = this->Pop();
			delete temp;
		}
	}

	eventQueue[cursorHead] = ie;
	cursorHead++;

	if(cursorHead == FUTZ_MAX_INPUT_EVENTS){
		cursorHead = 0;
	}
}

void InputEventQueue::Enqueue(futzInputEvent* event ){
	if(cursorHead + 1 == cursorTail){
		futzInputEvent* temp = this->Pop();
		free(temp);
	}
	if(cursorHead + 1 == FUTZ_MAX_INPUT_EVENTS){
		if(cursorTail == 0){
			futzInputEvent* temp = this->Pop();
			free(temp);
		}
	}

	eventQueue[cursorHead] = event;
	cursorHead++;

	if(cursorHead == FUTZ_MAX_INPUT_EVENTS){
		cursorHead = 0;
	}
}

futzInputEvent* InputEventQueue::Pop(){
	if(cursorHead == cursorTail){
		return NULL;
	}

	futzInputEvent* ie = eventQueue[cursorTail];
	cursorTail++;
	if(cursorTail == FUTZ_MAX_INPUT_EVENTS){
			cursorTail = 0;
	}
	return ie;
}

void InputEventQueue::Print(){
	printf("Event Queue:\n");
	printf("\tTail: %d\tHead: %d\n", cursorTail, cursorHead );

	if(cursorTail < cursorHead){
		for(int i = cursorTail; i < cursorHead; i++){
			printf("\t%d: %c\n",i,eventQueue[i]->character);
		}
	} else {
		for(int i = cursorTail; i < FUTZ_MAX_INPUT_EVENTS; i++){
			printf("\t%d: %c\n",i,eventQueue[i]->character);
		}
		for(int i = 0; i < cursorHead; i++){
			printf("\t%d: %c\n",i,eventQueue[i]->character);
		}
	}
}

