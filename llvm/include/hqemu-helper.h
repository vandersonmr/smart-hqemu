DEF_HELPER_1(export_hqemu, void, env)
DEF_HELPER_1(lookup_ibtc, ptr, env)
DEF_HELPER_1(lookup_cpbl, ptr, env)
DEF_HELPER_3(validate_cpbl, int, env, tl, int)
DEF_HELPER_2(NET_profile, void, env, int)
DEF_HELPER_2(NET_predict, void, env, int)
DEF_HELPER_2(verify_tb, void, env, int)
DEF_HELPER_3(profile_exec, void, env, ptr, int)
DEF_HELPER_1(timestamp_begin, void, i64)
DEF_HELPER_1(timestamp_end, void, i64)
