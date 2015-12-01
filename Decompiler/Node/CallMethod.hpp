#pragma once

#include <cassert>
#include <cstdint>
#include <memory>

#include "Base.hpp"
#include "FieldNodeMixin.hpp"
#include "Params.hpp"
#include "Visitor.hpp"

namespace Node {
class CallMethod final :
    public Base,
    public FieldObjectNodeMixin<0>,
    public FieldParametersNodeMixin<1>
{
public:
    CallMethod(size_t ip, const Pex::StringTable::Index& result, BasePtr& object, const Pex::StringTable::Index& method) :
        Base(2, ip, 0, result),
        FieldObjectNodeMixin(this, object),
        FieldParametersNodeMixin(this, Params::make()),
        m_Method(method)
    {
    }
    virtual ~CallMethod() = default;

    static std::shared_ptr<CallMethod> make(size_t ip, const Pex::StringTable::Index& result, BasePtr object, const Pex::StringTable::Index& method)
    {
        return std::make_shared<CallMethod>(ip, result, object, method);
    }

    virtual void visit(Visitor* visitor)
    {
        assert(visitor);
        visitor->visit(this);
    }

    const Pex::StringTable::Index& getMethod() const { return m_Method; }

private:
    Pex::StringTable::Index m_Method;
};

}