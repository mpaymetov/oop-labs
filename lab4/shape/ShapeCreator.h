#include "stdafx.h"
#include "Shape.h"

using ActionMap = std::map<std::string, std::function<std::shared_ptr<IShape>(std::istream & args)>>;

class CShapeCreator
{
public:
	CShapeCreator(std::istream &input);
	std::shared_ptr<IShape> ExecuteCommand() const;

private:
	std::shared_ptr<IShape> CreateLine(std::istream &args) const;
	std::shared_ptr<IShape> CreateTriangle(std::istream &args) const;
	std::shared_ptr<IShape> CreateRectangle(std::istream &args) const;
	std::shared_ptr<IShape> CreateCircle(std::istream &args) const;
private:
	std::istream &m_input;
	const ActionMap m_actionMap;
};
