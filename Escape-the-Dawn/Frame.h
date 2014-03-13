#ifndef Frame_h__
#define  Frame_h__

#include <map>
#include "Renderer.h"
#include "Rectangle.h"
#include "GUIManager.h"
#include "Texture.h"
#include "Color.h"
#include "Camera.h"

namespace GUI
{

class Frame
{
public:
	Frame();
	GUIManager Manager;
	std::string Name;
	int GetWidth();
	int GetHeight();
	int GetX();
	int GetY();
	int GetRight();
	int GetLeft();
	int GetBottom();
	int GetTop();
	void SetWidth(int _width);
	void SetHeight(int _height);
	void SetX( int _x);
	void SetY(int _y);
	void SetTexture(std::string fileName);
	Rectangle *rectangle;
	Rectangle AbsouluteRectangle();
	Texture* texture;
	Color* color;
	bool _Visible;
	bool Visible();
	int layer;
	int layerSum;
	int LayerSum();
	int UID();
	Frame *Parent;
	std::map<std::string, void*> Properties = new std::map<std::string, void*>();
	void AddChild(Frame childFrame);
	void RemoveChild(Frame childFrame);
	void Update(double dt);
	void Draw();
protected:
	virtual void Initialize();

}; 
}

#endif