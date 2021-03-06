
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_LINKTYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_LINKTYPE_HXX

#include <prevc/pipeline/semantic_analysis/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief Represent a link type in a Prev module.
             * */
            class LinkType: public Type
            {
            public:
                /**
                 * \brief Create a new link-type.
                 * \param id The id of the string.
                 * */
                LinkType(util::String&& id);

                /**
                 * \brief Release used resources.
                 * */
                virtual ~LinkType();

                /**
                 * \brief Tells if this type is a link type.
                 * */
                virtual bool is_link() const noexcept override;

                /**
                 * \brief Sets the real type.
                 * \param The real type.
                 * */
                void set_real(const Type* real) noexcept;

                /**
                 * \brief Cut the path (removing link types) to the real type.
                 * */
                void compress();

                /**
                 * \brief Returns the id of the type.
                 * \return The id of the type.
                 * */
                virtual const util::String& get_id() const noexcept override;

                /**
                 * \brief Returns the id of the type.
                 * \return The id of the type.
                 * */
                virtual Kind get_kind() const noexcept override;

                /**
                 * \brief Converts this to an atom-type.
                 * \return The converted this.
                 * */
                virtual const AtomType* as_atom() const override;

                /**
                 * \brief Converts this to an array-type.
                 * \return The converted this.
                 * */
                virtual const ArrayType* as_array() const override;

                /**
                 * \brief Converts this to an record-type.
                 * \return The converted this.
                 * */
                virtual const RecordType* as_record() const override;

                /**
                 * \brief Converts this to an pointer-type.
                 * \return The converted this.
                 * */
                virtual const PointerType* as_pointer() const override;

                /**
                 * \brief Tells if this type and the one specified as the parameter equals.
                 * \param other The other type.
                 * \return True if they equals, false otherwise.
                 *
                 * Note that two records equals even if they have different components names, but the same types
                 * in the same order.
                 * */
                virtual bool equals(const Type* other) const noexcept override;

                /**
                 * \brief Tells if the type is cyclic.
                 * \param set The set containing the link types seen before.
                 * \return True if it is, false otherwise.
                 * */
                virtual bool is_cyclic(std::set<const LinkType*>* set) const noexcept override;

                /**
                 * \brief Returns a string representation of a type.
                 * \return The representation.
                 * */
                virtual util::String to_string() const noexcept override;

            protected:
                /**
                 * \brief Generate the llvm-type representing this type.
                 * */
                virtual llvm::Type* generate_llvm_type(llvm::LLVMContext& context) override;

            private:
                /**
                 * \brief The id of the type.
                 * */
                const util::String id;

                /**
                 * \brief The real type represented by this link.
                 * */
                const Type* real;
            };
        }
    }
}

#endif
