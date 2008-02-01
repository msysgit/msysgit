/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef APR_COMPAT_H
#define APR_COMPAT_H

 /**
 * @file apr_compat.h
 * @brief APR Legacy Apache 1.3 Compatibility
 * @deprecated These defines are only present for historical purposes
 */

/**
 * @defgroup apr_compat APR Legacy Apache 1.3 Compatibility
 * @ingroup APR 
 * @{
 */

/* redefine 1.3.x symbols to those that now live in libapr */

/** @see APR_INLINE */
#define ap_inline APR_INLINE

/** @deprecated @see apr_md5_ctx_t */
#define ap_md5_ctx_t apr_md5_ctx_t
/** @deprecated @see apr_md5_encode */
#define ap_MD5Encode apr_md5_encode
/** @deprecated @see apr_md5_final */
#define ap_MD5Final apr_md5_final
/** @deprecated @see apr_md5_init */
#define ap_MD5Init apr_md5_init
/** @deprecated @see apr_md5_update */
#define ap_MD5Update apr_md5_update
/** @deprecated @see apr_array_append */
#define ap_append_arrays apr_array_append
/** @deprecated @see apr_array_cat */
#define ap_array_cat apr_array_cat
/** @deprecated @see apr_array_header_t */
#define ap_array_header_t apr_array_header_t
/** @deprecated @see apr_array_pstrcat */
#define ap_array_pstrcat apr_array_pstrcat
/** @deprecated @see apr_pool_free_blocks_num_bytes */
#define ap_bytes_in_free_blocks apr_pool_free_blocks_num_bytes
/** @deprecated @see apr_pool_num_bytes */
#define ap_bytes_in_pool apr_pool_num_bytes
/** @deprecated @see apr_check_file_time */
#define ap_check_file_time apr_check_file_time
/** @deprecated @see apr_filetype_e */
#define ap_filetype_e apr_filetype_e
/** @deprecated @see apr_pool_cleanup_for_exec */
#define ap_cleanup_for_exec apr_pool_cleanup_for_exec
/** @deprecated @see apr_pool_clear */
#define ap_clear_pool apr_pool_clear
/** @deprecated @see apr_table_clear */
#define ap_clear_table apr_table_clear
/** @deprecated @see apr_array_copy */
#define ap_copy_array apr_array_copy
/** @deprecated @see apr_array_copy_hdr */
#define ap_copy_array_hdr apr_array_copy_hdr
/** @deprecated @see apr_table_copy */
#define ap_copy_table apr_table_copy
/** @deprecated @see apr_cpystrn */
#define ap_cpystrn apr_cpystrn
/** @deprecated @see apr_day_snames */
#define ap_day_snames apr_day_snames
/** @deprecated @see apr_pool_destroy */
#define ap_destroy_pool apr_pool_destroy
/** @deprecated @see apr_time_exp_t */
#define ap_exploded_time_t apr_time_exp_t
/** @deprecated @see apr_fnmatch */
#define ap_fnmatch apr_fnmatch
/** @deprecated @see apr_getopt */
#define ap_getopt apr_getopt
/** @deprecated @see apr_inet_addr */
#define ap_inet_addr apr_inet_addr
/** @deprecated @see apr_pool_alloc_init */
#define ap_init_alloc apr_pool_alloc_init
/** @deprecated @see apr_is_empty_table */
#define ap_is_empty_table apr_is_empty_table
/** @deprecated @see apr_fnmatch_test */
#define ap_is_fnmatch apr_fnmatch_test
/** @deprecated @see apr_pool_cleanup_kill */
#define ap_kill_cleanup apr_pool_cleanup_kill
/** @deprecated @see apr_array_make */
#define ap_make_array apr_array_make
/** @deprecated @see apr_pool_sub_make */
#define ap_make_sub_pool apr_pool_sub_make
/** @deprecated @see apr_table_make */
#define ap_make_table apr_table_make
/** @deprecated @see apr_month_snames */
#define ap_month_snames apr_month_snames
/** @deprecated @see apr_pool_note_subprocess*/
#define ap_note_subprocess apr_pool_note_subprocess
/** @deprecated @see apr_pool_cleanup_null */
#define ap_null_cleanup apr_pool_cleanup_null
/** @deprecated @see apr_filepath_merge */
#define ap_os_canonical_filename apr_filepath_merge
/** @deprecated @see apr_filepath_merge */
#define ap_os_case_canonical_filename apr_filepath_merge
/** @deprecated @see apr_dso_load */
#define ap_os_dso_load apr_dso_load
/** @deprecated @see apr_dso_unload */
#define ap_os_dso_unload apr_dso_unload
/** @deprecated @see apr_dso_sym */
#define ap_os_dso_sym apr_dso_sym
/** @deprecated @see apr_dso_error */
#define ap_os_dso_error apr_dso_error
/** @deprecated @see apr_filepath_merge
 *  @warning apr_filepath_merge rejects invalid filenames */
#define ap_os_is_filename_valid apr_filepath_merge
/** @deprecated @see apr_proc_kill */
#define ap_os_kill apr_proc_kill
/** @deprecated @see apr_filepath_merge */
#define ap_os_systemcase_canonical_filename apr_filepath_merge
/** @deprecated @see apr_table_overlap */
#define ap_overlap_tables apr_table_overlap
/** @deprecated @see apr_table_overlay */
#define ap_overlay_tables apr_table_overlay
/** @deprecated @see apr_palloc */
#define ap_palloc apr_palloc
/** @deprecated @see apr_pcalloc */
#define ap_pcalloc apr_pcalloc
/** @deprecated @see apr_pool_join */
#define ap_pool_join apr_pool_join
/** @deprecated @see apr_psprintf */
#define ap_psprintf apr_psprintf
/** @deprecated @see apr_pstrcat */
#define ap_pstrcat apr_pstrcat
/** @deprecated @see apr_pstrdup */
#define ap_pstrdup apr_pstrdup
/** @deprecated @see apr_pstrndup */
#define ap_pstrndup apr_pstrndup
/** @deprecated @see apr_array_push */
#define ap_push_array apr_array_push
/** @deprecated @see apr_pvsprintf */
#define ap_pvsprintf apr_pvsprintf
/** @deprecated @see apr_pool_cleanup_register */
#define ap_register_cleanup apr_pool_cleanup_register
/** @deprecated @see apr_proc_other_child_register */
#define ap_register_other_child apr_proc_other_child_register
/** @deprecated @see apr_pool_cleanup_run */
#define ap_run_cleanup apr_pool_cleanup_run
/** @deprecated @see apr_signal */
#define ap_signal apr_signal
/** @deprecated @see apr_snprintf */
#define ap_snprintf apr_snprintf
/** @deprecated @see apr_table_add */
#define ap_table_add apr_table_add
/** @deprecated @see apr_table_addn */
#define ap_table_addn apr_table_addn
/** @deprecated @see apr_table_do */
#define ap_table_do apr_table_do
/** @deprecated @see apr_table_elts */
#define ap_table_elts apr_table_elts
/** @deprecated @see apr_table_get */
#define ap_table_get apr_table_get
/** @deprecated @see apr_table_merge */
#define ap_table_merge apr_table_merge
/** @deprecated @see apr_table_mergen */
#define ap_table_mergen apr_table_mergen
/** @deprecated @see apr_table_set */
#define ap_table_set apr_table_set
/** @deprecated @see apr_table_setn */
#define ap_table_setn apr_table_setn
/** @deprecated @see apr_table_unset */
#define ap_table_unset apr_table_unset
/** @deprecated @see apr_proc_other_child_unregister */
#define ap_unregister_other_child apr_proc_other_child_unregister
/** @deprecated @see apr_password_validate */
#define ap_validate_password apr_password_validate
/** @deprecated @see apr_vformatter */
#define ap_vformatter apr_vformatter
/** @deprecated @see apr_vsnprintf */
#define ap_vsnprintf apr_vsnprintf
/** @deprecated @see apr_wait_t */
#define ap_wait_t apr_wait_t

/** @deprecated @see apr_isalnum */
#define ap_isalnum apr_isalnum
/** @deprecated @see apr_isalpha*/
#define ap_isalpha apr_isalpha
/** @deprecated @see apr_iscntrl */
#define ap_iscntrl apr_iscntrl
/** @deprecated @see apr_isdigit */
#define ap_isdigit apr_isdigit
/** @deprecated @see apr_isgraph */
#define ap_isgraph apr_isgraph
/** @deprecated @see apr_islower */
#define ap_islower apr_islower
/** @deprecated @see apr_isascii */
#define ap_isascii apr_isascii
/** @deprecated @see apr_isprint */
#define ap_isprint apr_isprint
/** @deprecated @see apr_ispunct */
#define ap_ispunct apr_ispunct
/** @deprecated @see apr_isspace */
#define ap_isspace apr_isspace
/** @deprecated @see apr_isupper */
#define ap_isupper apr_isupper
/** @deprecated @see apr_isxdigit */
#define ap_isxdigit apr_isxdigit
/** @deprecated @see apr_tolower */
#define ap_tolower apr_tolower
/** @deprecated @see apr_toupper */
#define ap_toupper apr_toupper

/** @deprecated @see APR_USEC_PER_SEC */
#define AP_USEC_PER_SEC APR_USEC_PER_SEC
/** @deprecated @see APR_RFC822_DATE_LEN */
#define AP_RFC822_DATE_LEN APR_RFC822_DATE_LEN
/** @deprecated @see APR_OVERLAP_TABLES_MERGE */
#define AP_OVERLAP_TABLES_MERGE APR_OVERLAP_TABLES_MERGE
/** @deprecated @see APR_OVERLAP_TABLES_SET */
#define AP_OVERLAP_TABLES_SET APR_OVERLAP_TABLES_SET

/** @} */

#endif /* APR_COMPAT_H */
