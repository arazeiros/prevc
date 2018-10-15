
#ifndef PREVC_PIPELINE_AST_COMPONENT_HXX
#define PREVC_PIPELINE_AST_COMPONENT_HXX

#include <prevc/pipeline/AST/node.hxx>
#include <prevc/pipeline/AST/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a component in the AST.
             * */
            class Component: public Node
            {
            public:
                /**
                 * \brief The component name.
                 * */
                 const util::String name;

                /**
                 * \brief Create an AST component at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the parameter in the source code.
                 * \param name The component name.
                 * \param type The component type.
                 * */
                Component(Pipeline* pipeline, util::Location&& location, const util::String& name, Type* type);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~Component();

                /**
                 * \brief Returns a string representation of this component.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            protected:
                /**
                 * \brief The component type.
                 * */
                Type* type;
            };
        }
    }
}

#endif
