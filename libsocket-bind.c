/**
 * 
 * @file    libsocket-bind.c
 *
 * @brief   main libsocket binding source code for DragonRuby.
 *
 * The core goal of this library is to provide scalable and functional networking
 * support for the DragonRuby Game Toolkit. This library is based on the C portion of
 * libsocket found at https://github.com/dermesser/libsocket
 * 
 */

/*
   The committers of the libsocket project, all rights reserved
   (c) 2012 and following, dermesser <lbo@spheniscida.de>
 
   DragonRuby is a registered trademark of DragonRuby LLP 
   (c) 2012 and following, amirrajan <amir.rajan@dragonruby.org>
 
   All modifications of the original code belong to a partnership between the
   name below and the DragonRuby game development community, all rights reserved
   (c) 2023 and following, bedwardly-down <social@brandongrows.me>

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS “AS IS” AND ANY
   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/**
*
* Header order is kind of important for Windows; 
* this solves a warning caused by dragonruby.h including windows.h
*
* */
#if defined(_WIN32)
#define _WINSOCKAPI_
#include <winsock2.h>
#include <ws2tcpip.h>
#elif defined(linux) || defined(__APPLE__)
#include <sys/socket.h>
#include <net/if.h>
#include <netdb.h>       // getaddrinfo()
#include <netinet/in.h>  // e.g. struct sockaddr_in on OpenBSD
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>  // read()/write()
#include <errno.h>
#endif

#include <mruby.h>
#include <string.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>
#include "libsocket.c"


static drb_api_t *drb_api;

static void drb_free_foreign_object_indirect(mrb_state *state, void *pointer) {
    drb_api->drb_free_foreign_object(state, pointer);
}
static int drb_ffi__ZTSi_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSi_ToRuby(mrb_state *state, int value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTS7C_Hooks {
    drb_foreign_object_kind kind;
    C_Hooks value;
};
static mrb_data_type ForeignObjectType_ZTS7C_Hooks = {"C_Hooks", drb_free_foreign_object_indirect};
static C_Hooks drb_ffi__ZTS7C_Hooks_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "C_Hooks");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS7C_Hooks);
    return ((struct drb_foreign_object_ZTS7C_Hooks *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS7C_Hooks_ToRuby(mrb_state *state, C_Hooks value) {
    struct drb_foreign_object_ZTS7C_Hooks *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS7C_Hooks));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "C_Hooks");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS7C_Hooks);
    return mrb_obj_value(rdata);
}
static unsigned int drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, unsigned int value) {
    return mrb_fixnum_value(value);
}
static mrb_value drb_ffi__ZTS7C_Hooks_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS7C_Hooks *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS7C_Hooks *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "C_Hooks");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS7C_Hooks);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS7C_Hooks_socket_connected_Get(mrb_state *state, mrb_value self) {
    C_Hooks record = drb_ffi__ZTS7C_Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.socket_connected);
}
static mrb_value drb_ffi__ZTS7C_Hooks_socket_connected_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7C_Hooks *)DATA_PTR(self))->value)->socket_connected = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7C_Hooks_error_thrown_Get(mrb_state *state, mrb_value self) {
    C_Hooks record = drb_ffi__ZTS7C_Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.error_thrown);
}
static mrb_value drb_ffi__ZTS7C_Hooks_error_thrown_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7C_Hooks *)DATA_PTR(self))->value)->error_thrown = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7C_Hooks_data_sent_Get(mrb_state *state, mrb_value self) {
    C_Hooks record = drb_ffi__ZTS7C_Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.data_sent);
}
static mrb_value drb_ffi__ZTS7C_Hooks_data_sent_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7C_Hooks *)DATA_PTR(self))->value)->data_sent = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7C_Hooks_data_received_Get(mrb_state *state, mrb_value self) {
    C_Hooks record = drb_ffi__ZTS7C_Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.data_received);
}
static mrb_value drb_ffi__ZTS7C_Hooks_data_received_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7C_Hooks *)DATA_PTR(self))->value)->data_received = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7C_Hooks_use_tcp_Get(mrb_state *state, mrb_value self) {
    C_Hooks record = drb_ffi__ZTS7C_Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.use_tcp);
}
static mrb_value drb_ffi__ZTS7C_Hooks_use_tcp_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7C_Hooks *)DATA_PTR(self))->value)->use_tcp = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7C_Hooks_use_ipv4_Get(mrb_state *state, mrb_value self) {
    C_Hooks record = drb_ffi__ZTS7C_Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.use_ipv4);
}
static mrb_value drb_ffi__ZTS7C_Hooks_use_ipv4_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7C_Hooks *)DATA_PTR(self))->value)->use_ipv4 = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7C_Hooks_close_socket_Get(mrb_state *state, mrb_value self) {
    C_Hooks record = drb_ffi__ZTS7C_Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.close_socket);
}
static mrb_value drb_ffi__ZTS7C_Hooks_close_socket_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7C_Hooks *)DATA_PTR(self))->value)->close_socket = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7C_Hooks_shutdown_socket_Get(mrb_state *state, mrb_value self) {
    C_Hooks record = drb_ffi__ZTS7C_Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.shutdown_socket);
}
static mrb_value drb_ffi__ZTS7C_Hooks_shutdown_socket_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7C_Hooks *)DATA_PTR(self))->value)->shutdown_socket = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_c_tick_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_tick': wrong number of arguments (%d for 0)", argc);
    int ret_val = c_tick();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_hook_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_hook': wrong number of arguments (%d for 0)", argc);
    C_Hooks ret_val = c_hook();
    return drb_ffi__ZTS7C_Hooks_ToRuby(state, ret_val);
}
DRB_FFI_EXPORT
void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "SOCKET");
    struct RClass *object_class = state->object_class;
    drb_api->mrb_define_module_function(state, module, "c_tick", drb_ffi_c_tick_Binding, MRB_ARGS_REQ(0));
    drb_api->mrb_define_module_function(state, module, "c_hook", drb_ffi_c_hook_Binding, MRB_ARGS_REQ(0));
    struct RClass *C_HooksClass = drb_api->mrb_define_class_under(state, module, "C_Hooks", object_class);
    drb_api->mrb_define_class_method(state, C_HooksClass, "new", drb_ffi__ZTS7C_Hooks_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "socket_connected", drb_ffi__ZTS7C_Hooks_socket_connected_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "socket_connected=", drb_ffi__ZTS7C_Hooks_socket_connected_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, C_HooksClass, "error_thrown", drb_ffi__ZTS7C_Hooks_error_thrown_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "error_thrown=", drb_ffi__ZTS7C_Hooks_error_thrown_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, C_HooksClass, "data_sent", drb_ffi__ZTS7C_Hooks_data_sent_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "data_sent=", drb_ffi__ZTS7C_Hooks_data_sent_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, C_HooksClass, "data_received", drb_ffi__ZTS7C_Hooks_data_received_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "data_received=", drb_ffi__ZTS7C_Hooks_data_received_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, C_HooksClass, "use_tcp", drb_ffi__ZTS7C_Hooks_use_tcp_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "use_tcp=", drb_ffi__ZTS7C_Hooks_use_tcp_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, C_HooksClass, "use_ipv4", drb_ffi__ZTS7C_Hooks_use_ipv4_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "use_ipv4=", drb_ffi__ZTS7C_Hooks_use_ipv4_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, C_HooksClass, "close_socket", drb_ffi__ZTS7C_Hooks_close_socket_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "close_socket=", drb_ffi__ZTS7C_Hooks_close_socket_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, C_HooksClass, "socket_host", drb_ffi__ZTS7C_Hooks_socket_host_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "socket_host=", drb_ffi__ZTS7C_Hooks_socket_host_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, C_HooksClass, "socket_port", drb_ffi__ZTS7C_Hooks_socket_port_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "socket_port=", drb_ffi__ZTS7C_Hooks_socket_port_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, C_HooksClass, "message", drb_ffi__ZTS7C_Hooks_message_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, C_HooksClass, "message=", drb_ffi__ZTS7C_Hooks_message_Set, MRB_ARGS_REQ(1));
}
