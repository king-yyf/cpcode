# -*- coding: UTF8 -*-

import os
import argparse
import sys
import dragonfly
current_dir = os.path.dirname(__file__)

from dragonfly.common_leaf_dsl import LeafFlow, OfflineRunner
from dragonfly.ext.mio.mio_api_mixin import MioApiMixin
from dragonfly.ext.offline.offline_api_mixin import OfflineApiMixin
from dragonfly.ext.gsu.gsu_api_mixin import GsuApiMixin
from dragonfly.ext.embed_calc.embed_calc_api_mixin import EmbedCalcApiMixin

parser = argparse.ArgumentParser()
parser.add_argument('--run', dest="run", default=False, action='store_true')
parser.add_argument('--eval', dest="eval", default=False, action='store_true')
parser.add_argument('--remove_no_realshow', dest="remove_no_realshow", default=False, action='store_true')
parser.add_argument("--remove_non_slide_sample", dest="remove_non_slide_sample", default=True, action="store_true")
parser.add_argument('--dump-division', dest="dump_division", type=int, default=1000000)
parser.add_argument('--feature_list_path', dest='feature_list_path', default='./oversea_feature_list_sign.txt')
parser.add_argument("--context_sign_fea_file", dest="context_sign_fea_file", default="./context_sign_feature.lua")
parser.add_argument("--product", dest="product", choices=["KwaiPro", "KwaiMe"], default="KwaiPro")
args = parser.parse_args()

short_view_threshold = 3000
effective_view_threshold = 7000
effective_view_l3 = 18000
long_view_threshold = 18000
very_long_view_threshold = 40000
watch_time_unit = 1000

# load plugins
class DataReaderFlow(LeafFlow, MioApiMixin, OfflineApiMixin,GsuApiMixin, EmbedCalcApiMixin):
    def clean_all(self, reason, **kwargs):
        return self.limit(0, name="clean_all_for_" + reason, **kwargs)
    # 根据不同条件过滤photo
    def do_snack_filter(self, remove_no_realshow=False, remove_non_slide_sample=True):
        self.enrich_attr_by_lua(
            name="filter_valid_record",
            import_common_attr=["request_page_type"],
            import_item_attr=["realshow", "playing_time"],
            function_for_item="calculate",
            export_item_attr=["has_playing_time_or_realshow"],
            lua_script="""
            function calculate()
                local has_playing_time = ((request_page_type == 11 or request_page_type == 12) and (playing_time > 0)) or false
                local has_realshow = (realshow == 1) or false
                return has_playing_time or has_realshow
            end
            """) \
        .filter_by_attr(attr_name="has_playing_time_or_realshow", remove_if="<", compare_to=1, name="remove_no_playing_time_or_realshow") \
        .enrich_attr_by_lua(
            name="reset_realshow_labels",
            import_item_attr=["realshow"],
            export_item_attr=["realshow", "slide_enter", "no_realshow"],
            function_for_item="reset",
            lua_script="""
                function reset()
                    return 0, realshow, (realshow < 1)
                end
            """)
        return self
    
    def do_kwai_filter(self, remove_no_realshow=False, remove_non_slide_sample=True):
        self.enrich_attr_by_lua(
                name="enrich_no_realshow",
                import_item_attr=["realshow", "slide_enter"],
                function_for_item="calculate",
                export_item_attr=["no_realshow"],
                lua_script="""
                    function calculate()
                        local show = realshow or 0
                        local slide = slide_enter or 0
                        return (show < 1) and (slide < 1)
                    end
                """)
        if remove_no_realshow:
            self.filter_by_attr(attr_name="no_realshow", remove_if=">", compare_to=0, name="remove_no_realshow")
        if remove_non_slide_sample:
            self.if_("is_slide_sample <= 0") \
                    .clean_all("remove_non_slide_sample") \
                .end_if_()    
        self.enrich_attr_by_lua(
                name="enrich_invalid_xtrs",
                import_item_attr=["ctr", "ltr", "ftr", "fpr", "evr"],
                function_for_item="calc",
                export_item_attr=["invalid_xtr"],
                lua_script="""
                    function calc()
                        local flag_ctr = (ctr ~= nil) and (ctr < 0.0 or ctr > 1.0) or false
                        local flag_ltr = (ltr ~= nil) and (ltr < 0.0 or ltr > 1.0) or false
                        local flag_ftr = (ftr ~= nil) and (ftr < 0.0 or ftr > 1.0) or false
                        local flag_fpr = (fpr ~= nil) and (fpr < 0.0 or fpr > 1.0) or false
                        local flag_evr = (evr ~= nil) and (evr < 0.0 or evr > 1.0) or false
                        return  flag_ctr or flag_ltr or flag_ftr or flag_fpr or flag_evr
                    end
                """) \
            .filter_by_attr(attr_name="invalid_xtr", remove_if=">", compare_to=0, name="remove_invalid_xtr")   
        return self

    def filter_samples(self, remove_no_realshow=False, remove_non_slide_sample=True):
        self.if_("app_name == 'snack'") \
            .clean_all("not target bucket") \
        .end_if_()


        self.if_("item_num < 8") \
            .clean_all("not_enough_photo") \
        .end_if_() \
        .if_("app_name == 'kwaipro' or app_name == 'kwaime' ") \
            .do_kwai_filter(remove_no_realshow, remove_non_slide_sample) \
        .end_if_() \
        .if_("app_name == 'snack'") \
            .do_snack_filter(remove_no_realshow, remove_non_slide_sample) \
        .end_if_()

        self.count_reco_result(save_count_to="filtered_item_num") \
            .if_("filtered_item_num < item_num") \
                .clean_all("lack_photo") \
            .end_if_() \
            .count_reco_result(save_count_to="item_num")
        return self

def read_reco_log_flow():
    read_reco_log = DataReaderFlow(name="read_reco_log") \
        .fetch_message(
            name="fetch_message",
            group_id="ksib_rerank_v5",
            kafka_topic="ksib_reco_joint_log",
            # hdfs_path="viewfs:/home/reco_log/rawdata/ksib_reco_joint_log/%Y-%m-%d/%H",
            hdfs_path="viewfs:/home/oversea/rawdata/kwaipro-reco/union_joint_reco_log/%Y/%m/%d/%H#2021-08-06 00#2022-08-31 00",
            #hdfs_path="viewfs:/home/reco/rawdata/app/kuaishou/kwai_v2_egy_joint_reco_log/history/%Y-%m-%d/%H/data",
            #hdfs_path="viewfs:/home/reco/rawdata/app/kuaishou/kwai_v2_egy_joint_reco_log/%Y-%m-%d/%H",
            hdfs_read_thread_num=4,
            local_path="joint_reco_log_20220418",
            output_attr="oversea_reco_log_str") \
        .parse_protobuf_from_string(
            name="parse_recolog_from_str",
            input_attr="oversea_reco_log_str",
            output_attr="oversea_reco_log",
            class_name="ksib::reco::FullRecoLog") \
        .enrich_with_protobuf(
            name="attr_from_reco_log",
            from_extra_var="oversea_reco_log",
            is_common_attr=True,
            attrs=[
                dict(path="reader", name="reader_info"),
                dict(path="bucket", name="bucket"),
                dict(path="llsid", name="llsid"),
                dict(path="time_ms", name="time_ms"),
                dict(path="time_ms", name="request_time"),
                # dict(path="request_info", name="request_info"),
                dict(path="request_page_type", name="request_page_type")
            ]) \
        .enrich_attr_by_lua(
            name="enrich_app_name",
            import_common_attr=["bucket"],
            export_common_attr=["app_name"],
            function_for_common="get_app_name_by_bucket",
            lua_script="""
                function get_app_name_by_bucket()
                    map_app_name = {}
                    map_app_name[8]="snack"
                    map_app_name[26]="snack"
                    map_app_name[6]="snack"
                    map_app_name[27]="snack"
                    map_app_name[40]="snack"
                    map_app_name[41]="snack"
                    map_app_name[11]="kwaipro"
                    map_app_name[18]="kwaipro"
                    map_app_name[9]="kwaipro"
                    map_app_name[29]="kwaime"
                    map_app_name[16]="kwaime"

                    return map_app_name[bucket] or 'invalid'
                end
            """) \
        .retrieve_from_oversea_reco_log(
            name="retr_from_reco_log",
            from_extra_var="oversea_reco_log",
            save_reco_photo_to="reco_photo_info",
            save_context_attrs=["comment_stay_time", dict({"from":"profile_stay_time_v2", "to":"profile_stay_time"})]) \
        .enrich_with_protobuf(
            name="attr_from_reco_photo",
            from_extra_var="reco_photo_info",
            is_common_attr=False,
            attrs=["photo_info", "context_info"]
            ) \
        .enrich_with_protobuf(
            name="attr_from_reader_info",
            from_extra_var="reader_info",
            is_common_attr=True,
            attrs=[
                dict(path="common", name="user_common"),
                dict(path="user_type", name="user_type"),
                dict(path="is_slide", name="is_slide_sample"),
            ]) \
        .enrich_with_protobuf(
            name="attr_from_user_common",
            from_extra_var="user_common",
            is_common_attr=True,
            attrs=["user_id", "device_id"]) \
        .enrich_with_protobuf(
            name='attr_from_user_type',
            from_extra_var="user_type",
            is_common_attr=True,
            attrs=[
                dict(path="is_first_day_device", name="is_firstday_device"),
                dict(path="is_new_user_v2", name="is_new_user"),
            ]) \
        .enrich_with_protobuf(
            name="attr_from_photo_info",
            from_extra_var="photo_info",
            is_common_attr=False,
            attrs=["photo_id", "upload_info",
                dict(path="primary_tag_id", name="primary_tag"),
                dict(path="second_tag_id", name="second_tag"),
                dict(path="mmu_info.cluster_id", name="mmu_cluster_id"),
                dict(path="bucket", name="photo_bucket")]) \
        .enrich_with_protobuf(
            name="attr_from_upload_info",
            from_extra_var="upload_info",
            is_common_attr=False,
            attrs=["upload_time_ms", "duration_ms", ]) \
        .enrich_with_protobuf(
            name="attr_from_context_info",
            from_extra_var="context_info",
            is_common_attr=False,
            attrs=[
                "click", "like", "follow", "forward", "comment",
                "distribute_cause", "exp_tag",
                "playing_time", "download", "profile_enter", "slide_enter",
                dict(path="real_show", name="realshow"),
                dict(path="feedback_negative", name="hate"),
                dict(path="predict_rate", name="predict_rate"),
                dict(path="slide_enter", name="is_slide_enter"),
                dict(path="real_show", name="is_realshow"),
            ] \
        .filter_by_attr(
            name="remove_force_insert_item",
            attr_name="distribute_cause",
            remove_if="!=",
            compare_to=1) \
        .filter_by_attr(
            name="remove_op_force_insert_item",
            attr_name="exp_tag",
            remove_if="==",
            compare_to="se145",
            skip=True) \
        .enrich_with_protobuf(
            name="attr_from_predict_rate",
            from_extra_var="predict_rate",
            is_common_attr=False,
            attrs=["ctr", "ltr", "ftr", "fpr", "evr"]) \
        .enrich_attr_by_lua(
            name="convert_double",
            import_item_attr=["playing_time", "duration_ms"],
            export_item_attr=["playing_time_double", "duration_ms_double"],
            function_for_item="convert",
            lua_script="""
            function convert()
                local playing_time_double = playing_time ~= nil and playing_time * 1.0 or nil
                local duration_ms_double = duration_ms ~= nil and duration_ms * 1.0 or nil
                return playing_time_double, duration_ms_double
            end
            """) \
        .count_reco_result(save_count_to="item_num")

    return read_reco_log


def filter_samples_flow(eval_model=False):
    filter_samples = DataReaderFlow(name="filter_samples") \
        .filter_samples(eval_model)
    return filter_samples

def run_main():
    runner = OfflineRunner("kwai_list_feature_pipeline")

    read_reco_log = read_reco_log_flow()
    filter_samples = filter_samples_flow(args.remove_no_realshow)
    debug_ignore_attr=["rr_ftr","emp_svr","rr_vtr","emp_ltr","fr_dtr","rr_evr","emp_dtr","fr_ltr","fr_ftr","rr_svr","fr_lvr","fr_evr","rr_ctr","fr_wtr","emp_ftr","emp_fpr","emp_lvr","emp_wtr","emp_evr","fr_ctr","fr_svr","rr_ltr","fr_fpr","rr_fpr","rr_lvr","emp_epr","emp_vtr","fr_vtr","fr_epr","rr_dtr","rr_epr","emp_ctr"]
    ignore_unsed_attr = ["llsid", "user_id", "device_id", "photo_id", "upload_time_ms", "time_ms", "common_signs", "common_slots", "list_slots", "list_signs", "realshow", "bucket", "duration", "request_time", 'photo_bucket', 'second_tag', 'primary_tag', 'is_firstday_device', 'is_new_user', 'is_slide_enter', 'is_realshow', 'mmu_cluster_id', 'item_keys', 'context_feature_pos', "no_realshow", "l2r_reward", "feature_pos",
                         "duration_ms_double", "playing_time_double", "rr_ftr_list","emp_plr_list","emp_ltr_list",
                         "rr_epr_list","emp_evr_list","rr_ltr_list","rr_dtr_list","emp_dtr_list","emp_ctr_list",
                         "emp_lvr_list","emp_fpr_list","rr_fpr_list","emp_svr_list","emp_epr_list","rr_lvr_list",
                         "emp_ftr_list","rr_svr_list","emp_wtr_list","emp_vtr_list","rr_evr_list","rr_vtr_list","rr_ctr_list",
                         "bucket_in", "bucket_pak", "bucket_br", "bucket_spa", "bucket_egy", "bucket_tur"
    ] 
    if args.run:
        runner.IGNORE_UNUSED_ATTR = ignore_unsed_attr
        runner.add_leaf_flows(leaf_flows=[read_reco_log, filter_samples])
        exe = runner.executor()
        i = 0
        while not exe["MESSAGE_END"] and i < 100:
            i += 1
            exe.reset()
            exe.run("read_reco_log")
            exe.run("filter_samples")

            print(f"\n********** sample {i} **************\n")
            
            for item in exe.items:
                print(item["duration_ms"])


if __name__ == '__main__':
    run_main()
