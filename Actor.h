#pragma once
#include "Core.h"
#include "TransformableModifier.h"
#include "TransformableViewer.h"
#include "Component.h"
#include "RootComponent.h"
#include "TimerManager.h"

class Actor : public Core, public ITransformableModifier, public ITransformableViewer
{
	bool isToDelete;
	u_int id;
	string name;
	string displayName;
	set<Component*> components;
	RootComponent* root;
	Actor* parent;
	AttachmentType attachment;
	set<Actor*> children;
protected:
	float lifeSpan;

protected:
	template <typename Type, typename ...Args, IS_BASE_OF(Component, Type)>
	FORCEINLINE Type* CreateComponent(Args... _args)
	{
		Type* _component = new Type(this, _args...);
		AddComponent(_component);
		return _component;
	}
	FORCEINLINE void CreateSocket(const string& _name, const TransformData& _transform = TransformData(),
								  const AttachmentType& _type = AT_SNAP_TO_TARGET)
	{
		Actor* _socket = new Actor(_name, _transform);
		AddChild(_socket, _type);
	}

public:
	FORCEINLINE void SetToDelete()
	{
		isToDelete = true;
	}
	FORCEINLINE bool IsToDelete() const
	{
		return isToDelete;
	}
	FORCEINLINE u_int GetID() const
	{
		return id;
	}
	FORCEINLINE string GetName() const
	{
		return name;
	}
	FORCEINLINE string GetDisplayName() const
	{
		return displayName;
	}

	#pragma region Children

private:
	FORCEINLINE void SetParent(Actor* _parent)
	{
		parent = _parent;
	}
	FORCEINLINE void UpdateChildTransform(Actor* _child)
	{
		UpdateChildPosition(_child);
		UpdateChildRotation(_child);
		UpdateChildScale(_child);
	}
	FORCEINLINE void UpdateChildPosition(Actor* _child)
	{
		const vector<function<Vector2f()>>& _computePosition =
		{
			// Keep the child�s relative position to the parent.
			[&]() { return _child->GetPosition() - GetPosition(); },
			// Keep the child�s world position.
			[&]() { return _child->GetPosition(); },
			// Snap the child to the parent's position.
			[&]() { return GetPosition(); },
		};

		const AttachmentType& _type = _child->GetAttachmentType();
		_child->SetPosition(_computePosition[_type]());
	}
	FORCEINLINE void UpdateChildRotation(Actor* _child)
	{
		const vector<function<Angle()>>& _computeRotation =
		{
			// Keep the child�s relative rotation to the parent.
			[&]() { return _child->GetRotation() - GetRotation(); },
			// Keep the child�s world rotation.
			[&]() { return _child->GetRotation(); },
			// Snap the child to the parent's rotation.
			[&]() { return GetRotation(); },
		};

		const AttachmentType& _type = _child->GetAttachmentType();
		_child->SetRotation(_computeRotation[_type]());
	}
	FORCEINLINE void UpdateChildScale(Actor* _child)
	{
		const vector<function<Vector2f()>>& _computeScale =
		{
			// Keep the child�s relative scale to the parent.
			[&]() { return _child->GetScale() - GetScale(); },
			// Keep the child�s world scale.
			[&]() { return _child->GetScale(); },
			// Snap the child to the parent's scale.
			[&]() { return GetScale(); },
		};

		const AttachmentType& _type = _child->GetAttachmentType();
		_child->SetScale(_computeScale[_type]());
	}

public:
	FORCEINLINE void AddChild(Actor* _child, const AttachmentType& _type)
	{
		_child->SetAttachmentType(_type);
		_child->SetParent(this);
		UpdateChildTransform(_child);
		children.insert(_child);
	}
	FORCEINLINE void RemoveChild(Actor* _child)
	{
		if (!_child || !children.contains(_child)) return;

		_child->SetParent(nullptr);
		children.erase(_child);
	}
	FORCEINLINE void SetAttachmentType(const AttachmentType& _attachment)
	{
		attachment = _attachment;
	}
	FORCEINLINE AttachmentType GetAttachmentType() const
	{
		return attachment;
	}
	FORCEINLINE Actor* GetParent() const
	{
		return parent;
	}
	FORCEINLINE set<Actor*> GetChildren() const
	{
		return children;
	}
	FORCEINLINE Actor* GetChildrenAtIndex(const int _index) const
	{
		set<Actor*>::const_iterator _it = children.begin();
		advance(_it, _index);
		return *_it;
	}

	#pragma endregion

	#pragma region Transformable

	#pragma region Viewer

	FORCEINLINE virtual Vector2f GetOrigin() const override
	{
		return root->GetOrigin();
	}
	FORCEINLINE virtual Vector2f GetPosition() const override
	{
		return root->GetPosition();
	}
	FORCEINLINE virtual Angle GetRotation() const override
	{
		return root->GetRotation();
	}
	FORCEINLINE virtual Vector2f GetScale() const override
	{
		return root->GetScale();
	}
	FORCEINLINE virtual TransformData GetTransform() const override
	{
		return root->GetTransform();
	}

	#pragma endregion

	#pragma region Modifier

	FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
	{
		root->SetPosition(_position);

		for (Actor* _child : children)
		{
			UpdateChildPosition(_child);
		}
	}
	FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
	{
		root->SetRotation(_rotation);

		for (Actor* _child : children)
		{
			UpdateChildRotation(_child);
		}
	}
	FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
	{
		root->SetScale(_scale);

		for (Actor* _child : children)
		{
			UpdateChildScale(_child);
		}
	}
	FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
	{
		root->SetOrigin(_origin);
	}
	FORCEINLINE virtual void Move(const Vector2f& _offset) override
	{
		root->Move(_offset);

		for (Actor* _child : children)
		{
			_child->Move(_offset);
		}
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle) override
	{
		root->Rotate(_angle);

		for (Actor* _child : children)
		{
			_child->Rotate(_angle);
		}
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor) override
	{
		root->Scale(_factor);

		for (Actor* _child : children)
		{
			_child->Scale(_factor);
		}
	}

	#pragma endregion

	#pragma endregion

public:
	Actor(const string& _name = "Actor", const TransformData& _transform = TransformData());
	Actor(const Actor& _actor);
	virtual ~Actor();

public:
	virtual void Construct();
	virtual void Deconstruct();
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void BeginDestroy() override;

	void Destroy();

	#pragma region Components

	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);
	template <typename T>
	T* GetComponent()
	{
		for (Component* _component : components)
		{
			if (is_same_v<decltype(_component), T*>)
			{
				return dynamic_cast<T*>(_component);
			}
		}

		return nullptr;
	}

	#pragma endregion
};