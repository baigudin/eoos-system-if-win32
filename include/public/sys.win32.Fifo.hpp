/**
 * Class implements FIFO files.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_WIN32_FIFO_HPP_
#define SYS_WIN32_FIFO_HPP_

#include "Object.hpp"
#include "api.Read.hpp"
#include "api.Write.hpp"
#include "lib.String.hpp"

#if EOOS_CPP_STANDARD < 2011
#error "C++ language standard less than C++11 is not supported"
#endif

namespace eoos
{
    namespace sys
    {
        namespace win32
        {        
            class Fifo final : public Object<>, public api::Read, public api::Write
            {
                typedef ::eoos::Object<> Parent;                
                
            public:
            
                /**
                 * Flag for this FIFO
                 */
                union Flag
                {
                    /**
                     * Creates a new FIFO file if it does not exist.
                     */
                    static const uint32_t CREATE = 0x00000001;
                    
                    /**
                     * Removes the FIFO file if it already exists and CREATE is set, otherwise no effect.
                     */
                    static const uint32_t REMOVE = 0x00000002;
                    
                    /**
                     * Blocks on the FIFO file until the other end will be opened.
                     */
                    static const uint32_t BLOCK = 0x00000004;
                    
                    /**
                     * Reads from the FIFO file.
                     */
                    static const uint32_t READ = 0x00000008;
                    
                    /**
                     * Writes to the FIFO file.
                     */
                    static const uint32_t WRITE = 0x00000008;
            
                    Flag() : value {0} {}
                    explicit Flag(uint32_t v) : value {v} {}
            
                    uint32_t value;
                    struct
                    {
                        uint32_t create : 1;
                        uint32_t remove : 1;
                        uint32_t block  : 1;
                        uint32_t read   : 1;
                        uint32_t write  : 1;
                        uint32_t        : 27;
                    } bit;
                };
            
                /**        
                 * Constructor.
                 *
                 * @param path - A path to a file to be opened.
                 * @param flag - Flags of the FIFO.
                 */
                Fifo(const String& path, Flag const flag) : Parent(),
                    path_ {path},
                    flag_ {flag}
                {
                    setConstructed( construct() );
                }
                
                /**
                 * Destructor.
                 */
                virtual ~Fifo() noexcept
                {
                    destruct();
                }
            
                /**
                 * Copy constructor.
                 */
                Fifo(const Fifo&) = delete;
            
                /**
                 * Move constructor.
                 */
                Fifo(Fifo&&) = delete;
            
                /**
                 * Copy assignment operator.
                 */
                Fifo& operator=(const Fifo&) = delete;
            
                /**
                 * Move assignment operator.
                 */
                Fifo& operator=(Fifo&&) = delete;
                
                /**
                 * Tests if this object has been constructed.
                 *
                 * @return true if object has been constructed successfully.
                 */
                bool_t isConstructed() const override
                {
                    return Parent::isConstructed();
                }                   
            
                /**
                 * Read data from this FIFO.
                 *
                 * @param data - Pointer to data.
                 * @param size - Size of data in Bytes.
                 * @return number of bytes written read.
                 */
                size_t read(void* const data, size_t const size) const noexcept override
                {
                    if( not isConstructed() )
                    {
                        return 0;
                    }
                    if( flag_.bit.read != 1 || data == NULLPTR || size == 0 )
                    {
                        return 0;
                    }
// TODO                    ::ssize_t bytes {::read(file_, data, size)};
                    auto bytes = -1;
                    return (bytes == -1) ? 0 : static_cast<size_t>(bytes);
                }
            
                /**
                 * Writes data from this FIFO.
                 *
                 * @param data - Pointer to data.
                 * @param size - Size of data in Bytes.
                 * @return number of bytes written.
                 */
                size_t write(const void* const data, size_t const size) noexcept override
                {
                    if( not isConstructed() )
                    {
                        return 0;
                    }
                    if( flag_.bit.write != 1 || data == NULLPTR || size == 0 )
                    {
                        return 0;
                    }
// TODO                    ::ssize_t bytes {::write(file_, data, size)};
                    auto bytes = -1;
                    return (bytes == -1) ? 0 : static_cast<size_t>(bytes);
                }
            
            private:
            
                /**
                 * Constructs this object.
                 *
                 * @return true if this object has been constructed successfully.
                 */
                bool_t construct()
                {
                    bool_t res {false};
                    do{
                        if( not isConstructed() )
                        {
                            break;
                        }
                        int error {0};
                        const char_t* const pathname {path_.getChar()};
                        // Create a FIFO file
                        if( flag_.bit.create == 1 )
                        {
                            error = create(pathname);
                            // Exit from if the error is not about the creating file exists and we have to retry
                            if(error != 0) {
                                if(error != EEXIST)
                                {
                                    break;
                                }
                                if(flag_.bit.remove == 0)
                                {
                                    break;
                                }
                            }
                        }
                        // Remove the FIFO file if it needs and try to re-create
                        if( error != 0 && flag_.bit.create == 1 && flag_.bit.remove == 1 )
                        {
                            error = remove(pathname);
                            if(error != 0)
                            {
                                break;
                            }
                            error = create(pathname);
                            if(error != 0) {
                                break;
                            }
                        }
                        // Open the FIFO file
// TODO                        if( flag_.bit.read == 1 || flag_.bit.write == 1 ){
// TODO                            int flags {0};
// TODO                            if( flag_.bit.read == 1 && flag_.bit.read == 1 ){
// TODO                                flags = O_RDWR | O_NONBLOCK;
// TODO                            } else if (flag_.bit.read == 1){
// TODO                                flags = O_RDONLY | O_NONBLOCK;
// TODO                            } else if (flag_.bit.write == 1){
// TODO                                flags = O_WRONLY | O_NONBLOCK;
// TODO                            } else {
// TODO                                break;
// TODO                            }
// TODO                            // Open FIFO in NONBLOCK mode
// TODO                            file_ = ::open(pathname, flags);
// TODO                            if( file_ == -1 ){
// TODO                                break;
// TODO                            }
// TODO                            // Remove NONBLOCK flag if it needs
// TODO                            if(flag_.bit.block == 1) {
// TODO                                flags &= ~O_NONBLOCK;
// TODO                                error = ::fcntl(file_, F_SETFL, flags);
// TODO                                error = -1;
// TODO                                if (error == -1) {
// TODO                                    break;
// TODO                                }
// TODO                            }
// TODO                        }
                        res = true;
                    }while(false);
                    return res;
                }
                
                /**
                 * Destructs this object.
                 */
                void destruct()
                {
                    if(file_ > 0) 
                    {
// TODO                        ::close(file_);
                    }
                    if( flag_.bit.create == 1 )
                    {
                        const char_t* const pathname {path_.getChar()};
                        remove(pathname);
                    }
                }
            
                /**
                 * Creates a FIFO file.
                 *
                 * @param pathname - A path to the file to be created.
                 * @return zero on success, or an errno number.
                 */
                static int create(const char_t* const pathname) noexcept
                {
// TODO                    ::mode_t const mode {S_IRUSR | S_IWUSR | S_IWGRP | S_IWGRP};
// TODO                    int error { ::mkfifo(pathname, mode) };
                    int error {-1};
                    if( error == -1 )
                    {
                        error = errno;
                    }
                    return error;
                }
            
                /**
                 * Removes a FIFO file.
                 *
                 * @param pathname - A path to the file to be removed.
                 * @return zero on success, or an errno number.
                 */
                static int remove(const char_t* const pathname) noexcept
                {
// TODO                    int error { ::unlink(pathname) };
                    int error {-1};                    
                    if( error == -1 )
                    {
                        error = errno;
                    }
                    return error;
                }
            
                /**
                 * Path to this FIFO.
                 */
                String path_;
                
                /**
                 * Flags of this FIFO.
                 */
                Flag flag_ {};
                
                /**
                 * File descriptor.
                 */
                int file_ {-1};

            };
        }
    }
}
#endif // SYS_WIN32_FIFO_HPP_
