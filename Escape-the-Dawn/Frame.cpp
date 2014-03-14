/*#include "Frame.h"

GUI::Frame::Frame()
{
	rectangle = new Rectangle();
	texture = nullptr;
}

int GUI::Frame::GetWidth()
{
	return rectangle->Width();
}

int GUI::Frame::GetHeight()
{
	return rectangle->Height();
}

int GUI::Frame::GetX()
{
	return rectangle->X();
}

int GUI::Frame::GetY()
{
	return rectangle->Y();
}

int GUI::Frame::GetRight()
{
	return rectangle->Right();
}

int GUI::Frame::GetLeft()
{
	return rectangle->Left();
}

int GUI::Frame::GetBottom()
{
	return rectangle->Bottom();
}

int GUI::Frame::GetTop()
{
	return rectangle->Right();
}

void GUI::Frame::SetWidth(int _width)
{
	rectangle->Width(_width);
}

void GUI::Frame::SetHeight(int _height)
{
	rectangle->Height(_height);
}

void GUI::Frame::SetX(int _x)
{
	rectangle->X(_x);
}

void GUI::Frame::SetY(int _y)
{
	rectangle->Y(_y);
}



Rectangle GUI::Frame::AbsouluteRectangle()
{

}

bool GUI::Frame::Visible()
{

}

int GUI::Frame::LayerSum()
{

}

int GUI::Frame::UID()
{

}

void GUI::Frame::AddChild(Frame childFrame)
{

}

void GUI::Frame::RemoveChild(Frame childFrame)
{

}

void GUI::Frame::Initialize()
{

}

void GUI::Frame::Update(double dt)
{

}

void AddChild(GUI::Frame childFrame)
{
	childFrame.Parent = this;
	if (!Children.Contains(childFrame))
		Children.Add(childFrame);
}

/// <summary>
/// Remove a child frame from the frame.
/// </summary>
/// <param name="childFrame">The child frame to remove.</param>
void RemoveChild(GUI::Frame childFrame)
{
	if (Children.Contains(childFrame))
		Children.Remove(childFrame);
}

/// <summary>
/// Destroys the frame and all its children.
/// </summary>
void Destroy()
{
	if (Parent != null)
		Parent.RemoveChild(this);

	Manager.Remove(this);
}

void GUI::Frame::SetTexture(std::string fileName)
{
	//texture == någonTextureIDunno;
}

void GUI::Frame::Draw()
{
	if (Visible)
	{
		if (texture != nullptr)
		{
			//Drawshit
		}
	}
}

*/