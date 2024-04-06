import os
import os.path as op
import sys
import random
import string


def random_string(length):
    """
    生成指定长度的随机字符串
    
    :param length: 字符串长度
    :return: 生成字符串
    """
    characters = string.ascii_letters + string.digits
    return ''.join(random.choice(characters) for _ in range(length))


def generate_string_util_case(num: int):
    """ 生成string_util.cpp的测例 """
    with open(op.join(op.dirname(__file__), "string_util_case.txt"), "w") as f:
        for i in range(num):
            string_ori = random_string(10)
            string_lower = string_ori.lower()
            string_upper = string_ori.upper()
            f.write("{} {} {}\n".format(string_ori, string_lower, string_upper))


if __name__ == '__main__':
    generate_string_util_case(100)

