#pragma once

#include <cassert>
#include <cstdint>
#include <memory>
#include <string>

#include "Base.hpp"
#include "FieldNodeMixin.hpp"
#include "Visitor.hpp"

namespace Node {

class AssignOperator final :
    public Base,
    public FieldValueNodeMixin<0>,
    public FieldDestinationNodeMixin<1>
{
public:
    AssignOperator(size_t ip, BasePtr destination, const std::string& op, BasePtr expr) :
        Base(2, ip, 10),
        FieldValueNodeMixin(this, expr),
        FieldDestinationNodeMixin(this, destination),
        m_Operator(op)
    {
    }
    virtual ~AssignOperator() = default;

    static std::shared_ptr<AssignOperator> make(size_t ip, BasePtr destination, const std::string& op, BasePtr expr)
    {
        return std::make_shared<AssignOperator>(ip, destination, op, expr);
    }

    virtual void visit(Visitor* visitor)
    {
        assert(visitor);
        visitor->visit(this);
    }

    const std::string& getOperator() const { return m_Operator; }

private:
    std::string m_Operator;
};

}