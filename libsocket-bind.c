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
struct drb_foreign_object_ZTS4Flag {
    drb_foreign_object_kind kind;
    Flag value;
};
static mrb_data_type ForeignObjectType_ZTS4Flag = {"Flag", drb_free_foreign_object_indirect};
static Flag drb_ffi__ZTS4Flag_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Flag");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS4Flag);
    return ((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS4Flag_ToRuby(mrb_state *state, Flag value) {
    struct drb_foreign_object_ZTS4Flag *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS4Flag));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Flag");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS4Flag);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS5Error {
    drb_foreign_object_kind kind;
    Error value;
};
static mrb_data_type ForeignObjectType_ZTS5Error = {"Error", drb_free_foreign_object_indirect};
static Error drb_ffi__ZTS5Error_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Error");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS5Error);
    return ((struct drb_foreign_object_ZTS5Error *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS5Error_ToRuby(mrb_state *state, Error value) {
    struct drb_foreign_object_ZTS5Error *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS5Error));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Error");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS5Error);
    return mrb_obj_value(rdata);
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
struct drb_foreign_object_ZTSPv {
    drb_foreign_object_kind kind;
    void *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPv = {"void*", drb_free_foreign_object_indirect};
static void *drb_ffi__ZTSPv_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "VoidPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSPv);
    return ((struct drb_foreign_object_ZTSPv *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPv_ToRuby(mrb_state *state, void *value) {
    struct drb_foreign_object_ZTSPv *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPv));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "VoidPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSPv);
    return mrb_obj_value(rdata);
}
static size_t drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, size_t value) {
    return mrb_fixnum_value(value);
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
static mrb_value drb_ffi__ZTS4Flag_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS4Flag *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS4Flag *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Flag");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS4Flag);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS4Flag_connected_Get(mrb_state *state, mrb_value self) {
    Flag record = drb_ffi__ZTS4Flag_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.connected);
}
static mrb_value drb_ffi__ZTS4Flag_connected_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value)->connected = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Flag_kill_Get(mrb_state *state, mrb_value self) {
    Flag record = drb_ffi__ZTS4Flag_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.kill);
}
static mrb_value drb_ffi__ZTS4Flag_kill_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value)->kill = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Flag_error_Get(mrb_state *state, mrb_value self) {
    Flag record = drb_ffi__ZTS4Flag_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.error);
}
static mrb_value drb_ffi__ZTS4Flag_error_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value)->error = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Flag_protocol_Get(mrb_state *state, mrb_value self) {
    Flag record = drb_ffi__ZTS4Flag_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.protocol);
}
static mrb_value drb_ffi__ZTS4Flag_protocol_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value)->protocol = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Flag_ipv4_Get(mrb_state *state, mrb_value self) {
    Flag record = drb_ffi__ZTS4Flag_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.ipv4);
}
static mrb_value drb_ffi__ZTS4Flag_ipv4_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value)->ipv4 = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Flag_ipv6_Get(mrb_state *state, mrb_value self) {
    Flag record = drb_ffi__ZTS4Flag_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.ipv6);
}
static mrb_value drb_ffi__ZTS4Flag_ipv6_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value)->ipv6 = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Flag_read_Get(mrb_state *state, mrb_value self) {
    Flag record = drb_ffi__ZTS4Flag_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.read);
}
static mrb_value drb_ffi__ZTS4Flag_read_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value)->read = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Flag_write_Get(mrb_state *state, mrb_value self) {
    Flag record = drb_ffi__ZTS4Flag_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.write);
}
static mrb_value drb_ffi__ZTS4Flag_write_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value)->write = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Flag_step_Get(mrb_state *state, mrb_value self) {
    Flag record = drb_ffi__ZTS4Flag_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.step);
}
static mrb_value drb_ffi__ZTS4Flag_step_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value)->step = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Flag_accept_Get(mrb_state *state, mrb_value self) {
    Flag record = drb_ffi__ZTS4Flag_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.accept);
}
static mrb_value drb_ffi__ZTS4Flag_accept_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value)->accept = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Error_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS5Error *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS5Error *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "SOCKET");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Error");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS5Error);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS5Error_code_Get(mrb_state *state, mrb_value self) {
    Error record = drb_ffi__ZTS5Error_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.code);
}
static mrb_value drb_ffi__ZTS5Error_code_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Error *)DATA_PTR(self))->value)->code = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Error_message_Get(mrb_state *state, mrb_value self) {
    Error record = drb_ffi__ZTS5Error_FromRuby(state, self);
    return drb_ffi__ZTSPc_ToRuby(state, record.message);
}
static mrb_value drb_ffi__ZTS5Error_message_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    char *new_value = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Error *)DATA_PTR(self))->value)->message = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Error_trigger_Get(mrb_state *state, mrb_value self) {
    Error record = drb_ffi__ZTS5Error_FromRuby(state, self);
    return drb_ffi__ZTSPc_ToRuby(state, record.trigger);
}
static mrb_value drb_ffi__ZTS5Error_trigger_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    char *new_value = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Error *)DATA_PTR(self))->value)->trigger = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_c_hook_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_hook': wrong number of arguments (%d for 0)", argc);
    Flag ret_val = c_hook();
    return drb_ffi__ZTS4Flag_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_error_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_error': wrong number of arguments (%d for 0)", argc);
    Error ret_val = c_error();
    return drb_ffi__ZTS5Error_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_start_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 3)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_start': wrong number of arguments (%d for 3)", argc);
    char *bind_addr_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *bind_port_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    int flags_2 = drb_ffi__ZTSi_FromRuby(state, args[2]);
    int ret_val = c_start(bind_addr_0, bind_port_1, flags_2);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_send_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 6)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_send': wrong number of arguments (%d for 6)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    void *buf_1 = drb_ffi__ZTSPv_FromRuby(state, args[1]);
    size_t size_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    char *host_3 = drb_ffi__ZTSPc_FromRuby(state, args[3]);
    char *service_4 = drb_ffi__ZTSPc_FromRuby(state, args[4]);
    int sendto_flags_5 = drb_ffi__ZTSi_FromRuby(state, args[5]);
    ssize_t ret_val = c_send(sfd_0, buf_1, size_2, host_3, service_4, sendto_flags_5);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_receive_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 8)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_receive': wrong number of arguments (%d for 8)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    void *buffer_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    size_t size_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    char *src_host_3 = drb_ffi__ZTSPc_FromRuby(state, args[3]);
    size_t src_host_len_4 = drb_ffi__ZTSj_FromRuby(state, args[4]);
    char *src_service_5 = drb_ffi__ZTSPc_FromRuby(state, args[5]);
    size_t src_service_len_6 = drb_ffi__ZTSj_FromRuby(state, args[6]);
    int recvfrom_flags_7 = drb_ffi__ZTSi_FromRuby(state, args[7]);
    ssize_t ret_val = c_receive(sfd_0, buffer_1, size_2, src_host_3, src_host_len_4, src_service_5, src_service_len_6, recvfrom_flags_7);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_open_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 3)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_open': wrong number of arguments (%d for 3)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    char *host_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    char *service_2 = drb_ffi__ZTSPc_FromRuby(state, args[2]);
    int ret_val = c_open(sfd_0, host_1, service_2);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_close_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_close': wrong number of arguments (%d for 1)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    int ret_val = c_close(sfd_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_c_shutdown_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'c_shutdown': wrong number of arguments (%d for 1)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    int ret_val = c_shutdown(sfd_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
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
DRB_FFI_EXPORT
void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "SOCKET");
    struct RClass *object_class = state->object_class;
    drb_api->mrb_define_module_function(state, module, "c_hook", drb_ffi_c_hook_Binding, MRB_ARGS_REQ(0));
    drb_api->mrb_define_module_function(state, module, "c_error", drb_ffi_c_error_Binding, MRB_ARGS_REQ(0));
    drb_api->mrb_define_module_function(state, module, "c_start", drb_ffi_c_start_Binding, MRB_ARGS_REQ(3));
    drb_api->mrb_define_module_function(state, module, "c_send", drb_ffi_c_send_Binding, MRB_ARGS_REQ(6));
    drb_api->mrb_define_module_function(state, module, "c_receive", drb_ffi_c_receive_Binding, MRB_ARGS_REQ(9));
    drb_api->mrb_define_module_function(state, module, "c_open", drb_ffi_c_open_Binding, MRB_ARGS_REQ(3));
    drb_api->mrb_define_module_function(state, module, "c_close", drb_ffi_c_close_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "c_shutdown", drb_ffi_c_shutdown_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "c_tick", drb_ffi_c_tick_Binding, MRB_ARGS_REQ(0));
    struct RClass *CharPointerClass = drb_api->mrb_define_class_under(state, module, "CharPointer", object_class);
    drb_api->mrb_define_class_method(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
    struct RClass *VoidPointerClass = drb_api->mrb_define_class_under(state, module, "VoidPointer", object_class);
    struct RClass *FlagClass = drb_api->mrb_define_class_under(state, module, "Flag", object_class);
    drb_api->mrb_define_class_method(state, FlagClass, "new", drb_ffi__ZTS4Flag_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "connected", drb_ffi__ZTS4Flag_connected_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "connected=", drb_ffi__ZTS4Flag_connected_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagClass, "kill", drb_ffi__ZTS4Flag_kill_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "kill=", drb_ffi__ZTS4Flag_kill_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagClass, "error", drb_ffi__ZTS4Flag_error_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "error=", drb_ffi__ZTS4Flag_error_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagClass, "protocol", drb_ffi__ZTS4Flag_protocol_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "protocol=", drb_ffi__ZTS4Flag_protocol_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagClass, "ipv4", drb_ffi__ZTS4Flag_ipv4_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "ipv4=", drb_ffi__ZTS4Flag_ipv4_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagClass, "ipv6", drb_ffi__ZTS4Flag_ipv6_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "ipv6=", drb_ffi__ZTS4Flag_ipv6_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagClass, "read", drb_ffi__ZTS4Flag_read_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "read=", drb_ffi__ZTS4Flag_read_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagClass, "write", drb_ffi__ZTS4Flag_write_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "write=", drb_ffi__ZTS4Flag_write_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagClass, "step", drb_ffi__ZTS4Flag_step_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "step=", drb_ffi__ZTS4Flag_step_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagClass, "accept", drb_ffi__ZTS4Flag_accept_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "accept=", drb_ffi__ZTS4Flag_accept_Set, MRB_ARGS_REQ(1));
    struct RClass *ErrorClass = drb_api->mrb_define_class_under(state, module, "Error", object_class);
    drb_api->mrb_define_class_method(state, ErrorClass, "new", drb_ffi__ZTS5Error_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ErrorClass, "code", drb_ffi__ZTS5Error_code_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ErrorClass, "code=", drb_ffi__ZTS5Error_code_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ErrorClass, "message", drb_ffi__ZTS5Error_message_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ErrorClass, "message=", drb_ffi__ZTS5Error_message_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ErrorClass, "trigger", drb_ffi__ZTS5Error_trigger_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ErrorClass, "trigger=", drb_ffi__ZTS5Error_trigger_Set, MRB_ARGS_REQ(1));
}
