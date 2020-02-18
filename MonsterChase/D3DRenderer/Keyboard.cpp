#include "Keyboard.h"

bool Keyboard::IsKeyPressed(unsigned char keycode) const
{
	return keystates[keycode];
}

Keyboard::Event Keyboard::ReadKey()
{
	if (keyBuffer.size() > 0u)
	{
		Event e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
	else
	{
		return Event();
	}
}

bool Keyboard::IsKeyEmpty() const
{
	return keyBuffer.empty();
}

char Keyboard::ReadChar()
{
	if (charBuffer.size() > 0u)
	{
		unsigned char charCode = charBuffer.front();
		charBuffer.pop();
		return charCode;
	}
	else
	{
		return 0;
	}
}

bool Keyboard::IsEmptyChar() const
{
	return charBuffer.empty();
}

void Keyboard::FlushChar()
{
	charBuffer = std::queue<char>();
}

void Keyboard::FlushKey()
{
	keyBuffer = std::queue<Event>();
}

void Keyboard::Flush()
{
	FlushKey();
	FlushChar();
}

void Keyboard::EnableAutoRepeat()
{
	autoRepeatEnabled = true;
}

void Keyboard::DisableAutoRepeat()
{
	autoRepeatEnabled = false;
}

bool Keyboard::IsAutoRepeatEnabled() const
{
	return autoRepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char keycode)
{
	keystates[keycode] = true;
	keyBuffer.push(Event(Event::Type::Pressed, keycode));
	TrimBuffer(keyBuffer);
}

void Keyboard::OnKeyReleased(unsigned char keycode)
{
	keystates[keycode] = false;
	keyBuffer.push(Event(Event::Type::Released, keycode));
	TrimBuffer(keyBuffer);
}

void Keyboard::OnChar(char character)
{
	charBuffer.push(character);
	TrimBuffer(charBuffer);
}

void Keyboard::ClearState()
{
	keystates.reset();
}

template <typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer)
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}