// C/C++ File
// AUTHOR:   juno
// FILE:     trace.c
// ROLE:     TODO (some explanation)
// CREATED:  2020-02-21 22:54:15
// MODIFIED: 2020-03-18 16:08:12

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#define __USE_GNU
#include <dlfcn.h>

static struct timespec first_ts;
static struct timespec now_ts;
static _Bool first_call = 1;

void __attribute__((__no_instrument_function__))
__cyg_profile_func_enter(void *this_fn, void *caller) {
  Dl_info dlinfo1, dlinfo2;
  const int lStatus1 = dladdr(this_fn, &dlinfo1);
  const int lStatus2 = dladdr(caller, &dlinfo2);
  if(first_call) {
      timespec_get(&first_ts, TIME_UTC);
      first_call = 0;
  }
  timespec_get(&now_ts, TIME_UTC);
  const double deltaTime = (now_ts.tv_sec + now_ts.tv_nsec * 1e-9) -
                     (first_ts.tv_sec + first_ts.tv_nsec * 1e-9);

  fprintf(stdout, "%f - [E] - %s => %s\n", deltaTime, dlinfo2.dli_sname,
          dlinfo1.dli_sname);
  //    fprintf(stdout, "   ... fname=%s, raddr=0x%lx, saddr=0x%lx, fbase=0x%lx,
  //    sname=%s",
  //            dlinfo1.dli_fname,
  //            (size_t)dlinfo1.dli_saddr - (size_t)dlinfo1.dli_fbase,
  //            (size_t)dlinfo1.dli_saddr,
  //            (size_t)dlinfo1.dli_fbase,
  //            dlinfo1.dli_sname);
}

void __attribute__((__no_instrument_function__))
__cyg_profile_func_exit(void *this_fn, void *caller) {
  Dl_info dlinfo1, dlinfo2;
  const int lStatus1 = dladdr(this_fn, &dlinfo1);
  const int lStatus2 = dladdr(caller, &dlinfo2);
  timespec_get(&now_ts, TIME_UTC);
  const double deltaTime = (now_ts.tv_sec + now_ts.tv_nsec * 1e-9) -
                     (first_ts.tv_sec + first_ts.tv_nsec * 1e-9);
  fprintf(stdout, "%f - [L] - %s => %s\n",
          deltaTime,
          dlinfo1.dli_sname,
          dlinfo2.dli_sname);
}
