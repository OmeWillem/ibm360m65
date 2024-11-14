/* OPCODE.C     (c) Copyright Jan Jaeger, 2000-2009                  */
/*              Instruction decoding functions                       */

/* Interpretive Execution - (c) Copyright Jan Jaeger, 1999-2009      */
/* z/Architecture support - (c) Copyright Jan Jaeger, 1999-2009      */

// $Id: opcode.c 5574 2009-12-29 13:13:41Z bernard $

#include "hstdinc.h"

#if !defined(_HENGINE_DLL_)
#define _HENGINE_DLL_
#endif

#if !defined(_OPCODE_C_)
#define _OPCODE_C_
#endif

#if !defined(SOFTWARE_M65) && !defined(HARDWARE_M65)

#include "feature.h"


#if !defined(_GEN_ARCH)

#if defined(_ARCHMODE3)
 #define  _GEN_ARCH _ARCHMODE3
 #include "opcode.c"
 #undef   _GEN_ARCH
#endif

#if defined(_ARCHMODE2)
 #define  _GEN_ARCH _ARCHMODE2
 #include "opcode.c"
 #undef   _GEN_ARCH
#endif

#endif /*!defined(_GEN_ARCH)*/

#include "hercules.h"

#include "opcode.h"


#define UNDEF_INST(_x) \
        DEF_INST(_x) { ARCH_DEP(operation_exception) \
        (inst,regs); }


 UNDEF_INST(clear_subchannel)
 UNDEF_INST(halt_subchannel)
 UNDEF_INST(modify_subchannel)
 UNDEF_INST(reset_channel_path)
 UNDEF_INST(resume_subchannel)
 UNDEF_INST(set_address_limit)
 UNDEF_INST(set_channel_monitor)
 UNDEF_INST(start_subchannel)
 UNDEF_INST(store_channel_path_status)
 UNDEF_INST(store_channel_report_word)
 UNDEF_INST(store_subchannel)
 UNDEF_INST(test_pending_interruption)
 UNDEF_INST(test_subchannel)
 UNDEF_INST(test_under_mask_high)
 UNDEF_INST(test_under_mask_low)
 UNDEF_INST(branch_relative_on_condition)
 UNDEF_INST(branch_relative_and_save)
 UNDEF_INST(branch_relative_on_count)
 UNDEF_INST(load_halfword_immediate)
 UNDEF_INST(add_halfword_immediate)
 UNDEF_INST(multiply_halfword_immediate)
 UNDEF_INST(compare_halfword_immediate)
 UNDEF_INST(multiply_single_register)
 UNDEF_INST(multiply_single)
 UNDEF_INST(branch_relative_on_index_high)
 UNDEF_INST(branch_relative_on_index_low_or_equal)
 UNDEF_INST(compare_logical_string)
 UNDEF_INST(compare_until_substring_equal)
 UNDEF_INST(move_string)
 UNDEF_INST(search_string)
 UNDEF_INST(compare_logical_long_extended)
 UNDEF_INST(move_long_extended)
 UNDEF_INST(checksum)
 UNDEF_INST(program_call)
 UNDEF_INST(program_transfer)
 UNDEF_INST(set_address_space_control)
 UNDEF_INST(set_secondary_asn)
 UNDEF_INST(extract_primary_asn_and_instance)
 UNDEF_INST(extract_secondary_asn_and_instance)
 UNDEF_INST(program_transfer_with_instance)
 UNDEF_INST(set_secondary_asn_with_instance)
 UNDEF_INST(load_access_multiple)
 UNDEF_INST(store_access_multiple)
 UNDEF_INST(purge_accesslist_lookaside_buffer)
 UNDEF_INST(test_access)
 UNDEF_INST(copy_access)
 UNDEF_INST(set_access_register)
 UNDEF_INST(extract_access_register)
 UNDEF_INST(insert_storage_key_extended)
 UNDEF_INST(reset_reference_bit_extended)
 UNDEF_INST(set_storage_key_extended)
 UNDEF_INST(perform_timing_facility_function)
 UNDEF_INST(set_clock_programmable_field)
 UNDEF_INST(store_clock_extended)
 UNDEF_INST(move_with_optional_specifications)
 UNDEF_INST(extract_cpu_time)
 UNDEF_INST(compare_and_swap_and_store)
 UNDEF_INST(store_system_information)
 UNDEF_INST(perform_topology_function)                          /*208*/
 UNDEF_INST(perform_frame_management_function)                  /*208*/
 UNDEF_INST(execute_relative_long)                              /*208*/
 UNDEF_INST(add_immediate_long_storage)
 UNDEF_INST(add_immediate_storage)
 UNDEF_INST(add_logical_with_signed_immediate)
 UNDEF_INST(add_logical_with_signed_immediate_long)
 UNDEF_INST(compare_and_branch_register)
 UNDEF_INST(compare_and_branch_long_register)
 UNDEF_INST(compare_and_branch_relative_register)
 UNDEF_INST(compare_and_branch_relative_long_register)
 UNDEF_INST(compare_and_trap_long_register)
 UNDEF_INST(compare_and_trap_register)
 UNDEF_INST(compare_halfword_immediate_halfword_storage)
 UNDEF_INST(compare_halfword_immediate_long_storage)
 UNDEF_INST(compare_halfword_immediate_storage)
 UNDEF_INST(compare_halfword_long)
 UNDEF_INST(compare_halfword_relative_long)
 UNDEF_INST(compare_halfword_relative_long_long)
 UNDEF_INST(compare_immediate_and_branch)
 UNDEF_INST(compare_immediate_and_branch_long)
 UNDEF_INST(compare_immediate_and_branch_relative)
 UNDEF_INST(compare_immediate_and_branch_relative_long)
 UNDEF_INST(compare_immediate_and_trap)
 UNDEF_INST(compare_immediate_and_trap_long)
 UNDEF_INST(compare_logical_and_branch_long_register)
 UNDEF_INST(compare_logical_and_branch_register)
 UNDEF_INST(compare_logical_and_branch_relative_long_register)
 UNDEF_INST(compare_logical_and_branch_relative_register)
 UNDEF_INST(compare_logical_and_trap_long_register)
 UNDEF_INST(compare_logical_and_trap_register)
 UNDEF_INST(compare_logical_immediate_and_branch)
 UNDEF_INST(compare_logical_immediate_and_branch_long)
 UNDEF_INST(compare_logical_immediate_and_branch_relative)
 UNDEF_INST(compare_logical_immediate_and_branch_relative_long)
 UNDEF_INST(compare_logical_immediate_and_trap_fullword)
 UNDEF_INST(compare_logical_immediate_and_trap_long)
 UNDEF_INST(compare_logical_immediate_fullword_storage)
 UNDEF_INST(compare_logical_immediate_halfword_storage)
 UNDEF_INST(compare_logical_immediate_long_storage)
 UNDEF_INST(compare_logical_relative_long)
 UNDEF_INST(compare_logical_relative_long_halfword)
 UNDEF_INST(compare_logical_relative_long_long)
 UNDEF_INST(compare_logical_relative_long_long_fullword)
 UNDEF_INST(compare_logical_relative_long_long_halfword)
 UNDEF_INST(compare_relative_long)
 UNDEF_INST(compare_relative_long_long)
 UNDEF_INST(compare_relative_long_long_fullword)
 UNDEF_INST(extract_cache_attribute)
 UNDEF_INST(load_address_extended_y)
 UNDEF_INST(load_and_test_long_fullword)
 UNDEF_INST(load_halfword_relative_long)
 UNDEF_INST(load_halfword_relative_long_long)
 UNDEF_INST(load_logical_halfword_relative_long)
 UNDEF_INST(load_logical_halfword_relative_long_long)
 UNDEF_INST(load_logical_relative_long_long_fullword)
 UNDEF_INST(load_relative_long)
 UNDEF_INST(load_relative_long_long)
 UNDEF_INST(load_relative_long_long_fullword)
 UNDEF_INST(move_fullword_from_halfword_immediate)
 UNDEF_INST(move_halfword_from_halfword_immediate)
 UNDEF_INST(move_long_from_halfword_immediate)
 UNDEF_INST(multiply_halfword_y)
 UNDEF_INST(multiply_single_immediate_fullword)
 UNDEF_INST(multiply_single_immediate_long_fullword)
 UNDEF_INST(multiply_y)
 UNDEF_INST(prefetch_data)
 UNDEF_INST(prefetch_data_relative_long)
 UNDEF_INST(rotate_then_and_selected_bits_long_reg)
 UNDEF_INST(rotate_then_exclusive_or_selected_bits_long_reg)
 UNDEF_INST(rotate_then_insert_selected_bits_long_reg)
 UNDEF_INST(rotate_then_or_selected_bits_long_reg)
 UNDEF_INST(store_halfword_relative_long)
 UNDEF_INST(store_relative_long)
 UNDEF_INST(store_relative_long_long)
 UNDEF_INST(execute_a4xx)
 UNDEF_INST(execute_a5xx)
 UNDEF_INST(execute_a6xx)
 UNDEF_INST(execute_e4xx)
 UNDEF_INST(v_test_vmr)
 UNDEF_INST(v_complement_vmr)
 UNDEF_INST(v_count_left_zeros_in_vmr)
 UNDEF_INST(v_count_ones_in_vmr)
 UNDEF_INST(v_extract_vct)
 UNDEF_INST(v_extract_vector_modes)
 UNDEF_INST(v_restore_vr)
 UNDEF_INST(v_save_changed_vr)
 UNDEF_INST(v_save_vr)
 UNDEF_INST(v_load_vmr)
 UNDEF_INST(v_load_vmr_complement)
 UNDEF_INST(v_store_vmr)
 UNDEF_INST(v_and_to_vmr)
 UNDEF_INST(v_or_to_vmr)
 UNDEF_INST(v_exclusive_or_to_vmr)
 UNDEF_INST(v_save_vsr)
 UNDEF_INST(v_save_vmr)
 UNDEF_INST(v_restore_vsr)
 UNDEF_INST(v_restore_vmr)
 UNDEF_INST(v_load_vct_from_address)
 UNDEF_INST(v_clear_vr)
 UNDEF_INST(v_set_vector_mask_mode)
 UNDEF_INST(v_load_vix_from_address)
 UNDEF_INST(v_store_vector_parameters)
 UNDEF_INST(v_save_vac)
 UNDEF_INST(v_restore_vac)
 UNDEF_INST(execute_e3xx)
 UNDEF_INST(execute_ecxx)
 UNDEF_INST(execute_c0xx)
 UNDEF_INST(execute_c2xx)                                       /*@Z9*/
 UNDEF_INST(execute_c8xx)
 UNDEF_INST(execute_b3xx)
 UNDEF_INST(execute_edxx)
 UNDEF_INST(load_lengthened_float_short_to_long_reg)
 UNDEF_INST(load_lengthened_float_long_to_ext_reg)
 UNDEF_INST(load_lengthened_float_short_to_ext_reg)
 UNDEF_INST(squareroot_float_ext_reg)
 UNDEF_INST(multiply_float_short_reg)
 UNDEF_INST(load_positive_float_ext_reg)
 UNDEF_INST(load_negative_float_ext_reg)
 UNDEF_INST(load_and_test_float_ext_reg)
 UNDEF_INST(load_complement_float_ext_reg)
 UNDEF_INST(load_rounded_float_ext_to_short_reg)
 UNDEF_INST(load_fp_int_float_ext_reg)
 UNDEF_INST(compare_float_ext_reg)
 UNDEF_INST(load_fp_int_float_short_reg)
 UNDEF_INST(load_fp_int_float_long_reg)
 UNDEF_INST(convert_fixed_to_float_short_reg)
 UNDEF_INST(convert_fixed_to_float_long_reg)
 UNDEF_INST(convert_fixed_to_float_ext_reg)
 UNDEF_INST(convert_float_short_to_fixed_reg)
 UNDEF_INST(convert_float_long_to_fixed_reg)
 UNDEF_INST(convert_float_ext_to_fixed_reg)
 UNDEF_INST(load_lengthened_float_short_to_long)
 UNDEF_INST(load_lengthened_float_long_to_ext)
 UNDEF_INST(load_lengthened_float_short_to_ext)
 UNDEF_INST(squareroot_float_short)
 UNDEF_INST(squareroot_float_long)
 UNDEF_INST(multiply_float_short)
 UNDEF_INST(convert_bfp_long_to_float_long_reg)
 UNDEF_INST(convert_bfp_short_to_float_long_reg)
 UNDEF_INST(convert_float_long_to_bfp_long_reg)
 UNDEF_INST(convert_float_long_to_bfp_short_reg)
 UNDEF_INST(load_float_ext_reg)
 UNDEF_INST(load_zero_float_ext_reg)
 UNDEF_INST(load_zero_float_long_reg)
 UNDEF_INST(load_zero_float_short_reg)
 UNDEF_INST(copy_sign_fpr_long_reg)
 UNDEF_INST(load_complement_fpr_long_reg)
 UNDEF_INST(load_fpr_from_gr_long_reg)
 UNDEF_INST(load_gr_from_fpr_long_reg)
 UNDEF_INST(load_negative_fpr_long_reg)
 UNDEF_INST(load_positive_fpr_long_reg)
 UNDEF_INST(set_dfp_rounding_mode)
 UNDEF_INST(load_fpc_and_signal)
 UNDEF_INST(set_fpc_and_signal)
 UNDEF_INST(multiply_add_float_short_reg)
 UNDEF_INST(multiply_add_float_long_reg)
 UNDEF_INST(multiply_add_float_short)
 UNDEF_INST(multiply_add_float_long)
 UNDEF_INST(multiply_subtract_float_short_reg)
 UNDEF_INST(multiply_subtract_float_long_reg)
 UNDEF_INST(multiply_subtract_float_short)
 UNDEF_INST(multiply_subtract_float_long)
 UNDEF_INST(multiply_unnormal_float_long_to_ext_reg)            /*@Z9*/
 UNDEF_INST(multiply_unnormal_float_long_to_ext_low_reg)        /*@Z9*/
 UNDEF_INST(multiply_unnormal_float_long_to_ext_high_reg)       /*@Z9*/
 UNDEF_INST(multiply_add_unnormal_float_long_to_ext_reg)        /*@Z9*/
 UNDEF_INST(multiply_add_unnormal_float_long_to_ext_low_reg)    /*@Z9*/
 UNDEF_INST(multiply_add_unnormal_float_long_to_ext_high_reg)   /*@Z9*/
 UNDEF_INST(multiply_unnormal_float_long_to_ext)                /*@Z9*/
 UNDEF_INST(multiply_unnormal_float_long_to_ext_low)            /*@Z9*/
 UNDEF_INST(multiply_unnormal_float_long_to_ext_high)           /*@Z9*/
 UNDEF_INST(multiply_add_unnormal_float_long_to_ext)            /*@Z9*/
 UNDEF_INST(multiply_add_unnormal_float_long_to_ext_low)        /*@Z9*/
 UNDEF_INST(multiply_add_unnormal_float_long_to_ext_high)       /*@Z9*/
 UNDEF_INST(store_fpc)
 UNDEF_INST(load_fpc)
 UNDEF_INST(set_fpc)
 UNDEF_INST(extract_fpc)
 UNDEF_INST(set_bfp_rounding_mode)
 UNDEF_INST(add_bfp_ext_reg)
 UNDEF_INST(add_bfp_long)
 UNDEF_INST(add_bfp_long_reg)
 UNDEF_INST(add_bfp_short)
 UNDEF_INST(add_bfp_short_reg)
 UNDEF_INST(compare_and_signal_bfp_ext_reg)
 UNDEF_INST(compare_and_signal_bfp_long)
 UNDEF_INST(compare_and_signal_bfp_long_reg)
 UNDEF_INST(compare_and_signal_bfp_short)
 UNDEF_INST(compare_and_signal_bfp_short_reg)
 UNDEF_INST(compare_bfp_ext_reg)
 UNDEF_INST(compare_bfp_long)
 UNDEF_INST(compare_bfp_long_reg)
 UNDEF_INST(compare_bfp_short)
 UNDEF_INST(compare_bfp_short_reg)
 UNDEF_INST(convert_bfp_ext_to_fix32_reg)
 UNDEF_INST(convert_bfp_long_to_fix32_reg)
 UNDEF_INST(convert_bfp_short_to_fix32_reg)
 UNDEF_INST(convert_fix32_to_bfp_ext_reg)
 UNDEF_INST(convert_fix32_to_bfp_long_reg)
 UNDEF_INST(convert_fix32_to_bfp_short_reg)
 UNDEF_INST(convert_fix64_to_bfp_ext_reg);
 UNDEF_INST(convert_fix64_to_bfp_long_reg);
 UNDEF_INST(convert_fix64_to_bfp_short_reg);
 UNDEF_INST(convert_bfp_ext_to_fix64_reg);
 UNDEF_INST(convert_bfp_long_to_fix64_reg);
 UNDEF_INST(convert_bfp_short_to_fix64_reg);
 UNDEF_INST(divide_bfp_ext_reg)
 UNDEF_INST(divide_bfp_long)
 UNDEF_INST(divide_bfp_long_reg)
 UNDEF_INST(divide_bfp_short)
 UNDEF_INST(divide_bfp_short_reg)
 UNDEF_INST(divide_integer_bfp_long_reg)
 UNDEF_INST(divide_integer_bfp_short_reg)
 UNDEF_INST(load_and_test_bfp_ext_reg)
 UNDEF_INST(load_and_test_bfp_long_reg)
 UNDEF_INST(load_and_test_bfp_short_reg)
 UNDEF_INST(load_fp_int_bfp_ext_reg)
 UNDEF_INST(load_fp_int_bfp_long_reg)
 UNDEF_INST(load_fp_int_bfp_short_reg)
 UNDEF_INST(load_complement_bfp_ext_reg)
 UNDEF_INST(load_complement_bfp_long_reg)
 UNDEF_INST(load_complement_bfp_short_reg)
 UNDEF_INST(load_negative_bfp_ext_reg)
 UNDEF_INST(load_negative_bfp_long_reg)
 UNDEF_INST(load_negative_bfp_short_reg)
 UNDEF_INST(load_positive_bfp_ext_reg)
 UNDEF_INST(load_positive_bfp_long_reg)
 UNDEF_INST(load_positive_bfp_short_reg)
 UNDEF_INST(load_lengthened_bfp_short_to_long)
 UNDEF_INST(load_lengthened_bfp_short_to_long_reg)
 UNDEF_INST(load_lengthened_bfp_long_to_ext)
 UNDEF_INST(load_lengthened_bfp_long_to_ext_reg)
 UNDEF_INST(load_lengthened_bfp_short_to_ext)
 UNDEF_INST(load_lengthened_bfp_short_to_ext_reg)
 UNDEF_INST(load_rounded_bfp_long_to_short_reg)
 UNDEF_INST(load_rounded_bfp_ext_to_long_reg)
 UNDEF_INST(load_rounded_bfp_ext_to_short_reg)
 UNDEF_INST(multiply_bfp_ext_reg)
 UNDEF_INST(multiply_bfp_long_to_ext_reg)
 UNDEF_INST(multiply_bfp_long_to_ext)
 UNDEF_INST(multiply_bfp_long)
 UNDEF_INST(multiply_bfp_long_reg)
 UNDEF_INST(multiply_bfp_short_to_long_reg)
 UNDEF_INST(multiply_bfp_short_to_long)
 UNDEF_INST(multiply_bfp_short)
 UNDEF_INST(multiply_bfp_short_reg)
 UNDEF_INST(multiply_add_bfp_long_reg)
 UNDEF_INST(multiply_add_bfp_long)
 UNDEF_INST(multiply_add_bfp_short_reg)
 UNDEF_INST(multiply_add_bfp_short)
 UNDEF_INST(multiply_subtract_bfp_long_reg)
 UNDEF_INST(multiply_subtract_bfp_long)
 UNDEF_INST(multiply_subtract_bfp_short_reg)
 UNDEF_INST(multiply_subtract_bfp_short)
 UNDEF_INST(squareroot_bfp_ext_reg)
 UNDEF_INST(squareroot_bfp_long)
 UNDEF_INST(squareroot_bfp_long_reg)
 UNDEF_INST(squareroot_bfp_short)
 UNDEF_INST(squareroot_bfp_short_reg)
 UNDEF_INST(subtract_bfp_ext_reg)
 UNDEF_INST(subtract_bfp_long)
 UNDEF_INST(subtract_bfp_long_reg)
 UNDEF_INST(subtract_bfp_short)
 UNDEF_INST(subtract_bfp_short_reg)
 UNDEF_INST(test_data_class_bfp_short)
 UNDEF_INST(test_data_class_bfp_long)
 UNDEF_INST(test_data_class_bfp_ext)
 UNDEF_INST(add_dfp_ext_reg)
 UNDEF_INST(add_dfp_long_reg)
 UNDEF_INST(compare_dfp_ext_reg)
 UNDEF_INST(compare_dfp_long_reg)
 UNDEF_INST(compare_and_signal_dfp_ext_reg)
 UNDEF_INST(compare_and_signal_dfp_long_reg)
 UNDEF_INST(compare_exponent_dfp_ext_reg)
 UNDEF_INST(compare_exponent_dfp_long_reg)
 UNDEF_INST(convert_fix64_to_dfp_ext_reg)
 UNDEF_INST(convert_fix64_to_dfp_long_reg)
 UNDEF_INST(convert_sbcd128_to_dfp_ext_reg)
 UNDEF_INST(convert_sbcd64_to_dfp_long_reg)
 UNDEF_INST(convert_ubcd128_to_dfp_ext_reg)
 UNDEF_INST(convert_ubcd64_to_dfp_long_reg)
 UNDEF_INST(convert_dfp_ext_to_fix64_reg)
 UNDEF_INST(convert_dfp_long_to_fix64_reg)
 UNDEF_INST(convert_dfp_ext_to_sbcd128_reg)
 UNDEF_INST(convert_dfp_long_to_sbcd64_reg)
 UNDEF_INST(convert_dfp_ext_to_ubcd128_reg)
 UNDEF_INST(convert_dfp_long_to_ubcd64_reg)
 UNDEF_INST(divide_dfp_ext_reg)
 UNDEF_INST(divide_dfp_long_reg)
 UNDEF_INST(extract_biased_exponent_dfp_ext_to_fix64_reg)
 UNDEF_INST(extract_biased_exponent_dfp_long_to_fix64_reg)
 UNDEF_INST(extract_significance_dfp_ext_reg)
 UNDEF_INST(extract_significance_dfp_long_reg)
 UNDEF_INST(insert_biased_exponent_fix64_to_dfp_ext_reg)
 UNDEF_INST(insert_biased_exponent_fix64_to_dfp_long_reg)
 UNDEF_INST(load_and_test_dfp_ext_reg)
 UNDEF_INST(load_and_test_dfp_long_reg)
 UNDEF_INST(load_fp_int_dfp_ext_reg)
 UNDEF_INST(load_fp_int_dfp_long_reg)
 UNDEF_INST(load_lengthened_dfp_long_to_ext_reg)
 UNDEF_INST(load_lengthened_dfp_short_to_long_reg)
 UNDEF_INST(load_rounded_dfp_ext_to_long_reg)
 UNDEF_INST(load_rounded_dfp_long_to_short_reg)
 UNDEF_INST(multiply_dfp_ext_reg)
 UNDEF_INST(multiply_dfp_long_reg)
 UNDEF_INST(quantize_dfp_ext_reg)
 UNDEF_INST(quantize_dfp_long_reg)
 UNDEF_INST(reround_dfp_ext_reg)
 UNDEF_INST(reround_dfp_long_reg)
 UNDEF_INST(shift_coefficient_left_dfp_ext)
 UNDEF_INST(shift_coefficient_left_dfp_long)
 UNDEF_INST(shift_coefficient_right_dfp_ext)
 UNDEF_INST(shift_coefficient_right_dfp_long)
 UNDEF_INST(subtract_dfp_ext_reg)
 UNDEF_INST(subtract_dfp_long_reg)
 UNDEF_INST(test_data_class_dfp_ext)
 UNDEF_INST(test_data_class_dfp_long)
 UNDEF_INST(test_data_class_dfp_short)
 UNDEF_INST(test_data_group_dfp_ext)
 UNDEF_INST(test_data_group_dfp_long)
 UNDEF_INST(test_data_group_dfp_short)
 UNDEF_INST(perform_floating_point_operation)
 UNDEF_INST(inter_user_communication_vehicle)
 UNDEF_INST(resume_program)
 UNDEF_INST(lock_page)
 UNDEF_INST(squareroot_float_long_reg)
 UNDEF_INST(squareroot_float_short_reg)
 UNDEF_INST(start_interpretive_execution)
 UNDEF_INST(store_zone_parameter)
 UNDEF_INST(set_zone_parameter)
 UNDEF_INST(test_pending_zone_interrupt)
 UNDEF_INST(signal_adapter)
 UNDEF_INST(connect_channel_set)
 UNDEF_INST(disconnect_channel_set)
 UNDEF_INST(set_program_parameter)
 UNDEF_INST(extract_coprocessor_group_address)
 UNDEF_INST(extract_cpu_counter)
 UNDEF_INST(extract_peripheral_counter)
 UNDEF_INST(query_counter_information)
 UNDEF_INST(set_cpu_counter)
 UNDEF_INST(set_cpu_counter_set_controls)
 UNDEF_INST(set_peripheral_counter)
 UNDEF_INST(set_peripheral_counter_set_controls)
 UNDEF_INST(query_sampling_information)
 UNDEF_INST(set_sampling_controls)
 UNDEF_INST(translate_extended)
 UNDEF_INST(convert_utf16_to_utf8)
 UNDEF_INST(convert_utf8_to_utf16)
 UNDEF_INST(test_decimal)
 UNDEF_INST(translate_one_to_one)
 UNDEF_INST(translate_one_to_two)
 UNDEF_INST(translate_two_to_one)
 UNDEF_INST(translate_two_to_two)
 UNDEF_INST(load_reversed_register)
 UNDEF_INST(load_reversed)
 UNDEF_INST(load_reversed_half)
 UNDEF_INST(store_reversed)
 UNDEF_INST(store_reversed_half)
 UNDEF_INST(load_reversed_long_register)
 UNDEF_INST(store_reversed_long)
 UNDEF_INST(service_call)
 UNDEF_INST(channel_subsystem_call)
 UNDEF_INST(add_logical_carry)
 UNDEF_INST(add_logical_carry_register)
 UNDEF_INST(branch_relative_and_save_long)
 UNDEF_INST(branch_relative_on_condition_long)
 UNDEF_INST(divide_logical)
 UNDEF_INST(divide_logical_register)
 UNDEF_INST(extract_psw)
 UNDEF_INST(load_address_relative_long)
 UNDEF_INST(multiply_logical)
 UNDEF_INST(multiply_logical_register)
 UNDEF_INST(rotate_left_single_logical)
 UNDEF_INST(set_addressing_mode_24)
 UNDEF_INST(set_addressing_mode_31)
 UNDEF_INST(subtract_logical_borrow)
 UNDEF_INST(subtract_logical_borrow_register)
 UNDEF_INST(test_addressing_mode)
 UNDEF_INST(store_facility_list);
 UNDEF_INST(cancel_subchannel)
 UNDEF_INST(ecpsvm_basic_freex)
 UNDEF_INST(ecpsvm_basic_fretx)
 UNDEF_INST(ecpsvm_lock_page)
 UNDEF_INST(ecpsvm_unlock_page)
 UNDEF_INST(ecpsvm_decode_next_ccw)
 UNDEF_INST(ecpsvm_free_ccwstor)
 UNDEF_INST(ecpsvm_locate_vblock)
 UNDEF_INST(ecpsvm_disp1)
 UNDEF_INST(ecpsvm_tpage)
 UNDEF_INST(ecpsvm_tpage_lock)
 UNDEF_INST(ecpsvm_inval_segtab)
 UNDEF_INST(ecpsvm_inval_ptable)
 UNDEF_INST(ecpsvm_decode_first_ccw)
 UNDEF_INST(ecpsvm_dispatch_main)
 UNDEF_INST(ecpsvm_locate_rblock)
 UNDEF_INST(ecpsvm_comm_ccwproc)
 UNDEF_INST(ecpsvm_unxlate_ccw)
 UNDEF_INST(ecpsvm_disp2)
 UNDEF_INST(ecpsvm_store_level)
 UNDEF_INST(ecpsvm_loc_chgshrpg)
 UNDEF_INST(ecpsvm_extended_freex)
 UNDEF_INST(ecpsvm_extended_fretx)
 UNDEF_INST(ecpsvm_prefmach_assist)
 UNDEF_INST(add_y)
 UNDEF_INST(add_halfword_y)
 UNDEF_INST(add_logical_y)
 UNDEF_INST(and_immediate_y)
 UNDEF_INST(and_y)
 UNDEF_INST(compare_y)
 UNDEF_INST(compare_and_swap_y)
 UNDEF_INST(compare_halfword_y)
 UNDEF_INST(compare_logical_y)
 UNDEF_INST(compare_logical_immediate_y)
 UNDEF_INST(convert_to_binary_y)
 UNDEF_INST(convert_to_decimal_y)
 UNDEF_INST(exclusive_or_immediate_y)
 UNDEF_INST(exclusive_or_y)
 UNDEF_INST(insert_character_y)
 UNDEF_INST(load_y)
 UNDEF_INST(load_address_y)
 UNDEF_INST(load_byte)
 UNDEF_INST(load_byte_long)
 UNDEF_INST(load_halfword_y)
 UNDEF_INST(load_multiple_y)
 UNDEF_INST(move_immediate_y)
 UNDEF_INST(multiply_single_y)
 UNDEF_INST(or_immediate_y)
 UNDEF_INST(or_y)
 UNDEF_INST(store_y)
 UNDEF_INST(store_character_y)
 UNDEF_INST(store_halfword_y)
 UNDEF_INST(store_multiple_y)
 UNDEF_INST(subtract_y)
 UNDEF_INST(subtract_halfword_y)
 UNDEF_INST(subtract_logical_y)
 UNDEF_INST(test_under_mask_y)
 UNDEF_INST(load_access_multiple_y)
 UNDEF_INST(store_access_multiple_y)
 UNDEF_INST(load_float_long_y)
 UNDEF_INST(load_float_short_y)
 UNDEF_INST(store_float_long_y)
 UNDEF_INST(store_float_short_y)
 UNDEF_INST(compare_and_swap_and_purge_long)
 UNDEF_INST(invalidate_dat_table_entry)
 UNDEF_INST(add_fullword_immediate)                             /*@Z9*/
 UNDEF_INST(add_long_fullword_immediate)                        /*@Z9*/
 UNDEF_INST(add_logical_fullword_immediate)                     /*@Z9*/
 UNDEF_INST(add_logical_long_fullword_immediate)                /*@Z9*/
 UNDEF_INST(and_immediate_high_fullword)                        /*@Z9*/
 UNDEF_INST(and_immediate_low_fullword)                         /*@Z9*/
 UNDEF_INST(compare_fullword_immediate)                         /*@Z9*/
 UNDEF_INST(compare_long_fullword_immediate)                    /*@Z9*/
 UNDEF_INST(compare_logical_fullword_immediate)                 /*@Z9*/
 UNDEF_INST(compare_logical_long_fullword_immediate)            /*@Z9*/
 UNDEF_INST(exclusive_or_immediate_high_fullword)               /*@Z9*/
 UNDEF_INST(exclusive_or_immediate_low_fullword)                /*@Z9*/
 UNDEF_INST(insert_immediate_high_fullword)                     /*@Z9*/
 UNDEF_INST(insert_immediate_low_fullword)                      /*@Z9*/
 UNDEF_INST(load_long_fullword_immediate)                       /*@Z9*/
 UNDEF_INST(load_logical_immediate_high_fullword)               /*@Z9*/
 UNDEF_INST(load_logical_immediate_low_fullword)                /*@Z9*/
 UNDEF_INST(or_immediate_high_fullword)                         /*@Z9*/
 UNDEF_INST(or_immediate_low_fullword)                          /*@Z9*/
 UNDEF_INST(subtract_logical_fullword_immediate)                /*@Z9*/
 UNDEF_INST(subtract_logical_long_fullword_immediate)           /*@Z9*/
 UNDEF_INST(load_and_test)                                      /*@Z9*/
 UNDEF_INST(load_and_test_long)                                 /*@Z9*/
 UNDEF_INST(load_byte_register)                                 /*@Z9*/
 UNDEF_INST(load_long_byte_register)                            /*@Z9*/
 UNDEF_INST(load_halfword_register)                             /*@Z9*/
 UNDEF_INST(load_long_halfword_register)                        /*@Z9*/
 UNDEF_INST(load_logical_character)                             /*@Z9*/
 UNDEF_INST(load_logical_character_register)                    /*@Z9*/
 UNDEF_INST(load_logical_long_character_register)               /*@Z9*/
 UNDEF_INST(load_logical_halfword)                              /*@Z9*/
 UNDEF_INST(load_logical_halfword_register)                     /*@Z9*/
 UNDEF_INST(load_logical_long_halfword_register)                /*@Z9*/
 UNDEF_INST(find_leftmost_one_long_register)                    /*@Z9*/
 UNDEF_INST(load_page_table_entry_address)                      /*@Z9*/
 UNDEF_INST(store_clock_fast)
 UNDEF_INST(store_facility_list_extended)                       /*@Z9*/


DEF_INST(operation_exception)
{
    INST_UPDATE_PSW (regs, ILC(inst[0]), ILC(inst[0]));
    ARCH_DEP(program_interrupt)(regs, PGM_OPERATION_EXCEPTION);
}


DEF_INST(dummy_instruction)
{
//  logmsg(_("Dummy instruction: ")); ARCH_DEP(display_inst) (regs, inst);
    INST_UPDATE_PSW (regs, ILC(inst[0]), ILC(inst[0]));
}


#if !defined(_GEN_ARCH)

#define DISASM_ROUTE(_table,_route) \
void disasm_ ## _table (BYTE inst[], char unused[]) \
{ \
func disasm_fn; \
char* mnemonic; \
    UNREFERENCED(unused); \
    mnemonic = (void*)opcode_ ## _table [inst _route ][GEN_MAXARCH-1]; \
    disasm_fn = (void*)opcode_ ## _table [inst _route ][GEN_MAXARCH-2]; \
    disasm_fn(inst, mnemonic); \
}


DISASM_ROUTE(table,[0])

#define DISASM_COMMON_VARS \
char* name; \
char operands[64]

#define DISASM_SET_NAME \
    name = mnemonic+1; while(*name++)

#define DISASM_PRINT_OPERANDS \
    snprintf(operands,sizeof(operands)-1,

#define DISASM_LOGMSG \
    operands[sizeof(operands)-1]=0; \
    logmsg("%-6.6s%-19s    %s\n",mnemonic,operands,name)

void disasm_none (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
    UNREFERENCED(inst);
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%c",',');
    DISASM_LOGMSG;
}

void disasm_E (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
    UNREFERENCED(inst);
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%c",',');
    DISASM_LOGMSG;
}

void disasm_RR (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1, r2;
    r1 = inst[1] >> 4;
    r2 = inst[1] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d",r1,r2);
    DISASM_LOGMSG;
}

// "Mnemonic   R1"
void disasm_RR_R1 (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1;
    r1 = inst[1] >> 4;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d",r1);
    DISASM_LOGMSG;
}

void disasm_RR_SVC (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d",inst[1]);
    DISASM_LOGMSG;
}

void disasm_RRE (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1, r2;
    r1 = inst[3] >> 4;
    r2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d",r1,r2);
    DISASM_LOGMSG;
}

// "Mnemonic   R1"
void disasm_RRE_R1 (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1;
    r1 = inst[3] >> 4;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d",r1);
    DISASM_LOGMSG;
}

void disasm_RRF_R (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r3,r2;
    r1 = inst[2] >> 4;
    r3 = inst[3] >> 4;
    r2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d",r1,r3,r2);
    DISASM_LOGMSG;
}

void disasm_RRF_M (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int m3,r1,r2;
    m3 = inst[2] >> 4;
    r1 = inst[3] >> 4;
    r2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d",r1,m3,r2);
    DISASM_LOGMSG;
}

void disasm_RRF_M3 (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int m3,r1,r2;
    m3 = inst[2] >> 4;
    r1 = inst[3] >> 4;
    r2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d",r1,r2,m3);
    DISASM_LOGMSG;
}

void disasm_RRF_M4 (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int m4,r1,r2;
    m4 = inst[2] & 0x0F;
    r1 = inst[3] >> 4;
    r2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d",r1,r2,m4);
    DISASM_LOGMSG;
}

void disasm_RRF_MM (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int m3,m4,r1,r2;
    m3 = inst[2] >> 4;
    m4 = inst[2] & 0x0F;
    r1 = inst[3] >> 4;
    r2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d,%d",r1,m3,r2,m4);
    DISASM_LOGMSG;
}

void disasm_RRF_RM (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r3,m4,r1,r2;
    r3 = inst[2] >> 4;
    m4 = inst[2] & 0x0F;
    r1 = inst[3] >> 4;
    r2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d,%d",r1,r3,r2,m4);
    DISASM_LOGMSG;
}

void disasm_RRR (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r2,r3;
    r3 = inst[2] >> 4;
    r1 = inst[3] >> 4;
    r2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d",r1,r2,r3);
    DISASM_LOGMSG;
}

void disasm_RX (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,x2,b2,d2;
    r1 = inst[1] >> 4;
    x2 = inst[1] & 0x0F;
    b2 = inst[2] >> 4;
    d2 = (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d(%d,%d)",r1,d2,x2,b2);
    DISASM_LOGMSG;
}

void disasm_RXE (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,x2,b2,d2;
    r1 = inst[1] >> 4;
    x2 = inst[1] & 0x0F;
    b2 = inst[2] >> 4;
    d2 = (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d(%d,%d)",r1,d2,x2,b2);
    DISASM_LOGMSG;
}

void disasm_RXY (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,x2,b2,d2;
    r1 = inst[1] >> 4;
    x2 = inst[1] & 0x0F;
    b2 = inst[2] >> 4;
    d2 = (((S8)inst[4]) << 12) | (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d(%d,%d)",r1,d2,x2,b2);
    DISASM_LOGMSG;
}

void disasm_RXF (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r3,x2,b2,d2;
    r1 = inst[4] >> 4;
    r3 = inst[1] >> 4;
    x2 = inst[1] & 0x0F;
    b2 = inst[2] >> 4;
    d2 = (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d(%d,%d)",r1,r3,d2,x2,b2);
    DISASM_LOGMSG;
}

void disasm_RS (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r3,b2,d2;
    r1 = inst[1] >> 4;
    r3 = inst[1] & 0x0F;
    b2 = inst[2] >> 4;
    d2 = (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d(%d)",r1,r3,d2,b2);
    DISASM_LOGMSG;
}

// "Mnemonic   R1,D2(B2)"
void disasm_RS_R1D2B2 (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,b2,d2;
    r1 = inst[1] >> 4;
    b2 = inst[2] >> 4;
    d2 = (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d(%d)",r1,d2,b2);
    DISASM_LOGMSG;
}

void disasm_RSE (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r3,b2,d2;
    r1 = inst[1] >> 4;
    r3 = inst[1] & 0x0F;
    b2 = inst[2] >> 4;
    d2 = (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d(%d)",r1,r3,d2,b2);
    DISASM_LOGMSG;
}

void disasm_RSY (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r3,b2,d2;
    r1 = inst[1] >> 4;
    r3 = inst[1] & 0x0F;
    b2 = inst[2] >> 4;
    d2 = (((S8)inst[4]) << 12) | (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d(%d)",r1,r3,d2,b2);
    DISASM_LOGMSG;
}

void disasm_RSL (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int l1,b1,d1;
    l1 = inst[1] >> 4;
    b1 = inst[2] >> 4;
    d1 = (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d,%d)",d1,l1+1,b1);
    DISASM_LOGMSG;
}

void disasm_RSI (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r3,i2;
    r1 = inst[1] >> 4;
    r3 = inst[1] & 0x0F;
    i2 = (S16)(((U16)inst[2] << 8) | inst[3]);
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,*%+d",r1,r3,i2*2);
    DISASM_LOGMSG;
}

void disasm_RI (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,i2;
    r1 = inst[1] >> 4;
    i2 = (S16)(((U16)inst[2] << 8) | inst[3]);
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d",r1,i2);
    DISASM_LOGMSG;
}

void disasm_RI_B (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,i2;
    r1 = inst[1] >> 4;
    i2 = (S16)(((U16)inst[2] << 8) | inst[3]);
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,*%+d",r1,i2*2);
    DISASM_LOGMSG;
}

void disasm_RIE (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r3,i2;
    r1 = inst[1] >> 4;
    r3 = inst[1] & 0x0F;
    i2 = (S16)(((U16)inst[2] << 8) | inst[3]);
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,*%+d",r1,r3,i2*2);
    DISASM_LOGMSG;
}

void disasm_RIE_RIM (BYTE inst[], char mnemonic[])              /*208*/
{
DISASM_COMMON_VARS;
int r1,i2,m3;
    r1 = inst[1] >> 4;
    i2 = (S16)(((U16)inst[2] << 8) | inst[3]);
    m3 = inst[4] >> 4;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d",r1,i2,m3);
    DISASM_LOGMSG;
}

void disasm_RIE_RRIM (BYTE inst[], char mnemonic[])             /*208*/
{
DISASM_COMMON_VARS;
int r1,r2,i4,m3;
    r1 = inst[1] >> 4;
    r2 = inst[1] & 0x0F;
    i4 = (S16)(((U16)inst[2] << 8) | inst[3]);
    m3 = inst[4] >> 4;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d,*%+d",r1,r2,m3,i4*2);
    DISASM_LOGMSG;
}

void disasm_RIE_RMII (BYTE inst[], char mnemonic[])             /*208*/
{
DISASM_COMMON_VARS;
int r1,m3,i4,i2;
    r1 = inst[1] >> 4;
    m3 = inst[1] & 0x0F;
    i4 = (S16)(((U16)inst[2] << 8) | inst[3]);
    i2 = inst[4];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d,*%+d",r1,i2,m3,i4*2);
    DISASM_LOGMSG;
}

void disasm_RIE_RRIII (BYTE inst[], char mnemonic[])            /*208*/
{
DISASM_COMMON_VARS;
int r1,r2,i3,i4,i5;
    r1 = inst[1] >> 4;
    r2 = inst[1] & 0x0F;
    i3 = inst[2];
    i4 = inst[3];
    i5 = inst[4];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d,%d,%d",r1,r2,i3,i4,i5);
    DISASM_LOGMSG;
}

void disasm_RIL (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,i2;
    r1 = inst[1] >> 4;
    i2 = (S32)((((U32)inst[2] << 24) | ((U32)inst[3] << 16)
       | ((U32)inst[4] << 8)) | inst[5]);
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%"I32_FMT"d",r1,i2);
    DISASM_LOGMSG;
}

void disasm_RIL_A (BYTE inst[], char mnemonic[])                /*208*/
{
DISASM_COMMON_VARS;
int r1,i2;
    const S64 Two_S64=2;
    r1 = inst[1] >> 4;
    i2 = (S32)((((U32)inst[2] << 24) | ((U32)inst[3] << 16)
       | ((U32)inst[4] << 8)) | inst[5]);
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,*%+"I64_FMT"d",r1,i2*Two_S64);
    DISASM_LOGMSG;
}

void disasm_RIS (BYTE inst[], char mnemonic[])                  /*208*/
{
DISASM_COMMON_VARS;
int r1,i2,m3,b4,d4;
    r1 = inst[1] >> 4;
    m3 = inst[1] & 0x0F;
    b4 = inst[2] >> 4;
    d4 = (inst[2] & 0x0F) << 8 | inst[3];
    i2 = inst[4];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d,%d(%d)",r1,i2,m3,d4,b4);
    DISASM_LOGMSG;
}

void disasm_RRS (BYTE inst[], char mnemonic[])                  /*208*/
{
DISASM_COMMON_VARS;
int r1,r2,m3,b4,d4;
    r1 = inst[1] >> 4;
    r2 = inst[1] & 0x0F;
    b4 = inst[2] >> 4;
    d4 = (inst[2] & 0x0F) << 8 | inst[3];
    m3 = inst[4] >> 4;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d,%d(%d)",r1,r2,m3,d4,b4);
    DISASM_LOGMSG;
}

void disasm_SI (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int i2,b1,d1;
    i2 = inst[1];
    b1 = inst[2] >> 4;
    d1 = (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d),%d",d1,b1,i2);
    DISASM_LOGMSG;
}

void disasm_SIY (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int i2,b1,d1;
    i2 = inst[1];
    b1 = inst[2] >> 4;
    d1 = (((S8)inst[4]) << 12) | (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d),%d",d1,b1,i2);
    DISASM_LOGMSG;
}

void disasm_SIL (BYTE inst[], char mnemonic[])                  /*208*/
{
DISASM_COMMON_VARS;
int b1,d1,i2;
    b1 = inst[2] >> 4;
    d1 = (inst[2] & 0x0F) << 8 | inst[3];
    i2 = (S16)(((U16)inst[4] << 8) | inst[5]);
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d),%d",d1,b1,i2);
    DISASM_LOGMSG;
}

void disasm_S (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int d2,b2;
    b2 = inst[2] >> 4;
    d2 = (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d)",d2,b2);
    DISASM_LOGMSG;
}

void disasm_SS (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int l1,l2,b1,d1,b2,d2;
    l1 = inst[1] >> 4;
    l2 = inst[1] & 0x0F;
    b1 = inst[2] >> 4;
    d1 = (inst[2] & 0x0F) << 8 | inst[3];
    b2 = inst[4] >> 4;
    d2 = (inst[4] & 0x0F) << 8 | inst[5];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d,%d),%d(%d,%d)",d1,l1+1,b1,d2,l2+1,b2);
    DISASM_LOGMSG;
}

void disasm_SS_L (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int l1,b1,d1,b2,d2;
    l1 = inst[1];
    b1 = inst[2] >> 4;
    d1 = (inst[2] & 0x0F) << 8 | inst[3];
    b2 = inst[4] >> 4;
    d2 = (inst[4] & 0x0F) << 8 | inst[5];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d,%d),%d(%d)",d1,l1+1,b1,d2,b2);
    DISASM_LOGMSG;
}

// "Mnemonic   D1(B1),D2(L2,B2)"
void disasm_SS_L2 (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int l2,b1,d1,b2,d2;
    l2 = inst[1];
    b1 = inst[2] >> 4;
    d1 = (inst[2] & 0x0F) << 8 | inst[3];
    b2 = inst[4] >> 4;
    d2 = (inst[4] & 0x0F) << 8 | inst[5];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d),%d(%d,%d)",d1,b1,d2,l2+1,b2);
    DISASM_LOGMSG;
}

void disasm_SS_R (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r3,b2,d2,b4,d4;
    r1 = inst[1] >> 4;
    r3 = inst[1] & 0x0F;
    b2 = inst[2] >> 4;
    d2 = (inst[2] & 0x0F) << 8 | inst[3];
    b4 = inst[4] >> 4;
    d4 = (inst[4] & 0x0F) << 8 | inst[5];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d(%d),%d(%d)",r1,r3,d2,b2,d4,b4);
    DISASM_LOGMSG;
}

// "Mnemonic   D1(R1,B1),D2(B2),R3"
void disasm_SS_R3 (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r3,b1,d1,b2,d2;
    r1 = inst[1] >> 4;
    r3 = inst[1] & 0x0F;
    b1 = inst[2] >> 4;
    d1 = (inst[2] & 0x0F) << 8 | inst[3];
    b2 = inst[4] >> 4;
    d2 = (inst[4] & 0x0F) << 8 | inst[5];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d,%d),%d(%d),%d",d1,r1,b1,d2,b2,r3);
    DISASM_LOGMSG;
}

// "Mnemonic   R1,D2(B2),R3,D4(B4)"
void disasm_SS_RSRS (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r1,r3,b2,d2,b4,d4;
    r1 = inst[1] >> 4;
    r3 = inst[1] & 0x0F;
    b2 = inst[2] >> 4;
    d2 = (inst[2] & 0x0F) << 8 | inst[3];
    b4 = inst[4] >> 4;
    d4 = (inst[4] & 0x0F) << 8 | inst[5];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d(%d),%d,%d(%d)",r1,d2,b2,r3,d4,b4);
    DISASM_LOGMSG;
}

// "Mnemonic   D1(L1,B1),D2(B2),I3"
void disasm_SS_I (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int l1,i3,b1,d1,b2,d2;
    l1 = inst[1] >> 4;
    i3 = inst[1] & 0x0F;
    b1 = inst[2] >> 4;
    d1 = (inst[2] & 0x0F) << 8 | inst[3];
    b2 = inst[4] >> 4;
    d2 = (inst[4] & 0x0F) << 8 | inst[5];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d,%d),%d(%d),%d",d1,l1,b1,d2,b2,i3);
    DISASM_LOGMSG;
}

void disasm_SSE (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int b1,d1,b2,d2;
    b1 = inst[2] >> 4;
    d1 = (inst[2] & 0x0F) << 8 | inst[3];
    b2 = inst[4] >> 4;
    d2 = (inst[4] & 0x0F) << 8 | inst[5];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d),%d(%d)",d1,b1,d2,b2);
    DISASM_LOGMSG;
}

void disasm_SSF (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int r3,b1,d1,b2,d2;
    r3 = inst[1] >> 4;
    b1 = inst[2] >> 4;
    d1 = (inst[2] & 0x0F) << 8 | inst[3];
    b2 = inst[4] >> 4;
    d2 = (inst[4] & 0x0F) << 8 | inst[5];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d),%d(%d),%d",d1,b1,d2,b2,r3);
    DISASM_LOGMSG;
}

void disasm_VST (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int vr3,rt2,vr1,rs2;
    vr3 = inst[2] >> 4;
    rt2 = inst[2] & 0x0F;
    vr1 = inst[3] >> 4;
    rs2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d(%d)",vr1,vr3,rs2,rt2);
    DISASM_LOGMSG;
}

void disasm_VR (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int vr1,fr3,gr2;
    fr3 = inst[2] >> 4;
    vr1 = inst[3] >> 4;
    gr2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d",vr1,fr3,gr2);
    DISASM_LOGMSG;
}

void disasm_VS (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int rs2;
    rs2 = inst[3] & 0x0F;
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d",rs2);
    DISASM_LOGMSG;
}

void disasm_VRSE (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int vr1,vr3,d2,b2;
    vr3 = inst[2] >> 4;
    vr1 = inst[3] >> 4;
    b2 = inst[4] >> 4;
    d2 = (inst[4] & 0x0F) << 8 | inst[5];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d,%d,%d(%d)",vr1,vr3,d2,b2);
    DISASM_LOGMSG;
}

void disasm_S_NW (BYTE inst[], char mnemonic[])
{
DISASM_COMMON_VARS;
int d2,b2;
    b2 = inst[2] >> 4;
    d2 = (inst[2] & 0x0F) << 8 | inst[3];
    DISASM_SET_NAME;
    DISASM_PRINT_OPERANDS
        "%d(%d)",d2,b2);
    DISASM_LOGMSG;
}

/* Gabor Hoffer (performance option) */
DLL_EXPORT zz_func s370_opcode_table[256];

DLL_EXPORT void copy_opcode_tables()
{
int i;

    for (i = 0; i < 256; i++)
    {
        s370_opcode_table[i] = opcode_table[i][ARCH_370];
    }
}

void set_opcode_pointers(REGS *regs)
{
    memcpy(regs->s370_opcode_table, s370_opcode_table,
           sizeof(s370_opcode_table));
}

DLL_EXPORT zz_func opcode_table[256][GEN_MAXARCH] = {
 /*00*/   GENx___x___x___ ,
 /*01*/   GENx___x___x___ ,
 /*02*/   GENx___x___x___ ,
 /*03*/   GENx___x___x___ ,
 /*04*/   GENx370x390x900 (set_program_mask,RR_R1,"SPM"),
 /*05*/   GENx370x390x900 (branch_and_link_register,RR,"BALR"),
 /*06*/   GENx370x390x900 (branch_on_count_register,RR,"BCTR"),
 /*07*/   GENx370x390x900 (branch_on_condition_register,RR,"BCR"),
 /*08*/   GENx370x___x___ (set_storage_key,RR,"SSK"),
 /*09*/   GENx370x___x___ (insert_storage_key,RR,"ISK"),
 /*0A*/   GENx370x390x900 (supervisor_call,RR_SVC,"SVC"),
 /*0B*/   GENx___x390x900 (branch_and_set_mode,RR,"BSM"),
 /*0C*/   GENx___x390x900 (branch_and_save_and_set_mode,RR,"BASSM"),
 /*0D*/   GENx___x390x900 (branch_and_save_register,RR,"BASR"),
 /*0E*/   GENx___x390x900 (move_long,RR,"MVCL"),
 /*0F*/   GENx___x390x900 (compare_logical_character_long,RR,"CLCL"),
 /*10*/   GENx370x390x900 (load_positive_register,RR,"LPR"),
 /*11*/   GENx370x390x900 (load_negative_register,RR,"LNR"),
 /*12*/   GENx370x390x900 (load_and_test_register,RR,"LTR"),
 /*13*/   GENx370x390x900 (load_complement_register,RR,"LCR"),
 /*14*/   GENx370x390x900 (and_register,RR,"NR"),
 /*15*/   GENx370x390x900 (compare_logical_register,RR,"CLR"),
 /*16*/   GENx370x390x900 (or_register,RR,"OR"),
 /*17*/   GENx370x390x900 (exclusive_or_register,RR,"XR"),
 /*18*/   GENx370x390x900 (load_register,RR,"LR"),
 /*19*/   GENx370x390x900 (compare_register,RR,"CR"),
 /*1A*/   GENx370x390x900 (add_register,RR,"AR"),
 /*1B*/   GENx370x390x900 (subtract_register,RR,"SR"),
 /*1C*/   GENx370x390x900 (multiply_register,RR,"MR"),
 /*1D*/   GENx370x390x900 (divide_register,RR,"DR"),
 /*1E*/   GENx370x390x900 (add_logical_register,RR,"ALR"),
 /*1F*/   GENx370x390x900 (subtract_logical_register,RR,"SLR"),
 /*20*/   GENx370x390x900 (load_positive_float_long_reg,RR,"LPDR"),
 /*21*/   GENx370x390x900 (load_negative_float_long_reg,RR,"LNDR"),
 /*22*/   GENx370x390x900 (load_and_test_float_long_reg,RR,"LTDR"),
 /*23*/   GENx370x390x900 (load_complement_float_long_reg,RR,"LCDR"),
 /*24*/   GENx370x390x900 (halve_float_long_reg,RR,"HDR"),
 /*25*/   GENx___x390x900 (load_rounded_float_long_reg,RR,"LDXR"),
 /*26*/   GENx___x390x900 (multiply_float_ext_reg,RR,"MXR"),
 /*27*/   GENx___x390x900 (multiply_float_long_to_ext_reg,RR,"MXDR"),
 /*28*/   GENx370x390x900 (load_float_long_reg,RR,"LDR"),
 /*29*/   GENx370x390x900 (compare_float_long_reg,RR,"CDR"),
 /*2A*/   GENx370x390x900 (add_float_long_reg,RR,"ADR"),
 /*2B*/   GENx370x390x900 (subtract_float_long_reg,RR,"SDR"),
 /*2C*/   GENx370x390x900 (multiply_float_long_reg,RR,"MDR"),
 /*2D*/   GENx370x390x900 (divide_float_long_reg,RR,"DDR"),
 /*2E*/   GENx370x390x900 (add_unnormal_float_long_reg,RR,"AWR"),
 /*2F*/   GENx370x390x900 (subtract_unnormal_float_long_reg,RR,"SWR"),
 /*30*/   GENx370x390x900 (load_positive_float_short_reg,RR,"LPER"),
 /*31*/   GENx370x390x900 (load_negative_float_short_reg,RR,"LNER"),
 /*32*/   GENx370x390x900 (load_and_test_float_short_reg,RR,"LTER"),
 /*33*/   GENx370x390x900 (load_complement_float_short_reg,RR,"LCER"),
 /*34*/   GENx370x390x900 (halve_float_short_reg,RR,"HER"),
 /*35*/   GENx___x390x900 (load_rounded_float_short_reg,RR,"LEDR"),
 /*36*/   GENx___x390x900 (add_float_ext_reg,RR,"AXR"),
 /*37*/   GENx___x390x900 (subtract_float_ext_reg,RR,"SXR"),
 /*38*/   GENx370x390x900 (load_float_short_reg,RR,"LER"),
 /*39*/   GENx370x390x900 (compare_float_short_reg,RR,"CER"),
 /*3A*/   GENx370x390x900 (add_float_short_reg,RR,"AER"),
 /*3B*/   GENx370x390x900 (subtract_float_short_reg,RR,"SER"),
 /*3C*/   GENx370x390x900 (multiply_float_short_to_long_reg,RR,"MDER"),
 /*3D*/   GENx370x390x900 (divide_float_short_reg,RR,"DER"),
 /*3E*/   GENx370x390x900 (add_unnormal_float_short_reg,RR,"AUR"),
 /*3F*/   GENx370x390x900 (subtract_unnormal_float_short_reg,RR,"SUR"),
 /*40*/   GENx370x390x900 (store_halfword,RX,"STH"),
 /*41*/   GENx370x390x900 (load_address,RX,"LA"),
 /*42*/   GENx370x390x900 (store_character,RX,"STC"),
 /*43*/   GENx370x390x900 (insert_character,RX,"IC"),
 /*44*/   GENx370x390x900 (execute,RX,"EX"),
 /*45*/   GENx370x390x900 (branch_and_link,RX,"BAL"),
 /*46*/   GENx370x390x900 (branch_on_count,RX,"BCT"),
 /*47*/   GENx370x390x900 (branch_on_condition,RX,"BC"),
 /*48*/   GENx370x390x900 (load_halfword,RX,"LH"),
 /*49*/   GENx370x390x900 (compare_halfword,RX,"CH"),
 /*4A*/   GENx370x390x900 (add_halfword,RX,"AH"),
 /*4B*/   GENx370x390x900 (subtract_halfword,RX,"SH"),
 /*4C*/   GENx370x390x900 (multiply_halfword,RX,"MH"),
 /*4D*/   GENx___x390x900 (branch_and_save,RX,"BAS"),
 /*4E*/   GENx370x390x900 (convert_to_decimal,RX,"CVD"),
 /*4F*/   GENx370x390x900 (convert_to_binary,RX,"CVB"),
 /*50*/   GENx370x390x900 (store,RX,"ST"),
 /*51*/   GENx___x390x900 (load_address_extended,RX,"LAE"),
 /*52*/   GENx___x___x___ ,
 /*53*/   GENx___x___x___ ,
 /*54*/   GENx370x390x900 (and,RX,"N"),
 /*55*/   GENx370x390x900 (compare_logical,RX,"CL"),
 /*56*/   GENx370x390x900 (or,RX,"O"),
 /*57*/   GENx370x390x900 (exclusive_or,RX,"X"),
 /*58*/   GENx370x390x900 (load,RX,"L"),
 /*59*/   GENx370x390x900 (compare,RX,"C"),
 /*5A*/   GENx370x390x900 (add,RX,"A"),
 /*5B*/   GENx370x390x900 (subtract,RX,"S"),
 /*5C*/   GENx370x390x900 (multiply,RX,"M"),
 /*5D*/   GENx370x390x900 (divide,RX,"D"),
 /*5E*/   GENx370x390x900 (add_logical,RX,"AL"),
 /*5F*/   GENx370x390x900 (subtract_logical,RX,"SL"),
 /*60*/   GENx370x390x900 (store_float_long,RX,"STD"),
 /*61*/   GENx___x___x___ ,
 /*62*/   GENx___x___x___ ,
 /*63*/   GENx___x___x___ ,
 /*64*/   GENx___x___x___ ,
 /*65*/   GENx___x___x___ ,
 /*66*/   GENx___x___x___ ,
 /*67*/   GENx___x390x900 (multiply_float_long_to_ext,RX,"MXD"),
 /*68*/   GENx370x390x900 (load_float_long,RX,"LD"),
 /*69*/   GENx370x390x900 (compare_float_long,RX,"CD"),
 /*6A*/   GENx370x390x900 (add_float_long,RX,"AD"),
 /*6B*/   GENx370x390x900 (subtract_float_long,RX,"SD"),
 /*6C*/   GENx370x390x900 (multiply_float_long,RX,"MD"),
 /*6D*/   GENx370x390x900 (divide_float_long,RX,"DD"),
 /*6E*/   GENx370x390x900 (add_unnormal_float_long,RX,"AW"),
 /*6F*/   GENx370x390x900 (subtract_unnormal_float_long,RX,"SW"),
 /*70*/   GENx370x390x900 (store_float_short,RX,"STE"),
 /*71*/   GENx___x390x900 (multiply_single,RX,"MS"),
 /*72*/   GENx___x___x___ ,
 /*73*/   GENx___x___x___ ,
 /*74*/   GENx___x___x___ ,
 /*75*/   GENx___x___x___ ,
 /*76*/   GENx___x___x___ ,
 /*77*/   GENx___x___x___ ,
 /*78*/   GENx370x390x900 (load_float_short,RX,"LE"),
 /*79*/   GENx370x390x900 (compare_float_short,RX,"CE"),
 /*7A*/   GENx370x390x900 (add_float_short,RX,"AE"),
 /*7B*/   GENx370x390x900 (subtract_float_short,RX,"SE"),
 /*7C*/   GENx370x390x900 (multiply_float_short_to_long,RX,"MDE"),
 /*7D*/   GENx370x390x900 (divide_float_short,RX,"DE"),
 /*7E*/   GENx370x390x900 (add_unnormal_float_short,RX,"AU"),
 /*7F*/   GENx370x390x900 (subtract_unnormal_float_short,RX,"SU"),
 /*80*/   GENx370x390x900 (set_system_mask,S,"SSM"),
 /*81*/   GENx___x___x___ ,
 /*82*/   GENx370x390x900 (load_program_status_word,S,"LPSW"),
 /*83*/   GENx370x390x900 (diagnose,RS,"DIAG"),
 /*84*/   GENx___x390x900 (branch_relative_on_index_high,RSI,"BRXH"),
 /*85*/   GENx___x390x900 (branch_relative_on_index_low_or_equal,RSI,"BRXLE"),
 /*86*/   GENx370x390x900 (branch_on_index_high,RS,"BXH"),
 /*87*/   GENx370x390x900 (branch_on_index_low_or_equal,RS,"BXLE"),
 /*88*/   GENx370x390x900 (shift_right_single_logical,RS_R1D2B2,"SRL"),
 /*89*/   GENx370x390x900 (shift_left_single_logical,RS_R1D2B2,"SLL"),
 /*8A*/   GENx370x390x900 (shift_right_single,RS_R1D2B2,"SRA"),
 /*8B*/   GENx370x390x900 (shift_left_single,RS_R1D2B2,"SLA"),
 /*8C*/   GENx370x390x900 (shift_right_double_logical,RS_R1D2B2,"SRDL"),
 /*8D*/   GENx370x390x900 (shift_left_double_logical,RS_R1D2B2,"SLDL"),
 /*8E*/   GENx370x390x900 (shift_right_double,RS_R1D2B2,"SRDA"),
 /*8F*/   GENx370x390x900 (shift_left_double,RS_R1D2B2,"SLDA"),
 /*90*/   GENx370x390x900 (store_multiple,RS,"STM"),
 /*91*/   GENx370x390x900 (test_under_mask,SI,"TM"),
 /*92*/   GENx370x390x900 (move_immediate,SI,"MVI"),
 /*93*/   GENx370x390x900 (test_and_set,S,"TS"),
 /*94*/   GENx370x390x900 (and_immediate,SI,"NI"),
 /*95*/   GENx370x390x900 (compare_logical_immediate,SI,"CLI"),
 /*96*/   GENx370x390x900 (or_immediate,SI,"OI"),
 /*97*/   GENx370x390x900 (exclusive_or_immediate,SI,"XI"),
 /*98*/   GENx370x390x900 (load_multiple,RS,"LM"),
 /*99*/   GENx___x390x900 (trace,RS,"TRACE"),
 /*9A*/   GENx___x390x900 (load_access_multiple,RS,"LAM"),
 /*9B*/   GENx___x390x900 (store_access_multiple,RS,"STAM"),
 /*9C*/   GENx370x___x___ (start_io,S,"SIO"),
 /*9D*/   GENx370x___x___ (test_io,S,"TIO"),
 /*9E*/   GENx370x___x___ (halt_io,S,"HIO"),
 /*9F*/   GENx370x___x___ (test_channel,S,"TCH"),
 /*A0*/   GENx___x___x___ ,
 /*A1*/   GENx___x___x___ ,
 /*A2*/   GENx___x___x___ ,
 /*A3*/   GENx___x___x___ ,
 /*A4*/   GENx___x___x___ ,
 /*A5*/   GENx___x___x___ ,
 /*A6*/   GENx___x___x___ ,
 /*A7*/   GENx___x___x___ ,
 /*A8*/   GENx___x390x900 (move_long_extended,RS,"MVCLE"),
 /*A9*/   GENx___x390x900 (compare_logical_long_extended,RS,"CLCLE"),
 /*AA*/   GENx___x___x___ ,
 /*AB*/   GENx___x___x___ ,
 /*AC*/   GENx___x390x900 (store_then_and_system_mask,SI,"STNSM"),
 /*AD*/   GENx___x390x900 (store_then_or_system_mask,SI,"STOSM"),
 /*AE*/   GENx___x390x900 (signal_procesor,RS,"SIGP"),
 /*AF*/   GENx___x390x900 (monitor_call,SI,"MC"),
 /*B0*/   GENx___x___x___ ,
 /*B1*/   GENx___x390x900 (load_real_address,RX,"LRA"),
 /*B2*/   GENx___x___x___ ,
 /*B3*/   GENx___x___x___ ,
 /*B4*/   GENx___x___x___ ,
 /*B5*/   GENx___x___x___ ,
 /*B6*/   GENx___x390x900 (store_control,RS,"STCTL"),
 /*B7*/   GENx___x390x900 (load_control,RS,"LCTL"),
 /*B8*/   GENx___x___x___ ,
 /*B9*/   GENx___x___x___ ,
 /*BA*/   GENx___x390x900 (compare_and_swap,RS,"CS"),
 /*BB*/   GENx___x390x900 (compare_double_and_swap,RS,"CDS"),
 /*BC*/   GENx___x___x___ ,
 /*BD*/   GENx___x390x900 (compare_logical_characters_under_mask,RS,"CLM"),
 /*BE*/   GENx___x390x900 (store_characters_under_mask,RS,"STCM"),
 /*BF*/   GENx___x390x900 (insert_characters_under_mask,RS,"ICM"),
 /*C0*/   GENx___x___x___ ,
 /*C1*/   GENx___x___x___ ,
 /*C2*/   GENx___x___x___ ,               /*@Z9*/
 /*C3*/   GENx___x___x___ ,
 /*C4*/   GENx___x___x___ ,               /*208*/
 /*C5*/   GENx___x___x___ ,
 /*C6*/   GENx___x___x___ ,               /*208*/
 /*C7*/   GENx___x___x___ ,
 /*C8*/   GENx___x___x___ ,
 /*C9*/   GENx___x___x___ ,
 /*CA*/   GENx___x___x___ ,
 /*CB*/   GENx___x___x___ ,
 /*CC*/   GENx___x___x___ ,
 /*CD*/   GENx___x___x___ ,
 /*CE*/   GENx___x___x___ ,
 /*CF*/   GENx___x___x___ ,
 /*D0*/   GENx___x390x900 (translate_and_test_reverse,SS_L,"TRTR"),
 /*D1*/   GENx370x390x900 (move_numerics,SS_L,"MVN"),
 /*D2*/   GENx370x390x900 (move_character,SS_L,"MVC"),
 /*D3*/   GENx370x390x900 (move_zones,SS_L,"MVZ"),
 /*D4*/   GENx370x390x900 (and_character,SS_L,"NC"),
 /*D5*/   GENx370x390x900 (compare_logical_character,SS_L,"CLC"),
 /*D6*/   GENx370x390x900 (or_character,SS_L,"OC"),
 /*D7*/   GENx370x390x900 (exclusive_or_character,SS_L,"XC"),
 /*D8*/   GENx___x___x___ ,
 /*D9*/   GENx___x390x900 (move_with_key,SS_R3,"MVCK"),
 /*DA*/   GENx___x390x900 (move_to_primary,SS_R3,"MVCP"),
 /*DB*/   GENx___x390x900 (move_to_secondary,SS_R3,"MVCS"),
 /*DC*/   GENx370x390x900 (translate,SS_L,"TR"),
 /*DD*/   GENx370x390x900 (translate_and_test,SS_L,"TRT"),
 /*DE*/   GENx370x390x900 (edit_x_edit_and_mark,SS_L,"ED"),
 /*DF*/   GENx370x390x900 (edit_x_edit_and_mark,SS_L,"EDMK"),
 /*E0*/   GENx___x___x___ ,
 /*E1*/   GENx___x390x900 (pack_unicode,SS_L2,"PKU"),
 /*E2*/   GENx___x390x900 (unpack_unicode,SS_L,"UNPKU"),
 /*E3*/   GENx___x___x___ ,
 /*E4*/   GENx___x___x___ ,
 /*E5*/   GENx___x___x___ ,
 /*E6*/   GENx___x___x___ ,
 /*E7*/   GENx___x___x___ ,
 /*E8*/   GENx___x390x900 (move_inverse,SS_L,"MVCIN"),
 /*E9*/   GENx___x390x900 (pack_ascii,SS_L2,"PKA"),
 /*EA*/   GENx___x390x900 (unpack_ascii,SS_L,"UNPKA"),
 /*EB*/   GENx___x___x___ ,
 /*EC*/   GENx___x___x___ ,
 /*ED*/   GENx___x___x___ ,
 /*EE*/   GENx___x390x900 (perform_locked_operation,SS_RSRS,"PLO"),
 /*EF*/   GENx___x___x900 (load_multiple_disjoint,SS_R,"LMD"),
 /*F0*/   GENx___x390x900 (shift_and_round_decimal,SS_I,"SRP"),
 /*F1*/   GENx370x390x900 (move_with_offset,SS,"MVO"),
 /*F2*/   GENx370x390x900 (pack,SS,"PACK"),
 /*F3*/   GENx370x390x900 (unpack,SS,"UNPK"),
 /*F4*/   GENx___x___x___ ,
 /*F5*/   GENx___x___x___ ,
 /*F6*/   GENx___x___x___ ,
 /*F7*/   GENx___x___x___ ,
 /*F8*/   GENx370x390x900 (zero_and_add,SS,"ZAP"),
 /*F9*/   GENx370x390x900 (compare_decimal,SS,"CP"),
 /*FA*/   GENx370x390x900 (add_decimal,SS,"AP"),
 /*FB*/   GENx370x390x900 (subtract_decimal,SS,"SP"),
 /*FC*/   GENx370x390x900 (multiply_decimal,SS,"MP"),
 /*FD*/   GENx370x390x900 (divide_decimal,SS,"DP"),
 /*FE*/   GENx___x___x___ ,
 /*FF*/   GENx___x___x___  };

#endif /*!defined (_GEN_ARCH)*/

#endif

/* end of OPCODE.C */
