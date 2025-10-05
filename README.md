### Compile All Project components

- make

### Run Test Application

- ./test_app
-  vmmap $(pgrep test_app) | grep libmalicious # verify the .dylib is injected successfully

<pre>
MacBook-Air-2:macOS-process-injection-detector anish$ ./test_app
[Injected] Malicious library loaded!
Library injected successfully.
</pre>

### Run Process Injection Detector

- ./detector [process_name] # e.g test_app

<pre>
MacBook-Air-2:macOS-process-injection-detector anish$ ./detector test_app
[ALERT] Suspicious library loaded: /Users/USER/*/libmalicious.dylib in PID 52516
[ALERT] Suspicious library loaded: /Users/USER/*/libmalicious.dylib in PID 52516
[ALERT] Suspicious library loaded: /Users/USER/*/libmalicious.dylib in PID 52516
[INFO] Whitelisted library: /usr/lib/libobjc.A.dylib
[INFO] Whitelisted library: /usr/lib/system/libsystem_blocks.dylib
[INFO] Whitelisted library: /usr/lib/system/libxpc.dylib
[INFO] Whitelisted library: /usr/lib/system/libsystem_trace.dylib
[INFO] Whitelisted library: /usr/lib/system/libcorecrypto.dylib
[INFO] Whitelisted library: /usr/lib/system/libsystem_malloc.dylib
[INFO] Whitelisted library: /usr/lib/system/libdispatch.dylib
[INFO] Whitelisted library: /usr/lib/system/libsystem_featureflags.dylib
[INFO] Whitelisted library: /usr/lib/system/libsystem_c.dylib
[INFO] Whitelisted library: /usr/lib/libc++.1.dylib
[INFO] Whitelisted library: /usr/lib/libc++abi.dylib
[INFO] Whitelisted library: /usr/lib/system/libsystem_kernel.dylib
[INFO] Whitelisted library: /usr/lib/system/libsystem_pthread.dylib
[INFO] Whitelisted library: /usr/lib/system/libdyld.dylib
[INFO] Whitelisted library: /usr/lib/system/libsystem_platform.dylib
...
...
...
</pre>

- cat detector_log.txt

<pre>
MacBook-Air-2:macOS-process-injection-detector anish$ cat detector_log.txt 
[ALERT] Suspicious library loaded: /Users/USER/*/libmalicious.dylib in PID 52516
[ALERT] Suspicious library loaded: /Users/USER/*/libmalicious.dylib in PID 52516
[ALERT] Suspicious library loaded: /Users/USER/*/libmalicious.dylib in PID 52516
</pre>
