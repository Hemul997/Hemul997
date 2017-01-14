#pragma once

class CStringStack
{
public:
	CStringStack() = default;
	CStringStack(CStringStack const &stack);
	CStringStack(CStringStack && stack);
	~CStringStack();
	void Push(std::string const & element);
	void Pop();
	void Clear();
	std::string GetLastElement() const;
	size_t GetSize() const;
	bool IsEmpty() const;
	CStringStack & operator=(CStringStack const & stack);
	CStringStack & operator=(CStringStack && stack);
	bool operator==(CStringStack const & stack) const;
	bool operator!=(CStringStack const & stack) const;
private:
	struct Node
	{
		std::string value;
		std::shared_ptr<Node> m_prevNode = nullptr;
	};
	std::shared_ptr<Node> m_top = nullptr;
	size_t m_size = 0;
};