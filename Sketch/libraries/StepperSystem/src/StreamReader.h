#pragma once

////////////////////////////////////////////////////////
// 
// class for scanning an commandstream
//

class CStreamReader
{
public:

	CStreamReader();
	void Init(char* buffer)					{ _buffer = buffer; _error = NULL; }

	bool IsError()							{ return _error != NULL; };
	const __FlashStringHelper * GetError()	{ return _error; }

	char SkipSpaces();
	char SkipSpacesToUpper()				{ return Toupper(SkipSpaces()); }
	char GetNextCharSkipScaces()			{ _buffer++; return SkipSpaces(); }		// move to next and skip spaces

	char GetCharToUpper()					{ return (char)Toupper(*_buffer); }
	char GetChar()							{ return *_buffer; }
	char GetNextChar()						{ return *(++_buffer); }					// skip current and move to next
	char GetNextCharToUpper()				{ return Toupper(GetNextChar()); }			// skip current and move to next

	void MoveToEnd()						{ while (*_buffer) _buffer++; }				// move to "no more char in stream"

	const char*	GetBuffer()					{ return _buffer; }
	void ResetBuffer(const char* buffer)	{ _buffer = buffer; }

	static char Toupper(char ch)			{ return (char)toupper(ch); }
	static bool IsEOC(char ch)				{ return ch == 0 || ch == ';'; }			// is EndOfCommand

	static bool IsSpace(char ch)			{ return ch == ' ' || ch == '\t'; }
	static bool IsSpaceOrEnd(char ch)		{ return ch == 0 || IsSpace(ch); }

	static bool IsMinus(char ch)			{ return ch == '-'; }
	static bool IsDot(char ch)				{ return ch == '.'; }
	static bool IsDigit(char ch)			{ return isdigit(ch) != 0; }
	static bool IsDigitDot(char ch)			{ return IsDigit(ch) || IsDot(ch); }

	static bool IsAlpha(char ch)			{ ch = Toupper(ch); return ch == '_' || (ch >= 'A' && ch <= 'Z'); }

	void Error(const __FlashStringHelper * error)		{ _error = error; MoveToEnd(); }

	const char* _buffer;
	const __FlashStringHelper * _error;

	class CSetTemporary
	{
	private:
		char* _buffer;
		char  _oldch;

	public:
		CSetTemporary(const char*buffer)			{ _buffer = (char*)buffer;  _oldch = *_buffer;  *_buffer = 0; }
		CSetTemporary(const char*buffer, char ch)	{ _buffer = (char*)buffer;  _oldch = *_buffer;  *_buffer = ch; }
		~CSetTemporary()							{ *_buffer = _oldch; }
	};
};

////////////////////////////////////////////////////////


