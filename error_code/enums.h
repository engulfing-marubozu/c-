#include <string>
namespace hgng_ns {
    enum class error_code {
        ok,
        failed_to_initialize,
        failed_to_load_config,
        err
    };

     std::string GetErrorDesc(error_code value) {
        switch (value) {
        case error_code::ok: return "OK";
        case error_code::failed_to_initialize: return "FAILED_TO_INITIALIZE";
        case error_code::failed_to_load_config: return "FAILED_TO_LOAD_CONFIG";
        default: return "UNKNOWN_ERROR_CODE";
        }
    }
}

                                                        