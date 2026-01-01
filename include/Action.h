#ifndef ACTION_H
#define ACTION_H
enum eActionName{
	NONE = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	PLAY,
	PAUSE,
	EXIT,
	SHOOT,
	JUMP,
};

enum eActionType{
	START = 0,
	END,
};

class Action{
public:
	eActionName name;
	eActionType type;
	Action() {}
	Action(eActionName name, eActionType type) : name(name), type(type) {}
};
#endif
