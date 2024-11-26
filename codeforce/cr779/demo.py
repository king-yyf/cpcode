.enrich_attr_by_lua(
    import_common_attr = ["topk_before_rerank", "topk_after_rerank", "topk_before_variant", "topk_after_variant","all_before_rerank", "all_after_rerank"],
    export_common_attr= ["origin_score"],
    function_for_common = "calc",
    lua_script = """
        function calc()
            local topk_hamming_dis = 0
            local all_hamming_dis = 
            local topk_intersect = 0
            local topk_before_rerank = topk_before_rerank or {}
            local topk_after_rerank = topk_after_rerank or {}
            local all_before_rerank = all_before_rerank or {}
            local all_after_rerank = all_after_rerank or {}
            local topk_before_variant = topk_before_variant or {}
            local topk_after_variant = topk_after_variant or {}
            local pos0=0
            local pos1=0
            local pos2=0
            local pos3=0
            local pos4=0
            local pos5=0
            local pos6=0
            local pos7=0
            n = #topk_before_rerank
            m = #all_before_rerank
        end
    """) \