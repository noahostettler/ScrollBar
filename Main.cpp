#include "Game.h"
#include "GameManager.h"
#include "DuckHuntGame.h"

void InitConfig()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Logger::Reset();
}

int main()
{
    InitConfig();
    M_GAME.Launch(new DuckHuntGame());

    unique_ptr _uniquePtr = make_unique<int>(5);
    const int _value = *_uniquePtr.get();

    if (_uniquePtr)
    {
        LOG(Display, to_string(_value));
    }
    

    /*sf::RenderWindow _window(sf::VideoMode({ 800, 600 }), "SFML works!");

    const Vector2f& _size = Vector2f(200, 50);
    const Vector2f& _position = Vector2f(_window.getSize().x /2 - _size.x /2, 
                                        _window.getSize().y / 2 - _size.y / 2);

    

    vector<Vertex> _vertices =
    {
        { Vector2f(_position.x, _position.y), Color::Red },
        { Vector2f(_position.x + _size.x, _position.y), Color::Blue },
        { Vector2f(_position.x + _size.x, _position.y + _size.y), Color::Green },
        { Vector2f(_position.x, _position.y + _size.y), Color::Yellow },
        { Vector2f(_position.x, _position.y), Color::Magenta },
        { Vector2f(_position.x + _size.x, _position.y + _size.y), Color::Cyan },
        { Vector2f(_position.x + _size.x, _position.y), Color::White },
        { Vector2f(_position.x, _position.y + _size.y), Color::Blue },
    };

    Vertex _vertex;
    _vertex.position = Vector2f(10.0f, 100.0f);
    _vertex.color = Color::Red;

    while (_window.isOpen())
    {
        while (const std::optional _event = _window.pollEvent())
        {
            if (_event->is<sf::Event::Closed>())
                _window.close();

            if (const Event::Resized* _resized = _event->getIf<sf::Event::Resized>())
            {
                const int _newX = _resized->size.x <= (int)_size.x ? (int)_size.x : _resized->size.x;
                const int _newY = _resized->size.y <= (int)_size.y ? (int)_size.y : _resized->size.y;

                _window.setSize(Vector2u(_newX, _newY));
            }
        }
        _window.clear();
        _window.draw(_vertices.data(), _vertices.size(), PrimitiveType::LineStrip);
        _window.display();

    }*/

	return EXIT_SUCCESS;

  }

