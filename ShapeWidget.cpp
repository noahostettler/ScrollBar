#include "ShapeWidget.h"


UI::ShapeWidget::ShapeWidget(const MeshActor& _data, const RenderType& _type, const string& _name)
	: Widget(_name, _type)
{
	shapeWidget = new MeshActor(_data);
	shapeWidget->SetOriginAtMiddle();
}

UI::ShapeWidget::~ShapeWidget()
{
	delete shapeWidget;
}

void UI::ShapeWidget::Construct()
{
}

void UI::ShapeWidget::Deconstruct()
{
}

void UI::ShapeWidget::Render(RenderWindow& _window)
{
}
