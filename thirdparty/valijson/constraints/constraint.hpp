#ifndef __VALIJSON_CONSTRAINTS_CONSTRAINT_HPP
#define __VALIJSON_CONSTRAINTS_CONSTRAINT_HPP

namespace valijson {
namespace constraints {

class ConstraintVisitor;

/**
 * @brief  Interface that must be implemented by concrete constraint types.
 *
 * @todo  Consider using something like the boost::cloneable concept here.
 */
struct Constraint {

    /**
     * @brief  Virtual destructor.
     */
    virtual ~Constraint() { }

    /**
     * @brief  Perform an action on the constraint using the visitor pattern.
     *
     * Note that Constraints cannot be modified by visitors.
     *
     * @param  visitor  Reference to a ConstraintVisitor object.
     *
     * @returns  the boolean value returned by one of the visitor's visit
     *           functions.
     */
    virtual bool accept(ConstraintVisitor &visitor) const = 0;

    /**
     * @brief  Make a copy of a constraint.
     *
     * Note that this should be a deep copy of the constraint.
     *
     * @returns  an owning-pointer to the new constraint.
     */
    virtual Constraint * clone() const = 0;

};

inline Constraint * new_clone(const Constraint &constraint)
{
    return constraint.clone();
}

} // namespace constraints
} // namespace valijson

#endif
