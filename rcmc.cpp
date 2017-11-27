/*
 *
 */

#include <otawa/proc/ProcessorPlugin.h>

namespace rcmc {

using namespace elm;
using namespace otawa;

class Plugin: public ProcessorPlugin {
public:
    typedef elm::genstruct::Table<AbstractRegistration * > procs_t;

    Plugin(void): ProcessorPlugin("rcmc", Version(1, 0, 0), OTAWA_PROC_VERSION) { }
    virtual procs_t& processors (void) const { return procs_t::EMPTY; };
};

} 

rcmc::Plugin rcmc_plugin;
ELM_PLUGIN(rcmc_plugin, OTAWA_PROC_HOOK);

