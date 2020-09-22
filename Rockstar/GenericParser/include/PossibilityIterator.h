#pragma once
#include "Possibility.h"
#include <memory>
#include <unordered_map>

namespace genericparser
{

	class SequencePossibilityIterator;
	class TokenPossibilityIterator;
	class OrPossibilityIterator;

	class PossiblityIterator
	{
	public:
		PossiblityIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines);
		PossiblityIterator(const PossiblityIterator& other);

		Possibility current();
		virtual bool getNext() = 0;

	protected:
		static std::unique_ptr<PossiblityIterator> getIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines);
		static std::unique_ptr<PossiblityIterator> getIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines, bool lazy);

		Possibility _curr;
		const tinyxml2::XMLElement* _tag;
		const tinyxml2::XMLElement* _defines;
		std::vector<Token> _line;

		std::string _tagName;
		std::string _nameAttr;
		bool _lazy;
		bool _optional;
	private:
		Possibility addNameAttr(const Possibility& possibility) const;
	};

	class OrPossibilityIterator : public PossiblityIterator
	{
	public:
		OrPossibilityIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines);
		OrPossibilityIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines, bool lazy);
		OrPossibilityIterator(OrPossibilityIterator&& other) noexcept;

		OrPossibilityIterator& operator=(OrPossibilityIterator&& other) noexcept;

		virtual bool getNext();

	private:
		std::vector<std::unique_ptr<PossiblityIterator>> _possibilityIterators;
		std::vector<Possibility> _possibilities;
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

		virtual bool getNext();

	private:
		int _end;
		std::stack<StackPossibility> _possibilities;
	};

	class TokenPossibilityIterator : public PossiblityIterator
	{
	public:
		TokenPossibilityIterator(const std::vector<Token>& line, const tinyxml2::XMLElement* tag, const tinyxml2::XMLElement* defines);
		TokenPossibilityIterator(TokenPossibilityIterator&& other) noexcept;

		virtual bool getNext();

	private:
		bool _define;
		std::unique_ptr<OrPossibilityIterator> _definePossibilities;
	};

}