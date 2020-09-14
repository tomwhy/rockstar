import os
import argparse
import sys
import test
from typing import Tuple, Iterator

GREEN = u"\u001b[32m"
RED = u"\u001b[31m"
YELLOW = u"\u001b[33m"
RESET = u"\u001b[0m"


def get_tests(interpeter: str, path: str) -> Iterator[Tuple[str, test.Test]]:
    for entry in os.scandir(path):
        if not entry.is_dir():
            continue
        test_path = os.path.join(entry.path, "test.rock")
        output_path = os.path.join(entry.path, "output.txt")
        input_path = os.path.join(entry.path, "input.txt")

        yield (entry.name, test.Test(interpeter, test_path, output_path, input_path))


def main(args):
    for t in get_tests(args.Interpeter, args.Tests):
        print("[ ] Running {}".format(t[0]), end="")
        test_result, total_time = t[1].test()
        # clear the current line and return to the start of the line
        print(u"\u001b[2K", end="\r")
        if test_result.success:
            print("[{0}V{1}] Test {2}{3}{1} {0}succeeded{1}. test took: {4}".format(
                GREEN, RESET, YELLOW, t[0], total_time))
        else:
            print("[{0}X{1}] Test {2}{3}{1} {0}falied{1} with the following error:\n{4}".format(
                RED, RESET, YELLOW, t[0], test_result.msg))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "Interpeter", help="The path to the rockstar interpeter")
    parser.add_argument("Tests", help="""The path to the folder containing the tests. 
        each test is a folder containing three files:
            test.rock - the acutal test file
            output.txt - the expected output from test.rock
            input.txt - this file is optional and it contains the input from stdin for test.rock
        the name of the test is the name of the directory""")

    main(parser.parse_args(sys.argv[1:]))
