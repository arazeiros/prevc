#include <prevc/pipeline/AST/parameter.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Parameter::Parameter(Pipeline* pipeline, util::Location&& location,
                                     const util::String& name, Type* type):
                Node(pipeline, std::move(location)),
                name(name),
                type(type)
            {

            }

            Parameter::~Parameter()
            {
                delete type;
            }

            util::String Parameter::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "parameter", "location": %s, "name": "%s", "declarationType": %s})",
                        location.to_string().c_str(),
                        name.c_str(),
                        type->to_string().c_str());
            }
        }
    }
}
