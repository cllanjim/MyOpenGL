#include "InputManager.h"
#include "GameManager.h"

InputManager::InputManager()
{
	bMouseMove = false;
	//g_ojbInputManager._handle.bind(&GameManager::GetInstance(), &GameManager::MouseEven);
}

InputManager::~InputManager()
{
}

InputManager& InputManager::GetInstance()
{
	static InputManager _instance;
	return*(&_instance);
}




void InputManager::MouseEven(MouseType nType, MousePos pos)
{
	switch (nType)
	{
	case MouseDown:
	{
					  mouseLast.X = pos.X;
					  mouseLast.Y = pos.Y;
					  bMouseMove = true;
	}
		break;
	case MouseUp:
	{
					mouseLast.X = pos.X;
					mouseLast.Y = pos.Y;
					bMouseMove = false;
	}
		break;
	case MouseDClick:
	{
						mouseLast.X = pos.X;
						mouseLast.Y = pos.Y;
	}
		break;
	case MouseMove:
	{
					  if (bMouseMove)
					  {
						  MousePos _tmp(pos.X, pos.Y);
						  pos.X -= mouseLast.X;
						  pos.Y -= mouseLast.Y;

						  mouseLast.X = _tmp.X;
						  mouseLast.Y = _tmp.Y;
					  }
					  else
					  {
						  return;
					  }
	
	}
		break;
	case MouseWheel:
	{

	}
		break;
	}
	g_objGameManager.MouseEven(nType,pos);
	//_handle(nType, pos);
}
