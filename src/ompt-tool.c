#include <stdio.h>
#include <omp-tools.h>
#include "include/ompt-callbacks.h"
#include "include/macros.h"

static int ompt_initialise(ompt_function_lookup_t, int, ompt_data_t *);
static void ompt_finalise(ompt_data_t *);
static uint64_t get_unique_thread_id(void);

// Invoked by OpenMP runtime
ompt_start_tool_result_t *
ompt_start_tool(
    unsigned int omp_version,
    const char  *runtime_version)
{
    fprintf(stderr, "OMPT: Runtime: %s\n", runtime_version);

    static ompt_start_tool_result_t result;
    result.initialize    = &ompt_initialise;
    result.finalize      = &ompt_finalise;
    result.tool_data.ptr = NULL;

    return &result;
}

// Initialise tool, obtain runtime entrypoints and register callbacks
static int
ompt_initialise(
    ompt_function_lookup_t lookup, 
    int                    initial_device_num, 
    ompt_data_t *          tool_data)
{   
    ompt_set_callback_t ompt_set_callback = (ompt_set_callback_t) lookup("ompt_set_callback");

    ompt_set_result_t result = ompt_set_never;

    // Register callbacks and print registration result
    SET_CALLBACK(ompt_callback_thread_begin);
    SET_CALLBACK(ompt_callback_thread_end);
    SET_CALLBACK(ompt_callback_parallel_begin);
    SET_CALLBACK(ompt_callback_parallel_end);
    SET_CALLBACK(ompt_callback_target);
    SET_CALLBACK(ompt_callback_target_submit);
    SET_CALLBACK(ompt_callback_target_data_op);
    SET_CALLBACK(ompt_callback_target_map);
    SET_CALLBACK(ompt_callback_device_initialize);
    SET_CALLBACK(ompt_callback_device_finalize);
    SET_CALLBACK(ompt_callback_device_load);
    SET_CALLBACK(ompt_callback_device_unload);

    return 1;
}

static void
ompt_finalise(
    ompt_data_t *tool_data)
{
    LOG_MESSAGE("Tool finalised");
    return;
}

static void
on_ompt_callback_thread_begin(
    ompt_thread_t            thread_type,
    ompt_data_t             *thread)
{
    thread->value = get_unique_thread_id();
    LOG_MESSAGE("t=%3lu", thread->value);
    return;
}

static void
on_ompt_callback_thread_end(
    ompt_data_t             *thread)
{
    LOG_MESSAGE();
    return;
}

static void
on_ompt_callback_parallel_begin(
    ompt_data_t             *encountering_task,
    const ompt_frame_t      *encountering_task_frame,
    ompt_data_t             *parallel,
    unsigned int             requested_parallelism,
    int                      flags,
    const void              *codeptr_ra)
{
    LOG_MESSAGE();
    return;
}

static void
on_ompt_callback_parallel_end(
    ompt_data_t             *parallel,
    ompt_data_t             *encountering_task,
    int                      flags,
    const void              *codeptr_ra)
{
    LOG_MESSAGE();
    return;
}

static void
on_ompt_callback_target(
    ompt_target_t            kind,
    ompt_scope_endpoint_t    endpoint,
    int                      device_num,
    ompt_data_t             *task,
    ompt_id_t                target_id,
    const void              *codeptr_ra)
{
    LOG_MESSAGE();
    return;
}

static void
on_ompt_callback_target_map(
    ompt_id_t                target_id,
    unsigned int             nitems,
    void *                  *host_addr,
    void *                  *device_addr,
    size_t                  *bytes,
    unsigned int            *mapping_flags,
    const void              *codeptr_ra)
{
    LOG_MESSAGE();
    return;
}

static void
on_ompt_callback_target_data_op(
    ompt_id_t                target_id,
    ompt_id_t                host_op_id,
    ompt_target_data_op_t    optype,
    void                    *src_addr,
    int                      src_device_num,
    void                    *dest_addr,
    int                      dest_device_num,
    size_t                   bytes,
    const void              *codeptr_ra)
{
    LOG_MESSAGE();
    return;
}

static void
on_ompt_callback_target_submit(
    ompt_id_t                target_id,
    ompt_id_t                host_op_id,
    unsigned int             requested_num_teams)
{
    LOG_MESSAGE();
    return;
}

static void
on_ompt_callback_buffer_request( 
    int device_num, 
    ompt_buffer_t **buffer, 
    size_t *bytes)
{
    *bytes = 0; // do not provide an event buffer
    LOG_MESSAGE();
    return;
}

static void
on_ompt_callback_buffer_complete( 
    int device_num, 
    ompt_buffer_t *buffer, 
    size_t bytes, 
    ompt_buffer_cursor_t begin, 
    int buffer_owned)
{
    LOG_MESSAGE();
    return;
}

static void
on_ompt_callback_device_initialize(
    int                      device_num,
    const char              *type,
    ompt_device_t           *device,
    ompt_function_lookup_t   lookup,
    const char              *documentation)
{
    LOG_MESSAGE("initialising device %d (%s)", device_num, type);
    fprintf(stderr, "Device: %s\n"
                    "Documentation:%s\n", type, documentation);
    return;
}

static void
on_ompt_callback_device_finalize(
    int                      device_num)
{
    LOG_MESSAGE("finalising device %d", device_num);
    return;
}

static void
on_ompt_callback_device_load(
    int                      device_num,
    const char              *filename,
    int64_t                  offset_in_file,
    void                    *vma_in_file,
    size_t                   bytes,
    void                    *host_addr,
    void                    *device_addr,
    uint64_t                 module_id)
{
    LOG_MESSAGE();
    return;
}

static void
on_ompt_callback_device_unload(
    int                      device_num,
    uint64_t                 module_id)
{
    LOG_MESSAGE();
    return;
}

static uint64_t
get_unique_thread_id(void)
{
    static uint64_t id = 0;
    return __sync_fetch_and_add(&id, 1);
}
