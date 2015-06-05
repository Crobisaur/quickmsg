#ifndef __SERVICE_WRAP_H_INCLUDED__
#define __SERVICE_WRAP_H_INCLUDED__

#include <quickmsg/ctypes.h>

#ifdef __cplusplus
extern "C" {
#endif

  qm_service_t
  qm_service_new (const char* srv_name, qm_service_handler_t impl, void* arg);

  void
  qm_service_destroy (qm_service_t self_p);

  void
  qm_service_spin(qm_service_t self_p);


#ifdef __cplusplus
}
#endif

#endif
