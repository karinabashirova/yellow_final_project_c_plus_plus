#include "node.h"

bool DateComparisonNode::Evaluate(const Date& date, const string& event) {
	switch (cmp_) {
	case  Comparison::Equal:
	{
		return date == date_;
	}
	case Comparison::Greater:
	{
		return date > date_;
	}
	case  Comparison::GreaterOrEqual:
	{
		return date >= date_;
	}
	case  Comparison::Less:
	{
		return date < date_;

	}
	case  Comparison::LessOrEqual:
	{
		return date <= date_;

	}
	case  Comparison::NotEqual:
	{
		return date != date_;
	}
	}
}


bool EventComparisonNode::Evaluate(const Date& date, const string& event) {
	switch (cmp_) {
	case Comparison::Equal:
		return (event == this->events);
	case Comparison::Greater:
		return (event > this->events);
	case Comparison::GreaterOrEqual:
		return (event >= this->events);
	case Comparison::Less:
		return (event < this->events);
	case Comparison::LessOrEqual:
		return (event <= this->events);
	case Comparison::NotEqual:
		return (event != this->events);
	default:throw invalid_argument("Unknown comparison"); 
	}
}


bool LogicalOperationNode::Evaluate(const Date& date, const string& event) {
	switch (logical_operation)
	{
	case LogicalOperation::And:
		return left->Evaluate(date, event) && right->Evaluate(date, event);
	case LogicalOperation::Or:
		return left->Evaluate(date, event) || right->Evaluate(date, event);
	default: throw invalid_argument("Unknown operation");//заглушка 
	}
}