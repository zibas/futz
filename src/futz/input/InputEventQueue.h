/*
 * InputEventQueue.h
 *
 *  Created on: Jul 1, 2010
 *      Author: ziba
 */

#ifndef INPUTEVENTQUEUE_H_
#define INPUTEVENTQUEUE_H_

enum futzInputEventTypes {FUTZ_UP, FUTZ_DOWN, FUTZ_LEFT, FUTZ_RIGHT, FUTZ_ASCEND, FUTZ_DESCEND, FUTZ_MOUSE_MOVE, FUTZ_UNMAPPED, FUTZ_BACK};
enum futzPlayers {FUTZ_PLAYER_ONE, FUTZ_PLAYER_TWO};

#define FUTZ_MAX_INPUT_EVENTS 10

struct futzInputEvent{
	futzInputEventTypes eventType;
	futzPlayers player;
	char character;
	int x;
	int y;
};

struct futzMouseState{
	int pixelX;
	int pixelY;
	float relativeX;
	float relativeY;
};

class InputEventQueue {

	futzInputEvent* eventQueue[FUTZ_MAX_INPUT_EVENTS];
	int cursorTail;
	int cursorHead;

	
	void Enqueue(futzInputEvent*);


public:
	futzMouseState mouseState;
	futzMouseState lastMouseState;

	InputEventQueue();
	virtual ~InputEventQueue();
	void Print();
	void PushMouse(int, int);
	void Push(unsigned char);
	futzInputEvent* Pop();
};

#endif /* INPUTEVENTQUEUE_H_ */
