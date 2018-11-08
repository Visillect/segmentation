/**
 * @file
 *
 * @brief   Adapter implementation for the json11 parser library.
 *
 * Include this file in your program to enable support for json11.
 *
 * This file defines the following classes (not in this order):
 *  - Json11Adapter
 *  - Json11Array
 *  - Json11ArrayValueIterator
 *  - Json11FrozenValue
 *  - Json11Object
 *  - Json11ObjectMember
 *  - Json11ObjectMemberIterator
 *  - Json11Value
 *
 * Due to the dependencies that exist between these classes, the ordering of
 * class declarations and definitions may be a bit confusing. The best place to
 * start is Json11Adapter. This class definition is actually very small,
 * since most of the functionality is inherited from the BasicAdapter class.
 * Most of the classes in this file are provided as template arguments to the
 * inherited BasicAdapter class.
 */

#ifndef __VALIJSON_ADAPTERS_JSON11_ADAPTER_HPP
#define __VALIJSON_ADAPTERS_JSON11_ADAPTER_HPP

#include <string>
#include <json11.hpp>
#include <boost/optional.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <valijson/adapters/adapter.hpp>
#include <valijson/adapters/basic_adapter.hpp>
#include <valijson/adapters/frozen_value.hpp>

namespace valijson {
namespace adapters {

class Json11Adapter;
class Json11ArrayValueIterator;
class Json11ObjectMemberIterator;

typedef std::pair<std::string, Json11Adapter> Json11ObjectMember;

/**
 * @brief  Light weight wrapper for a Json11 array value.
 *
 * This class is light weight wrapper for a Json11 array. It provides a
 * minimum set of container functions and typedefs that allow it to be used as
 * an iterable container.
 *
 * An instance of this class contains a single reference to the underlying
 * Json11 value, assumed to be an array, so there is very little overhead
 * associated with copy construction and passing by value.
 */
class Json11Array
{
public:

    typedef Json11ArrayValueIterator const_iterator;
    typedef Json11ArrayValueIterator iterator;

    /// Construct a Json11Array referencing an empty array.
    Json11Array()
      : value(emptyArray()) { }

    /**
     * @brief   Construct a Json11Array referencing a specific Json11
     *          value.
     *
     * @param   value   reference to a Json11 value
     *
     * Note that this constructor will throw an exception if the value is not
     * an array.
     */
    Json11Array(const json11::Json &value)
      : value(value)
    {
        if (!value.is_array()) {
            throw std::runtime_error("Value is not an array.");
        }
    }

    /**
     * @brief   Return an iterator for the first element of the array.
     *
     * The iterator return by this function is effectively the iterator
     * returned by the underlying Json11 implementation.
     */
    Json11ArrayValueIterator begin() const;

    /**
     * @brief   Return an iterator for one-past the last element of the array.
     *
     * The iterator return by this function is effectively the iterator
     * returned by the underlying Json11 implementation.
     */
    Json11ArrayValueIterator end() const;

    /// Return the number of elements in the array
    size_t size() const
    {
        return value.array_items().size();
    }

private:

    /**
     * @brief   Return a reference to a Json11 value that is an empty array.
     *
     * Note that the value returned by this function is a singleton.
     */
    static const json11::Json & emptyArray()
    {
        static const json11::Json array((json11::Json::array()));
        return array;
    }

    /// Reference to the contained value
    const json11::Json &value;
};

/**
 * @brief  Light weight wrapper for a Json11 object.
 *
 * This class is light weight wrapper for a Json11 object. It provides a
 * minimum set of container functions and typedefs that allow it to be used as
 * an iterable container.
 *
 * An instance of this class contains a single reference to the underlying
 * Json11 value, assumed to be an object, so there is very little overhead
 * associated with copy construction and passing by value.
 */
class Json11Object
{
public:

    typedef Json11ObjectMemberIterator const_iterator;
    typedef Json11ObjectMemberIterator iterator;

    /// Construct a Json11Object referencing an empty object singleton.
    Json11Object()
      : value(emptyObject()) { }

    /**
     * @brief   Construct a Json11Object referencing a specific Json11
     *          value.
     *
     * @param   value  reference to a Json11 value
     *
     * Note that this constructor will throw an exception if the value is not
     * an object.
     */
    Json11Object(const json11::Json &value)
      : value(value)
    {
        if (!value.is_object()) {
            throw std::runtime_error("Value is not an object.");
        }
    }

    /**
     * @brief   Return an iterator for this first object member
     *
     * The iterator return by this function is effectively a wrapper around
     * the iterator value returned by the underlying Json11 implementation.
     */
    Json11ObjectMemberIterator begin() const;

    /**
     * @brief   Return an iterator for an invalid object member that indicates
     *          the end of the collection.
     *
     * The iterator return by this function is effectively a wrapper around
     * the iterator value returned by the underlying Json11 implementation.
     */
    Json11ObjectMemberIterator end() const;

    /**
     * @brief   Return an iterator for the object member with the specified
     *          property name.
     *
     * If an object member with the specified name does not exist, the iterator
     * returned will be the same as the iterator returned by the end() function.
     *
     * @param   propertyName  property name to search for
     */
    Json11ObjectMemberIterator find(const std::string &propertyName) const;

    /// Returns the number of members belonging to this object.
    size_t size() const
    {
        return value.object_items().size();
    }

private:

    /**
     * @brief   Return a reference to a Json11 value that is empty object.
     *
     * Note that the value returned by this function is a singleton.
     */
    static const json11::Json & emptyObject()
    {
        static const json11::Json object((json11::Json::object()));
        return object;
    }

    /// Reference to the contained object
    const json11::Json &value;
};

/**
 * @brief   Stores an independent copy of a Json11 value.
 *
 * This class allows a Json11 value to be stored independent of its original
 * document. Json11 makes this easy to do, as it does not perform any
 * custom memory management.
 *
 * @see FrozenValue
 */
class Json11FrozenValue: public FrozenValue
{
public:

    /**
     * @brief  Make a copy of a Json11 value
     *
     * @param  source  the Json11 value to be copied
     */
    Json11FrozenValue(const json11::Json &source)
      : value(source) { }

    virtual FrozenValue * clone() const
    {
        return new Json11FrozenValue(value);
    }

    virtual bool equalTo(const Adapter &other, bool strict) const;

private:

    /// Stored Json11 value
    json11::Json value;
};

/**
 * @brief   Light weight wrapper for a Json11 value.
 *
 * This class is passed as an argument to the BasicAdapter template class,
 * and is used to provide access to a Json11 value. This class is responsible
 * for the mechanics of actually reading a Json11 value, whereas the
 * BasicAdapter class is responsible for the semantics of type comparisons
 * and conversions.
 *
 * The functions that need to be provided by this class are defined implicitly
 * by the implementation of the BasicAdapter template class.
 *
 * @see BasicAdapter
 */
class Json11Value
{
public:

    /// Construct a wrapper for the empty object singleton
    Json11Value()
      : value(emptyObject()) { }

    /// Construct a wrapper for a specific Json11 value
    Json11Value(const json11::Json &value)
      : value(value) { }

    /**
     * @brief   Create a new Json11FrozenValue instance that contains the
     *          value referenced by this Json11Value instance.
     *
     * @returns pointer to a new Json11FrozenValue instance, belonging to the
     *          caller.
     */
    FrozenValue * freeze() const
    {
        return new Json11FrozenValue(value);
    }

    /**
     * @brief   Optionally return a Json11Array instance.
     *
     * If the referenced Json11 value is an array, this function will return
     * a boost::optional containing a Json11Array instance referencing the
     * array.
     *
     * Otherwise it will return boost::none.
     */
    boost::optional<Json11Array> getArrayOptional() const
    {
        if (value.is_array()) {
            return boost::make_optional(Json11Array(value));
        }

        return boost::none;
    }

    /**
     * @brief   Retrieve the number of elements in the array
     *
     * If the referenced Json11 value is an array, this function will
     * retrieve the number of elements in the array and store it in the output
     * variable provided.
     *
     * @param   result  reference to size_t to set with result
     *
     * @returns true if the number of elements was retrieved, false otherwise.
     */
    bool getArraySize(size_t &result) const
    {
        if (value.is_array()) {
            result = value.array_items().size();
            return true;
        }

        return false;
    }

    bool getBool(bool &result) const
    {
        if (value.is_bool()) {
            result = value.bool_value();
            return true;
        }

        return false;
    }

    bool getDouble(double &result) const
    {
        if (value.is_number()) {
            result = value.number_value();
            return true;
        }

        return false;
    }

    bool getInteger(int64_t &result) const
    {
        if(isInteger()) {
            result = value.int_value();
            return true;
        }
        return false;
    }

    /**
     * @brief   Optionally return a Json11Object instance.
     *
     * If the referenced Json11 value is an object, this function will return a
     * boost::optional containing a Json11Object instance referencing the
     * object.
     *
     * Otherwise it will return boost::none.
     */
    boost::optional<Json11Object> getObjectOptional() const
    {
        if (value.is_object()) {
            return boost::make_optional(Json11Object(value));
        }

        return boost::none;
    }

    /**
     * @brief   Retrieve the number of members in the object
     *
     * If the referenced Json11 value is an object, this function will
     * retrieve the number of members in the object and store it in the output
     * variable provided.
     *
     * @param   result  reference to size_t to set with result
     *
     * @returns true if the number of members was retrieved, false otherwise.
     */
    bool getObjectSize(size_t &result) const
    {
        if (value.is_object()) {
            result = value.object_items().size();
            return true;
        }

        return false;
    }

    bool getString(std::string &result) const
    {
        if (value.is_string()) {
            result = value.string_value();
            return true;
        }

        return false;
    }

    static bool hasStrictTypes()
    {
        return true;
    }

    bool isArray() const
    {
        return value.is_array();
    }

    bool isBool() const
    {
        return value.is_bool();
    }

    bool isDouble() const
    {
        return value.is_number();
    }

    bool isInteger() const
    {
        return value.is_number()
            && value.int_value() == value.number_value();
    }

    bool isNull() const
    {
        return value.is_null();
    }

    bool isNumber() const
    {
        return value.is_number();
    }

    bool isObject() const
    {
        return value.is_object();
    }

    bool isString() const
    {
        return value.is_string();
    }

private:

    /// Return a reference to an empty object singleton
    static const json11::Json & emptyObject()
    {
        static const json11::Json object((json11::Json::object()));
        return object;
    }

    /// Reference to the contained Json11 value.
    const json11::Json &value;
};

/**
 * @brief   An implementation of the Adapter interface supporting Json11.
 *
 * This class is defined in terms of the BasicAdapter template class, which
 * helps to ensure that all of the Adapter implementations behave consistently.
 *
 * @see Adapter
 * @see BasicAdapter
 */
class Json11Adapter:
    public BasicAdapter<Json11Adapter,
                        Json11Array,
                        Json11ObjectMember,
                        Json11Object,
                        Json11Value>
{
public:

    /// Construct a Json11Adapter that contains an empty object
    Json11Adapter()
      : BasicAdapter() { }

    /// Construct a Json11Adapter containing a specific Json11 value
    Json11Adapter(const json11::Json &value)
      : BasicAdapter(value) { }
};

/**
 * @brief   Class for iterating over values held in a JSON array.
 *
 * This class provides a JSON array iterator that dereferences as an instance of
 * Json11Adapter representing a value stored in the array. It has been
 * implemented using the boost iterator_facade template.
 *
 * @see Json11Array
 */
class Json11ArrayValueIterator:
    public boost::iterator_facade<
        Json11ArrayValueIterator,          // name of derived type
        Json11Adapter,                     // value type
        boost::bidirectional_traversal_tag,  // bi-directional iterator
        Json11Adapter>                     // type returned when dereferenced
{
public:

    /**
     * @brief   Construct a new Json11ArrayValueIterator using an existing
     *          Json11 iterator.
     *
     * @param   itr  Json11 iterator to store
     */
    Json11ArrayValueIterator(
        const json11::Json::array::const_iterator &itr)
      : itr(itr) { }

    /// Returns a Json11Adapter that contains the value of the current
    /// element.
    Json11Adapter dereference() const
    {
        return Json11Adapter(*itr);
    }

    /**
     * @brief   Compare this iterator against another iterator.
     *
     * Note that this directly compares the iterators, not the underlying
     * values, and assumes that two identical iterators will point to the same
     * underlying object.
     *
     * @param   other  iterator to compare against
     *
     * @returns true   if the iterators are equal, false otherwise.
     */
    bool equal(const Json11ArrayValueIterator &other) const
    {
        return itr == other.itr;
    }

    void increment()
    {
        itr++;
    }

    void decrement()
    {
        itr--;
    }

    void advance(std::ptrdiff_t n)
    {
        itr += n;
    }

private:

    json11::Json::array::const_iterator itr;
};

/**
 * @brief   Class for iterating over the members belonging to a JSON object.
 *
 * This class provides a JSON object iterator that dereferences as an instance
 * of Json11ObjectMember representing one of the members of the object. It
 * has been implemented using the boost iterator_facade template.
 *
 * @see Json11Object
 * @see Json11ObjectMember
 */
class Json11ObjectMemberIterator:
    public boost::iterator_facade<
        Json11ObjectMemberIterator,        // name of derived type
        Json11ObjectMember,                // value type
        boost::bidirectional_traversal_tag,  // bi-directional iterator
        Json11ObjectMember>                // type returned when dereferenced
{
public:

    /**
     * @brief   Construct an iterator from a Json11 iterator.
     *
     * @param   itr  Json11 iterator to store
     */
    Json11ObjectMemberIterator(
        const json11::Json::object::const_iterator &itr)
      : itr(itr) { }

    /**
     * @brief   Returns a Json11ObjectMember that contains the key and value
     *          belonging to the object member identified by the iterator.
     */
    Json11ObjectMember dereference() const
    {
        return Json11ObjectMember(itr->first, itr->second);
    }

    /**
     * @brief   Compare this iterator with another iterator.
     *
     * Note that this directly compares the iterators, not the underlying
     * values, and assumes that two identical iterators will point to the same
     * underlying object.
     *
     * @param   other  Iterator to compare with
     *
     * @returns true if the underlying iterators are equal, false otherwise
     */
    bool equal(const Json11ObjectMemberIterator &other) const
    {
        return itr == other.itr;
    }

    void increment()
    {
        itr++;
    }

    void decrement()
    {
        itr--;
    }

private:

    /// Iternal copy of the original Json11 iterator
    json11::Json::object::const_iterator itr;
};

/// Specialisation of the AdapterTraits template struct for Json11Adapter.
template<>
struct AdapterTraits<valijson::adapters::Json11Adapter>
{
    typedef json11::Json DocumentType;

    static std::string adapterName()
    {
        return "Json11Adapter";
    }
};

inline bool Json11FrozenValue::equalTo(const Adapter &other, bool strict) const
{
    return Json11Adapter(value).equalTo(other, strict);
}

inline Json11ArrayValueIterator Json11Array::begin() const
{
    return value.array_items().begin();
}

inline Json11ArrayValueIterator Json11Array::end() const
{
    return value.array_items().end();
}

inline Json11ObjectMemberIterator Json11Object::begin() const
{
    return value.object_items().begin();
}

inline Json11ObjectMemberIterator Json11Object::end() const
{
    return value.object_items().end();
}

inline Json11ObjectMemberIterator Json11Object::find(
    const std::string &propertyName) const
{
    return value.object_items().find(propertyName);
}

}  // namespace adapters
}  // namespace valijson

#endif
