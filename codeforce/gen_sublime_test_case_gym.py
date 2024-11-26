import sys
import os
import shutil
path = "/Users/yangyf/Desktop/cpcode/codeforce/cf/gym/"

def main(contest_id):
    """
    从 cf-tool 生成便于 sublime text 使用的 test样例和文件
    :param contest_id: cf contest id exm: 1825
    :return: void
    """
    file_path = path + contest_id + '/' # xx/contest/1825
    problem_sets = os.listdir(file_path) # ['d1', 'a', 'd2', 'c', 'e', 'b']
    # 将每个问题的cpp 模板移动到相同父目录 contest/1825/a.cpp ...
    for problem in problem_sets:
        cpp_file = file_path + problem + '/' + problem + '.cpp'
        dst_file = file_path + problem + '.cpp'
        if not os.path.isfile(cpp_file):
            print(f"{problem}.cpp not exist!")
        else:
            shutil.move(cpp_file, dst_file)
        test_cases = []
        test_case_ls = os.listdir(file_path + problem)
        for case_num in range(len(test_case_ls) // 2):
            test_case = dict()
            try:
                with open(file_path + problem + '/testO' + str(case_num + 1) + '.txt', "r") as f:
                    s = str(f.read())
                    if s[-1] == '\n':
                        s = s[:-1]
                    test_case["correct_answers"] = [s]
            except FileNotFoundError:
                print(f"{problem}.{case_num} answer file not exist!")
            try:
                with open(file_path + problem + '/testI' + str(case_num + 1) + ".txt", "r") as f:
                    test_case["test"] = f.read()
            except FileNotFoundError:
                print(f"{problem}.{case_num} input file not exist!")
            test_cases.append(test_case)

        with open(dst_file + ":tests", 'w', encoding="utf-8") as outf:
            outf.write("[\n")
            for i, test_case in enumerate(test_cases):
                s = str(test_case)
                outf.write(s.replace("\'", "\""))
                if i != len(test_cases) - 1:
                    outf.write(",\n")
            outf.write("\n]")
        shutil.rmtree(file_path + problem)  # 删除目录 ['d1', 'a', 'd2', 'c', 'e', 'b']

if __name__ == "__main__":
    main(sys.argv[1])
