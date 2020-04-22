#ifndef COLORNODE_H_INCLUDED
#define COLORNODE_H_INCLUDED

struct ColorNode
{
private:
	int PreviousColor;
	int CurrentColor;
public:
    ColorNode();
    ~ColorNode();
	ColorNode(int PreviousColor, int CurrentColor) {
		this->PreviousColor = PreviousColor;
		this->CurrentColor = CurrentColor;
	}
	int GetPreColor() {
		return this->PreviousColor;
	}

	int GetCurColor() {
		return this->CurrentColor;
	}
};


#endif // COLORNODE_H_INCLUDED
