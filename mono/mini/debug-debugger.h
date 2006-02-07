/*
 * This is a private header file for the debugger.
 */

#ifndef __DEBUG_DEBUGGER_H__
#define __DEBUG_DEBUGGER_H__

#if !defined _IN_THE_MONO_DEBUGGER
#error "<debug-debugger.h> is a private header file only intended to be used by the debugger."
#endif

#include <mono/metadata/class-internals.h>
#include <mono/metadata/mono-debug-debugger.h>

typedef struct _MonoDebuggerInfo		MonoDebuggerInfo;
typedef struct _MonoDebuggerMetadataInfo	MonoDebuggerMetadataInfo;

/*
 * Address of the x86 trampoline code.  This is used by the debugger to check
 * whether a method is a trampoline.
 */
extern guint8 *mono_trampoline_code [];

/*
 * There's a global data symbol called `MONO_DEBUGGER__debugger_info' which
 * contains pointers to global variables and functions which must be accessed
 * by the debugger.
 */
struct _MonoDebuggerInfo {
	guint64 magic;
	guint32 version;
	guint32 total_size;
	guint32 symbol_table_size;
	guint32 dummy;
	gpointer notification_function;
	guint8 ***mono_trampoline_code;
	MonoSymbolTable **symbol_table;
	MonoDebuggerMetadataInfo *metadata_info;
	guint64 (*compile_method) (guint64 method_argument);
	guint64 (*get_virtual_method) (guint64 object_argument, guint64 method_argument);
	guint64 (*get_boxed_object_method) (guint64 klass_argument, guint64 val_argument);
	guint64 (*insert_breakpoint) (guint64 method_argument, const gchar *string_argument);
	guint64 (*remove_breakpoint) (guint64 breakpoint);
	MonoInvokeFunc runtime_invoke;
	guint64 (*create_string) (guint64 dummy_argument, const gchar *string_argument);
	guint64 (*class_get_static_field_data) (guint64 klass);
	guint64 (*lookup_class) (guint64 image_argument, guint64 token_arg);
	guint64 (*lookup_type) (guint64 dummy_argument, const gchar *string_argument);
	guint64 (*lookup_assembly) (guint64 dummy_argument, const gchar *string_argument);
	guint64 (*run_finally) (guint64 argument1, guint64 argument2);
	guint64 (*get_thread_id) (void);
	void (*attach) (void);
};

struct _MonoDebuggerMetadataInfo {
	int size;
	int mono_defaults_size;
	MonoDefaults *mono_defaults;
	int type_size;
	int array_type_size;
	int klass_size;
	int klass_instance_size_offset;
	int klass_parent_offset;
	int klass_token_offset;
	int klass_field_offset;
	int klass_methods_offset;
	int klass_method_count_offset;
	int klass_this_arg_offset;
	int klass_byval_arg_offset;
	int klass_generic_class_offset;
	int klass_generic_container_offset;
	int field_info_size;
};

#endif
