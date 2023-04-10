/**
 * @file    libsocket-bind.c
 *
 * @brief Contains the DragonRuby Game Toolkit FFI bindings.
 *
 * This file allows DragonRuby to interact with libinetsocket. 
 * Don't directly call these functions in DragonRuby but instead
 * see libinetsocket.c for the correct implementations and docs.
 * Any changes made there must be manually updated here for them
 * to take affect. Also, include all headers here so they get found
 * and used properly.
 */

/*
   The committers of the libsocket project, all rights reserved
   (c) 2012 and following, dermesser <lbo@spheniscida.de>
 
   DragonRuby is a registered trademark of DragonRuby LLP 
   (c) 2012 and following, amirrajan <amir.rajan@dragonruby.org>
 
   Miscellaneous code updates for this plugin that were not originally a part of libsocket
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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#endif
#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>
#include <errno.h>
#include "libsocket.h"
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
static mrb_value drb_ffi_create_stream_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 4)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'create_stream_socket': wrong number of arguments (%d for 4)", argc);
    char *host_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *service_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    char proto_osi3_2 = drb_ffi__ZTSc_FromRuby(state, args[2]);
    int flags_3 = drb_ffi__ZTSi_FromRuby(state, args[3]);
    int ret_val = create_stream_socket(host_0, service_1, proto_osi3_2, flags_3);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_create_dgram_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'create_dgram_socket': wrong number of arguments (%d for 2)", argc);
    char proto_osi3_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    int flags_1 = drb_ffi__ZTSi_FromRuby(state, args[1]);
    int ret_val = create_dgram_socket(proto_osi3_0, flags_1);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_sendto_dgram_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 6)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'sendto_dgram_socket': wrong number of arguments (%d for 6)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    void *buf_1 = drb_ffi__ZTSPv_FromRuby(state, args[1]);
    size_t sizem_2 = drb_ffi__ZTSi_FromRuby(state, args[2]);
    char *hostm_3 = drb_ffi__ZTSPc_FromRuby(state, args[3]);
    char *service_4 = drb_ffi__ZTSPc_FromRuby(state, args[4]);
    int sendto_flags_5 = drb_ffi__ZTSi_FromRuby(state, args[5]);
    ssize_t ret_val = sendto_dgram_socket(sfd_0, buf_1, sizem_2, hostm_3, service_4, sendto_flags_5);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_recvfrom_dgram_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 9)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'recvfrom_dgram_socket': wrong number of arguments (%d for 9)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    void *buffer_1 = drb_ffi__ZTSPv_FromRuby(state, args[1]);
    size_t size_2 = drb_ffi__ZTSi_FromRuby(state, args[2]);
    char *src_host_3 = drb_ffi__ZTSPc_FromRuby(state, args[3]);
    size_t src_host_len_4 = drb_ffi__ZTSi_FromRuby(state, args[4]);
    char *src_service_5 = drb_ffi__ZTSPc_FromRuby(state, args[5]);
    size_t src_service_len_6 = drb_ffi__ZTSi_FromRuby(state, args[6]);
    int recvfrom_flags_7 = drb_ffi__ZTSi_FromRuby(state, args[7]);
    int numeric_8 = drb_ffi__ZTSi_FromRuby(state, args[8]);
    ssize_t ret_val = recvfrom_dgram_socket(sfd_0, buffer_1, size_2, src_host_3, src_host_len_4, src_service_5, src_service_len_6, recvfrom_flags_7, numeric_8);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_connect_dgram_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 3)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'connect_dgram_socket': wrong number of arguments (%d for 3)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    char *host_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    char *service_2 = drb_ffi__ZTSPc_FromRuby(state, args[2]);
    int ret_val = connect_dgram_socket(sfd_0, host_1, service_2);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_destroy_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'destroy_socket': wrong number of arguments (%d for 1)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    int ret_val = destroy_socket(sfd_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_shutdown_stream_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'shutdown_stream_socket': wrong number of arguments (%d for 2)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    int method_1 = drb_ffi__ZTSi_FromRuby(state, args[1]);
    int ret_val = shutdown_stream_socket(sfd_0, method_1);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_create_server_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 5)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'create_server_socket': wrong number of arguments (%d for 5)", argc);
    char *bind_addr_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *bind_port_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    char proto_osi4_2 = drb_ffi__ZTSc_FromRuby(state, args[2]);
    char proto_osi3_3 = drb_ffi__ZTSc_FromRuby(state, args[3]);
    int flags_4 = drb_ffi__ZTSi_FromRuby(state, args[4]);
    int ret_val = create_server_socket(bind_addr_0, bind_port_1, proto_osi4_2, proto_osi3_3, flags_4);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_accept_stream_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 7)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'accept_stream_socket': wrong number of arguments (%d for 7)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    char *src_host_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    size_t src_host_len_2 = drb_ffi__ZTSi_FromRuby(state, args[2]);
    char *src_service_3 = drb_ffi__ZTSPc_FromRuby(state, args[3]);
    size_t src_service_len_4 = drb_ffi__ZTSi_FromRuby(state, args[4]);
    int flags_5 = drb_ffi__ZTSi_FromRuby(state, args[5]);
    int accept_flags_6 = drb_ffi__ZTSi_FromRuby(state, args[6]);
    int ret_val = accept_stream_socket(sfd_0, src_host_1, src_host_len_2, src_service_3, src_service_len_4, flags_5, accept_flags_6);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_address_family_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'get_address_family': wrong number of arguments (%d for 1)", argc);
    char *hostname_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    int ret_val = get_address_family(hostname_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_connection_result_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'get_connection_result': wrong number of arguments (%d for 0)", argc);
    int ret_val = get_connection_result();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_error_code_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'get_error_code': wrong number of arguments (%d for 0)", argc);
    int ret_val = get_error_code();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
#ifdef linux
static mrb_value drb_ffi_create_multicast_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 3)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'create_multicast_socket': wrong number of arguments (%d for 3)", argc);
    char *group_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *port_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    char *if_name_2 = drb_ffi__ZTSPc_FromRuby(state, args[2]);
    int ret_val = create_multicast_socket(group_0, port_1, if_name_2);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_nonblock_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'get_nonblock': wrong number of arguments (%d for 0)", argc);
    signed int ret_val = get_nonblock();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
#endif
DRB_FFI_EXPORT
void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "SOCKET");
    struct RClass *object_class = state->object_class;
    drb_api->mrb_define_module_function(state, module, "create_stream_socket", drb_ffi_create_stream_socket_Binding, MRB_ARGS_REQ(4));
    drb_api->mrb_define_module_function(state, module, "create_dgram_socket", drb_ffi_create_dgram_socket_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "sendto_dgram_socket", drb_ffi_sendto_dgram_socket_Binding, MRB_ARGS_REQ(6));
    drb_api->mrb_define_module_function(state, module, "recvfrom_dgram_socket", drb_ffi_recvfrom_dgram_socket_Binding, MRB_ARGS_REQ(9));
    drb_api->mrb_define_module_function(state, module, "connect_dgram_socket", drb_ffi_connect_dgram_socket_Binding, MRB_ARGS_REQ(3));
    drb_api->mrb_define_module_function(state, module, "destroy_socket", drb_ffi_destroy_socket_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "shutdown_stream_socket", drb_ffi_shutdown_stream_socket_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "create_server_socket", drb_ffi_create_server_socket_Binding, MRB_ARGS_REQ(5));
    drb_api->mrb_define_module_function(state, module, "accept_stream_socket", drb_ffi_accept_stream_socket_Binding, MRB_ARGS_REQ(7));
    drb_api->mrb_define_module_function(state, module, "get_address_family", drb_ffi_get_address_family_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "get_connection_result", drb_ffi_get_connection_result_Binding, MRB_ARGS_REQ(0));
    drb_api->mrb_define_module_function(state, module, "get_error_code", drb_ffi_get_error_code_Binding, MRB_ARGS_REQ(0));
#ifdef linux
    drb_api->mrb_define_module_function(state, module, "create_multicast_socket", drb_ffi_create_multicast_socket_Binding, MRB_ARGS_REQ(3));
    drb_api->mrb_define_module_function(state, module, "get_nonblock", drb_ffi_get_connection_result_Binding, MRB_ARGS_REQ(0));
#endif
    struct RClass *CharPointerClass = drb_api->mrb_define_class_under(state, module, "CharPointer", object_class);
    drb_api->mrb_define_class_method(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
    struct RClass *VoidPointerClass = drb_api->mrb_define_class_under(state, module, "VoidPointer", object_class);
}
