# Overview

OpenMP 5.0 introduced the OpenMP tools (OMPT) interface which allows first-party tools to be notified about OpenMP runtime events and to trace activity on target devices. This allows tools to observe runtime events without the need to modify the target application.

This project demonstrates the use of the oneAPI implementation of the OMPT interface to observe OpenMP events on the host device related to GPU offloading, using Intel DevCloud GPUs. A simple matrix multiplication application is used to demonstrate events triggered by a target region.

To execute this project on DevCloud:

```
git clone https://github.com/adamtuft/ompt-target-events.git
cd ompt-target-events
./submit.sh
```

The log file `tmp/err.txt` contains notifications of the events related to the offloading of the target region to the GPU:

```
$ grep "^OMPT:" tmp/err.txt
OMPT: Runtime: Intel(R) OMP version: 5.0.20211013
OMPT: set callback on_ompt_callback_thread_begin        = 5
OMPT: set callback on_ompt_callback_thread_end          = 5
OMPT: set callback on_ompt_callback_parallel_begin      = 5
OMPT: set callback on_ompt_callback_parallel_end        = 5
OMPT: set callback on_ompt_callback_target              = 5
OMPT: set callback on_ompt_callback_target_submit       = 5
OMPT: set callback on_ompt_callback_target_data_op      = 5
OMPT: set callback on_ompt_callback_target_map          = 5
OMPT: set callback on_ompt_callback_device_initialize   = 5
OMPT: set callback on_ompt_callback_device_finalize     = 5
OMPT: set callback on_ompt_callback_device_load         = 5
OMPT: set callback on_ompt_callback_device_unload       = 5
OMPT: [on_ompt_callback_thread_begin       ] t=  0
OMPT: [on_ompt_callback_device_initialize  ] initialising device 0 (Intel(R) UHD Graphics P630 [0x3e96])
OMPT: [on_ompt_callback_device_load        ] 
OMPT: [on_ompt_callback_target             ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_submit      ] 
OMPT: [on_ompt_callback_target_submit      ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target_data_op     ] 
OMPT: [on_ompt_callback_target             ] 
OMPT: [on_ompt_callback_thread_end         ] 
OMPT: [ompt_finalise                       ] Tool finalised
```

Building on this prototype, later work will make greater use of the device tracing interface to trace target device events related to the offloading of tasks.

# Technologies Used

Intel oneAPI

OpenMP

DevCloud

Intel GPU