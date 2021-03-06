#include <sn_stl/tr1/sn_exception.h>
#include <sn_stl/sn_map.h>
#include <stdarg.h>
#include <stdio.h>

namespace sn_std
{
	namespace tr1
	{
		void sn_exception::handle(bool condition, int32_t exception_code, const char* p_format, ...)
		{
            if (condition)
            {
                va_list args;
                va_start(args, p_format);
                vfprintf(stderr, p_format, args);
                va_end(args);
                fprintf(stderr, "\n");
            }
		}

		void sn_exception::register_handler(int32_t exception_code, handler_t p_func)
		{
			//handler_map[exception_code] = p_func;
		}
	}
}
