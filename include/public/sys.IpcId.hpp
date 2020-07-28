/**
 * Class implements IPC identifier.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
 */

#ifndef SYS_IPC_ID_H_
#define SYS_IPC_ID_H_

#include "Types.hpp"

#if EOOS_CPP_STANDARD < 2011
#error "C++ language standard less than C++11 is not supported"
#endif

namespace eoos
{
    namespace sys
    {
        class IpcId final
        {
            
        public:
        
            /**
             * Type of ID.
             */
            using Type = int64_t;
        
            /**
             * Constructor.
             *
             * @param id - An user defined IPC Identifier.
             */
            explicit IpcId(Type id) :
                id_ {id}
            {
            }
        
            /**
             * Casts to the template data type.
             *
             * @return a data value.
             */
            operator Type() const
            {
                return id_;
            }
            
            /**            
             * Tests if an ID is server ID.
             *
             * @param identifier - An IPC Identifier.
             * @return true if ID is for server.
             */
            static bool_t isServerId(const IpcId& identifier)
            {
                return identifier.id_ == SERVER_ID;
            }    
            
            /**            
             * Tests if an ID is server ID.
             *
             * @param identifier - An IPC Identifier.
             * @return true if ID is for server.
             */
            static Type getServerId()
            {
                return SERVER_ID;
            }             
        
        private:
        
            /**
             * Server IPC Identifier.
             */
            static const Type SERVER_ID = -1;
            
            /**
             * IPC Identifier.
             */
            Type id_;
        };

    }
}

#endif // SYS_IPC_ID_H_