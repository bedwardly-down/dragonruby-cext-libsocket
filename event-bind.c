#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>
#include "event.c"

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
struct drb_foreign_object_ZTS7manager {
    drb_foreign_object_kind kind;
    Manager value;
};
static mrb_data_type ForeignObjectType_ZTS7manager = {"manager", drb_free_foreign_object_indirect};
static Manager drb_ffi__ZTS7manager_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Manager");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS7manager);
    return ((struct drb_foreign_object_ZTS7manager *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS7manager_ToRuby(mrb_state *state, Manager value) {
    struct drb_foreign_object_ZTS7manager *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS7manager));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Manager");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS7manager);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSP4Flag {
    drb_foreign_object_kind kind;
    Flag *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP4Flag = {"Flag*", drb_free_foreign_object_indirect};
static Flag *drb_ffi__ZTSP4Flag_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "FlagPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSP4Flag);
    return ((struct drb_foreign_object_ZTSP4Flag *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP4Flag_ToRuby(mrb_state *state, Flag *value) {
    struct drb_foreign_object_ZTSP4Flag *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP4Flag));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "FlagPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSP4Flag);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSP4swap {
    drb_foreign_object_kind kind;
    Swap *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP4swap = {"swap*", drb_free_foreign_object_indirect};
static Swap *drb_ffi__ZTSP4swap_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "SwapPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSP4swap);
    return ((struct drb_foreign_object_ZTSP4swap *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP4swap_ToRuby(mrb_state *state, Swap *value) {
    struct drb_foreign_object_ZTSP4swap *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP4swap));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "SwapPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSP4swap);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS4Flag {
    drb_foreign_object_kind kind;
    Flag value;
};
static mrb_data_type ForeignObjectType_ZTS4Flag = {"Flag", drb_free_foreign_object_indirect};
static Flag drb_ffi__ZTS4Flag_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Flag");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS4Flag);
    return ((struct drb_foreign_object_ZTS4Flag *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS4Flag_ToRuby(mrb_state *state, Flag value) {
    struct drb_foreign_object_ZTS4Flag *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS4Flag));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Flag");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS4Flag);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS4swap {
    drb_foreign_object_kind kind;
    Swap value;
};
static mrb_data_type ForeignObjectType_ZTS4swap = {"swap", drb_free_foreign_object_indirect};
static Swap drb_ffi__ZTS4swap_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Swap");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS4swap);
    return ((struct drb_foreign_object_ZTS4swap *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS4swap_ToRuby(mrb_state *state, Swap value) {
    struct drb_foreign_object_ZTS4swap *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS4swap));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Swap");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS4swap);
    return mrb_obj_value(rdata);
}
static unsigned int drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, unsigned int value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTSP5error {
    drb_foreign_object_kind kind;
    Error *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP5error = {"error*", drb_free_foreign_object_indirect};
static Error *drb_ffi__ZTSP5error_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ErrorPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSP5error);
    return ((struct drb_foreign_object_ZTSP5error *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP5error_ToRuby(mrb_state *state, Error *value) {
    struct drb_foreign_object_ZTSP5error *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP5error));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ErrorPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSP5error);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS5error {
    drb_foreign_object_kind kind;
    Error value;
};
static mrb_data_type ForeignObjectType_ZTS5error = {"error", drb_free_foreign_object_indirect};
static Error drb_ffi__ZTS5error_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Error");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS5error);
    return ((struct drb_foreign_object_ZTS5error *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS5error_ToRuby(mrb_state *state, Error value) {
    struct drb_foreign_object_ZTS5error *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS5error));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Error");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS5error);
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
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "CharPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSPc);
    return ((struct drb_foreign_object_ZTSPc *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPc_ToRuby(mrb_state *state, char *value) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
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
static mrb_value drb_ffi__ZTSP4Flag_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP4Flag *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP4Flag));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Flag));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "FlagPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSP4Flag);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP4Flag_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS4Flag_ToRuby(mrb, *drb_ffi__ZTSP4Flag_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP4Flag_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP4Flag_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP4Flag_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS4Flag_ToRuby(mrb, drb_ffi__ZTSP4Flag_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP4Flag_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Flag new_value = drb_ffi__ZTS4Flag_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP4Flag_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSP4swap_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP4swap *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP4swap));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Swap));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "SwapPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSP4swap);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP4swap_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS4swap_ToRuby(mrb, *drb_ffi__ZTSP4swap_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP4swap_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP4swap_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP4swap_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS4swap_ToRuby(mrb, drb_ffi__ZTSP4swap_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP4swap_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Swap new_value = drb_ffi__ZTS4swap_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP4swap_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSP5error_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP5error *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP5error));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Error));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "ErrorPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSP5error);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP5error_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS5error_ToRuby(mrb, *drb_ffi__ZTSP5error_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP5error_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP5error_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP5error_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS5error_ToRuby(mrb, drb_ffi__ZTSP5error_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP5error_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Error new_value = drb_ffi__ZTS5error_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP5error_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPc_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(char));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "EVENT");
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
static mrb_value drb_ffi__ZTS7manager_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS7manager *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS7manager *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Manager");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS7manager);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS7manager_flag_Get(mrb_state *state, mrb_value self) {
    Manager record = drb_ffi__ZTS7manager_FromRuby(state, self);
    return drb_ffi__ZTSP4Flag_ToRuby(state, record.flag);
}
static mrb_value drb_ffi__ZTS7manager_flag_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    Flag *new_value = drb_ffi__ZTSP4Flag_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7manager *)DATA_PTR(self))->value)->flag = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7manager_swap_Get(mrb_state *state, mrb_value self) {
    Manager record = drb_ffi__ZTS7manager_FromRuby(state, self);
    return drb_ffi__ZTSP4swap_ToRuby(state, record.swap);
}
static mrb_value drb_ffi__ZTS7manager_swap_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    Swap *new_value = drb_ffi__ZTSP4swap_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7manager *)DATA_PTR(self))->value)->swap = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Flag_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS4Flag *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS4Flag *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
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
static mrb_value drb_ffi__ZTS4swap_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS4swap *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS4swap *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Swap");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS4swap);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS4swap_error_Get(mrb_state *state, mrb_value self) {
    Swap record = drb_ffi__ZTS4swap_FromRuby(state, self);
    return drb_ffi__ZTSP5error_ToRuby(state, record.error);
}
static mrb_value drb_ffi__ZTS4swap_error_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    Error *new_value = drb_ffi__ZTSP5error_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4swap *)DATA_PTR(self))->value)->error = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5error_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS5error *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS5error *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "EVENT");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Error");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS5error);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS5error_code_Get(mrb_state *state, mrb_value self) {
    Error record = drb_ffi__ZTS5error_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.code);
}
static mrb_value drb_ffi__ZTS5error_code_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5error *)DATA_PTR(self))->value)->code = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5error_message_Get(mrb_state *state, mrb_value self) {
    Error record = drb_ffi__ZTS5error_FromRuby(state, self);
    return drb_ffi__ZTSPc_ToRuby(state, record.message);
}
static mrb_value drb_ffi__ZTS5error_message_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    char *new_value = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5error *)DATA_PTR(self))->value)->message = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_get_manager_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 0)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'get_manager': wrong number of arguments (%d for 0)", argc);
    Manager ret_val = get_manager();
    return drb_ffi__ZTS7manager_ToRuby(state, ret_val);
}
DRB_FFI_EXPORT
void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "EVENT");
    struct RClass *object_class = state->object_class;
    drb_api->mrb_define_module_function(state, module, "get_manager", drb_ffi_get_manager_Binding, MRB_ARGS_REQ(0));
    struct RClass *FlagPointerClass = drb_api->mrb_define_class_under(state, module, "FlagPointer", object_class);
    drb_api->mrb_define_class_method(state, FlagPointerClass, "new", drb_ffi__ZTSP4Flag_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagPointerClass, "value", drb_ffi__ZTSP4Flag_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, FlagPointerClass, "[]", drb_ffi__ZTSP4Flag_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, FlagPointerClass, "[]=", drb_ffi__ZTSP4Flag_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, FlagPointerClass, "nil?", drb_ffi__ZTSP4Flag_IsNil, MRB_ARGS_REQ(0));
    struct RClass *SwapPointerClass = drb_api->mrb_define_class_under(state, module, "SwapPointer", object_class);
    drb_api->mrb_define_class_method(state, SwapPointerClass, "new", drb_ffi__ZTSP4swap_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, SwapPointerClass, "value", drb_ffi__ZTSP4swap_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, SwapPointerClass, "[]", drb_ffi__ZTSP4swap_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, SwapPointerClass, "[]=", drb_ffi__ZTSP4swap_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, SwapPointerClass, "nil?", drb_ffi__ZTSP4swap_IsNil, MRB_ARGS_REQ(0));
    struct RClass *ErrorPointerClass = drb_api->mrb_define_class_under(state, module, "ErrorPointer", object_class);
    drb_api->mrb_define_class_method(state, ErrorPointerClass, "new", drb_ffi__ZTSP5error_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ErrorPointerClass, "value", drb_ffi__ZTSP5error_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ErrorPointerClass, "[]", drb_ffi__ZTSP5error_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ErrorPointerClass, "[]=", drb_ffi__ZTSP5error_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, ErrorPointerClass, "nil?", drb_ffi__ZTSP5error_IsNil, MRB_ARGS_REQ(0));
    struct RClass *CharPointerClass = drb_api->mrb_define_class_under(state, module, "CharPointer", object_class);
    drb_api->mrb_define_class_method(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
    struct RClass *ManagerClass = drb_api->mrb_define_class_under(state, module, "Manager", object_class);
    drb_api->mrb_define_class_method(state, ManagerClass, "new", drb_ffi__ZTS7manager_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ManagerClass, "flag", drb_ffi__ZTS7manager_flag_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ManagerClass, "flag=", drb_ffi__ZTS7manager_flag_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ManagerClass, "swap", drb_ffi__ZTS7manager_swap_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ManagerClass, "swap=", drb_ffi__ZTS7manager_swap_Set, MRB_ARGS_REQ(1));
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
    struct RClass *SwapClass = drb_api->mrb_define_class_under(state, module, "Swap", object_class);
    drb_api->mrb_define_class_method(state, SwapClass, "new", drb_ffi__ZTS4swap_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, SwapClass, "error", drb_ffi__ZTS4swap_error_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, SwapClass, "error=", drb_ffi__ZTS4swap_error_Set, MRB_ARGS_REQ(1));
    struct RClass *ErrorClass = drb_api->mrb_define_class_under(state, module, "Error", object_class);
    drb_api->mrb_define_class_method(state, ErrorClass, "new", drb_ffi__ZTS5error_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ErrorClass, "code", drb_ffi__ZTS5error_code_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ErrorClass, "code=", drb_ffi__ZTS5error_code_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ErrorClass, "message", drb_ffi__ZTS5error_message_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ErrorClass, "message=", drb_ffi__ZTS5error_message_Set, MRB_ARGS_REQ(1));
}
