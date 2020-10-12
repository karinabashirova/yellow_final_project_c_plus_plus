#pragma once
#include "date.h"
#include <memory>
//#include "condition_parser.h"
//классы Node, EmptyNode, DateComparisonNode, EventComparisonNode и LogicalOperationNode
//— сформировать их иерархию и публичный интерфейс вам поможет анализ функций main и ParseCondition;
//
//node.h / cpp — эти файлы должны содержать объявления и определения класса Node, а также всех его потомков(см.выше),
//которые представляют собой узлы абстрактного синтаксического дерева, формируемого функцией ParseCondition;
enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};
class Node : public Date{
public:
	virtual bool Evaluate(const Date&, const string&) = 0;
};


class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event) override {
		date.~Date();
		return true;
	}
};


class DateComparisonNode : public Node {
public:	
	Comparison cmp_;
	Date date_;
	DateComparisonNode() {}
	DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {}
	DateComparisonNode(const Comparison& cmp, Date& date) : cmp_(cmp), date_(date) {}
	bool Evaluate(const Date& date, const string& event) override; 
};


class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& events_) : cmp_(cmp),  events(events_) {}
	Comparison cmp_;
	const string events;
	bool Evaluate(const Date& date, const string& event) override;
};
class LogicalOperationNode : public Node {		
public:
	LogicalOperationNode(const LogicalOperation& l_op, const shared_ptr<Node>& l, const shared_ptr<Node>& r)
		: Node()
		, logical_operation{ l_op }
		, left{ l }
		, right{ r }
	{}
	LogicalOperation logical_operation;
	shared_ptr<Node> left;
	shared_ptr<Node> right;
	LogicalOperation lo_;
	const string events;

	bool Evaluate(const Date& date, const string& event) override;
};