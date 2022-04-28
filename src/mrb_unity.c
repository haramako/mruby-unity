#include <mruby.h>
#include <mruby/string.h>
#include <mruby/throw.h>
#include <stdio.h>
#include <memory.h>

typedef void (*mrb_unity_abort_delegate_t)(const char *);

static mrb_unity_abort_delegate_t mrb_unity_abort_delegate;

void mrb_unity_abort_callback(mrb_state *mrb, mrb_value exc)
{
    mrb_value msg = mrb_funcall(mrb, exc, "to_s", 0);
    mrb_unity_abort_delegate(RSTRING_PTR(msg));
}

MRB_API void
mrb_unity_set_abort_func(mrb_state *mrb, mrb_unity_abort_delegate_t f)
{
    mrb_unity_abort_delegate = f;
    mrb->abort = mrb_unity_abort_callback;
}

// Value creation.
MRB_API mrb_value
mrb_unity_fixnum_value(mrb_int v)
{
    return mrb_fixnum_value(v);
}

MRB_API mrb_value
mrb_unity_int_value(mrb_state *mrb, mrb_int v)
{
    return mrb_int_value(mrb, v);
}

MRB_API mrb_value
mrb_unity_float_value(mrb_state *mrb, mrb_float v)
{
    return mrb_float_value(mrb, v);
}

MRB_API mrb_value
mrb_unity_nil_value()
{
    return mrb_nil_value();
}

MRB_API mrb_value
mrb_unity_false_value()
{
    return mrb_false_value();
}

MRB_API mrb_value
mrb_unity_true_value()
{
    return mrb_true_value();
}

MRB_API mrb_value
mrb_unity_bool_value(mrb_bool v)
{
    return mrb_bool_value(v);
}

// Value conversion.
MRB_API mrb_int
mrb_unity_as_int(mrb_state *mrb, mrb_value obj)
{
    return mrb_as_int(mrb, obj);
}

MRB_API mrb_int
mrb_unity_string_len(mrb_state *mrb, mrb_value obj)
{
    mrb_ensure_string_type(mrb, obj);
    return RSTRING_LEN(obj);
}

MRB_API mrb_int
mrb_unity_string_buf(mrb_state *mrb, mrb_value obj, char *buf, size_t buf_len)
{
    mrb_ensure_string_type(mrb, obj);
    size_t len = RSTRING_LEN(obj);
    if (len > buf_len)
    {
        return -1;
    }
    else
    {
        memcpy(buf, RSTRING_PTR(obj), len);
        return len;
    }
}

MRB_API mrb_value
mrb_unity_ptr_to_str(mrb_state *mrb, const char *p)
{
    return mrb_ptr_to_str(mrb, p);
}

MRB_API mrb_bool
mrb_unity_nil_p(mrb_value obj)
{
    return mrb_nil_p(obj);
}

// Other
MRB_API mrb_value
mrb_unity_funcall_argv(mrb_state *mrb, mrb_value val, const char *name, mrb_int argc, const mrb_value *args)
{
    mrb_sym name_sym = mrb_intern_cstr(mrb, name);
    return mrb_funcall_argv(mrb, val, name_sym, argc, args);
}

MRB_API mrb_value
mrb_unity_obj_value(void *p)
{
    return mrb_obj_value(p);
}

MRB_API mrb_value
mrb_unity_mrb_state_exc(mrb_state *mrb)
{
    return mrb_obj_value(mrb->exc);
}

MRB_API int
mrb_unity_gc_arena_save(mrb_state *mrb)
{
    return mrb_gc_arena_save(mrb);
}

MRB_API void
mrb_unity_gc_arena_restore(mrb_state *mrb, int idx)
{
    mrb_gc_arena_restore(mrb, idx);
}

void mrb_mruby_unity_gem_init(mrb_state *mrb)
{
}

void mrb_mruby_unity_gem_final(mrb_state *mrb)
{
}
