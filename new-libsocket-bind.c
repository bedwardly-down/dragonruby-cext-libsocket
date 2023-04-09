#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>
#include "new-libsocket.c"

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
static size_t drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, size_t value) {
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
static mrb_value drb_ffi_init_server_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 5)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'init_server': wrong number of arguments (%d for 5)", argc);
    char *bind_addr_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *bind_port_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    char proto_osi4_2 = drb_ffi__ZTSc_FromRuby(state, args[2]);
    char proto_osi3_3 = drb_ffi__ZTSc_FromRuby(state, args[3]);
    int flags_4 = drb_ffi__ZTSi_FromRuby(state, args[4]);
    int ret_val = init_server(bind_addr_0, bind_port_1, proto_osi4_2, proto_osi3_3, flags_4);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_send_to_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 6)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'send_to_socket': wrong number of arguments (%d for 6)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    void *buf_1 = drb_ffi__ZTSPv_FromRuby(state, args[1]);
    size_t size_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    char *host_3 = drb_ffi__ZTSPc_FromRuby(state, args[3]);
    char *service_4 = drb_ffi__ZTSPc_FromRuby(state, args[4]);
    int sendto_flags_5 = drb_ffi__ZTSi_FromRuby(state, args[5]);
    ssize_t ret_val = send_to_socket(sfd_0, buf_1, size_2, host_3, service_4, sendto_flags_5);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_receive_from_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 9)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'receive_from_socket': wrong number of arguments (%d for 9)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    void *buffer_1 = drb_ffi__ZTSPv_FromRuby(state, args[1]);
    size_t size_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    char *src_host_3 = drb_ffi__ZTSPc_FromRuby(state, args[3]);
    size_t src_host_len_4 = drb_ffi__ZTSj_FromRuby(state, args[4]);
    char *src_service_5 = drb_ffi__ZTSPc_FromRuby(state, args[5]);
    size_t src_service_len_6 = drb_ffi__ZTSj_FromRuby(state, args[6]);
    int recvfrom_flags_7 = drb_ffi__ZTSi_FromRuby(state, args[7]);
    int numeric_8 = drb_ffi__ZTSi_FromRuby(state, args[8]);
    ssize_t ret_val = receive_from_socket(sfd_0, buffer_1, size_2, src_host_3, src_host_len_4, src_service_5, src_service_len_6, recvfrom_flags_7, numeric_8);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_close_socket_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'close_socket': wrong number of arguments (%d for 1)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    int ret_val = close_socket(sfd_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_kill_server_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'kill_server': wrong number of arguments (%d for 1)", argc);
    int sfd_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    int ret_val = kill_server(sfd_0);
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
static mrb_value drb_ffi_get_error_code_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'get_error_code': wrong number of arguments (%d for 0)", argc);
    int ret_val = get_error_code();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_flag_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'get_flag': wrong number of arguments (%d for 0)", argc);
    Flag ret_val = get_flag();
    return drb_ffi__ZTS4Flag_ToRuby(state, ret_val);
}
DRB_FFI_EXPORT
void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "SOCKET");
    struct RClass *object_class = state->object_class;
    drb_api->mrb_define_module_function(state, module, "init_server", drb_ffi_init_server_Binding, MRB_ARGS_REQ(5));
    drb_api->mrb_define_module_function(state, module, "send_to_socket", drb_ffi_send_to_socket_Binding, MRB_ARGS_REQ(6));
    drb_api->mrb_define_module_function(state, module, "receive_from_socket", drb_ffi_receive_from_socket_Binding, MRB_ARGS_REQ(9));
    drb_api->mrb_define_module_function(state, module, "close_socket", drb_ffi_close_socket_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "kill_server", drb_ffi_kill_server_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "c_tick", drb_ffi_c_tick_Binding, MRB_ARGS_REQ(0));
    drb_api->mrb_define_module_function(state, module, "get_error_code", drb_ffi_get_error_code_Binding, MRB_ARGS_REQ(0));
    drb_api->mrb_define_module_function(state, module, "get_flag", drb_ffi_get_flag_Binding, MRB_ARGS_REQ(0));
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
    drb_api->mrb_define_method(state, FlagClass, "error", drb_ffi__ZTS4Flag_error_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "error=", drb_ffi__ZTS4Flag_error_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagClass, "kill", drb_ffi__ZTS4Flag_kill_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagClass, "kill=", drb_ffi__ZTS4Flag_kill_Set, MRB_ARGS_REQ(1));
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
}
