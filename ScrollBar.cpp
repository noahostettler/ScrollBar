#include "ScrollBar.h"
#include "Level.h"

UI::ScrollBar::ScrollBar(const MeshActor& _data, const int _scrollAmount, const function<void(bool)>& _callback)
	: ShapeWidget(_data)
{
	callback = _callback;
	baseIndex = 0;
	scrollAmount = _scrollAmount;

	const Vector2f& _buttonSize = Vector2f(35.0f, 35.0f);

	//bar = Level::SpawnActor(ShapeWidget(MeshActor(RectangleShapeData(Vector2f(15, 50), "ScrollBar", PNG))));
	//bar->SetPosition(Vector2f(500, 500));


}

void UI::ScrollBar::UpdateScroll(const Event& _event)
{
	if (const auto* _wheel = _event.getIf<Event::MouseWheelScrolled>())
	{
		if (_wheel->delta > 0)
			UpScroll();
		else
			DownScroll();
	}
}

void UI::ScrollBar::UpScroll()
{
	if (baseIndex < 0)
	{
		baseIndex++;
		ComputeByIndex(-85.0f);
		callback(true);
	}
	else return;
}

void UI::ScrollBar::DownScroll()
{
	if (baseIndex > -scrollAmount)
	{
		baseIndex--;
		ComputeByIndex(85.0f);
		callback(false);
	}
	else return;
}

void UI::ScrollBar::ComputeClickOnBar(const Vector2f& _position)
{
	//clique sur la bar et donne un pourcentage en fonction de la position Y du clic et de la taille de la bar
	const float _pourcentage = (_position.y - bar->GetPosition().y) / bar->GetScale().y;

	//on calcule la position de la bar en fonction du pourcentage
	const float _clickOnBar = (_pourcentage * scrollAmount - baseIndex - 10) * 10;
	cout << round(_clickOnBar) << endl;

	//on met la bar au pourcentage
	ComputeByIndex(_clickOnBar);
}

void UI::ScrollBar::ComputeByIndex(const float _destination)
{
	const float _position = GetPosition().y + _destination;
	SetPosition(Vector2f(GetPosition().x, _position));
}
