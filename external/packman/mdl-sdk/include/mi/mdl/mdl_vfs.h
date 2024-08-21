/******************************************************************************
 * Copyright 2023 NVIDIA Corporation. All rights reserved.
 *****************************************************************************/
/// \file mi/mdl/mdl_vfs.h
/// \brief Interfaces for the MDL core compiler file system access.
#ifndef MDL_VFS_H
#define MDL_VFS_H 1

#include <stdint.h>

#include <mi/base/iinterface.h>
#include <mi/base/interface_declare.h>

namespace mi {

namespace base { class IAllocator; }

namespace mdl {

/// An interface to virtualize file system access in the MDL core compiler.
///
/// This interface can be implemented by the user application.
class IVFS : public
    mi::base::Interface_declare<0xd7a0499f,0xb023,0x44e5,0x84,0x4b,0xaa,0x65,0xd9,0xd6,0xe1,0xc1,
    mi::base::IInterface>
{
public:
    /// Opaque type to represent streams.
    typedef void *Stream;

    enum Seek_origin {
        VFS_SEEK_SET = 0,
        VFS_SEEK_CUR = 1,
        VFS_SEEK_END = 2
    };

public:
    /// Return the OS-dependent path separator. This is the character separating the single
    /// directories from each other. E.g.  "\\" or "/".
    virtual char separator() = 0;

    /// Opens a file.
    ///
    /// \param filename  the name of the file to open, UTF8 encoded
    /// \param mode      the file access mode
    virtual Stream fopen(char const *filename, char const *mode) = 0;

    /// Close file.
    ///
    /// \param s       A stream opened by \c open().
    ///
    /// \return If the stream is successfully closed, a zero value is returned.
    ///         On failure, EOF is returned.
    virtual int fclose(Stream s) = 0;

    /// Read block of data from stream.
    ///
    /// \param ptr    Pointer to a block of memory with a size of at least (size*count) bytes.
    /// \param size   Size, in bytes, of each element to be read.
    /// \param count  Number of elements, each one with a size of \c size bytes.
    /// \param s      A stream opened by \c open().
    ///
    /// \return The total amount of bytes read if successful is (size*count).
    virtual size_t fread(void *ptr, size_t size, size_t count, Stream s) = 0;

    /// Reposition stream position indicator.
    ///
    /// \param s       A stream opened by \c open().
    /// \param offset  Number of bytes to offset from origin.
    /// \param origin  Position used as reference for the offset.
    virtual int fseek(Stream s, intptr_t offset, Seek_origin origin) = 0;

    /// Get current position in stream.
    ///
    /// \param s       A stream opened by \c open().
    virtual intptr_t ftell(Stream s) = 0;

    //// Check end - of - file indicator.
    ///
    /// \param s  a stream opened by \c open()
    ///
    /// \return non-zero if EOF was reached.
    virtual int feof(Stream s) = 0;

    /// Checks if the error indicator associated with stream is set.
    ///
    /// \param s  a stream opened by \c open()
    ///
    /// This indicator is generally set by a previous operation on the stream that failed, and is
    /// cleared by a call to clearerr(), or rewind().
    virtual int ferror(Stream s) = 0;

    /// Clear error indicators.
    /// \param s  a stream opened by \c open()
    ///
    /// Resets both the error and the eof indicators of the stream.
    virtual void clearerr(Stream s) = 0;

    /// Check if the given file name (UTF8 encoded) names a file on the file system.
    ///
    /// \param fname  an UTF8 encoded file name
    virtual bool is_file(
        char const *fname) = 0;

    /// Check if in the given directory a file matching the given mask exists.
    ///
    /// \param directory  an UTF8 encoded directory name
    /// \param mask       an UTF8 encoded file mask
    virtual bool has_file(
        char const *directory,
        char const *mask) = 0;

    /// Check if the given name (UTF8 encoded) names a directory on the file system.
    ///
    /// \param path   an UTF8 encoded file path
    virtual bool is_directory(
        char const *path) = 0;

    /// Creates a directory on the file system.
    ///
    /// \param path   an UTF8 encoded file path
    virtual bool mkdir(
        char const *path) = 0;

    /// Return true if a path is absolute, i.e. begins with / or X:/
    ///
    /// \param path   check this path
    virtual bool is_path_absolute(
        char const *path) = 0;

    /// Retrieve the current working directory.
    ///
    /// \param[out] buffer    point to the output buffer
    /// \param[in]  buf_size  length of the buffer
    ///
    /// \return true on success, false if the buffer is to small
    virtual bool get_cwd(char *buffer, size_t buf_size) = 0;

    /// errno for last VFS operation.
    virtual int verrno() = 0;
};

} // mdl
} // mi

#endif // MDL_VFS_H
