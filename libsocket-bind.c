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
/* check if file exists for writing the receive() buffer */
#include <io.h>
#define F_OK 0
#define access _access
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
struct drb_foreign_object_ZTS5Hooks {
    drb_foreign_object_kind kind;
    Hooks value;
};
static mrb_data_type ForeignObjectType_ZTS5Hooks = {"Hooks", drb_free_foreign_object_indirect};
static Hooks drb_ffi__ZTS5Hooks_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Hooks");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS5Hooks);
    return ((struct drb_foreign_object_ZTS5Hooks *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS5Hooks_ToRuby(mrb_state *state, Hooks value) {
    struct drb_foreign_object_ZTS5Hooks *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS5Hooks));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Hooks");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS5Hooks);
    return mrb_obj_value(rdata);
}
static unsigned int drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, unsigned int value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTSPc {
    drb_foreign_object_kind kind;
    char *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPc = {"char*", drb_free_foreign_object_indirect};
static char *drb_ffi__ZTSPc_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    if (mrb_type(self) == MRB_TT_STRING)
        return RSTRING_PTR(self);
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "CharPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSPc);
    return ((struct drb_foreign_object_ZTSPc *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPc_ToRuby(mrb_state *state, char *value) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "CharPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSPc);
    return mrb_obj_value(rdata);
}
static char drb_ffi__ZTSc_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSc_ToRuby(mrb_state *state, char value) {
    return mrb_fixnum_value(value);
}
static mrb_value drb_ffi__ZTSPc_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(char));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "CharPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSPc);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPc_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSc_ToRuby(mrb, *drb_ffi__ZTSPc_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPc_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPc_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPc_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSc_ToRuby(mrb, drb_ffi__ZTSPc_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPc_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    char new_value = drb_ffi__ZTSc_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPc_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPc_GetString(mrb_state *state, mrb_value self) {
    return drb_api->mrb_str_new_cstr(state, drb_ffi__ZTSPc_FromRuby(state, self));
}
static mrb_value drb_ffi__ZTS5Hooks_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS5Hooks *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS5Hooks *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Hooks");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS5Hooks);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS5Hooks_socket_connected_Get(mrb_state *state, mrb_value self) {
    Hooks record = drb_ffi__ZTS5Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.socket_connected);
}
static mrb_value drb_ffi__ZTS5Hooks_socket_connected_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Hooks *)DATA_PTR(self))->value)->socket_connected = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Hooks_error_thrown_Get(mrb_state *state, mrb_value self) {
    Hooks record = drb_ffi__ZTS5Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.error_thrown);
}
static mrb_value drb_ffi__ZTS5Hooks_error_thrown_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Hooks *)DATA_PTR(self))->value)->error_thrown = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Hooks_data_sent_Get(mrb_state *state, mrb_value self) {
    Hooks record = drb_ffi__ZTS5Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.data_sent);
}
static mrb_value drb_ffi__ZTS5Hooks_data_sent_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Hooks *)DATA_PTR(self))->value)->data_sent = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Hooks_data_received_Get(mrb_state *state, mrb_value self) {
    Hooks record = drb_ffi__ZTS5Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.data_received);
}
static mrb_value drb_ffi__ZTS5Hooks_data_received_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Hooks *)DATA_PTR(self))->value)->data_received = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Hooks_use_tcp_Get(mrb_state *state, mrb_value self) {
    Hooks record = drb_ffi__ZTS5Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.use_tcp);
}
static mrb_value drb_ffi__ZTS5Hooks_use_tcp_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Hooks *)DATA_PTR(self))->value)->use_tcp = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Hooks_use_ipv4_Get(mrb_state *state, mrb_value self) {
    Hooks record = drb_ffi__ZTS5Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.use_ipv4);
}
static mrb_value drb_ffi__ZTS5Hooks_use_ipv4_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Hooks *)DATA_PTR(self))->value)->use_ipv4 = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Hooks_close_socket_Get(mrb_state *state, mrb_value self) {
    Hooks record = drb_ffi__ZTS5Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.close_socket);
}
static mrb_value drb_ffi__ZTS5Hooks_close_socket_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Hooks *)DATA_PTR(self))->value)->close_socket = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Hooks_shutdown_socket_Get(mrb_state *state, mrb_value self) {
    Hooks record = drb_ffi__ZTS5Hooks_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.shutdown_socket);
}
static mrb_value drb_ffi__ZTS5Hooks_shutdown_socket_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Hooks *)DATA_PTR(self))->value)->shutdown_socket = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_c_send_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_send': wrong number of arguments (%d for 1)", argc);
    char *buf = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ssize_t ret_val = c_send(buf);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_receive_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_receive': wrong number of arguments (%d for 1)", argc);
    char *path = drb_ffi__ZTSPc_FromRuby(state,args[0]);
    ssize_t ret_val = c_receive(path);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_close_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_close': wrong number of arguments (%d for 0)", argc);
    int ret_val = c_close();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_open_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_open': wrong number of arguments (%d for 2)", argc);
    char *address = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *port = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    int ret_val = c_open(address, port);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_shutdown_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_shutdown': wrong number of arguments (%d for 0)", argc);
    int ret_val = c_shutdown();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_tick_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_tick': wrong number of arguments (%d for 1)", argc);
    int tick_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    int ret_val = c_tick(tick_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_hook_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_hook': wrong number of arguments (%d for 0)", argc);
    Hooks ret_val = c_hook();
    return drb_ffi__ZTS5Hooks_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_init_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_init': wrong number of arguments (%d for 2)", argc);
    char* address_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char* port_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    int ret_val = c_init(address_0, port_1);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
DRB_FFI_EXPORT
void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "SOCKET");
    struct RClass *object_class = state->object_class;
    drb_api->mrb_define_module_function(state, module, "c_tick", drb_ffi_c_tick_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "c_hook", drb_ffi_c_hook_Binding, MRB_ARGS_REQ(0));
    drb_api->mrb_define_module_function(state, module, "c_init", drb_ffi_c_init_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "c_send", drb_ffi_c_send_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "c_receive", drb_ffi_c_receive_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "c_close", drb_ffi_c_close_Binding, MRB_ARGS_REQ(0));
    drb_api->mrb_define_module_function(state, module, "c_open", drb_ffi_c_open_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "c_shutdown", drb_ffi_c_shutdown_Binding, MRB_ARGS_REQ(0));
    struct RClass *CharPointerClass = drb_api->mrb_define_class_under(state, module, "CharPointer", object_class);
    drb_api->mrb_define_class_method(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
    struct RClass *HooksClass = drb_api->mrb_define_class_under(state, module, "Hooks", object_class);
    drb_api->mrb_define_class_method(state, HooksClass, "new", drb_ffi__ZTS5Hooks_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, HooksClass, "socket_connected", drb_ffi__ZTS5Hooks_socket_connected_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, HooksClass, "socket_connected=", drb_ffi__ZTS5Hooks_socket_connected_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, HooksClass, "error_thrown", drb_ffi__ZTS5Hooks_error_thrown_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, HooksClass, "error_thrown=", drb_ffi__ZTS5Hooks_error_thrown_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, HooksClass, "data_sent", drb_ffi__ZTS5Hooks_data_sent_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, HooksClass, "data_sent=", drb_ffi__ZTS5Hooks_data_sent_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, HooksClass, "data_received", drb_ffi__ZTS5Hooks_data_received_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, HooksClass, "data_received=", drb_ffi__ZTS5Hooks_data_received_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, HooksClass, "use_tcp", drb_ffi__ZTS5Hooks_use_tcp_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, HooksClass, "use_tcp=", drb_ffi__ZTS5Hooks_use_tcp_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, HooksClass, "use_ipv4", drb_ffi__ZTS5Hooks_use_ipv4_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, HooksClass, "use_ipv4=", drb_ffi__ZTS5Hooks_use_ipv4_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, HooksClass, "close_socket", drb_ffi__ZTS5Hooks_close_socket_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, HooksClass, "close_socket=", drb_ffi__ZTS5Hooks_close_socket_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, HooksClass, "shutdown_socket", drb_ffi__ZTS5Hooks_shutdown_socket_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, HooksClass, "shutdown_socket=", drb_ffi__ZTS5Hooks_shutdown_socket_Set, MRB_ARGS_REQ(1));
}
