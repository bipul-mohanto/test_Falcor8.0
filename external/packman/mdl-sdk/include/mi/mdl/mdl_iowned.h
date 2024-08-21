/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/
/// \file mi/mdl/mdl_iowned.h
/// \brief Defines the Interface_owned interface.
#ifndef MDL_IOWNED_H
#define MDL_IOWNED_H 1

namespace mi {
namespace mdl {

/// This is the base class of all "owned" interfaces.
///
/// The lifetime of owned objects is coupled with the lifetime of its owners.
/// These objects can only be constructed through factories which become its owners
/// (and might be owned themselves).
class Interface_owned
{
protected:
    /// Interface_owned objects cannot be destructed, so hide its destructor.
    virtual ~Interface_owned() = 0;
};

/*!
 * \page mdl_ownership Ownership of objects in the MDL Core library
 *
 * Most object inside the MDL Core library are created by the MDL core compiler
 * or one of its backends. For those, the lifetime can be easily defined:
 * Once a higher level object is gone, there is no reason why they should survive.
 * For instance, if an IModule (the representation of a compiled MDL module) is
 * freed, there is no use case for AST nodes or types of this module.
 *
 * Hence, most objects are "owned" in the MDL Core. An owned interface is
 * always derived from the empty Interface_owned interface. This interface does not
 * add any functionality, it just serves as a marker.
 *
 * \section mdl_factories_and_objects Factories and objects
 *
 * Objects in the MDL Core world are always created by factories, in fact there
 * is no single \c new operator in the code itself. Because most interfaces returned
 * by factories are also immutable, sometimes factories even return singletons
 * without extra notice.
 *
 * Factories also are the owner of all object they create. However, all factories
 * are also owned by higher level objects like IModule or IGenerated_code_dag
 * which then are reference counted.
 *
 * Note that the ownership cannot be transferred. Especially it is illegal
 * to use a type owned by one IModule (through its type factory) inside another module.
 * This can be the source of bad crashes.
 *
 * However, it is possible to copy objects from one factory to another.
 * Factories that support such a copy operatiorn have a method \c import() which creates a
 * copy owned by the destination factory.
 *
 * \section mdl_no_new Allocation and the new operator in MDL Core
 *
 * The MDL Core library does not use the \c new operator. Instead, all objects
 * are allocated through an allocator interface mi::base::IAllocator.
 * Because all objects are created by factories, there is no need for operator \c new.
 */

} // mdl
} // mi

#endif // MDL_IOWNED_H
