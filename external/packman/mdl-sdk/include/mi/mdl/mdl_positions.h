/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/
/// \file mi/mdl/mdl_positions.h
/// \brief Interfaces for describing source positions
#ifndef MDL_POSITIONS_H
#define MDL_POSITIONS_H 1

#include <cstddef>

#include <mi/mdl/mdl_iowned.h>

namespace mi {
namespace mdl {

/// A source code position.
///
/// A source code position is a quadrupel of start line, start column, end line, and end column.
/// Additionally, a file identifier is stored. The file identifier (ID) is an index into
/// the file table, which is stored at the owner of the position.
class Position : public Interface_owned {
public:
    enum File_id {
        OWNER_FILE_ID = 0    ///< A predefined constant meaning "owner filename"
    };

    /// Get the start line.
    virtual int get_start_line() const = 0;

    /// Set the start line.
    ///
    /// \param line  the new start line
    virtual void set_start_line(int line) = 0;

    /// Get the start column.
    virtual int get_start_column() const = 0;

    /// Set the start column.
    ///
    /// \param column  the new start column
    virtual void set_start_column(int column) = 0;

    /// Get the end line.
    virtual int get_end_line() const = 0;

    /// Set the end line.
    ///
    /// \param line  the new end line
    virtual void set_end_line(int line) = 0;

    /// Get the end column.
    virtual int get_end_column() const = 0;

    /// Set the end column.
    ///
    /// \param column  the new end column
    virtual void set_end_column(int column) = 0;

    /// Get the filename id.
    virtual size_t get_filename_id() const = 0;

    /// Set the filename id.
    ///
    /// \param id  the file identifier
    virtual void set_filename_id(size_t id) = 0;
};

}  // mdl
}  // mi

#endif
