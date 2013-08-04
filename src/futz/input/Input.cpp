#include "Input.h"
#define FUTZ_INPUT_STATE_SIZE 256

Input::Input(){
	//mouseState = futzMouseState(); 
	lastMouseState = futzMouseState(); 
	mouseState.pixelX = mouseState.pixelY = 0;
	lastMouseState.pixelX = lastMouseState.pixelY = 0;
	mouseState.relativeX = mouseState.relativeY = 50;

    for(int i = 0; i < FUTZ_INPUT_STATE_SIZE; i++){
        eventStates[i] = 0;
        keyStates[i] = 0;
        keyStatesJustUp[i] = false;
        keyStatesJustDown[i] = false;
        eventStatesJustUp[i] = false;
        eventStatesJustDown[i] = false;
    }
}

bool Input::OnDown(futzInputEventTypes eventType){
    return OnDown(eventType, FUTZ_PLAYER_ONE);
}

bool Input::OnDown(futzInputEventTypes eventType, futzPlayers player){
    return eventStatesJustDown[eventType]; 
}

bool Input::OnDown(char key){
    return keyStatesJustDown[key]; 
}

bool Input::OnUp(futzInputEventTypes eventType){
    return OnUp(eventType, FUTZ_PLAYER_ONE);
}

bool Input::OnUp(futzInputEventTypes eventType, futzPlayers player){
    return eventStatesJustUp[eventType]; 
}

bool Input::OnUp(char key){
    return keyStatesJustUp[key]; 
}

bool Input::IsUp(futzInputEventTypes eventType, futzPlayers player){
    return !eventStates[eventType]; 
}

bool Input::IsUp(futzInputEventTypes eventType){
    return IsUp(eventType, FUTZ_PLAYER_ONE);
}

bool Input::IsUp(char key){
    return !keyStates[key]; 
}

bool Input::IsDown(futzInputEventTypes eventType, futzPlayers player){
    return eventStates[eventType]; 
}

bool Input::IsDown(futzInputEventTypes eventType){
    return IsDown(eventType, FUTZ_PLAYER_ONE);
}

bool Input::IsDown(char key){
    return keyStates[key]; 
}

bool Input::OnMouseMove(){
    return eventStatesJustDown[FUTZ_MOUSE_MOVE]; 
}

void Input::SetDown(unsigned char key){
    keyStates[key] = true;
    keyStatesJustDown[key] = true;
    keyStatesJustUp[key] = false;
    eventStates[MapKeyToEvent(key)] = true;
    eventStatesJustDown[MapKeyToEvent(key)] = true;
    eventStatesJustUp[MapKeyToEvent(key)] = false;
}

void Input::SetUp(unsigned char key){
    keyStates[key] = false;
    keyStatesJustUp[key] = true;
    eventStates[MapKeyToEvent(key)] = false;
    eventStatesJustUp[MapKeyToEvent(key)] = true;
}

void Input::SetMouse(int x, int y){
    eventStatesJustDown[FUTZ_MOUSE_MOVE] = true;

	lastMouseState.pixelX = mouseState.pixelX;
	lastMouseState.pixelY = mouseState.pixelY;

	mouseState.pixelX = x;
	mouseState.pixelY = y;
}

void Input::Update(){
    for(int i = 0; i < FUTZ_INPUT_STATE_SIZE; i++){
        eventStatesJustUp[i] = false;
        eventStatesJustDown[i] = false;
        keyStatesJustUp[i] = false;
        keyStatesJustDown[i] = false;
    }

}

futzInputEventTypes Input::MapKeyToEvent(unsigned char key){
    futzInputEventTypes eventType;
	switch(key){
		case 'w':
			eventType = FUTZ_UP;
			break;
		case 's':
			eventType = FUTZ_DOWN;
			break;
		case 'a':
			eventType = FUTZ_LEFT;
			break;
		case 'd':
			eventType = FUTZ_RIGHT;
			break;
		case '+':
			eventType = FUTZ_ASCEND;
			break;
		case '-':
			eventType = FUTZ_DESCEND;
			break;
		case 27:
			eventType = FUTZ_BACK;
			break;
		default:
			eventType = FUTZ_UNMAPPED;
			break;
	}

    return eventType;
}
