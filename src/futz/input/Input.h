#include "InputEventQueue.h"

class Input {
#define FUTZ_INPUT_STATE_SIZE 256
    private:
        bool keyStates[FUTZ_INPUT_STATE_SIZE]; 
        bool keyStatesJustUp[FUTZ_INPUT_STATE_SIZE];
        bool keyStatesJustDown[FUTZ_INPUT_STATE_SIZE];
        bool eventStates[FUTZ_INPUT_STATE_SIZE]; 
        bool eventStatesJustUp[FUTZ_INPUT_STATE_SIZE];
        bool eventStatesJustDown[FUTZ_INPUT_STATE_SIZE];

        futzInputEventTypes MapKeyToEvent(unsigned char key);

        unsigned int NextEventID();

    public:
        futzMouseState mouseState;
        futzMouseState lastMouseState;

        Input();
        bool OnDown(futzInputEventTypes);
        bool OnDown(futzInputEventTypes, futzPlayers);
        bool OnDown(char);

        bool OnUp(futzInputEventTypes);
        bool OnUp(futzInputEventTypes, futzPlayers);
        bool OnUp(char);

        bool IsDown(futzInputEventTypes);
        bool IsDown(futzInputEventTypes, futzPlayers);
        bool IsDown(char);

        bool IsUp(futzInputEventTypes);
        bool IsUp(futzInputEventTypes, futzPlayers);
        bool IsUp(char);

        bool OnMouseMove();

        void SetDown(unsigned char key);
        void SetUp(unsigned char key);
        void SetMouse(int x, int y);

        void Update();
};
