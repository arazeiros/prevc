
#ifndef PREVC_PIPELINE_AST_DECLARATION_HXX
#define PREVC_PIPELINE_AST_DECLARATION_HXX

#include <prevc/pipeline/AST/node.hxx>
#include <prevc/pipeline/AST/type.hxx>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a declaration in the AST.
             * */
            class Declaration: public Node
            {
            public:
                /**
                 * \brief The declaration name.
                 * */
                 const util::String name;

                /**
                 * \brief Create an AST declaration at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the declaration in the source code.
                 * \param name The declaration name.
                 * \param type The declaration type.
                 * */
                Declaration(Pipeline* pipeline, util::Location&& location, const util::String& name, Type* type);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~Declaration();

            protected:
                /**
                 * \brief The declaration type.
                 * */
                Type* type;
            };
        }
    }
}

#endif
