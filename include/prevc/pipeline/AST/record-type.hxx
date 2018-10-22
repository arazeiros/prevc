
#ifndef PREVC_PIPELINE_AST_RECORDTYPE_HXX
#define PREVC_PIPELINE_AST_RECORDTYPE_HXX

#include <prevc/pipeline/AST/components.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief The record-type node in an AST.
             * */
            class RecordType: public Type
            {
            public:
                /**
                 * \brief Create an AST record-type node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the node in the source code.
                 * \param components The components.
                 * */
                RecordType(Pipeline* pipeline, util::Location&& location, Components* components);

                /**
                 * \brief Release used resources.
                 * */
                virtual ~RecordType();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Returns a string representation of this record-type.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The components.
                 * */
                Components* components;
            };
        }
    }
}

#endif
