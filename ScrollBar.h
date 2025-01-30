#pragma once
#include "ShapeWidget.h"

namespace UI
{

	class ScrollBar : public ShapeWidget
	{
		int baseIndex;
		int scrollAmount;
		ShapeWidget* bar;
		function<void(bool)> callback;

	public:
		void SetScrollAmount(const int _scrollAmount) { scrollAmount = _scrollAmount; }
		ShapeWidget* GetBar() { return bar; }
		int GetBaseIndex() { return baseIndex; }

	public:
		ScrollBar(const MeshActor& _data, const int _scrollAmount, const function<void(bool)>& _callback);

	public:
		void UpdateScroll(const Event& _event);
		void UpScroll();
		void DownScroll();
		void ComputeClickOnBar(const Vector2f& _position);
		void ComputeByIndex(const float _destination);
	};
}