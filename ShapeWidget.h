#pragma once
#include "MeshActor.h"
#include "Widget.h"

namespace UI
{

	class ShapeWidget : public Widget
	{
	protected:
		MeshActor* shapeWidget;

	public:
		ShapeWidget(const MeshActor& _data, const RenderType& _type = Screen, const string& _name = "ShapeWidget");
		~ShapeWidget();

	public:

		virtual void Construct() override;
		virtual void Deconstruct() override;
		virtual void Render(RenderWindow& _window) override;
	};

}
