#pragma once
#include "Possibility.h"
#include <memory>

class SequencePossibilityIterator;
class TokenPossibilityIterator;
class OrPossibilityIterator;

class PossiblityIterator
{
public:
	PossiblityIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines);
	PossiblityIterator(const PossiblityIterator& other);

	const Possibility& operator*() const;
	const Possibility* operator->() const;

	virtual void getNext() = 0;

	operator bool();

protected:
	Possibility addNameAttr(const Possibility& possibility) const;
	static std::unique_ptr<PossiblityIterator> getIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines);
	

	Possibility _curr;
	const tinyxml2::XMLElement* _tag;
	const tinyxml2::XMLElement* _defines;
	std::vector<Token> _line;

	std::string _tagName;
	std::string _nameAttr;
	bool _lazy;
	bool _optional;
	bool _valid;
};

class OrPossibilityIterator : public PossiblityIterator
{
public:
	OrPossibilityIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines);
	OrPossibilityIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines, bool lazy);
	OrPossibilityIterator(OrPossibilityIterator&& other) noexcept;

	OrPossibilityIterator& operator=(OrPossibilityIterator&& other) noexcept;

	virtual void getNext();

private:
	void getPossibility();
	
	int _end;
	const tinyxml2::XMLElement* _currTag;
	std::unique_ptr<PossiblityIterator> _tagPossibilities;
};

class SequencePossibilityIterator : public PossiblityIterator
{
	struct StackPossibility
	{
		std::unique_ptr<PossiblityIterator> it;
		Possibility current;
		const tinyxml2::XMLElement* elem;
	};

public:
	SequencePossibilityIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines);
	SequencePossibilityIterator(SequencePossibilityIterator&& other) noexcept;

	virtual void getNext();

private:
	void getPossibility();

	size_t _end;
	std::stack<StackPossibility> _possibilities;
};

class TokenPossibilityIterator : public PossiblityIterator
{
public:
	TokenPossibilityIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines);
	TokenPossibilityIterator(TokenPossibilityIterator&& other) noexcept;

	virtual void getNext();

private:
	bool _define;
	Possibility _token;
	std::unique_ptr<OrPossibilityIterator> _definePossibilities;
};

